#include "Entity.hpp"

#include "Natives.hpp"
#include "core/util/Joaat.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "game/pointers/Pointers.hpp"
#include "types/rage/tlsContext.hpp"
#include "types/entity/CDynamicEntity.hpp"
#include "types/network/netObject.hpp"
#include "types/network/CNetworkPlayerMgr.hpp"
#include "game/gta/Scripts.hpp"
#include "types/ped/CPedFactory.hpp"
#include "types/network/netObjectMgrBase.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Packet.hpp"

namespace
{
	int GetNextTokenValue(int prev_token)
	{
		for (int i = 0; i < 0x1F; i++)
		{
			if ((i << 27) - (prev_token << 27) > 0)
				return i;
		}

		return 0;
	}
}

namespace YimMenu
{
	void Entity::PopulatePointer()
	{
		m_Pointer = Pointers.HandleToPtr(m_Handle);
	}

	void Entity::PopulateHandle()
	{
		if (m_Pointer)
			m_Handle = Pointers.PtrToHandle(m_Pointer);
	}

	void Entity::AssertValid(std::string_view function_name)
	{
		if (!IsValid())
		{
			LOG(WARNING) << "IsValid() assertion failed for " << function_name;
		}
	}

	void Entity::AssertControl(std::string_view function_name)
	{
		if (!IsValid())
			return;

		if (!HasControl())
		{
			LOG(WARNING) << "HasControl() assertion failed for " << function_name;
		}
	}

	void Entity::AssertScriptContext(std::string_view function_name)
	{
		if (!rage::tlsContext::Get()->m_ScriptThreadActive)
		{
			LOG(WARNING) << "Script thread not active for " << function_name;
		}
	}

	bool Entity::IsValid()
	{
		if (m_Handle)
		{
			return ENTITY::DOES_ENTITY_EXIST(m_Handle);
		}
		else if (m_Pointer)
		{
			return true; // TODO: potential use after free
		}

		return false;
	}

	bool Entity::IsPed()
	{
		ENTITY_ASSERT_VALID();

		if (auto ptr = GetPointer<rage::fwEntity*>())
			return ptr->IsPed();
		return false;
	}

	bool Entity::IsVehicle()
	{
		ENTITY_ASSERT_VALID();

		if (auto ptr = GetPointer<rage::fwEntity*>())
			return ptr->IsVehicle();
		return false;
	}

	bool Entity::IsObject()
	{
		ENTITY_ASSERT_VALID();

		if (auto ptr = GetPointer<rage::fwEntity*>())
			return ptr->IsObject();
		return false;
	}

	bool Entity::IsPlayer()
	{
		ENTITY_ASSERT_VALID();
		return PED::IS_PED_A_PLAYER(GetHandle());
	}


	bool Entity::IsMissionEntity()
	{
		ENTITY_ASSERT_VALID();
		return ENTITY::IS_ENTITY_A_MISSION_ENTITY(GetHandle()); // TODO: detect more mission states
	}

	Hash Entity::GetModel()
	{
		ENTITY_ASSERT_VALID();
		return ENTITY::GET_ENTITY_MODEL(GetHandle());
	}

	rage::fvector3 Entity::GetPosition()
	{
		ENTITY_ASSERT_VALID();
		if (!m_Handle && m_Pointer)
			return *reinterpret_cast<rage::fvector3*>(&GetPointer<rage::fwEntity*>()->m_Transform.rows[3]);
		return ENTITY::GET_ENTITY_COORDS(GetHandle(), false);
	}

	void Entity::SetPosition(rage::fvector3 position)
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();
		ENTITY_ASSERT_SCRIPT_CONTEXT();
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(GetHandle(), position.x, position.y, position.z, true, true, true);
	}

	rage::fvector3 Entity::GetRotation(int order)
	{
		ENTITY_ASSERT_VALID();
		return ENTITY::GET_ENTITY_ROTATION(GetHandle(), order);
	}

	void Entity::SetRotation(rage::fvector3 rotation, int order)
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();
		ENTITY::SET_ENTITY_ROTATION(GetHandle(), rotation.x, rotation.y, rotation.z, order, false);
	}

	rage::fvector3 Entity::GetVelocity()
	{
		ENTITY_ASSERT_VALID();
		return ENTITY::GET_ENTITY_VELOCITY(GetHandle());
	}

	void Entity::SetVelocity(rage::fvector3 vel)
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();
		ENTITY::SET_ENTITY_VELOCITY(GetHandle(), vel.x, vel.y, vel.z);
	}

	float Entity::GetHeading()
	{
		ENTITY_ASSERT_VALID();
		return ENTITY::GET_ENTITY_HEADING(GetHandle());
	}

	void Entity::SetHeading(float heading)
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();
		ENTITY::SET_ENTITY_HEADING(GetHandle(), heading);
	}

	float Entity::GetSpeed()
	{
		ENTITY_ASSERT_VALID();
		return ENTITY::GET_ENTITY_SPEED(GetHandle());
	}

	void Entity::SetCollision(bool enabled)
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();
		ENTITY::SET_ENTITY_COLLISION(GetHandle(), enabled, true);
	}

	void Entity::SetFrozen(bool enabled)
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();
		ENTITY::FREEZE_ENTITY_POSITION(GetHandle(), enabled);
	}

	void Entity::Delete()
	{
		ENTITY_ASSERT_VALID();

		if (!IsValid())
			return;

		if (IsNetworked())
		{
			auto net = GetPointer<CDynamicEntity*>()->m_NetObject;
			DeleteNetwork(net);
		}
		else
		{
			// TODO: call delete functions directly
			if (!ENTITY::IS_ENTITY_A_MISSION_ENTITY(GetHandle()))
				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(GetHandle(), true, true);
			auto hnd = GetHandle();
			ENTITY::DELETE_ENTITY(&hnd);
		}
	}

	void Entity::DeleteNetwork(std::uint16_t network_id, std::uint32_t ownership_token, bool local, Player* for_player)
	{
		char buf[0x200]{};
		rage::datBitBuffer remove_buf(buf, sizeof(buf));
		int msgs_written = 0;

		if (ownership_token == -1)
		{
			remove_buf.Write<std::uint16_t>(network_id, 13);
			remove_buf.Write<int>(GetNextTokenValue(ownership_token), 5);
			msgs_written++;
		}
		else
		{
			// try all tokens if we don't know it
			for (int i = 0; i < 0x1F; i++)
			{
				remove_buf.Write<std::uint16_t>(network_id, 13);
				remove_buf.Write<int>(i, 5);
				msgs_written++;
			}
		}

		Packet pack;
		pack.WriteMessageHeader(rage::netMessage::Type::PackedReliables);
		pack.GetBuffer().Write<int>(4, 4); // remove
		pack.GetBuffer().Write(msgs_written, 5);
		pack.GetBuffer().Write(remove_buf.m_BitsRead, 13);
		pack.GetBuffer().WriteArray(buf, remove_buf.m_BitsRead);

		if (for_player)
		{
			if (for_player->IsValid())
				pack.Send(for_player->GetMessageId());
		}
		else
		{
			for (int i = 0; i < 32; i++)
				if (auto player = (*Pointers.NetworkPlayerMgr)->m_Players[i]; player && player->IsPhysical() && !player->IsLocal())
					pack.Send(player->m_MessageId);
		}

		if (local)
			if (auto object = Pointers.GetNetObjectById(network_id))
				(*Pointers.NetworkObjectMgr)->UnregisterNetworkObject(object, 8, true, true);
	}

	void Entity::DeleteNetwork(rage::netObject* object, bool local, Player* for_player)
	{
		DeleteNetwork(object->m_ObjectId, object->m_OwnershipToken, local, for_player);
	}

	bool Entity::IsNetworked()
	{
		return GetNetworkObject() != nullptr;
	}

	bool Entity::IsRemote()
	{
		if (!IsNetworked())
			return false;

		return GetNetworkObject()->m_IsRemote;
	}

	rage::netObject* Entity::GetNetworkObject()
	{
		if (!IsValid())
			return nullptr;

		return GetPointer<CDynamicEntity*>()->m_NetObject;
	}

	int Entity::GetOwner()
	{
		if (!IsNetworked())
			return -1;

		return GetNetworkObject()->m_OwnerId;
	}

	std::uint16_t Entity::GetNetworkObjectId()
	{
		ENTITY_ASSERT_VALID();
		if (!IsNetworked())
			return 0;

		return GetNetworkObject()->m_ObjectId;
	}

	void Entity::PreventMigration()
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();

		if (!*Pointers.IsSessionStarted)
			return;

		if (!IsNetworked() || !NETWORK::NETWORK_HAS_ENTITY_BEEN_REGISTERED_WITH_THIS_THREAD(GetHandle()))
		{
#ifdef ENTITY_DEBUG
			LOGF(WARNING, "PreventMigration(): entity is not networked!");
#endif
			return;
		}

		NETWORK::NETWORK_DISABLE_PROXIMITY_MIGRATION(NETWORK::PED_TO_NET(GetHandle()));
	}

	void Entity::ForceControl()
	{
		ENTITY_ASSERT_VALID();

		if (!IsNetworked() || HasControl())
			return;

		(*Pointers.NetworkObjectMgr)->ChangeOwner(GetNetworkObject(), Self::GetPlayer().GetHandle(), 0);
	}

	bool Entity::RequestControl(int timeout)
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_SCRIPT_CONTEXT();

		if (!IsNetworked() || HasControl())
			return true;

		for (int i = 0; i < (timeout + 1); i++)
		{
			if (!IsValid() || !*Pointers.IsSessionStarted)
				return false;

			if (HasControl())
				return true;

			Pointers.RequestControl(GetNetworkObject());
			if (timeout)
				ScriptMgr::Yield();
		}

		return HasControl();
	}

	void Entity::ForceSync(Player* for_player)
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();
		ENTITY_ASSERT_SCRIPT_CONTEXT();

		if (!IsNetworked())
			return;

		char data[0x400];
		auto net = GetNetworkObject();
		for (int i = 0; i < 32; i++)
		{
			if ((*Pointers.NetworkPlayerMgr)->m_Players[i]
			    && (*Pointers.NetworkPlayerMgr)->m_Players[i] != (*Pointers.NetworkPlayerMgr)->m_LocalPlayer
			    && (!for_player || !for_player->IsValid() || for_player->GetId() == i))
			{
				rage::datBitBuffer buffer(data, sizeof(data));
				(*Pointers.NetworkObjectMgr)->PackCloneCreate(net, (*Pointers.NetworkPlayerMgr)->m_Players[i], &buffer);
			}
		}
	}

	bool Entity::HasControl()
	{
		return NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(GetHandle());
	}

	bool Entity::IsInvincible()
	{
		// TODO this is bad!
		ENTITY_ASSERT_VALID();
		return !ENTITY::GET_ENTITY_CAN_BE_DAMAGED(GetHandle());
	}

	void Entity::SetInvincible(bool status)
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();
		ENTITY::SET_ENTITY_INVINCIBLE(GetHandle(), status, true);
	}

	bool Entity::IsDead()
	{
		ENTITY_ASSERT_VALID();
		return ENTITY::IS_ENTITY_DEAD(GetHandle(), true);
	}

	void Entity::Kill()
	{
		ENTITY_ASSERT_VALID();

		if (HasControl())
		{
			ENTITY::SET_ENTITY_HEALTH(GetHandle(), 0, PLAYER::PLAYER_PED_ID(), 0);
		}
		else
		{
			auto ptr = GetPointer<CEntity*>();
			auto local = reinterpret_cast<CEntity*>((*Pointers.PedFactory)->m_LocalPed);
			auto pos = GetPosition();
			std::uint32_t weapon = "WEAPON_EXPLOSION"_J;

			if (!ptr || !local)
				return;

			Pointers.TriggerWeaponDamageEvent(local, ptr, &pos, 0, true, weapon, 9999.9f, 2, 0, (1 << 4) | 0x80000, 0, 0, 0, false, false, true, true, nullptr);
		}
	}

	int Entity::GetHealth()
	{
		ENTITY_ASSERT_VALID();
		return ENTITY::GET_ENTITY_HEALTH(GetHandle());
	}

	void Entity::SetHealth(int health)
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();
		ENTITY::SET_ENTITY_HEALTH(GetHandle(), health, 0, 0);
	}

	int Entity::GetMaxHealth()
	{
		ENTITY_ASSERT_VALID();
		return ENTITY::GET_ENTITY_MAX_HEALTH(GetHandle());
	}

	bool Entity::IsVisible()
	{
		ENTITY_ASSERT_VALID();
		return ENTITY::IS_ENTITY_VISIBLE(GetHandle());
	}

	void Entity::SetVisible(bool status)
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();
		ENTITY::SET_ENTITY_VISIBLE(GetHandle(), status, true);
	}

	int Entity::GetAlpha()
	{
		ENTITY_ASSERT_VALID();
		return ENTITY::GET_ENTITY_ALPHA(GetHandle());
	}

	void Entity::SetAlpha(int alpha)
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL(); // doesn't matter anyway because alpha changes are not networked
		ENTITY::SET_ENTITY_ALPHA(GetHandle(), alpha, false);
	}

	void Entity::ResetAlpha()
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL(); // doesn't matter anyway because alpha changes are not networked
		ENTITY::RESET_ENTITY_ALPHA(GetHandle());
	}

	bool Entity::HasInterior()
	{
		ENTITY_ASSERT_VALID();
		return INTERIOR::GET_INTERIOR_FROM_ENTITY(GetHandle()) != 0;
	}

	void Entity::Explode(ExplosionType explosion, float damage, bool is_visible, bool is_audible, float camera_shake)
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_SCRIPT_CONTEXT();

		if (!IsValid())
			return;

		auto pos = GetPosition();
		Scripts::RunWithSpoofedThreadName("am_mp_orbital_cannon"_J, [&] {
			// add_owned_explosion is more or less useless now
			FIRE::ADD_EXPLOSION(pos.x, pos.y, pos.z, static_cast<int>(explosion), damage, is_audible, !is_visible, camera_shake, damage == 0.0f);
		});
	}

	bool Entity::operator==(const Entity& other)
	{
		if (m_Handle != 0 && other.m_Handle != 0)
			return m_Handle == other.m_Handle;

		if (m_Pointer != nullptr && other.m_Pointer != nullptr)
			return m_Pointer == other.m_Pointer;

		if (other.m_Pointer != nullptr)
			if (auto ptr = GetPointer<void*>())
				return ptr == other.m_Pointer;

		if (other.m_Handle != 0)
			if (auto handle = GetHandle(); handle != 0)
				return handle == other.m_Handle;

		return false;
	}
}
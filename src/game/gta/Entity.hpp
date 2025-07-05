#pragma once
#include "types/rage/vector.hpp"
#include "types/script/types.hpp"

#define ENTITY_DEBUG

// TODO: debug stuff
#ifdef ENTITY_DEBUG
	#define ENTITY_ASSERT_VALID() AssertValid(__FUNCTION__);
	#define ENTITY_ASSERT_CONTROL() AssertControl(__FUNCTION__);
	#define ENTITY_ASSERT_SCRIPT_CONTEXT() AssertScriptContext(__FUNCTION__);
#else
	#define ENTITY_ASSERT_VALID()
	#define ENTITY_ASSERT_CONTROL()
	#define ENTITY_ASSERT_SCRIPT_CONTEXT()
#endif

enum class ExplosionType;

namespace rage
{
	class netObject;
}

namespace YimMenu
{
	class Player;
	class Entity
	{
		void* m_Pointer;
		int m_Handle;

		void PopulatePointer();
		void PopulateHandle();

	public:
		// debug
		void AssertValid(std::string_view function_name);
		void AssertControl(std::string_view function_name);
		static void AssertScriptContext(std::string_view function_name);

		constexpr Entity(void* pointer) :
		    m_Pointer(pointer),
		    m_Handle(0)
		{
		}

		constexpr Entity(int handle) :
		    m_Pointer(nullptr),
		    m_Handle(handle)
		{
		}

		constexpr Entity(void* pointer, int handle) :
		    m_Pointer(pointer),
		    m_Handle(handle)
		{
		}

		// raw data
		template<typename T>
		constexpr T GetPointer()
		{
			if (!m_Pointer)
				PopulatePointer();
			return (T)m_Pointer;
		}

		constexpr int GetHandle()
		{
			if (m_Handle == 0)
				PopulateHandle();
			return m_Handle;
		}

		template<typename T>
		constexpr T As()
		{
			return T(this->m_Pointer, this->m_Handle);
		}

		bool IsValid();
		inline operator bool()
		{
			return IsValid();
		}
		inline operator int() = delete;

		bool IsPed();
		bool IsVehicle();
		bool IsObject();
		bool IsPlayer();
		bool IsMissionEntity();

		// info
		Hash GetModel();

		// position
		rage::fvector3 GetPosition();
		void SetPosition(rage::fvector3 position);
		rage::fvector3 GetRotation(int order = 2);
		void SetRotation(rage::fvector3 rotation, int order = 2);
		rage::fvector3 GetVelocity();
		void SetVelocity(rage::fvector3 velocity);
		float GetHeading();
		void SetHeading(float heading);
		float GetSpeed();

		// physical
		void SetCollision(bool enabled);
		void SetFrozen(bool enabled);
		void Delete();
		static void DeleteNetwork(std::uint16_t network_id, std::uint32_t ownership_token = -1, bool local = true, Player* for_player = nullptr);
		static void DeleteNetwork(rage::netObject* object, bool local = true, Player* for_player = nullptr);

		// networking
		bool IsNetworked();
		bool IsRemote();
		bool HasControl();
		rage::netObject* GetNetworkObject();

		int GetOwner(); // index because we want to avoid cyclic imports
		std::uint16_t GetNetworkObjectId();

		void PreventMigration();

		/// <summary>
		/// WARNING: This function is potentially unstable when used on vehicles. Use RequestControl instead.
		/// Seems to cause crashes when spammed
		/// </summary>
		void ForceControl();

		/// <summary>
		/// Tries to request control of the entity
		/// </summary>
		/// <param name="timeout">In ticks. If zero, the function doesn't block</param>
		/// <returns>True if we managed to grab control</returns>
		bool RequestControl(int timeout = 100);
		/// <summary>
		/// Forces creation of a networked entity for a specified player or the entire session
		/// </summary>
		void ForceSync(Player* for_player = nullptr); // pointer because we want to avoid cyclic imports

		// health
		bool IsInvincible();
		void SetInvincible(bool status);
		bool IsDead();
		void Kill();
		int GetHealth();
		void SetHealth(int health);
		int GetMaxHealth();

		// visibility
		bool IsVisible();
		void SetVisible(bool status);
		int GetAlpha();
		void SetAlpha(int alpha);
		void ResetAlpha();

		bool HasInterior();

		// explosions
		void Explode(ExplosionType explosion, float damage = 1.0f, bool is_visible = true, bool is_audible = true, float camera_shake = 1.0f);

		bool operator==(const Entity& other);
		bool operator!=(const Entity& other)
		{
			return !this->operator==(other);
		}
	};
}
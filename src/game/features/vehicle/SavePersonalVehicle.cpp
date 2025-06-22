#include "SavePersonalVehicle.hpp"
#include "core/commands/Command.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Scripts.hpp"
#include "game/gta/ScriptFunction.hpp"
#include "game/gta/ScriptLocal.hpp"
#include "game/pointers/Pointers.hpp"
#include "types/script/locals/VehicleRewardData.hpp"
#include "types/script/globals/FreemodeGeneral.hpp"

namespace YimMenu::Features
{
	void SavePersonalVehicle::RunScriptImpl()
	{
		while (g_Running)
		{
			ScriptMgr::Yield();

			if (!m_ShouldRunScript)
				continue;

			if (!*Pointers.IsSessionStarted || !Self::GetVehicle().IsValid()) // if transition happens or player gets out of vehicle, cleanup immediately
			{
				if (m_StartedByUs && m_Thread)
				{
					m_Thread->m_Context.m_State = rage::scrThread::State::KILLED;
					m_StartedByUs = false;
				}
				m_Thread = nullptr;
				m_ShouldRunScript = false;
				continue;
			}

			if (!m_Thread)
			{
				if (Scripts::IsScriptActive("AM_MP_VEHICLE_REWARD"_J)) // This script already runs in freemode, so check if it is active first
				{
					m_Thread = Scripts::FindScriptThread("AM_MP_VEHICLE_REWARD"_J);
				}
				else // if not (e.g., we are in a mission), start and pause it
				{
					int id = Scripts::StartScript("AM_MP_VEHICLE_REWARD"_J, eStackSizes::FRIEND);
					m_Thread = Scripts::FindScriptThreadByID(id);
					if (m_Thread)
					{
						m_Thread->m_Context.m_State = rage::scrThread::State::PAUSED;
						m_StartedByUs = true; // mark so we only kill it if started by us
					}
				}
			}

			if (!m_Thread) // if still invalid, exit early
			{
				m_ShouldRunScript = false;
				continue;
			}

			if (auto VehicleRewardData = VEHICLE_REWARD_DATA::Get(m_Thread))
			{
				auto VehicleMenuData = ScriptLocal(m_Thread, 176).As<int*>(); // TO-DO: add struct for this?
				static ScriptFunction giveVehicleReward("AM_MP_VEHICLE_REWARD"_J, ScriptPointer("GiveVehicleReward", "2D 0C 1E 00 00"));
				if (giveVehicleReward.Call<bool>(Self::GetVehicle().GetHandle(), VehicleMenuData, &VehicleRewardData->TransactionStatus, &VehicleRewardData->Garage, &VehicleRewardData->GarageOffset, &VehicleRewardData->ControlStatus, false, true, true, false, 0, -1))
				{
					if (VehicleRewardData->ControlStatus != 3) // success (player either saved the vehicle or exited the menu)
					{
						VehicleRewardData->TransactionStatus = 0;
						VehicleRewardData->Garage = 0;
						VehicleRewardData->GarageOffset = 0;
						VehicleRewardData->ControlStatus = 0;
						if (m_StartedByUs)
						{
							m_Thread->m_Context.m_State = rage::scrThread::State::KILLED;
							m_StartedByUs = false;
						}
						m_Thread = nullptr;
						m_ShouldRunScript = false;
					}
				}
			}
		}
	}

	// Some vehicles cannot be safely acquired using this method, see #443
	static const std::unordered_set<std::uint32_t> s_BlacklistedVehicles = {"rcbandito"_J, "minitank"_J, "thruster"_J, "terbyte"_J, "avenger"_J, "policet3"_J, "brickade2"_J};

	class _SavePersonalVehicle : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
			{
				Notifications::Show("Save Personal Vehicle", "Please join GTA Online.", NotificationType::Error);
				return;
			}

			if (!Self::GetVehicle().IsValid())
			{
				Notifications::Show("Save Personal Vehicle", "Please get in a vehicle.", NotificationType::Error);
				return;
			}

			static ScriptFunction isVehicleValidForPV("freemode"_J, ScriptPointer("IsVehicleValidForPV", "5D ? ? ? 2A 06 56 13 00 38 00").Add(1).Rip());
			if (s_BlacklistedVehicles.contains(Self::GetVehicle().GetModel()) || !isVehicleValidForPV.Call<bool>(Self::GetVehicle().GetModel()))
			{
				Notifications::Show("Save Personal Vehicle", "This vehicle cannot be saved as a personal vehicle.", NotificationType::Error);
				return;
			}

			if (Self::GetVehicle().GetHandle() == FreemodeGeneral::Get()->PersonalVehicleIndex)
			{
				Notifications::Show("Save Personal Vehicle", "This vehicle is already a personal vehicle.", NotificationType::Error);
				return;
			}

			SavePersonalVehicle::SetShouldRunScript(true);
		}
	};

	static _SavePersonalVehicle __SavePersonalVehicle{"savepersonalvehicle", "Save Personal Vehicle", "Saves the current vehicle you are in as your personal vehicle."};
}
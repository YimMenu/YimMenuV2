#include "SavePersonalVehicle.hpp"
#include "core/commands/Command.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "game/backend/Self.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/gta/data/StackSizes.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/Scripts.hpp"
#include "game/gta/ScriptFunction.hpp"
#include "game/gta/ScriptLocal.hpp"
#include "types/script/locals/VehicleRewardData.hpp"

namespace YimMenu::Features
{
	void SavePersonalVehicle::RunScriptImpl()
	{
		while (g_Running)
		{
			ScriptMgr::Yield();

			if (!m_ShouldRunScript)
				continue;

			if (!*Pointers.IsSessionStarted || !Self::GetVehicle().IsValid())
			{
				if (m_StartedByUs && m_Thread)
				{
					m_Thread->m_Context.m_State = rage::scrThread::State::KILLED;
					m_StartedByUs               = false;
				}
				m_Thread = nullptr;
				m_ShouldRunScript = false;
				continue;
			}

			if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH("AM_MP_VEHICLE_REWARD"_J) == 0)
			{
				SCRIPT::REQUEST_SCRIPT_WITH_NAME_HASH("AM_MP_VEHICLE_REWARD"_J);
				if (SCRIPT::HAS_SCRIPT_WITH_NAME_HASH_LOADED("AM_MP_VEHICLE_REWARD"_J))
				{
					int id   = BUILTIN::START_NEW_SCRIPT_WITH_NAME_HASH("AM_MP_VEHICLE_REWARD"_J, eStackSizes::FRIEND);
					m_Thread = Scripts::FindScriptThreadByID(id);
					if (m_Thread)
						m_Thread->m_Context.m_State = rage::scrThread::State::PAUSED;
					SCRIPT::SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED("AM_MP_VEHICLE_REWARD"_J);
					m_StartedByUs = true;
				}
				else
				{
					continue;
				}
			}
			else
			{
				m_Thread = Scripts::FindScriptThread("AM_MP_VEHICLE_REWARD"_J);
			}

			if (!m_Thread)
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
					if (VehicleRewardData->ControlStatus != 3)
					{
						VehicleRewardData->TransactionStatus = 0;
						VehicleRewardData->Garage            = 0;
						VehicleRewardData->GarageOffset      = 0;
						VehicleRewardData->ControlStatus     = 0;
						if (m_StartedByUs)
						{
							m_Thread->m_Context.m_State = rage::scrThread::State::KILLED;
							m_StartedByUs               = false;
						}
						m_Thread          = nullptr;
						m_ShouldRunScript = false;
					}
				}
			}
		}
	}

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
			if (!isVehicleValidForPV.Call<bool>(Self::GetVehicle().GetModel()))
			{
				Notifications::Show("Save Personal Vehicle", "This vehicle cannot be saved as a personal vehicle.", NotificationType::Error);
				return;
			}

			SavePersonalVehicle::SetShouldRunScript(true);
		}
	};

	static _SavePersonalVehicle __SavePersonalVehicle{"savepersonalvehicle", "Save Personal Vehicle", "Saves the current vehicle you are in as your personal vehicle."};
}
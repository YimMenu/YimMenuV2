#include "GiveVehicleReward.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/ScriptFunction.hpp"
#include "game/gta/ScriptLocal.hpp"
#include "types/script/locals/VehicleRewardData.hpp"

namespace YimMenu
{
	static ScriptFunction giveVehicleReward("GVR", "AM_MP_VEHICLE_REWARD"_J, "2D 0C 1E 00 00");

	bool GiveVehicleReward::IsSafeToRunScript()
	{
		return Self::GetVehicle().IsValid() && *Pointers.IsSessionStarted && SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH("AM_MP_VEHICLE_REWARD"_J) > 0;
	}

	void GiveVehicleReward::RunScriptImpl()
	{
		while (g_Running)
		{
			if (m_ShouldRunScript)
			{
				if (IsSafeToRunScript())
				{
					if (auto thread = Scripts::FindScriptThread("AM_MP_VEHICLE_REWARD"_J))
					{
						if (auto VehicleRewardData = VEHICLE_REWARD_DATA::Get(thread))
						{
							auto VehicleMenuData = ScriptLocal(thread, 176).As<PINT>(); // TO-DO: add struct for this?
							if (giveVehicleReward.Call<bool>(Self::GetVehicle().GetHandle(), VehicleMenuData, &VehicleRewardData->TransactionStatus, &VehicleRewardData->Garage, &VehicleRewardData->GarageOffset, &VehicleRewardData->ControlStatus, false, true, true, false, 0, -1))
							{
								if (VehicleRewardData->ControlStatus != 3)
								{
									VehicleRewardData->TransactionStatus = 0;
									VehicleRewardData->Garage            = 0;
									VehicleRewardData->GarageOffset      = 0;
									VehicleRewardData->ControlStatus     = 0;
									m_ShouldRunScript                    = false;
								}
							}
						}
					}
				}
				else
				{
					m_ShouldRunScript = false;
				}
			}

			ScriptMgr::Yield();
		}
	}
}
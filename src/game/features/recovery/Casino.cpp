#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/ScriptLocal.hpp"
#include "game/gta/Stats.hpp"
#include "core/commands/ListCommand.hpp"
#include "game/backend/Tunables.hpp"
#include "core/backend/ScriptMgr.hpp"

#include <set>


namespace YimMenu::Features
{
	class CasinoManipulateRigSlotMachines : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		int slots_random_results_table = 1350;
		std::set<int> slots_blacklist = {9, 21, 22, 87, 152};
		int spin_state_var = 1668;
		std::set<int> spin_state_whitelist = {8, 14};

		virtual void OnTick() override
		{
			if (Scripts::SafeToModifyFreemodeBroadcastGlobals() && SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH("casino_slots"_J))
			{
				Player casinoSlotsScriptHostPlayer = NETWORK::NETWORK_GET_HOST_OF_SCRIPT("casino_slots", -1, 0);
				auto casinoSlotsScriptHostPlayerId = casinoSlotsScriptHostPlayer.GetId();
				auto selfPlayerId = Self::GetPlayer().GetId();
				if (casinoSlotsScriptHostPlayerId != selfPlayerId)
				{
					Scripts::ForceScriptHost(Scripts::FindScriptThread("casino_slots"_J));
				}
				int* spin_state = ScriptLocal("casino_slots"_J, spin_state_var).As<int*>();


				bool needs_run = false;
				for (int slots_iter = 3; slots_iter <= 196; ++slots_iter)
				{
					if (!slots_blacklist.contains(slots_iter))
					{
						if (*ScriptLocal("casino_slots"_J, slots_random_results_table + slots_iter).As<int*>() != 6)
						{
							needs_run = true;
							break;
						}
					}
				}
				if (needs_run)
				{
					for (int slots_iter = 3; slots_iter <= 196; ++slots_iter)
					{
						if (!slots_blacklist.contains(slots_iter) && spin_state_whitelist.contains(*spin_state))
						{
							int slot_result = 6;
							*ScriptLocal("casino_slots"_J, slots_random_results_table + slots_iter).As<int*>() = slot_result;
						}
					}
				}
			}
		}

virtual void OnDisable() override
		{
			if (Scripts::SafeToModifyFreemodeBroadcastGlobals() && SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH("casino_slots"_J))
			{
				Player casinoSlotsScriptHostPlayer = NETWORK::NETWORK_GET_HOST_OF_SCRIPT("casino_slots", -1, 0);
				auto casinoSlotsScriptHostPlayerId = casinoSlotsScriptHostPlayer.GetId();
				auto selfPlayerId = Self::GetPlayer().GetId();
				if (casinoSlotsScriptHostPlayerId != selfPlayerId)
				{
					Scripts::ForceScriptHost(Scripts::FindScriptThread("casino_slots"_J));
				}

				int* spin_state = ScriptLocal("casino_slots"_J, spin_state_var).As<int*>();
				// waiting for reset until next time using
				while (!spin_state_whitelist.contains(*spin_state))
				{
					ScriptMgr::Yield();
					spin_state = ScriptLocal("casino_slots"_J, spin_state_var).As<int*>();
					if (spin_state == nullptr){
						return;
					}
				}

				for (int slots_iter = 3; slots_iter <= 196; ++slots_iter)
				{
					if (!slots_blacklist.contains(slots_iter))
					{
						int slot_result = 6;
						std::srand(static_cast<unsigned int>(std::time(0)) + slots_iter);
						slot_result = 3 + std ::rand() % 7; // Generates a pseudo random number [3,9] 
						*ScriptLocal("casino_slots"_J, slots_random_results_table + slots_iter).As<int*>() = slot_result;
					}
				}
			}
		}
	};

	static CasinoManipulateRigSlotMachines _CasinoManipulateRigSlotMachines{"casinomanipulaterigslotmachines", "Manipulate Rig Slot Machines", "Lets you win the Rig Slot Machines every time"};
}

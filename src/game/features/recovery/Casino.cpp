#include <random>
#include <set>
#include "game/gta/Natives.hpp"
#include "core/commands/BoolCommand.hpp"
#include "game/gta/ScriptLocal.hpp"




namespace YimMenu::Features
{
	class Casino : public BoolCommand
	{
		using BoolCommand::BoolCommand;

        int slots_random_results_table = 1348;
        std::set<int> slots_blacklist = {9, 21, 22, 87, 152};

		virtual void OnEnable() override
		{
            bool needs_run = false;
            if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH("casino_slots"_J)) {
                for (int slots_iter = 3; slots_iter <= 196; ++slots_iter) {
                    if (!slots_blacklist.contains(slots_iter)) {
                        if (*ScriptLocal("casino_slots"_J, slots_random_results_table + slots_iter).As<int*>() != 6) {
                            needs_run = true;
                        }
                    }
                }
                if (needs_run) {
                    for (int slots_iter = 3; slots_iter <= 196; ++slots_iter) {
                        if (!slots_blacklist.contains(slots_iter)) {
                            int slot_result = 6;
                            *ScriptLocal("casino_slots"_J, slots_random_results_table + slots_iter).As<int*>() = slot_result;
                        }
                    }
                }
            }
		}

        virtual void OnDisable() override
        {
            if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH("casino_slots"_J))
            {
                for (int slots_iter = 3; slots_iter <= 196; ++slots_iter) {
                    if (!slots_blacklist.contains(slots_iter)) {
                        int slot_result = 6;
                        std::srand(static_cast<unsigned int>(std::time(0)) + slots_iter);
                        slot_result = std::rand() % 7; // Generates a pseudo random number between 0 and 7
                        *ScriptLocal("casino_slots"_J, slots_random_results_table + slots_iter).As<int*>() = slot_result;
                    }
                }
            }
        }
	};

    static Casino _Casino{"rigslotmachines", "Rig Slot Machines", "Rig Slot Machines"};

}
#include <iostream>
#include <random>
#include <ctime>
#include "game/gta/Natives.hpp"
#include "core/commands/BoolCommand.hpp"
#include "game/gta/ScriptLocal.hpp"


namespace YimMenu::Features
{
	class Casino : public BoolCommand
	{
		using BoolCommand::BoolCommand;

        int slots_random_results_table = 1348;

		virtual void OnEnable() override
		{
            bool needs_run = false;
            if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH("casino_slots"_J)) {
                for (int slots_iter = 3; slots_iter <= 196; ++slots_iter) {
                    if (slots_iter != 67 && slots_iter != 132) {
                        if (*ScriptLocal("casino_slots"_J, slots_random_results_table + slots_iter).As<int*>() != 6) {
                            needs_run = true;
                        }
                    }
                }
                if (needs_run) {
                    for (int slots_iter = 3; slots_iter <= 196; ++slots_iter) {
                        if (slots_iter != 67 && slots_iter != 132) {
                            int slot_result = 6;
                            *ScriptLocal("casino_slots"_J, slots_random_results_table + slots_iter).As<int*>() = slot_result;
                        }
                    }
                }
            }
		}

        virtual void OnDisable() override
        {
            bool needs_run = true;
            int sum = 0;

            if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH("casino_slots"_J)) {

                sum = 0;
                for (int slots_iter = 3; slots_iter <= 196; ++slots_iter) {
                    if (slots_iter != 67 && slots_iter != 132) {
                        sum += *ScriptLocal("casino_slots"_J, slots_random_results_table + slots_iter).As<int*>();
                    }
                }
                needs_run = (sum == 1152);
                if (needs_run) {
                    for (int slots_iter = 3; slots_iter <= 196; ++slots_iter) {
                        if (slots_iter != 67 && slots_iter != 132) {
                            int slot_result = 6;
                            std::srand(static_cast<unsigned int>(std::time(0)) + slots_iter);
                            slot_result = std::rand() % 8; // Generates a number between 0 and 7
                            *ScriptLocal("casino_slots"_J, slots_random_results_table + slots_iter).As<int*>() = slot_result;
                        }
                    }
                }
            }
        }
	};

    static Casino _Casino{"rigslotmachines", "Rig Slot Machines", "Rig Slot Machines"};

}
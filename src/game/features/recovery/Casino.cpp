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

        bool isEnabled = false;
        int slots_random_results_table = 1348;


		virtual void OnEnable() override
		{
            isEnabled = true;
            bool needs_run = true;
            int sum = 0;

            if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH("casino_slots"_J)) {
                needs_run = false;
                if (isEnabled) {
                    for (int slots_iter = 3; slots_iter <= 196; ++slots_iter) {
                        if (slots_iter != 67 && slots_iter != 132) {
                            LOG(INFO) << "Debug: [" << *ScriptLocal("casino_slots"_J, slots_random_results_table + slots_iter).As<int*>() << " ]";
                            if (*ScriptLocal("casino_slots"_J, slots_random_results_table + slots_iter).As<int*>() != 6) {
                                needs_run = true;
                            }
                        }
                    }
                } else {
                    sum = 0;
                    for (int slots_iter = 3; slots_iter <= 196; ++slots_iter) {
                        if (slots_iter != 67 && slots_iter != 132) {
                            LOG(INFO) << "Debug: [" << *ScriptLocal("casino_slots"_J, slots_random_results_table + slots_iter).As<int*>() << " ]";
                            sum += *ScriptLocal("casino_slots"_J, slots_random_results_table + slots_iter).As<int*>();
                        }
                    }
                    needs_run = (sum == 1152);
                }
                if (needs_run) {
                    for (int slots_iter = 3; slots_iter <= 196; ++slots_iter) {
                        if (slots_iter != 67 && slots_iter != 132) {
                            int slot_result = 6;
                            if (!isEnabled) {
                                std::srand(static_cast<unsigned int>(std::time(0)) + slots_iter);
                                slot_result = std::rand() % 8; // Generates a number between 0 and 7
                            }
                            LOG(INFO) << "Debug: [" << *ScriptLocal("casino_slots"_J, slots_random_results_table + slots_iter).As<int*>() << " " << slot_result << " ]";
                            *ScriptLocal("casino_slots"_J, slots_random_results_table + slots_iter).As<int*>() = slot_result;
                        }
                    }
                }
            }
		}

        virtual void OnDisable() override
        {
            isEnabled = false;
            bool needs_run = true;
            int sum = 0;

            if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH("casino_slots"_J)) {
                needs_run = false;
                sum = 0;

                for (int slots_iter = 3; slots_iter <= 196; ++slots_iter) {
                    if (slots_iter != 67 && slots_iter != 132) {
                        LOG(INFO) << "Debug: [" << *ScriptLocal("casino_slots"_J, slots_random_results_table + slots_iter).As<int*>() << " ]";
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
                            LOG(INFO) << "Debug: [" << *ScriptLocal("casino_slots"_J, slots_random_results_table + slots_iter).As<int*>() << " " << slot_result << " ]";
                            *ScriptLocal("casino_slots"_J, slots_random_results_table + slots_iter).As<int*>() = slot_result;
                        }
                    }
                }
            }
        }
	};

    static Casino _Casino{"rigslotmachines", "Rig Slot Machines", "Rig Slot Machines"};

}
#include "core/commands/LoopedCommand.hpp"
#include "game/backend/ScriptPatches.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	class PlayAllMissionsSolo : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		ScriptPatch m_CanLaunchJobPatch{};
		ScriptPatch m_MissionRequestPatch1{}; // TODO: do we need these patches?
		ScriptPatch m_MissionRequestPatch2{};
		ScriptPatch m_MissionRequestPatch3{};
		ScriptPatch m_MissionRequestPatch4{};
		ScriptPatch m_PlayerCountWatchdogPatch1{};
		ScriptPatch m_PlayerCountWatchdogPatch2{};
		ScriptPatch m_HeistTeamsPatch1{};
		ScriptPatch m_HeistTeamsPatch2{};
		ScriptPatch m_ShouldFailMissionPatch1{}; // god I hate this function
		std::vector<ScriptPatch> m_ShouldFailMissionPatches{};
		ScriptPatch m_ShouldFailMissionPatch2{};
		ScriptPatch m_ShouldFailMissionPatch3{};
		ScriptPatch m_NotEnoughTeamsPatch{};
		ScriptPatch m_IsTeamValidPatch{}; // TODO: probably has many unintended side effects
		ScriptPatch m_EnsureMissionPassedPatch{};
		ScriptPatch m_ProcessPhoneHackingPatch{};
		ScriptPatch m_QuickRestartPatch1{};
		ScriptPatch m_QuickRestartPatch2{};

		virtual void OnEnable() override
		{
			if (!m_CanLaunchJobPatch)
			{
				m_CanLaunchJobPatch = ScriptPatches::AddPatch("fmmc_launcher"_J, ScriptPointer("CanLaunchJobPatch", "2D 05 0C 00 00 71").Add(5), {0x72, 0x2E, 0x05, 0x01}); // the main patch that bypasses the not enough players alert
			}
			m_CanLaunchJobPatch->Enable();

			// these patches allow the mission request system to launch fm_mission_controller with insufficent players
			if (!m_MissionRequestPatch1)
			{
				m_MissionRequestPatch1 = ScriptPatches::AddPatch("freemode"_J, ScriptPointer("MissionRequestPatch1", "38 00 72 5D ? ? ? 38 00 5D ? ? ? 2E 02 00 38 00 38 01"), std::vector<std::uint8_t>(14, 0x0));
			}
			m_MissionRequestPatch1->Enable();

			if (!m_MissionRequestPatch2)
			{
				m_MissionRequestPatch2 = ScriptPatches::AddPatch("freemode"_J, ScriptPointer("MissionRequestPatch2", "25 ? 37 07 33 37 07 5D ? ? ? 39 11").Add(20), {0x72});
			}
			m_MissionRequestPatch2->Enable();

			if (!m_MissionRequestPatch3)
			{
				m_MissionRequestPatch3 = ScriptPatches::AddPatch("freemode"_J, ScriptPointer("MissionRequestPatch3", "2D 03 1A 00 00 38 00 5D ? ? ? 39 05").Add(5), {0x72, 0x2E, 0x03, 0x01});
			}
			m_MissionRequestPatch3->Enable();

			if (!m_MissionRequestPatch4)
			{
				m_MissionRequestPatch4 = ScriptPatches::AddPatch("freemode"_J, ScriptPointer("MissionRequestPatch4", "5D ? ? ? 39 06 38 01 5D ? ? ? 25"), {0x72, 0x2E, 0x04, 0x01});
			}
			m_MissionRequestPatch4->Enable();

			if (!m_PlayerCountWatchdogPatch1)
			{
				m_PlayerCountWatchdogPatch1 = ScriptPatches::AddPatch("fmmc_launcher"_J, ScriptPointer("PlayerCountWatchdogPatch1", "2D 02 09 00 00 25 A4").Add(5), {0x71, 0x2E, 0x02, 0x01}); // instant kick if this check fails
			}
			m_PlayerCountWatchdogPatch1->Enable();

			if (!m_PlayerCountWatchdogPatch2)
			{
				m_PlayerCountWatchdogPatch2 = ScriptPatches::AddPatch("fmmc_launcher"_J, ScriptPointer("PlayerCountWatchdogPatch2", "2D 04 0B 00 00 2C ? ? ? 71 5D").Add(5), {0x71, 0x2E, 0x04, 0x01});
			}
			m_PlayerCountWatchdogPatch2->Enable();

			if (!m_HeistTeamsPatch1)
			{
				m_HeistTeamsPatch1 = ScriptPatches::AddPatch("fmmc_launcher"_J, ScriptPointer("HeistTeamsPatch1", "47 ? ? 5B 7B 00 38 04"), {0x2B, 0x2B, 0x00, 0x55}); // TODO: doesn't work for doomsday heist
			}
			m_HeistTeamsPatch1->Enable();

			if (!m_HeistTeamsPatch2)
			{
				m_HeistTeamsPatch2 = ScriptPatches::AddPatch("fmmc_launcher"_J, ScriptPointer("HeistTeamsPatch2", "2D 01 05 00 00 25 5D").Add(5), {0x72, 0x2E, 0x01, 0x01});
			}
			m_HeistTeamsPatch2->Enable();

			if (!m_ShouldFailMissionPatch1)
			{
				m_ShouldFailMissionPatch1 = ScriptPatches::AddPatch("fm_mission_controller"_J, ScriptPointer("ShouldFailMissionPatch1", "50 ? ? 78 82 06 1F 56 ? ? 38 02"), {0x00, 0x00, 0x00, 0x72, 0x00});
			}
			m_ShouldFailMissionPatch1->Enable();

			if (m_ShouldFailMissionPatches.empty())
			{
				// TODO: this is a very bad idea that can break anytime
				// for some reason, Rockstar thought it's a good idea to copy-paste the same failure check in four different branches, "just in case"
				for (int i = 0; i < 4; i++)
				{
					std::string ptrName = "ShouldFailMissionPatches" + std::to_string(i);
					m_ShouldFailMissionPatches.push_back(ScriptPatches::AddPatch("fm_mission_controller"_J, ScriptPointer(ptrName, "38 02 5D ? ? ? 71 09 2A 56 07 00 71 5D ? ? ? 06 1F 56"), {0x71, 0x00, 0x00, 0x00, 0x00, 0x00}));
				}
			}

			for (auto& patch : m_ShouldFailMissionPatches)
				patch->Enable();

			if (!m_ShouldFailMissionPatch2)
			{
				m_ShouldFailMissionPatch2 = ScriptPatches::AddPatch("fm_mission_controller"_J, ScriptPointer("ShouldFailMissionPatch2", "56 07 00 38 02 5D ? ? ? 20 56 BC 01"), {0x2B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2B, 0x71}); // some heist check, more or less same as above
			}
			m_ShouldFailMissionPatch2->Enable();

			if (!m_ShouldFailMissionPatch3)
			{
				m_ShouldFailMissionPatch3 = ScriptPatches::AddPatch("fm_mission_controller"_J, ScriptPointer("ShouldFailMissionPatch3", "50 ? ? 78 82 06 1F 56 ? ? 71"), {0x00, 0x00, 0x00, 0x00, 0x72});
			}
			m_ShouldFailMissionPatch3->Enable();

			if (!m_NotEnoughTeamsPatch)
			{
				m_NotEnoughTeamsPatch = ScriptPatches::AddPatch("fm_mission_controller"_J, ScriptPointer("NotEnoughTeamsPatch", "2D 00 02 00 00 61 ? ? ? 47 ? ? 72 57 04 00 72 2E 00 01 4F").Add(5), {0x71, 0x2E, 0x00, 0x01});
			}
			m_NotEnoughTeamsPatch->Enable();

			if (!m_IsTeamValidPatch)
			{
				m_IsTeamValidPatch = ScriptPatches::AddPatch("fm_mission_controller"_J, ScriptPointer("IsTeamValidPatch", "2D 01 03 00 00 38 00 71 57 1D 00").Add(5), {0x72, 0x2E, 0x01, 0x01});
			}
			m_IsTeamValidPatch->Enable();

			if (!m_EnsureMissionPassedPatch)
			{
				m_EnsureMissionPassedPatch = ScriptPatches::AddPatch("fm_mission_controller"_J, ScriptPointer("EnsureMissionPassedPatch", "55 C8 FF 61").Add(3), {0x2E, 0x00, 0x00}); // the game does one final check to ensure all players exist before the mission is passed
			}
			m_EnsureMissionPassedPatch->Enable();

			if (!m_ProcessPhoneHackingPatch)
			{
				m_ProcessPhoneHackingPatch = ScriptPatches::AddPatch("fm_mission_controller"_J, ScriptPointer("ProcessPhoneHackingPatch", "58 13 00 38 00 4F ? ? 48"), {0x2B, 0x00, 0x00});
			}

			if (!m_QuickRestartPatch1)
			{
				m_QuickRestartPatch1 = ScriptPatches::AddPatch("fm_mission_controller"_J, ScriptPointer("QuickRestartPatch1", "2D 00 07 00 00 62 ? ? ? 56 04 00").Add(5), {0x72, 0x2E, 0x00, 0x01});
			}
			m_QuickRestartPatch1->Enable();

			if (!m_QuickRestartPatch2)
			{
				m_QuickRestartPatch2 = ScriptPatches::AddPatch("fm_mission_controller"_J, ScriptPointer("QuickRestartPatch2", "5A 47 00 5D ? ? ? 5D ? ? ? 75"), {0x2B, 0x00, 0x00});
			}
			m_QuickRestartPatch2->Enable();
		}

		virtual void OnTick() override
		{
			if (m_ProcessPhoneHackingPatch)
			{
				// the patch transfers the hacking minigame from the passenger to the driver, so we only want it applied when we're playing solo
				if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH("fm_mission_controller"_J) && NETWORK::NETWORK_GET_TOTAL_NUM_PLAYERS() == 1)
					m_ProcessPhoneHackingPatch->Enable();
				else
					m_ProcessPhoneHackingPatch->Disable();
			}
		}

		virtual void OnDisable() override
		{
			if (m_CanLaunchJobPatch)
			{
				m_CanLaunchJobPatch->Disable();
			}

			if (m_MissionRequestPatch1)
			{
				m_MissionRequestPatch1->Disable();
			}

			if (m_MissionRequestPatch2)
			{
				m_MissionRequestPatch2->Disable();
			}

			if (m_MissionRequestPatch3)
			{
				m_MissionRequestPatch3->Disable();
			}

			if (m_MissionRequestPatch4)
			{
				m_MissionRequestPatch4->Disable();
			}

			if (m_PlayerCountWatchdogPatch2)
			{
				m_PlayerCountWatchdogPatch2->Disable();
			}

			if (m_PlayerCountWatchdogPatch2)
			{
				m_PlayerCountWatchdogPatch2->Disable();
			}

			if (m_HeistTeamsPatch1)
			{
				m_HeistTeamsPatch1->Disable();
			}

			if (m_HeistTeamsPatch2)
			{
				m_HeistTeamsPatch2->Disable();
			}

			if (m_ShouldFailMissionPatch1)
			{
				m_ShouldFailMissionPatch1->Disable();
			}

			for (auto& patch : m_ShouldFailMissionPatches)
				patch->Disable();

			if (m_ShouldFailMissionPatch2)
			{
				m_ShouldFailMissionPatch2->Disable();
			}

			if (m_ShouldFailMissionPatch3)
			{
				m_ShouldFailMissionPatch3->Disable();
			}

			if (m_NotEnoughTeamsPatch)
			{
				m_NotEnoughTeamsPatch->Disable();
			}

			if (m_IsTeamValidPatch)
			{
				m_IsTeamValidPatch->Disable();
			}

			if (m_EnsureMissionPassedPatch)
			{
				m_EnsureMissionPassedPatch->Disable();
			}

			if (m_ProcessPhoneHackingPatch)
			{
				m_ProcessPhoneHackingPatch->Disable();
			}

			if (m_QuickRestartPatch1)
			{
				m_QuickRestartPatch1->Disable();
			}

			if (m_QuickRestartPatch2)
			{
				m_QuickRestartPatch2->Disable();
			}
		}
	};

	static PlayAllMissionsSolo _PlayAllMissionsSolo{"playallmissionssolo", "Play All Missions Solo", "Allows you to play any mission solo. Note that some missions might break if there aren't enough players"};
}
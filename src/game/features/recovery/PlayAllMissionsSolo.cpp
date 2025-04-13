#include "core/commands/BoolCommand.hpp"
#include "game/backend/ScriptPatches.hpp"

namespace YimMenu::Features
{
	class PlayAllMissionsSolo : public BoolCommand
	{
		using BoolCommand::BoolCommand;

		ScriptPatch m_CanLaunchJobPatch{};
		ScriptPatch m_MissionRequestPatch1{}; // TODO: do we need these patches?
		ScriptPatch m_MissionRequestPatch2{};
		ScriptPatch m_MissionRequestPatch3{};
		ScriptPatch m_MissionRequestPatch4{};
		ScriptPatch m_PlayerCountWatchdogPatch1{};
		ScriptPatch m_PlayerCountWatchdogPatch2{};
		ScriptPatch m_HeistTeamsPatch{};
		ScriptPatch m_ShouldFailMissionPatch1{}; // god I hate this function
		std::vector<ScriptPatch> m_ShouldFailMissionPatches{};
		ScriptPatch m_ShouldFailMissionPatch2{};
		ScriptPatch m_EnsureMissionPassedPatch{}; 

		virtual void OnEnable() override
		{
			if (!m_CanLaunchJobPatch)
			{
				m_CanLaunchJobPatch = ScriptPatches::AddPatch("fmmc_launcher"_J, "2D 05 0C 00 00 71", 5, {0x72, 0x2E, 0x05, 0x01});
			}
			m_CanLaunchJobPatch->Enable();

			if (!m_MissionRequestPatch1)
			{
				m_MissionRequestPatch1 = ScriptPatches::AddPatch("freemode"_J, "38 00 72 5D ? ? ? 38 00 5D ? ? ? 2E 02 00 38 00 38 01", 0, std::vector<std::uint8_t>(14, 0x0));
			}
			m_MissionRequestPatch1->Enable();

			if (!m_MissionRequestPatch2)
			{
				m_MissionRequestPatch2 = ScriptPatches::AddPatch("freemode"_J, "25 ? 37 07 33 37 07 5D ? ? ? 39 11", 20, {0x72});
			}
			m_MissionRequestPatch2->Enable();

			if (!m_MissionRequestPatch3)
			{
				m_MissionRequestPatch3 = ScriptPatches::AddPatch("freemode"_J, "2D 03 1A 00 00 38 00 5D ? ? ? 39 05", 5, {0x72, 0x2E, 0x03, 0x01});
			}
			m_MissionRequestPatch3->Enable();

			if (!m_MissionRequestPatch4)
			{
				m_MissionRequestPatch4 = ScriptPatches::AddPatch("freemode"_J, "5D ? ? ? 39 06 38 01 5D ? ? ? 25", 0, {0x72, 0x2E, 0x04, 0x01});
			}
			m_MissionRequestPatch4->Enable();

			if (!m_PlayerCountWatchdogPatch1)
			{
				m_PlayerCountWatchdogPatch1 = ScriptPatches::AddPatch("fmmc_launcher"_J, "2D 02 09 00 00 25 A4", 5, {0x71, 0x2E, 0x02, 0x01});
			}
			m_PlayerCountWatchdogPatch1->Enable();

			if (!m_PlayerCountWatchdogPatch2)
			{
				m_PlayerCountWatchdogPatch2 = ScriptPatches::AddPatch("fmmc_launcher"_J, "2D 04 0B 00 00 2C ? ? ? 71 5D", 5, {0x71, 0x2E, 0x04, 0x01});
			}
			m_PlayerCountWatchdogPatch2->Enable();

			if (!m_HeistTeamsPatch)
			{
				m_HeistTeamsPatch = ScriptPatches::AddPatch("fmmc_launcher"_J, "47 ? ? 5B 7B 00 38 04", 0, {0x2B, 0x2B, 0x00, 0x55});
			}
			m_HeistTeamsPatch->Enable();

			if (!m_ShouldFailMissionPatch1)
			{
				m_ShouldFailMissionPatch1 = ScriptPatches::AddPatch("fm_mission_controller"_J, "50 ? ? 78 82 06 1F 56 ? ? 38 02", 0, {0x00, 0x00, 0x00, 0x72, 0x00});
			}
			m_ShouldFailMissionPatch1->Enable();
			
			if (m_ShouldFailMissionPatches.empty())
			{
				// TODO: this is a very bad idea that can break anytime
				for (int i = 0; i < 4; i++)
					m_ShouldFailMissionPatches.push_back(ScriptPatches::AddPatch("fm_mission_controller"_J, "38 02 5D ? ? ? 71 09 2A 56 07 00 71 5D ? ? ? 06 1F 56", 0, {0x71, 0x00, 0x00, 0x00, 0x00, 0x00}));
			}

			for (auto& patch : m_ShouldFailMissionPatches)
				patch->Enable();

			if (!m_ShouldFailMissionPatch2)
			{
				m_ShouldFailMissionPatch2 = ScriptPatches::AddPatch("fm_mission_controller"_J, "56 07 00 38 02 5D ? ? ? 20 56 BC 01", 0, {0x2B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2B, 0x71});
			}
			m_ShouldFailMissionPatch2->Enable();
			
			if (!m_EnsureMissionPassedPatch)
			{
				m_EnsureMissionPassedPatch = ScriptPatches::AddPatch("fm_mission_controller"_J, "55 C8 FF 61", 3, {0x2E, 0x00, 0x00});
			}
			m_EnsureMissionPassedPatch->Enable();
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

			if (m_HeistTeamsPatch)
			{
				m_HeistTeamsPatch->Disable();
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

			if (m_EnsureMissionPassedPatch)
			{
				m_EnsureMissionPassedPatch->Disable();
			}
		}
	};

	static PlayAllMissionsSolo _PlayAllMissionsSolo{"playallmissionssolo", "Play All Missions Solo", "Allows you to play any mission solo. Note that some missions might break if there aren't enough players"};
}
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
				m_MissionRequestPatch2 = ScriptPatches::AddPatch("freemode"_J, "25 ? 37 07 33 37 07 5D ? ? ? 39 11", 20, {0x48});
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
		}
	};

	static PlayAllMissionsSolo _PlayAllMissionsSolo{"playallmissionssolo", "Play All Missions Solo", "Allows you to play any mission solo. Note that some missions might break if there aren't enough players"};
}
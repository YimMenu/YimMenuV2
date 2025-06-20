#include "core/commands/BoolCommand.hpp"
#include "game/backend/ScriptPatches.hpp"

namespace YimMenu
{
	static constexpr auto creatorScripts = std::to_array({
	    "fm_race_creator"_J,
	    "fm_survival_creator"_J,
	    "fm_lts_creator"_J,
	    "fm_deathmatch_creator"_J,
	    "fm_capture_creator"_J,
	});
	
	class EnableCreatorDevMode : public BoolCommand
	{
		using BoolCommand::BoolCommand;

		std::vector<ScriptPatch> m_IsDevModeEnabledPatches;

		virtual void OnEnable() override
		{
			if (m_IsDevModeEnabledPatches.empty())
			{
				for (int i = 0; i < creatorScripts.size(); i++)
				{
					m_IsDevModeEnabledPatches.push_back(ScriptPatches::AddPatch(creatorScripts[i], ScriptPointer("IsDevModeEnabledPatch", "5D ? ? ? 56 ? ? 38 00 46 F0 0B").Add(1).Rip(), {0x2D, 0x00, 0x02, 0x00, 0x00, 0x72, 0x2E, 0x00, 0x01}));
				}
			}

			for (auto& patch : m_IsDevModeEnabledPatches)
				patch->Enable();
		}

		virtual void OnDisable() override
		{
			for (auto& patch : m_IsDevModeEnabledPatches)
				patch->Disable();
		}
	};

	static EnableCreatorDevMode _EnableCreatorDevMode{"enablecreatordevmode", "Enable Creator Dev Mode", "Enables the developer mode in Creator."};
}
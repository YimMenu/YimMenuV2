#include "core/commands/BoolCommand.hpp"
#include "game/backend/ScriptPatches.hpp"

namespace YimMenu::Features
{
	class DisableDeathBarriers : public BoolCommand
	{
		using BoolCommand::BoolCommand;

		ScriptPatch m_DeathBarriersPatch{};

		virtual void OnEnable() override
		{
			if (!m_DeathBarriersPatch)
			{
				m_DeathBarriersPatch = ScriptPatches::AddPatch("freemode"_J, ScriptPointer("DeathBarriersPatch", "2D 01 09 00 00 5D ? ? ? 56 ? ? 3A").Add(5), {0x2E, 0x01, 0x00});
			}
			m_DeathBarriersPatch->Enable();
		}


		virtual void OnDisable() override
		{
			if (m_DeathBarriersPatch)
			{
				m_DeathBarriersPatch->Disable();
			}
		}
	};

	static DisableDeathBarriers _DisableDeathBarriers{"disabledeathbarriers", "Disable Death Barriers", "Disables death barriers found under the map. This also prevents dying randomly when spectating someone", true};
}
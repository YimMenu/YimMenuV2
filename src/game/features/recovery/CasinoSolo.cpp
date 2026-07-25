#include "core/commands/LoopedCommand.hpp"
#include "game/backend/ScriptPatches.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	class CasinoSolo : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		ScriptPatch m_casinosolo{};


		virtual void OnEnable() override
		{
			if (!m_casinosolo)
			{
				m_casinosolo = ScriptPatches::AddPatch("fmmc_launcher"_J, ScriptPointer("casinosolo", "2D 01 03 00 00 5D ? ? ? 2A 06 56 05 00 5D ? ? ? 20 2A 06 56 05 00 5D").Add(5), {0x71, 0x2E, 0x01, 0x01});
			}
			m_casinosolo->Enable();

		}

		virtual void OnTick() override
		{
			
		}

		virtual void OnDisable() override
		{
			if (m_casinosolo)
			{
				m_casinosolo->Disable();
			}
		}
	};

		static CasinoSolo _CasinoSolo{"casinosolo", "Casino Solo", "Allows you to play casino heist solo."};

}
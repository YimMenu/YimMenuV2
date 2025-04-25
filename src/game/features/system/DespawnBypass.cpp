#include "core/commands/BoolCommand.hpp"
#include "game/backend/ScriptPatches.hpp"

namespace YimMenu::Features
{
	class DespawnBypass : public BoolCommand
	{
		using BoolCommand::BoolCommand;

		ScriptPatch m_ShopPatch{};

		virtual void OnEnable() override
		{
			if (!m_ShopPatch)
			{
				m_ShopPatch = ScriptPatches::AddPatch("shop_controller"_J, ScriptPointer("ShopPatch", "2D 01 04 00 00 2C ? ? ? 56 ? ? 71").Add(5), {0x71, 0x2E, 0x01, 0x01}); // disable the kick out subroutine
			}
			m_ShopPatch->Enable();
		}


		virtual void OnDisable() override
		{
			if (m_ShopPatch)
			{
				m_ShopPatch->Disable();
			}
		}
	};

	static DespawnBypass _DespawnBypass{"despawnbypass", "Allow MP Vehicles in SP", "Allows MP vehicles to be used in SP", true};
}
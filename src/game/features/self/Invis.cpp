#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu::Features
{
	static BoolCommand _LocallyVisible{"localvis", "Locally Visible", "Be locally visible while remaining invisible to other players"};

	class Invis : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			if (Self::GetPed())
			{
				Self::GetPed().SetVisible(false);
				if (_LocallyVisible.GetState())
					Self::GetPlayer().SetVisibleLocally(true);
				else
					Self::GetPlayer().SetVisibleLocally(false);
			}
		}

		virtual void OnDisable() override
		{
			if (Self::GetPed())
			{
				Self::GetPed().SetVisible(true);
				Self::GetPlayer().SetVisibleLocally(false);
			}
		}
	};

	static Invis _Invis{"invis", "Invisibility", "Be invisible"};
}
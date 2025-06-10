#include "core/commands/BoolCommand.hpp"
#include "game/gta/Stats.hpp"

namespace YimMenu::Features
{
	class AllowGenderChange : public BoolCommand
	{
		using BoolCommand::BoolCommand;

		virtual void OnEnable() override
		{
			Stats::SetInt("MPx_ALLOW_GENDER_CHANGE", 52);
		}

		virtual void OnDisable() override
		{
			Stats::SetInt("MPX_HEIST_PLANNING_STAGE", 0);
		}
	};

	static AllowGenderChange _AllowGenderChange{"allowgenderchange", "Allow Gender Change", "Allows the player to change the character's gender"};
}
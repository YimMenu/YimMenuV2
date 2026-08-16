#include "core/commands/Command.hpp"
#include "core/commands/FloatCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	static FloatCommand _DirectionalTpDistance{"directionaltpdistance", "Teleport Distance", "Teleportation distance of directional teleports"};

	class TpForward : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			auto ped = Self::GetPed();
			ped.TeleportTo(ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped.GetHandle(), 0, _DirectionalTpDistance.GetState(), 0));
		}
	};

	class TpBackward : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			auto ped = Self::GetPed();
			ped.TeleportTo(ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped.GetHandle(), 0, -_DirectionalTpDistance.GetState(), 0));
		}
	};

	class TpRight : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			auto ped = Self::GetPed();
			ped.TeleportTo(ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped.GetHandle(), _DirectionalTpDistance.GetState(), 0, 0));
		}
	};

	class TpLeft : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			auto ped = Self::GetPed();
			ped.TeleportTo(ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped.GetHandle(), -_DirectionalTpDistance.GetState(), 0, 0));
		}
	};

	class TpUp : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			auto ped = Self::GetPed();
			ped.TeleportTo(ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped.GetHandle(), 0, 0, _DirectionalTpDistance.GetState()));
		}
	};

	class TpDown : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			auto ped = Self::GetPed();
			ped.TeleportTo(ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped.GetHandle(), 0, 0, -_DirectionalTpDistance.GetState()));
		}
	};

	static TpForward  _DirectionalTpForward {"directionaltpforward",  "Teleport Forward",  "Teleports you forward"     };
	static TpBackward _DirectionalTpBackward{"directionaltpbackward", "Teleport Backward", "Teleports you backward"    };
	static TpRight    _DirectionalTpRight   {"directionaltpright",    "Teleport Right",    "Teleports you to the right"};
	static TpLeft     _DirectionalTpLeft    {"directionaltpleft",     "Teleport Left",     "Teleports you to the left" };
	static TpUp       _DirectionalTpUp      {"directionaltpup",       "Teleport Up",       "Teleports you up"          };
	static TpDown     _DirectionalTpDown    {"directionaltpdown",     "Teleport Down",     "Teleports you down"        };
}

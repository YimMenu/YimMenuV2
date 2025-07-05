#include "core/commands/Command.hpp"
#include "game/backend/PersonalVehicles.hpp"
#include "game/pointers/Pointers.hpp"

namespace YimMenu
{
	class RequestPersonalVehicle : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			PersonalVehicles::GetCurrent()->Request();
		}
	};

	static RequestPersonalVehicle _RequestPersonalVehicle{"requestpv", "Request Personal Vehicle", "Requests your current Personal Vehicle."};
}
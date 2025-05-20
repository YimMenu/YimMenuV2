#include "core/commands/Command.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/data/StackSizes.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/Scripts.hpp"
#include "game/gta/ScriptLocal.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "types/script/Timer.hpp"

namespace YimMenu::Features
{
	class CallMechanic : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted || SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH("AM_CONTACT_REQUESTS"_J) > 0)
			{
				Notifications::Show("Mechanic", "Not safe to call the mechanic at the moment.", NotificationType::Error);
				return;
			}

			if (auto freemode = Scripts::FindScriptThread("freemode"_J))
			{
				auto data = ScriptLocal(freemode, 8732);
				*data.At(3).As<int*>()        = 215;
				*data.At(3).At(16).As<int*>() = Self::GetPlayer().GetId();
				*data.At(3).At(1).As<int*>()  = 89;
				*data.At(2).As<int*>()        = "AM_CONTACT_REQUESTS"_J;

				while (!SCRIPT::HAS_SCRIPT_WITH_NAME_HASH_LOADED("AM_CONTACT_REQUESTS"_J))
				{
					SCRIPT::REQUEST_SCRIPT_WITH_NAME_HASH("AM_CONTACT_REQUESTS"_J);
					ScriptMgr::Yield();
				}

				auto args = data.At(3).As<void*>();
				if (auto id = BUILTIN::START_NEW_SCRIPT_WITH_NAME_HASH_AND_ARGS("AM_CONTACT_REQUESTS"_J, args, 21, eStackSizes::SCRIPT_XML))
				{
					if (auto thread = Scripts::FindScriptThreadByID(id))
					{
						*ScriptLocal(thread, 519).As<int*>() = 1;
						ScriptGlobal(2685663).At(4344).At(251).At(7, 2).As<TIMER*>()->Destroy();
					}
				}
				else
				{
					Notifications::Show("Mechanic", "Failed to call the mechanic.", NotificationType::Error);
				}

				SCRIPT::SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED("AM_CONTACT_REQUESTS"_J);
			}
		}
	};

	static CallMechanic _CallMechanic{"callmechanic", "Call Mechanic", "Allows you to request your personal vehicles."};
}
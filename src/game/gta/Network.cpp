#include "Network.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/backend/NativeHooks.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "game/gta/ScriptFunction.hpp"
#include "game/pointers/Pointers.hpp"
#include "types/rage/atArray.hpp"
#include "types/network/rlSessionInfo.hpp"
#include "types/network/rlSessionByGamerHandleTaskResult.hpp"
#include "types/network/rlTaskStatus.hpp"
#include "types/socialclub/rlQueryAccountsResult.hpp"
#include "types/socialclub/rlGetAvatarsContext.hpp"
#include "types/socialclub/rlScTaskStatus.hpp"

namespace YimMenu::Network
{
	void LaunchJoinType(JoinType to_launch)
	{
		static ScriptFunction sendToClouds("shop_controller"_J, ScriptPointer("SendToClouds", "2D 00 02 00 00 72 5D ? ? ? 72"));
		static ScriptGlobal join_type_global(1575044);

		sendToClouds.Call<void>();
		*join_type_global.As<JoinType*>() = to_launch;
	}

	void JoinSessionInfo(rage::rlSessionInfo* info)
	{
		static std::optional<rage::rlSessionInfo> session_to_join;
		static bool ensure_native_hook_initialized = ([] {
			NativeHooks::AddHook("maintransition"_J, NativeIndex::NETWORK_SESSION_HOST, [](rage::scrNativeCallContext* ctx) {
				if (session_to_join)
				{
					if (!Pointers.JoinSessionByInfo(*Pointers.NetworkSession, &*session_to_join, 1, 1 | 2, nullptr, 0))
					{
						Notifications::Show("Joiner", "Failed to join session", NotificationType::Error);
						NativeInvoker::GetNativeHandler(NativeIndex::NETWORK_SESSION_HOST)(ctx);
					}
					else
					{
						ctx->SetReturnValue(TRUE);
					}
					session_to_join = std::nullopt;
				}
				else
				{
					NativeInvoker::GetNativeHandler(NativeIndex::NETWORK_SESSION_HOST)(ctx);
				}
			});
			return true;
		})();

		if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH("maintransition"_J) > 0 || STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS())
		{
			Notifications::Show("Joiner", "An existing transition is in progress", NotificationType::Error);
			return;
		}

		session_to_join = *info;
		LaunchJoinType(JoinType::NEW_PUBLIC);
	}

	void JoinRockstarId(std::uint64_t id)
	{
		rage::rlSessionByGamerTaskResult result;
		rage::rlTaskStatus status;
		rage::rlGamerHandle handle(id);
		bool success;

		if (Pointers.GetSessionByGamerHandle(0, &handle, 1, &result, 1, &success, &status))
		{
			while (status.m_Status == 1)
				ScriptMgr::Yield();

			if (status.m_Status == 3 && success)
			{
				JoinSessionInfo(&result.m_SessionInfo);
			}
			else
			{
				Notifications::Show("Joiner", "Failed to get session info by RID", NotificationType::Error);
				return;
			}
		}
		else
		{
			Notifications::Show("Joiner", "Failed to get session info by RID", NotificationType::Error);
			return;
		}
	}

	std::optional<std::uint64_t> ResolveRockstarId(std::string_view name)
	{
		if (!Pointers.GetAvatars)
			return std::nullopt;

		// these are probably too large to keep on the stack
		auto results = std::make_unique<rage::rlGetAvatarsResults>();
		auto players = std::make_unique<rage::rlGetAvatarsPlayerList>();

		rage::rlGetAvatarsContext context;

		strncpy(players->m_PlayerNames[0], name.data(), sizeof(players->m_PlayerNames[0]));
		players->m_NumEntries = 1;

		context.m_Type = rage::rlGetAvatarsContext::Type::BY_NICKNAME;
		context.m_AvatarSize = rage::rlGetAvatarsContext::AvatarSize::SMALL; // we don't need the avatars, but you gotta give it something
		context.m_Result = results.get();

		if (Pointers.GetAvatars(&context, players.get()))
		{
			while (context.m_Status.m_Status == 1)
			{
				ScriptMgr::Yield();
			}

			if (context.m_Status.m_Status == 3 && results->m_NumResults == 1)
			{
				return results->m_Results[0].m_RockstarId;
			}
		}

		return std::nullopt;
	}
}
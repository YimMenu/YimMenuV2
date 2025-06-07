#include "Scripts.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "game/pointers/Pointers.hpp"
#include "types/rage/atArray.hpp"
#include "types/rage/tlsContext.hpp"
#include "types/script/GtaThread.hpp"
#include "types/script/scrProgram.hpp"
#include "types/script/CGameScriptHandler.hpp"
#include "types/script/CGameScriptHandlerNetComponent.hpp"
#include "types/script/CGameScriptId.hpp"
#include "types/script/globals/GlobalPlayerBD.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/Packet.hpp"
#include "game/backend/Players.hpp"
#include "game/backend/Self.hpp"
#include "core/memory/Pattern.hpp"
#include "game/gta/Natives.hpp"
#include "core/frontend/Notifications.hpp"
#include "core/backend/ScriptMgr.hpp"

namespace YimMenu::Scripts
{
	int StartScript(joaat_t hash, eStackSizes stackSize, void* args, int argCount)
	{
		if (!SCRIPT::DOES_SCRIPT_WITH_NAME_HASH_EXIST(hash))
			return 0;

		if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(hash) > 0)
			return FindScriptThread(hash)->m_Context.m_ThreadId;

		for (int i = 0; !SCRIPT::HAS_SCRIPT_WITH_NAME_HASH_LOADED(hash); i++)
		{
			SCRIPT::REQUEST_SCRIPT_WITH_NAME_HASH(hash);
			ScriptMgr::Yield();

			if (i > 30)
				return 0;
		}

		int id = 0;
		if (args && argCount > 0)
		{
			id = BUILTIN::START_NEW_SCRIPT_WITH_NAME_HASH_AND_ARGS(hash, args, argCount, static_cast<int>(stackSize));
		}
		else
		{
			id = BUILTIN::START_NEW_SCRIPT_WITH_NAME_HASH(hash, static_cast<int>(stackSize));
		}

		SCRIPT::SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED(hash);
		return id;
	}

	bool IsScriptActive(joaat_t hash)
	{
		if (auto program = FindScriptProgram(hash))
			return (program->m_RefCount - 1) > 0;

		return false;
	}

	rage::scrThread* FindScriptThread(joaat_t hash)
	{
		for (auto& thread : *Pointers.ScriptThreads)
		{
			if (thread && thread->m_Context.m_ThreadId && thread->m_ScriptHash == hash)
			{
				return thread;
			}
		}

		return nullptr;
	}

	rage::scrThread* FindScriptThreadByID(std::uint32_t id)
	{
		for (auto& thread : *Pointers.ScriptThreads)
		{
			if (thread && thread->m_Context.m_ThreadId == id)
			{
				return thread;
			}
		}

		return nullptr;
	}

	rage::scrProgram* FindScriptProgram(joaat_t hash)
	{
		for (int i = 0; i < 176; i++)
		{
			if (Pointers.ScriptPrograms[i] && Pointers.ScriptPrograms[i]->m_NameHash == hash)
				return Pointers.ScriptPrograms[i];
		}

		return nullptr;
	}

	void RunAsScript(rage::scrThread* thread, std::function<void()> callback)
	{
		auto og_thread = rage::tlsContext::Get()->m_CurrentScriptThread;
		auto og_running_in_scrthread = rage::tlsContext::Get()->m_ScriptThreadActive;
		rage::tlsContext::Get()->m_CurrentScriptThread = thread;
		rage::tlsContext::Get()->m_ScriptThreadActive = true;
		callback();
		rage::tlsContext::Get()->m_ScriptThreadActive = og_running_in_scrthread;
		rage::tlsContext::Get()->m_CurrentScriptThread = og_thread;
	}

	void RunWithSpoofedThreadName(std::uint32_t name, std::function<void()> callback)
	{
		if (auto thread = reinterpret_cast<GtaThread*>(rage::tlsContext::Get()->m_CurrentScriptThread))
		{
			auto hash_1 = thread->m_Context.m_ScriptHash;
			auto hash_2 = thread->m_ScriptHash;
			auto hash_3 = thread->m_ScriptHash2;
			std::optional<std::uint32_t> hash_4;
			if (auto handler = thread->m_ScriptHandler)
				hash_4 = handler->GetId()->m_Hash;

			thread->m_Context.m_ScriptHash = name;
			thread->m_ScriptHash = name;
			thread->m_ScriptHash2 = name;
			if (hash_4)
				thread->m_ScriptHandler->GetId()->m_Hash = name;

			callback();

			thread->m_Context.m_ScriptHash = hash_1;
			thread->m_ScriptHash = hash_2;
			thread->m_ScriptHash2 = hash_3;
			if (hash_4)
				thread->m_ScriptHandler->GetId()->m_Hash = *hash_4;
		}
	}

	// we need this because modifying player broadcast data before they are registered causes the default values (when a new player joins) to be changed as well
	bool SafeToModifyFreemodeBroadcastGlobals()
	{
		if (!*Pointers.IsSessionStarted)
			return false;

		if (!FindScriptThread("freemode"_J))
			return false;

		if (auto gpbd = GlobalPlayerBD::Get())
		{
			return gpbd->Entries[Self::GetPlayer().GetId()].FreemodeState == eFreemodeState::RUNNING;
		}

		return false;
	}

	std::optional<std::uint32_t> GetCodeLocationByPattern(rage::scrProgram* program, SimplePattern pattern)
	{
		uint32_t codeSize = program->m_CodeSize;
		for (uint32_t i = 0; i < (codeSize - pattern.m_Bytes.size()); i++)
		{
			for (uint32_t j = 0; j < pattern.m_Bytes.size(); j++)
				if (pattern.m_Bytes[j].has_value())
					if (pattern.m_Bytes[j].value() != *program->GetCodeAddress(i + j))
						goto incorrect;

			return i;
		incorrect:
			continue;
		}

		return std::nullopt;
  }

	void ForceScriptHost(rage::scrThread* thread)
	{
		if (auto net_component = reinterpret_cast<GtaThread*>(thread)->m_NetComponent)
		{
			if (net_component->IsLocalPlayerHost())
				return;

			net_component->DoHostMigration(Self::GetPlayer().GetHandle(), net_component->m_HostToken + 1, false);

			Packet pkt;
			pkt.WriteMessageHeader(rage::netMessage::Type::ScriptVerifyHostAck);
			net_component->m_ScriptHandler->GetId()->Serialize(&pkt.GetBuffer());
			pkt.GetBuffer().Write<bool>(true, 1);
			pkt.GetBuffer().Write<bool>(true, 1);
			pkt.GetBuffer().Write<std::uint16_t>(net_component->m_HostToken, 16);

			for (auto& player : Players::GetPlayers())
				if (!player.second.IsLocal())
					pkt.Send(player.second.GetMessageId());
		}
	}

	void RunScript(std::string scriptName, int stackSize, std::int64_t* args, int argCount, bool pauseAfterStarting)
	{
		auto hash = Joaat(scriptName);

		if (!SCRIPT::DOES_SCRIPT_WITH_NAME_HASH_EXIST(hash))
		{
			Notifications::Show("Start Script", "Script does not exist.", NotificationType::Error);
			return;
		}

		if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(hash) > 0)
		{
			Notifications::Show("Start Script", "Script is already running.", NotificationType::Error);
			return;
		}

		if (MISC::GET_NUMBER_OF_FREE_STACKS_OF_THIS_SIZE(stackSize) == 0)
		{
			Notifications::Show("Start Script", "No free stack.", NotificationType::Error);
			return;
		}

		while (!SCRIPT::HAS_SCRIPT_WITH_NAME_HASH_LOADED(hash))
		{
			SCRIPT::REQUEST_SCRIPT_WITH_NAME_HASH(hash);
			ScriptMgr::Yield();
		}

		int id = 0;
		if (args && argCount > 0)
		{
			id = BUILTIN::START_NEW_SCRIPT_WITH_NAME_HASH_AND_ARGS(hash, args, argCount, stackSize);
		}
		else
		{
			id = BUILTIN::START_NEW_SCRIPT_WITH_NAME_HASH(hash, stackSize);
		}

		if (pauseAfterStarting)
		{
			if (auto thread = Scripts::FindScriptThreadByID(id))
				thread->m_Context.m_State = rage::scrThread::State::PAUSED;
		}

		SCRIPT::SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED(hash);
		Notifications::Show("Start Script", std::format("Started script with ID {}.", id), NotificationType::Success);
	}
}
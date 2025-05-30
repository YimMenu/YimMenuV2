#include "Scripts.hpp"
#include "core/backend/FiberPool.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/gta/data/ScriptNames.hpp"
#include "game/gta/data/StackSizes.hpp"
#include "game/gta/Scripts.hpp"
#include "game/gta/Natives.hpp"
#include "game/pointers/Pointers.hpp"
#include "types/rage/atArray.hpp"
#include "types/script/GtaThread.hpp"
#include "types/script/CGameScriptHandlerNetComponent.hpp"
#include "types/network/CNetGamePlayer.hpp"
#include "misc/cpp/imgui_stdlib.h"

namespace YimMenu::Submenus
{
	static constexpr std::pair<const char*, int> stackSizes[] = {
		{"MICRO", static_cast<int>(eStackSizes::MICRO)},
		{"MINI", static_cast<int>(eStackSizes::MINI)},
		{"DEFAULT", static_cast<int>(eStackSizes::DEFAULT)},
		{"SPECIAL_ABILITY", static_cast<int>(eStackSizes::SPECIAL_ABILITY)},
		{"FRIEND", static_cast<int>(eStackSizes::FRIEND)},
		{"SHOP", static_cast<int>(eStackSizes::SHOP)},
		{"CELLPHONE", static_cast<int>(eStackSizes::CELLPHONE)},
		{"VEHICLE_SPAWN", static_cast<int>(eStackSizes::VEHICLE_SPAWN)},
		{"CAR_MOD_SHOP", static_cast<int>(eStackSizes::CAR_MOD_SHOP)},
		{"PAUSE_MENU_SCRIPT", static_cast<int>(eStackSizes::PAUSE_MENU_SCRIPT)},
		{"APP_INTERNET", static_cast<int>(eStackSizes::APP_INTERNET)},
		{"MULTIPLAYER_MISSION", static_cast<int>(eStackSizes::MULTIPLAYER_MISSION)},
		{"CONTACTS_APP", static_cast<int>(eStackSizes::CONTACTS_APP)},
		{"INTERACTION_MENU", static_cast<int>(eStackSizes::INTERACTION_MENU)},
		{"SCRIPT_XML", static_cast<int>(eStackSizes::SCRIPT_XML)},
		{"PROPERTY_INT", static_cast<int>(eStackSizes::PROPERTY_INT)},
		{"ACTIVITY_CREATOR_INT", static_cast<int>(eStackSizes::ACTIVITY_CREATOR_INT)},
		{"SMPL_INTERIOR", static_cast<int>(eStackSizes::SMPL_INTERIOR)},
		{"WAREHOUSE", static_cast<int>(eStackSizes::WAREHOUSE)},
		{"IE_DELIVERY", static_cast<int>(eStackSizes::IE_DELIVERY)},
		{"SHOP_CONTROLLER", static_cast<int>(eStackSizes::SHOP_CONTROLLER)},
		{"AM_MP_YACHT", static_cast<int>(eStackSizes::AM_MP_YACHT)},
		{"INGAMEHUD", static_cast<int>(eStackSizes::INGAMEHUD)},
		{"TRANSITION", static_cast<int>(eStackSizes::TRANSITION)},
		{"FMMC_LAUNCHER", static_cast<int>(eStackSizes::FMMC_LAUNCHER)},
		{"MULTIPLAYER_FREEMODE", static_cast<int>(eStackSizes::MULTIPLAYER_FREEMODE)},
		{"MISSION", static_cast<int>(eStackSizes::MISSION)},
		{"MP_LAUNCH_SCRIPT", static_cast<int>(eStackSizes::MP_LAUNCH_SCRIPT)}
	};

	std::shared_ptr<Category> BuildScriptsMenu()
	{
		auto scripts = std::make_unique<Category>("Scripts");

		auto threads = std::make_unique<Group>("Threads");
		auto script  = std::make_unique<Group>("Start Script");

		static rage::scrThread* curThread      = nullptr;
		static std::string scriptSearch        = "";
		static std::string scriptName          = "";
		static std::string stackSizeName       = stackSizes[0].first;
		static int stackSize                   = 0;

		threads->AddItem(std::make_unique<ImGuiItem>([] {
			if (!Pointers.ScriptThreads || Pointers.ScriptThreads->size() == 0)
			{
				curThread = nullptr;
				return ImGui::TextDisabled("None");
			}

			if (ImGui::BeginCombo("Thread", curThread ? curThread->m_ScriptName : "(Select)"))
			{
				for (auto thread : *Pointers.ScriptThreads)
				{
					if (thread)
					{
						if (thread->m_Context.m_State == rage::scrThread::State::KILLED || thread->m_Context.m_StackSize == 0)
							continue;

						ImGui::PushID(thread->m_Context.m_ThreadId);

						if (ImGui::Selectable(thread->m_ScriptName, curThread == thread))
						{
							curThread = thread;
						}

						if (curThread == thread)
							ImGui::SetItemDefaultFocus();

						ImGui::PopID();
					}
				}

				ImGui::EndCombo();
			}

			if (!curThread)
				return;

			ImGui::Combo("State", (int*)&curThread->m_Context.m_State, "Idle\0Running\0Killed\0Paused\0Unk4\0");

			if (auto netComponent = reinterpret_cast<GtaThread*>(curThread)->m_NetComponent)
			{
				if (auto host = netComponent->GetHost())
				{
					ImGui::Text("Host: %s", host->GetName());
				}
				ImGui::SameLine();
				ImGui::BeginDisabled(netComponent->IsLocalPlayerHost());
				if (ImGui::SmallButton("Take Control"))
				{
					FiberPool::Push([] {
						Scripts::ForceScriptHost(curThread);
					});
				}
				ImGui::EndDisabled();
			}

			ImGui::Text("Thread ID: %d", curThread->m_Context.m_ThreadId);
			ImGui::Text("Stack Size: %d", curThread->m_Context.m_StackSize);
			ImGui::Text("Stack Pointer: 0x%p", &curThread->m_Context.m_StackPointer);
			ImGui::Text("Program Counter: 0x%p", &curThread->m_Context.m_ProgramCounter); // This is not really accurate (always points to the WAIT)
			if (curThread->m_Context.m_State == rage::scrThread::State::KILLED)
				ImGui::Text("Exit Reason: %s", curThread->m_ErrorMessage);
		}));

		script->AddItem(std::make_unique<ImGuiItem>([] {
			ImGui::InputTextWithHint("Script Name", "Search", &scriptSearch);

			if (ImGui::BeginCombo("Stack Size", stackSizeName.c_str()))
			{
				for (auto& p : stackSizes)
				{
					if (ImGui::Selectable(std::format("{} ({})", p.first, (int)p.second).data(), stackSize == p.second))
					{
						stackSizeName = p.first;
						stackSize     = p.second;
					}

					if (p.second == stackSize)
						ImGui::SetItemDefaultFocus();
				}

				ImGui::EndCombo();
			}

			if (ImGui::BeginListBox("##scripts"))
			{
				std::string lowerSearch = scriptSearch;
				std::transform(lowerSearch.begin(), lowerSearch.end(), lowerSearch.begin(), ::tolower);
				for (auto& script : scriptNames)
				{
					std::string lowerScript = script;
					std::transform(lowerScript.begin(), lowerScript.end(), lowerScript.begin(), ::tolower);
					if (lowerScript.find(lowerSearch) != std::string::npos)
					{
						if (ImGui::Selectable(script, scriptName == script))
						{
							scriptSearch = script;
							scriptName   = script;
						}
					}
				}

				ImGui::EndListBox();
			}

			if (ImGui::Button("Start Script"))
			{
				FiberPool::Push([] {
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

					BUILTIN::START_NEW_SCRIPT_WITH_NAME_HASH(hash, stackSize);
					SCRIPT::SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED(hash);
				});
			}
		}));

		scripts->AddItem(std::move(threads));
		scripts->AddItem(std::move(script));
		return scripts;
	}
}
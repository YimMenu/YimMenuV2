#include "HotkeySystem.hpp"
#include "core/backend/FiberPool.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "Commands.hpp"
#include "LoopedCommand.hpp"
#include "core/util/Joaat.hpp"

// TODO: serialization isn't stable

#include "game/pointers/Pointers.hpp" // game import in core!
#include "game/gta/Natives.hpp"       // game import in core!
#include "game/frontend/GUI.hpp"

namespace YimMenu
{
	HotkeySystem::HotkeySystem() :
	    IStateSerializer("hotkeys")
	{
	}

	void HotkeySystem::RegisterCommands()
	{
		auto& cmds = Commands::GetCommands();

		for (auto& [hash, cmd] : cmds)
		{
			CommandLink link;
			m_CommandHotkeys.insert(std::make_pair(hash, link));
		}

		m_CommandHotkeys.at("chathelper"_J).m_Chain.clear(); // ensure chat is always bound
		m_CommandHotkeys.at("chathelper"_J).m_Chain.push_back(0x54);
	}

	bool HotkeySystem::ListenAndApply(int& Hotkey, std::vector<int> Blacklist)
	{
		static auto IsKeyBlacklisted = [Blacklist](int Key) -> bool {
			for (auto Key_ : Blacklist)
				if (Key_ == Key)
					return true;

			return false;
		};

		// VK_OEM_CLEAR Is about the limit in terms of virtual key codes
		for (int i = 0; i < VK_OEM_CLEAR; i++)
		{
			if ((GetKeyState(i) & 0x8000) && i != 1 && !IsKeyBlacklisted(i))
			{
				Hotkey = i;

				return true;
			}
		}

		return false;
	}

	// Will return the keycode if there are no labels
	std::string HotkeySystem::GetHotkeyLabel(int HotkeyModifier)
	{
		char KeyName[32];
		GetKeyNameTextA(MapVirtualKey(HotkeyModifier, MAPVK_VK_TO_VSC) << 16, KeyName, 32);

		if (std::string(KeyName).empty())
			strcpy(KeyName, std::to_string(HotkeyModifier).data());

		return KeyName;
	}

	// Meant to be called in a loop
	void HotkeySystem::CreateHotkey(std::vector<int>& chain)
	{
		static auto is_key_unique = [this](int Key, std::vector<int> List) -> bool {
			for (auto& _key : List)
				if (_key == Key)
					return false;

			return true;
		};

		int pressed_key = 0;
		if (ListenAndApply(pressed_key, chain))
		{
			MarkStateDirty();

			if (is_key_unique(pressed_key, chain))
			{
				chain.push_back(pressed_key);
			}
		}
	}

	void HotkeySystem::RunScriptImpl()
	{
		while (g_Running)
		{
			if (GetForegroundWindow() == *Pointers.Hwnd && !HUD::IS_PAUSE_MENU_ACTIVE() && !HUD::IS_SOCIAL_CLUB_ACTIVE() && !m_BeingModified && !GUI::IsUsingKeyboard())
			{
				for (auto& [hash, link] : m_CommandHotkeys)
				{
					if (link.m_Chain.empty())
						continue;

					bool all_keys_pressed = true;

					for (auto modifier : link.m_Chain)
					{
						if (!(GetAsyncKeyState(modifier) & 0x8000))
						{
							all_keys_pressed = false;
						}
					}

					if (all_keys_pressed && std::chrono::system_clock::now() - m_LastHotkeyTriggerTime > 100ms)
					{
						auto command = Commands::GetCommand(hash);
						if (command)
						{
							// TODO: this is the only way I can prevent chat from blocking the main loop while keeping everything else fast
							if (hash != "chathelper"_J)
								command->Call();
							else
							{
								FiberPool::Push([command] {
									command->Call();
								});
							}
						}
						m_LastHotkeyTriggerTime = std::chrono::system_clock::now();
					}
				}
			}
			ScriptMgr::Yield();
		}
	}

	void HotkeySystem::RunScript()
	{
		g_HotkeySystem.RunScriptImpl();
	}

	void HotkeySystem::SaveStateImpl(nlohmann::json& state)
	{
		for (const auto& hotkey : m_CommandHotkeys)
		{
			std::string key = std::to_string(hotkey.first);

			if (!hotkey.second.m_Chain.empty())
			{
				state[key] = hotkey.second.m_Chain;
			}
			else if (state.contains(key))
			{
				state.erase(key);
			}
		}
	}

	void HotkeySystem::LoadStateImpl(nlohmann::json& state)
	{
		for (auto& [key, value] : state.items())
		{
			if (m_CommandHotkeys.contains(static_cast<uint32_t>(std::stoul(key.data()))))
				m_CommandHotkeys[static_cast<uint32_t>(std::stoul(key.data()))].m_Chain = value.get<std::vector<int>>();
		}
	}

	void HotkeySystem::SetBeingModifed(bool being_modified)
	{
		g_HotkeySystem.m_BeingModified = being_modified;
	}
}

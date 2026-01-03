#pragma once
#include "core/settings/IStateSerializer.hpp"

namespace YimMenu
{
	// TODO: this should be called something else
	struct CommandLink
	{
	public:
		std::vector<int> m_Chain{};

		CommandLink() {};
	};

	class HotkeySystem :
	    public IStateSerializer
	{
		std::chrono::system_clock::time_point m_LastHotkeyTriggerTime;
		bool m_BeingModified = false;

	public:
		HotkeySystem();

		std::map<uint32_t, CommandLink> m_CommandHotkeys;
		void RegisterCommands();
		bool ListenAndApply(int& Hotkey, std::vector<int> blacklist = {0});
		std::string GetHotkeyLabel(int hotkey_modifiers);
		void CreateHotkey(std::vector<int>& Hotkey);

		void RunScriptImpl();
		static void RunScript();

		virtual void SaveStateImpl(nlohmann::json& state) override;
		virtual void LoadStateImpl(nlohmann::json& state) override;

		static void SetBeingModifed(bool being_modified);
	};

	inline HotkeySystem g_HotkeySystem;
}
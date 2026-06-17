#pragma once

#include "core/commands/BoolCommand.hpp"
#include "core/commands/Command.hpp"
#include "core/commands/FloatCommand.hpp"
#include "core/commands/IntCommand.hpp"
#include "core/commands/ListCommand.hpp"
#include "core/commands/LoopedCommand.hpp"

namespace YimMenu
{
	class LuaUserInterface;

	class LuaCommand : public Command
	{
		LuaUserInterface* m_Interface;
		int m_OnCall;

	public:
		LuaCommand(LuaUserInterface* iface, std::string name, std::string label, std::string description, int on_call);
		~LuaCommand();

		bool ShouldSaveState() const override { return false; }

	protected:
		void OnCall() override;
	};

	class LuaBoolCommand : public BoolCommand
	{
		LuaUserInterface* m_Interface;
		int m_OnEnable;
		int m_OnDisable;

	public:
		LuaBoolCommand(LuaUserInterface* iface, std::string name, std::string label, std::string description, bool default_value, int on_enable, int on_disable);
		~LuaBoolCommand();

		bool ShouldSaveState() const override { return false; }

	protected:
		void OnEnable() override;
		void OnDisable() override;
	};

	class LuaLoopedCommand : public LoopedCommand
	{
		LuaUserInterface* m_Interface;
		int m_OnTick;
		int m_OnEnable;
		int m_OnDisable;
		bool m_TickRegistered = false;

	public:
		LuaLoopedCommand(LuaUserInterface* iface, std::string name, std::string label, std::string description, int on_tick, int on_enable, int on_disable);
		~LuaLoopedCommand();

		bool ShouldSaveState() const override { return false; }

	protected:
		void OnTick() override {}
		void OnEnable() override;
		void OnDisable() override;
	};

	class LuaIntCommand : public IntCommand
	{
		LuaUserInterface* m_Interface;
		int m_OnChange;

	public:
		LuaIntCommand(LuaUserInterface* iface, std::string name, std::string label, std::string description, std::optional<int> min, std::optional<int> max, int default_value, int on_change);
		~LuaIntCommand();

		bool ShouldSaveState() const override { return false; }

	protected:
		void OnChange() override;
	};

	class LuaFloatCommand : public FloatCommand
	{
		LuaUserInterface* m_Interface;
		int m_OnChange;

	public:
		LuaFloatCommand(LuaUserInterface* iface, std::string name, std::string label, std::string description, std::optional<float> min, std::optional<float> max, float default_value, int on_change);
		~LuaFloatCommand();

		bool ShouldSaveState() const override { return false; }

	protected:
		void OnChange() override;
	};

	class LuaListCommand : public ListCommand
	{
		LuaUserInterface* m_Interface;
		int m_OnChange;

		std::vector<std::string> m_LabelStorage;

	public:
		LuaListCommand(LuaUserInterface* iface, std::string name, std::string label, std::string description, std::vector<std::pair<int, std::string>> entries, int default_value, int on_change);
		~LuaListCommand();

		bool ShouldSaveState() const override { return false; }

	protected:
		void OnChange() override;
	};
}

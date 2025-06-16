#pragma once
#include "Command.hpp"

namespace YimMenu
{
	class BoolCommand : public Command
	{
	protected:
		virtual void OnEnable() {};
		virtual void OnDisable() {};
		virtual void OnCall() override;
		virtual void SaveState(nlohmann::json& value) override;
		virtual void LoadState(nlohmann::json& value) override;

		bool m_State = false;
		bool m_Ready = false;

	public:
		BoolCommand(std::string name, std::string label, std::string description, bool def_value = false);
		bool GetState();
		void SetState(bool state);
		void Initialize();
		void Shutdown();
		// returns true unless there's a pending OnEnable()/OnDisable() call that hasn't run yet
		inline bool IsReady()
		{
			return m_Ready;
		}
	};
}
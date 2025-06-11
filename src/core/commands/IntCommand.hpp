#pragma once
#include "Command.hpp"

namespace YimMenu
{
	class IntCommand : public Command
	{
	protected:
		virtual void OnChange() {};
		virtual void OnCall() override;
		virtual void SaveState(nlohmann::json& value) override;
		virtual void LoadState(nlohmann::json& value) override;

		int m_State = 0;
		std::optional<int> m_Min;
		std::optional<int> m_Max;

	public:
		IntCommand(std::string name, std::string label, std::string description, std::optional<int> min = std::nullopt, std::optional<int> max = std::nullopt, int def_val = 0);
		int GetState();
		void SetState(int state);
		std::optional<int> GetMinimum();
		std::optional<int> GetMaximum();
	};
}
#pragma once
#include "Command.hpp"

namespace YimMenu
{
	class FloatCommand : public Command
	{
	protected:
		virtual void OnChange() {};
		virtual void OnCall() override;
		virtual void SaveState(nlohmann::json& value) override;
		virtual void LoadState(nlohmann::json& value) override;

		float m_State = 0;
		std::optional<float> m_Min;
		std::optional<float> m_Max;

	public:
		FloatCommand(std::string name, std::string label, std::string description, std::optional<float> min = std::nullopt, std::optional<float> max = std::nullopt, float def_val = 0.0f);
		float GetState();
		void SetState(float state);
		std::optional<float> GetMinimum();
		std::optional<float> GetMaximum();
	};
}
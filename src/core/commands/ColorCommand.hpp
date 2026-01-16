#pragma once
#include "Command.hpp"

namespace YimMenu
{
	class ColorCommand : public Command
	{
	protected:
		virtual void OnChange() {};
		virtual void OnCall() override;

		ImVec4 m_State = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

	public:
		ColorCommand(std::string name, std::string label, std::string description, ImVec4 color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
		ImVec4 GetState();
		void SetState(ImVec4 state);
		virtual void SaveState(nlohmann::json& value) override;
		virtual void LoadState(nlohmann::json& value) override;
	};
}
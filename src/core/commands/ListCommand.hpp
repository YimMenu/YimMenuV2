#pragma once
#include "Command.hpp"

namespace YimMenu
{
	class ListCommand : public Command
	{
	protected:
		virtual void OnChange() {};
		virtual void OnCall() override;
		virtual void SaveState(nlohmann::json& value) override;
		virtual void LoadState(nlohmann::json& value) override;

		int m_State = 0;
		std::vector<std::pair<int, const char*>> m_List; // not very efficient but keeps things sorted

	public:
		ListCommand(std::string name, std::string label, std::string description, std::vector<std::pair<int, const char*>> list, int def_val = 0);
		int GetState();
		void SetState(int state);
		void SetList(std::vector<std::pair<int, const char*>> list);
		std::vector<std::pair<int, const char*>>& GetList();
	};
}
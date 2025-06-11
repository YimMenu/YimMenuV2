#pragma once
#include "types/rage/vector.hpp"
#include "Command.hpp"

namespace YimMenu
{
	class Vector3Command : public Command
	{
	protected:
		virtual void OnChange() {};
		virtual void OnCall() override;
		virtual void SaveState(nlohmann::json& value) override;
		virtual void LoadState(nlohmann::json& value) override;

		rage::fvector3 m_State{};

	public:
		Vector3Command(std::string name, std::string label, std::string description, rage::fvector3 def_val = {});
		rage::fvector3 GetState();
		void SetState(const rage::fvector3& state);
	};
}
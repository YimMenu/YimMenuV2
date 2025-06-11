#pragma once
#include "core/commands/Command.hpp"
#include "game/gta/Player.hpp"

namespace YimMenu
{
	class PlayerCommand;
	class PlayerAllCommand : public Command
	{
		PlayerCommand* m_PlayerCommand;

	public:
		PlayerAllCommand(std::string name, std::string label, std::string description, int num_args, PlayerCommand* parent);
		virtual void OnCall() override;
	};

	class PlayerCommand : public Command
	{
		virtual void OnCall() override;
		std::unique_ptr<PlayerAllCommand> m_AllCommand;

	protected:
		virtual void OnCall(Player) = 0;
		virtual void OnCall(const std::vector<Player>&);

	public:
		PlayerCommand(std::string name, std::string label, std::string description, int num_args = 0, bool all_version = true);
		void Call(Player target);
		void Call(const std::vector<Player>& targets);
	};
}
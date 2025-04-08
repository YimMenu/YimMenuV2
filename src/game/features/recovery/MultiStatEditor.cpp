#include "core/commands/Command.hpp"
#include "core/commands/StringCommand.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/gta/Stats.hpp"

namespace YimMenu::Features
{
	
	static StringCommand _StatsToModify{"statstomodify", "Stats to modify", "Placeholder."};

	class MultiStatEditor : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			std::string allStats = _StatsToModify.GetString();
			std::stringstream ss(allStats);
			std::string pair;

			while (std::getline(ss, pair, ';'))
			{
				std::stringstream pairstream(pair);
				std::string stat;
				std::string value;

				if (std::getline(pairstream, stat, ',') && std::getline(pairstream, value))
				{
					stat.erase(remove_if(stat.begin(), stat.end(), isspace), stat.end());
					value.erase(remove_if(value.begin(), value.end(), isspace), value.end());

					if (value == "true" || value == "false")
					{
						bool val = (value == "true");
						Stats::SetBool(stat, val);
					}
					else if (!value.empty() && value.front() == '"' && value.back() == '"')
					{
						std::string val = value.substr(1, value.length() - 2);
						Stats::SetString(stat, val.c_str());
					}
					else if (value.find('.') != std::string::npos)
					{
						float val = std::stof(value);
						Stats::SetFloat(stat, val);
					}
					else
					{
						int val = std::stoi(value);
						Stats::SetInt(stat, val);
					}
				}
			}
			Notifications::Show("MultiStatEditor", "Stats modified successfully.", NotificationType::Success);
		}
	};

	static MultiStatEditor _MultiStatEditor{"multistateditor", "Modifies the stats", "Placeholder."};
}
#include "LogSink.hpp"

#include "LogColor.hpp"

#include <format>

#include "core/util/Wine.hpp"

namespace YimMenu
{
	LogColor LogSink::GetColor(const eLogLevel level)
	{
		switch (level)
		{
		case eLogLevel::VERBOSE: return LogColor::BLUE;
		case eLogLevel::INFO: return LogColor::GREEN;
		case eLogLevel::WARNING: return LogColor::YELLOW;
		case eLogLevel::FATAL: return LogColor::RED;
		}
		return LogColor::WHITE;
	}

	const char* LogSink::GetLevelStr(const eLogLevel level)
	{
		constexpr std::array<const char*, 4> levelStrings = {"DEBUG", "INFO", "WARN", "ERROR"};

		return levelStrings[level];
	}

	std::string LogSink::FormatConsole(const LogMessagePtr msg)
	{
		std::stringstream out;

		static std::optional<bool> simplified = std::nullopt;
		if (!simplified.has_value())
			simplified = InWine();
		if (simplified.value_or(false))
			return FormatFile(msg);

		const auto timestamp = std::format("{0:%H:%M:%S}", msg->Timestamp());
		const auto& location = msg->Location();
		const auto level = msg->Level();
		const auto color = LogSink::GetColor(level);

		const auto file = std::filesystem::path(location.file_name()).filename().string();

		out << "[" << timestamp << "]" << ADD_COLOR_TO_STREAM(color) << "[" << GetLevelStr(level) << "/" << file << ":"
		    << location.line() << "] " << RESET_STREAM_COLOR << msg->Message();

		return out.str();
	}

	std::string LogSink::FormatFile(const LogMessagePtr msg)
	{
		std::stringstream out;

		const auto timestamp = std::format("{0:%H:%M:%S}", msg->Timestamp());
		const auto& location = msg->Location();
		const auto level = msg->Level();
		const auto file = std::filesystem::path(location.file_name()).filename().string();

		out << "[" << timestamp << "]"
		    << "[" << GetLevelStr(level) << "/" << file << ":" << location.line() << "] " << msg->Message();

		return out.str();
	}
}

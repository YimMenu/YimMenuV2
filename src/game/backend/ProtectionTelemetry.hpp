#pragma once

#include <array>
#include <atomic>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <string_view>

namespace YimMenu
{
	class ProtectionTelemetry
	{
	public:
		enum class Event : std::size_t
		{
			MalformedPackedEvents,
			MalformedPackedEvent,
			MalformedPackedReliables,
			MalformedBattlEyeCommand,
			MalformedScriptEvent,
			BlockedKickMessage,
			BlockedBounty,
			BlockedTextLabelSms,
			BlockedCeoKick,
			BlockedInteriorControl,
			Count
		};

		struct Entry
		{
			Event m_Event;
			std::string_view m_Name;
			std::uint64_t m_Count;
			std::optional<std::chrono::seconds> m_LastSeenAgo;
		};

		using Snapshot = std::array<Entry, static_cast<std::size_t>(Event::Count)>;

		static void Increment(Event event);
		static Snapshot GetSnapshot();
		static void Reset();
		static std::chrono::seconds Uptime();

	private:
		ProtectionTelemetry();
		static ProtectionTelemetry& GetInstance();

		std::array<std::atomic_uint64_t, static_cast<std::size_t>(Event::Count)> m_Counters{};
		std::array<std::atomic_int64_t, static_cast<std::size_t>(Event::Count)> m_LastSeenMilliseconds{};
		std::chrono::steady_clock::time_point m_StartedAt;
	};
}

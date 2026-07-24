#include "ProtectionTelemetry.hpp"

namespace YimMenu
{
	namespace
	{
		constexpr std::array<std::string_view, static_cast<std::size_t>(ProtectionTelemetry::Event::Count)> EventNames{
			"Malformed packed-event container",
			"Malformed packed event",
			"Malformed packed-reliables container",
			"Malformed BattlEye command",
			"Malformed script event",
			"Kick message blocked",
			"Bounty blocked",
			"Text-label SMS blocked",
			"Unauthorized CEO kick blocked",
			"Interior control blocked",
		};
	}

	ProtectionTelemetry::ProtectionTelemetry() :
	    m_StartedAt(std::chrono::steady_clock::now())
	{
	}

	ProtectionTelemetry& ProtectionTelemetry::GetInstance()
	{
		static ProtectionTelemetry instance;
		return instance;
	}

	void ProtectionTelemetry::Increment(Event event)
	{
		auto& instance = GetInstance();
		const auto index = static_cast<std::size_t>(event);
		instance.m_Counters[index].fetch_add(1, std::memory_order_relaxed);
		const auto now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
		instance.m_LastSeenMilliseconds[index].store(now, std::memory_order_relaxed);
	}

	ProtectionTelemetry::Snapshot ProtectionTelemetry::GetSnapshot()
	{
		auto& instance = GetInstance();
		Snapshot result{};
		const auto now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
		for (std::size_t i = 0; i < result.size(); ++i)
		{
			const auto last_seen = instance.m_LastSeenMilliseconds[i].load(std::memory_order_relaxed);
			result[i] = {
				static_cast<Event>(i),
				EventNames[i],
				instance.m_Counters[i].load(std::memory_order_relaxed),
				last_seen > 0 ? std::optional{std::chrono::duration_cast<std::chrono::seconds>(std::chrono::milliseconds(now - last_seen))} : std::nullopt,
			};
		}
		return result;
	}

	void ProtectionTelemetry::Reset()
	{
		auto& instance = GetInstance();
		for (auto& counter : instance.m_Counters)
			counter.store(0, std::memory_order_relaxed);
		for (auto& last_seen : instance.m_LastSeenMilliseconds)
			last_seen.store(0, std::memory_order_relaxed);
	}

	std::chrono::seconds ProtectionTelemetry::Uptime()
	{
		return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - GetInstance().m_StartedAt);
	}
}

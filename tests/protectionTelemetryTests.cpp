#include "game/backend/ProtectionTelemetry.hpp"

#include <cstdint>
#include <thread>
#include <vector>

#define CHECK(condition) \
	do \
	{ \
		if (!(condition)) \
			return __LINE__; \
	} while (false)

int main()
{
	using Telemetry = YimMenu::ProtectionTelemetry;
	constexpr auto Event = Telemetry::Event::MalformedPackedEvent;
	constexpr std::uint64_t ThreadCount = 8;
	constexpr std::uint64_t IncrementsPerThread = 1'000;

	Telemetry::Reset();
	std::vector<std::thread> workers;
	workers.reserve(ThreadCount);
	for (std::uint64_t i = 0; i < ThreadCount; ++i)
	{
		workers.emplace_back([] {
			for (std::uint64_t increment = 0; increment < IncrementsPerThread; ++increment)
				Telemetry::Increment(Event);
		});
	}
	for (auto& worker : workers)
		worker.join();

	const auto snapshot = Telemetry::GetSnapshot();
	const auto& entry = snapshot[static_cast<std::size_t>(Event)];
	CHECK(entry.m_Count == ThreadCount * IncrementsPerThread);
	CHECK(entry.m_LastSeenAgo.has_value());
	CHECK(entry.m_LastSeenAgo->count() <= 1);
	CHECK(Telemetry::Uptime().count() >= 0);

	Telemetry::Reset();
	const auto reset_entry = Telemetry::GetSnapshot()[static_cast<std::size_t>(Event)];
	CHECK(reset_entry.m_Count == 0);
	CHECK(!reset_entry.m_LastSeenAgo.has_value());
}

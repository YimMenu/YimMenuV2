#pragma once

#include "AutoDriveShared.hpp"

#include <chrono>
#include <cstdint>
#include <memory>
#include <vector>

namespace YimMenu::Features::AutoDriveInternal
{
	struct HudPoint
	{
		float m_X = 0.0f; // metres to the right of the ego vehicle
		float m_Y = 0.0f; // metres in front of the ego vehicle
	};

	enum class HudEntityKind
	{
		Vehicle,
		Pedestrian,
		TrafficLight,
		Cone,
		Barrier,
		Barrel,
		Bollard,
		Tree,
		Obstacle
	};

	enum class TrafficLightState
	{
		Unknown,
		RedInferred
	};

	enum class HudManeuver
	{
		None,
		LaneChangeLeft,
		LaneChangeRight
	};

	struct HudEntitySnapshot
	{
		std::uint32_t m_TrackId = 0;
		HudEntityKind m_Kind = HudEntityKind::Obstacle;
		TrafficLightState m_TrafficLightState = TrafficLightState::Unknown;
		HudPoint m_Position{};
		HudPoint m_Velocity{};
		HudPoint m_Footprint{1.0f, 1.0f};
		float m_RelativeHeadingRadians = 0.0f;
	};

	struct AutoDriveHudSnapshot
	{
		bool m_Visible = false;
		bool m_Suppressed = false;
		Owner m_Owner = Owner::None;
		RoutePhase m_Phase = RoutePhase::Idle;
		int m_SpeedKph = 0;
		int m_TargetSpeedKph = 0;
		HudManeuver m_Maneuver = HudManeuver::None;
		bool m_RouteReliable = false;
		bool m_RouteCalculating = false;
		bool m_RoutePredicted = false;
		std::vector<HudPoint> m_RoutePoints;
		std::vector<std::vector<HudPoint>> m_LaneBoundaries;
		std::vector<HudEntitySnapshot> m_Entities;
		std::chrono::steady_clock::time_point m_CapturedAt{};
	};

	class AutoDriveHudTelemetry
	{
	public:
		static void Update(SessionToken token, Ped driver, Vehicle vehicle, const RoadDriveStatus& status);
		static void Clear(SessionToken token);
		static std::shared_ptr<const AutoDriveHudSnapshot> GetSnapshot();
		static bool IsEnabled();
	};
}

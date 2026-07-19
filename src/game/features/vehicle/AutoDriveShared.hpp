#pragma once

#include "game/gta/Ped.hpp"

#include <chrono>
#include <cstdint>
#include <functional>
#include <string_view>

namespace YimMenu::Features::AutoDriveInternal
{
	enum class Owner
	{
		None,
		Player,
		Npc
	};

	struct SessionToken
	{
		Owner m_Owner = Owner::None;
		std::uint64_t m_Generation = 0;
	};

	class Coordinator
	{
		Owner m_Owner = Owner::None;
		std::uint64_t m_Generation = 0;
		std::function<void()> m_Cleanup;

		static Coordinator& GetInstance();

		SessionToken ClaimImpl(Owner owner, std::function<void()> cleanup);
		bool OwnsImpl(SessionToken token) const;
		void ReleaseImpl(SessionToken token);

	public:
		static SessionToken Claim(Owner owner, std::function<void()> cleanup);
		static bool Owns(SessionToken token);
		static void Release(SessionToken token);
		static Owner GetOwner();
	};

	enum class RouteResult
	{
		Driving,
		DestinationReached
	};

	enum class NavigationTargetSource
	{
		None,
		UserWaypoint,
		GpsRoute
	};

	enum class RoutePhase
	{
		Idle,
		Navigation,
		TargetLost,
		Wander,
		Arrived
	};

	struct NavigationTarget
	{
		NavigationTargetSource m_Source = NavigationTargetSource::None;
		Blip m_BlipHandle = 0;
		Vector3 m_Position{};
	};

	struct RoadDriveStatus
	{
		RoutePhase m_Phase = RoutePhase::Idle;
		NavigationTargetSource m_TargetSource = NavigationTargetSource::None;
		Vector3 m_Target{};
		Vector3 m_RoadTarget{};
		bool m_HasTask = false;
	};

	class RoadDriveController
	{
		enum class Mode
		{
			Idle,
			Navigation,
			TargetLost,
			Wander,
			Arrived
		};

		static constexpr float target_loss_arrival_distance_squared = 2500.0f;
		static constexpr float arrival_distance_squared = 100.0f;
		static constexpr float arrival_height_threshold = 5.0f;
		static constexpr float arrival_speed_threshold = 1.0f;
		static constexpr auto target_loss_grace_period = std::chrono::seconds(1);
		static constexpr float stopping_range = 8.0f;

		Mode m_Mode = Mode::Idle;
		int m_DriverHandle = 0;
		int m_VehicleHandle = 0;
		int m_LastSpeedKph = -1;
		int m_LastDrivingStyle = -1;
		NavigationTarget m_Target{};
		Vector3 m_RoadTarget{};
		std::chrono::steady_clock::time_point m_TargetLostAt{};
		bool m_HasTask = false;
		bool m_HasResolvedRoadTarget = false;
		bool m_ArrivalLatched = false;
		bool m_IsBringingToHalt = false;

		bool IsNearStoredDestination(Vehicle vehicle, float distanceSquared) const;
		bool IsNearRoadTarget(Vehicle vehicle) const;
		void StopBringingToHalt();
		void AssignVehicle(Ped driver, Vehicle vehicle);
		void StartNavigationTask(Ped driver, Vehicle vehicle, const NavigationTarget& target, std::string_view startMessage);
		void StartWanderTask(Ped driver, Vehicle vehicle, std::string_view startMessage);
		void EnterArrived(Vehicle vehicle);

	public:
		RouteResult Tick(Ped driver, Vehicle vehicle, std::string_view startMessage);
		void ClearTask(bool clearPedTask = true, bool clearVehicleTask = true);
		bool HasTask() const;
		RoadDriveStatus GetStatus() const;
	};

	bool IsSupportedRoadVehicle(Vehicle vehicle);
	bool IsSupportedNpcVehicle(Vehicle vehicle);
	int GetCruiseSpeedKph();
	int GetDrivingStyle();
}

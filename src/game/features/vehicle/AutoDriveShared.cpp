#include "AutoDriveShared.hpp"

#include "core/commands/IntCommand.hpp"
#include "core/commands/ListCommand.hpp"
#include "game/gta/Natives.hpp"
#include "types/blip/BlipSprite.hpp"

#include <array>
#include <cmath>
#include <format>
#include <limits>
#include <string>
#include <vector>

namespace YimMenu::Features::AutoDriveInternal
{
	static constexpr int lawful_driving_style = 786603;
	static constexpr int ignore_lights_driving_style = 2883621;
	// Keep this value stable so existing serialized settings continue to select Aggressive.
	static constexpr int aggressive_driving_style = 1074528293;
	static constexpr int aggressive_driving_flags = 1074529087;
	static constexpr int reckless_driving_style = 1074529086;
	static constexpr float target_move_threshold_squared = 25.0f;

	static IntCommand _AutoDriveSpeed{
	    "autodrivespeed",
	    "Cruise Speed (km/h)",
	    "The target speed used by Auto Drive",
	    20,
	    160,
	    70};

	static std::vector<std::pair<int, const char*>> g_AutoDriveStyles = {
	    {lawful_driving_style, "Lawful"},
	    {ignore_lights_driving_style, "Ignore Traffic Lights"},
	    {aggressive_driving_style, "Aggressive"},
	    {reckless_driving_style, "Reckless (No Vehicle Braking)"}};

	static ListCommand _AutoDriveStyle{
	    "autodrivestyle",
	    "Driving Style",
	    "How Auto Drive behaves around traffic and traffic lights",
	    g_AutoDriveStyles,
	    lawful_driving_style};

	static float DistanceSquared2D(const Vector3& first, const Vector3& second)
	{
		const auto deltaX = first.x - second.x;
		const auto deltaY = first.y - second.y;
		return deltaX * deltaX + deltaY * deltaY;
	}

	static float DistanceSquared2D(const rage::fvector3& first, const Vector3& second)
	{
		const auto deltaX = first.x - second.x;
		const auto deltaY = first.y - second.y;
		return deltaX * deltaX + deltaY * deltaY;
	}

	static float GetCruiseSpeed()
	{
		return GetCruiseSpeedKph() / 3.6f;
	}

	static constexpr int ResolveDrivingStyle(int drivingStyle)
	{
		return drivingStyle == aggressive_driving_style ? aggressive_driving_flags : drivingStyle;
	}

	static const char* GetDrivingStyleName(int drivingStyle)
	{
		for (const auto& [value, name] : g_AutoDriveStyles)
		{
			if (value == drivingStyle)
				return name;
		}

		return "Unknown";
	}

	static bool IsValidLocationName(const char* name)
	{
		return name && name[0] != '\0' && std::string_view(name) != "NULL";
	}

	static std::string GetDestinationName(const Vector3& destination)
	{
		Hash streetHash = 0;
		Hash crossingRoadHash = 0;
		PATH::GET_STREET_NAME_AT_COORD(
		    destination.x,
		    destination.y,
		    destination.z,
		    &streetHash,
		    &crossingRoadHash);

		const auto streetName = HUD::GET_STREET_NAME_FROM_HASH_KEY(streetHash);
		const auto crossingRoadName = HUD::GET_STREET_NAME_FROM_HASH_KEY(crossingRoadHash);
		if (IsValidLocationName(streetName))
		{
			if (IsValidLocationName(crossingRoadName) && std::string_view(streetName) != crossingRoadName)
				return std::format("{} / {}", streetName, crossingRoadName);

			return streetName;
		}

		const auto zoneLabel = ZONE::GET_NAME_OF_ZONE(destination.x, destination.y, destination.z);
		if (IsValidLocationName(zoneLabel))
		{
			const auto zoneName = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(zoneLabel);
			if (IsValidLocationName(zoneName))
				return zoneName;
		}

		return "Waypoint";
	}

	static void ShowStartNotification(std::string_view startMessage, std::string_view destination)
	{
		const auto message = std::format(
		    "{}~n~Style: {}~n~Destination: {}~n~Cruise speed: {} km/h",
		    startMessage,
		    GetDrivingStyleName(GetDrivingStyle()),
		    destination,
		    GetCruiseSpeedKph());

		HUD::SET_TEXT_OUTLINE();
		HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(message.c_str());
		HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(false, false);
	}

	struct NavigationTargetSnapshot
	{
		bool m_HasTrackedTarget = false;
		NavigationTarget m_TrackedTarget{};
		bool m_HasPreferredTarget = false;
		NavigationTarget m_PreferredTarget{};
	};

	static constexpr int GetTargetPriority(NavigationTargetSource source)
	{
		switch (source)
		{
		case NavigationTargetSource::UserWaypoint: return 2;
		case NavigationTargetSource::GpsRoute: return 1;
		default: return 0;
		}
	}

	static bool TryGetUserWaypoint(NavigationTarget& target)
	{
		if (!HUD::IS_WAYPOINT_ACTIVE())
			return false;

		const auto blip = HUD::GET_CLOSEST_BLIP_INFO_ID(HUD::GET_WAYPOINT_BLIP_ENUM_ID());
		if (!HUD::DOES_BLIP_EXIST(blip))
			return false;

		target.m_Source = NavigationTargetSource::UserWaypoint;
		target.m_BlipHandle = blip;
		target.m_Position = HUD::GET_BLIP_COORDS(blip);
		return true;
	}

	static bool IsGpsRouteBlip(Blip blip)
	{
		return HUD::DOES_BLIP_EXIST(blip) && HUD::DOES_BLIP_HAVE_GPS_ROUTE(blip);
	}

	static NavigationTargetSnapshot GetNavigationTargets(
	    const rage::fvector3& vehiclePosition,
	    const NavigationTarget& trackedTarget)
	{
		NavigationTargetSnapshot snapshot;
		NavigationTarget userWaypoint;
		const auto hasUserWaypoint = TryGetUserWaypoint(userWaypoint);

		static constexpr std::array gpsRouteSprites = {
		    BlipSprite::RADAR_LEVEL,
		    BlipSprite::RADAR_HIGHER,
		    BlipSprite::RADAR_LOWER,
		    BlipSprite::RADAR_OBJECTIVE_BLUE,
		    BlipSprite::RADAR_OBJECTIVE_GREEN,
		    BlipSprite::RADAR_OBJECTIVE_RED,
		    BlipSprite::RADAR_OBJECTIVE_YELLOW};

		NavigationTarget closestGpsTarget;
		NavigationTarget replacementGpsTarget;
		NavigationTarget exactGpsTarget;
		float closestGpsDistanceSquared = std::numeric_limits<float>::max();
		float replacementDistanceSquared = std::numeric_limits<float>::max();
		std::size_t closestGpsSpriteIndex = gpsRouteSprites.size();
		std::size_t replacementSpriteIndex = gpsRouteSprites.size();
		bool hasClosestGpsTarget = false;
		bool hasReplacementGpsTarget = false;
		bool hasExactGpsTarget = false;

		for (std::size_t spriteIndex = 0; spriteIndex < gpsRouteSprites.size(); ++spriteIndex)
		{
			const auto sprite = gpsRouteSprites[spriteIndex];
			const auto spriteId = static_cast<int>(sprite);
			for (auto blip = HUD::GET_FIRST_BLIP_INFO_ID(spriteId);
			    HUD::DOES_BLIP_EXIST(blip);
			    blip = HUD::GET_NEXT_BLIP_INFO_ID(spriteId))
			{
				if (!IsGpsRouteBlip(blip))
					continue;

				NavigationTarget candidate{
				    NavigationTargetSource::GpsRoute,
				    blip,
				    HUD::GET_BLIP_COORDS(blip)};
				const auto vehicleDistanceSquared = DistanceSquared2D(vehiclePosition, candidate.m_Position);
				if (!hasClosestGpsTarget
				    || vehicleDistanceSquared < closestGpsDistanceSquared
				    || (vehicleDistanceSquared == closestGpsDistanceSquared
				        && spriteIndex == closestGpsSpriteIndex
				        && candidate.m_BlipHandle < closestGpsTarget.m_BlipHandle))
				{
					closestGpsTarget = candidate;
					closestGpsDistanceSquared = vehicleDistanceSquared;
					closestGpsSpriteIndex = spriteIndex;
					hasClosestGpsTarget = true;
				}

				if (trackedTarget.m_Source != NavigationTargetSource::GpsRoute)
					continue;

				if (candidate.m_BlipHandle == trackedTarget.m_BlipHandle)
				{
					exactGpsTarget = candidate;
					hasExactGpsTarget = true;
					continue;
				}

				const auto replacementDistance = DistanceSquared2D(
				    trackedTarget.m_Position,
				    candidate.m_Position);
				if (replacementDistance <= target_move_threshold_squared
				    && (!hasReplacementGpsTarget
				        || replacementDistance < replacementDistanceSquared
				        || (replacementDistance == replacementDistanceSquared
				            && spriteIndex == replacementSpriteIndex
				            && candidate.m_BlipHandle < replacementGpsTarget.m_BlipHandle)))
				{
					replacementGpsTarget = candidate;
					replacementDistanceSquared = replacementDistance;
					replacementSpriteIndex = spriteIndex;
					hasReplacementGpsTarget = true;
				}
			}
		}

		if (trackedTarget.m_Source == NavigationTargetSource::UserWaypoint && hasUserWaypoint)
		{
			snapshot.m_HasTrackedTarget = true;
			snapshot.m_TrackedTarget = userWaypoint;
		}
		else if (trackedTarget.m_Source == NavigationTargetSource::GpsRoute)
		{
			if (hasExactGpsTarget)
			{
				snapshot.m_HasTrackedTarget = true;
				snapshot.m_TrackedTarget = exactGpsTarget;
			}
			else if (hasReplacementGpsTarget)
			{
				snapshot.m_HasTrackedTarget = true;
				snapshot.m_TrackedTarget = replacementGpsTarget;
			}
		}

		if (hasUserWaypoint)
		{
			snapshot.m_HasPreferredTarget = true;
			snapshot.m_PreferredTarget = userWaypoint;
		}
		else if (trackedTarget.m_Source == NavigationTargetSource::GpsRoute
		    && snapshot.m_HasTrackedTarget)
		{
			snapshot.m_HasPreferredTarget = true;
			snapshot.m_PreferredTarget = snapshot.m_TrackedTarget;
		}
		else if (hasClosestGpsTarget)
		{
			snapshot.m_HasPreferredTarget = true;
			snapshot.m_PreferredTarget = closestGpsTarget;
		}

		return snapshot;
	}

	static bool TryResolveRoadTarget(const Vector3& waypoint, Vector3& roadTarget)
	{
		roadTarget = waypoint;
		float heading = 0.0f;
		return PATH::GET_CLOSEST_VEHICLE_NODE_WITH_HEADING(
		    waypoint.x,
		    waypoint.y,
		    waypoint.z,
		    &roadTarget,
		    &heading,
		    1,
		    3.0f,
		    0.0f);
	}

	Coordinator& Coordinator::GetInstance()
	{
		static Coordinator instance;
		return instance;
	}

	SessionToken Coordinator::ClaimImpl(Owner owner, std::function<void()> cleanup)
	{
		if (m_Cleanup)
		{
			auto previousCleanup = std::move(m_Cleanup);
			m_Cleanup = {};
			previousCleanup();
		}

		m_Owner = owner;
		m_Cleanup = std::move(cleanup);
		return {owner, ++m_Generation};
	}

	bool Coordinator::OwnsImpl(SessionToken token) const
	{
		return token.m_Owner != Owner::None
		    && token.m_Owner == m_Owner
		    && token.m_Generation == m_Generation;
	}

	void Coordinator::ReleaseImpl(SessionToken token)
	{
		if (!OwnsImpl(token))
			return;

		auto cleanup = std::move(m_Cleanup);
		m_Cleanup = {};
		m_Owner = Owner::None;
		++m_Generation;
		if (cleanup)
			cleanup();
	}

	SessionToken Coordinator::Claim(Owner owner, std::function<void()> cleanup)
	{
		return GetInstance().ClaimImpl(owner, std::move(cleanup));
	}

	bool Coordinator::Owns(SessionToken token)
	{
		return GetInstance().OwnsImpl(token);
	}

	void Coordinator::Release(SessionToken token)
	{
		GetInstance().ReleaseImpl(token);
	}

	Owner Coordinator::GetOwner()
	{
		return GetInstance().m_Owner;
	}

	bool RoadDriveController::IsNearStoredDestination(Vehicle vehicle, float distanceSquared) const
	{
		const auto position = vehicle.GetPosition();
		return DistanceSquared2D(position, m_Target.m_Position) <= distanceSquared
		    || DistanceSquared2D(position, m_RoadTarget) <= distanceSquared;
	}

	bool RoadDriveController::IsNearRoadTarget(Vehicle vehicle) const
	{
		const auto position = vehicle.GetPosition();
		if (DistanceSquared2D(position, m_RoadTarget) > arrival_distance_squared)
			return false;

		return !m_HasResolvedRoadTarget
		    || std::abs(position.z - m_RoadTarget.z) <= arrival_height_threshold;
	}

	void RoadDriveController::StopBringingToHalt()
	{
		if (!m_IsBringingToHalt)
			return;

		if (m_VehicleHandle && ENTITY::DOES_ENTITY_EXIST(m_VehicleHandle))
			VEHICLE::STOP_BRINGING_VEHICLE_TO_HALT(m_VehicleHandle);

		m_IsBringingToHalt = false;
	}

	void RoadDriveController::ClearTask(bool clearPedTask, bool clearVehicleTask)
	{
		StopBringingToHalt();

		if (m_HasTask && clearPedTask && m_DriverHandle && ENTITY::DOES_ENTITY_EXIST(m_DriverHandle))
		{
			TASK::CLEAR_PED_TASKS(m_DriverHandle);
			PED::SET_PED_KEEP_TASK(m_DriverHandle, false);
		}

		if (m_HasTask && clearVehicleTask && m_VehicleHandle && ENTITY::DOES_ENTITY_EXIST(m_VehicleHandle))
			TASK::CLEAR_PRIMARY_VEHICLE_TASK(m_VehicleHandle);

		m_Mode = Mode::Idle;
		m_DriverHandle = 0;
		m_VehicleHandle = 0;
		m_LastSpeedKph = -1;
		m_LastDrivingStyle = -1;
		m_Target = {};
		m_RoadTarget = {};
		m_TargetLostAt = {};
		m_HasTask = false;
		m_HasResolvedRoadTarget = false;
		m_ArrivalLatched = false;
		m_IsBringingToHalt = false;
	}

	bool RoadDriveController::HasTask() const
	{
		return m_HasTask;
	}

	RoadDriveStatus RoadDriveController::GetStatus() const
	{
		RoutePhase phase = RoutePhase::Idle;
		switch (m_Mode)
		{
		case Mode::Navigation: phase = RoutePhase::Navigation; break;
		case Mode::TargetLost: phase = RoutePhase::TargetLost; break;
		case Mode::Wander: phase = RoutePhase::Wander; break;
		case Mode::Arrived: phase = RoutePhase::Arrived; break;
		default: break;
		}

		return {
		    phase,
		    m_Target.m_Source,
		    m_Target.m_Position,
		    m_RoadTarget,
		    m_HasTask};
	}

	void RoadDriveController::AssignVehicle(Ped driver, Vehicle vehicle)
	{
		m_DriverHandle = driver.GetHandle();
		m_VehicleHandle = vehicle.GetHandle();
	}

	void RoadDriveController::StartNavigationTask(
	    Ped driver,
	    Vehicle vehicle,
	    const NavigationTarget& target,
	    std::string_view startMessage)
	{
		const auto isInitialTask = !m_HasTask;
		StopBringingToHalt();
		AssignVehicle(driver, vehicle);
		m_Target = target;
		m_HasResolvedRoadTarget = TryResolveRoadTarget(target.m_Position, m_RoadTarget);
		m_TargetLostAt = {};
		m_ArrivalLatched = false;
		m_LastSpeedKph = GetCruiseSpeedKph();
		m_LastDrivingStyle = GetDrivingStyle();

		PED::SET_PED_KEEP_TASK(m_DriverHandle, true);
		TASK::TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(
		    m_DriverHandle,
		    m_VehicleHandle,
		    m_RoadTarget.x,
		    m_RoadTarget.y,
		    m_RoadTarget.z,
		    GetCruiseSpeed(),
		    ResolveDrivingStyle(m_LastDrivingStyle),
		    stopping_range);

		m_Mode = Mode::Navigation;
		m_HasTask = true;
		if (isInitialTask)
			ShowStartNotification(startMessage, GetDestinationName(target.m_Position));
	}

	void RoadDriveController::StartWanderTask(Ped driver, Vehicle vehicle, std::string_view startMessage)
	{
		const auto isInitialTask = !m_HasTask;
		StopBringingToHalt();
		AssignVehicle(driver, vehicle);
		m_Target = {};
		m_RoadTarget = {};
		m_TargetLostAt = {};
		m_ArrivalLatched = false;
		m_HasResolvedRoadTarget = false;
		m_LastSpeedKph = GetCruiseSpeedKph();
		m_LastDrivingStyle = GetDrivingStyle();

		PED::SET_PED_KEEP_TASK(m_DriverHandle, true);
		TASK::TASK_VEHICLE_DRIVE_WANDER(
		    m_DriverHandle,
		    m_VehicleHandle,
		    GetCruiseSpeed(),
		    ResolveDrivingStyle(m_LastDrivingStyle));

		m_Mode = Mode::Wander;
		m_HasTask = true;
		if (isInitialTask)
			ShowStartNotification(startMessage, "Roaming");
	}

	void RoadDriveController::EnterArrived(Vehicle vehicle)
	{
		if (m_Mode == Mode::Arrived)
			return;

		m_Mode = Mode::Arrived;
		TASK::SET_DRIVE_TASK_CRUISE_SPEED(m_DriverHandle, 0.0f);
		vehicle.BringToHalt(5.0f, 1);
		m_IsBringingToHalt = true;
	}

	RouteResult RoadDriveController::Tick(Ped driver, Vehicle vehicle, std::string_view startMessage)
	{
		if (m_HasTask && (m_DriverHandle != driver.GetHandle() || m_VehicleHandle != vehicle.GetHandle()))
			ClearTask();

		const auto speedChanged = m_LastSpeedKph != GetCruiseSpeedKph();
		const auto styleChanged = m_LastDrivingStyle != GetDrivingStyle();
		auto targets = GetNavigationTargets(vehicle.GetPosition(), m_Target);
		const auto hasStoredNavigationTask = m_Mode == Mode::Navigation
		    || m_Mode == Mode::TargetLost
		    || m_Mode == Mode::Arrived;

		if (hasStoredNavigationTask
		    && targets.m_HasPreferredTarget
		    && GetTargetPriority(targets.m_PreferredTarget.m_Source) > GetTargetPriority(m_Target.m_Source))
		{
			if (m_Mode == Mode::Arrived
			    || DistanceSquared2D(m_Target.m_Position, targets.m_PreferredTarget.m_Position)
			        > target_move_threshold_squared)
			{
				StartNavigationTask(driver, vehicle, targets.m_PreferredTarget, startMessage);
				return RouteResult::Driving;
			}

			m_Target.m_Source = targets.m_PreferredTarget.m_Source;
			m_Target.m_BlipHandle = targets.m_PreferredTarget.m_BlipHandle;
			targets.m_HasTrackedTarget = true;
			targets.m_TrackedTarget = targets.m_PreferredTarget;
		}

		if (hasStoredNavigationTask
		    && targets.m_HasTrackedTarget
		    && targets.m_TrackedTarget.m_Source == m_Target.m_Source)
		{
			m_Target.m_BlipHandle = targets.m_TrackedTarget.m_BlipHandle;
			if (DistanceSquared2D(m_Target.m_Position, targets.m_TrackedTarget.m_Position)
			    > target_move_threshold_squared)
			{
				StartNavigationTask(driver, vehicle, targets.m_TrackedTarget, startMessage);
				return RouteResult::Driving;
			}
		}

		if (m_Mode == Mode::Arrived)
		{
			m_LastSpeedKph = GetCruiseSpeedKph();
			m_LastDrivingStyle = GetDrivingStyle();
			if (vehicle.GetSpeed() <= arrival_speed_threshold
			    || VEHICLE::IS_VEHICLE_STOPPED(vehicle.GetHandle()))
				return RouteResult::DestinationReached;

			return RouteResult::Driving;
		}

		if ((m_Mode == Mode::Navigation || m_Mode == Mode::TargetLost)
		    && IsNearRoadTarget(vehicle))
		{
			m_LastSpeedKph = GetCruiseSpeedKph();
			m_LastDrivingStyle = GetDrivingStyle();
			EnterArrived(vehicle);
			if (vehicle.GetSpeed() <= arrival_speed_threshold
			    || VEHICLE::IS_VEHICLE_STOPPED(vehicle.GetHandle()))
				return RouteResult::DestinationReached;

			return RouteResult::Driving;
		}

		if (!targets.m_HasTrackedTarget && m_Mode == Mode::Navigation)
		{
			if (IsNearStoredDestination(vehicle, target_loss_arrival_distance_squared))
			{
				m_Mode = Mode::TargetLost;
				m_TargetLostAt = std::chrono::steady_clock::now();
				m_ArrivalLatched = true;
			}
			else if (targets.m_HasPreferredTarget)
			{
				StartNavigationTask(driver, vehicle, targets.m_PreferredTarget, startMessage);
				return RouteResult::Driving;
			}
			else
			{
				m_Mode = Mode::TargetLost;
				m_TargetLostAt = std::chrono::steady_clock::now();
				m_ArrivalLatched = false;
			}
		}

		if (m_Mode == Mode::TargetLost)
		{
			if (targets.m_HasTrackedTarget)
			{
				m_Mode = Mode::Navigation;
				m_TargetLostAt = {};
				m_ArrivalLatched = false;
			}
			else
			{
				if (!m_ArrivalLatched && targets.m_HasPreferredTarget)
				{
					StartNavigationTask(driver, vehicle, targets.m_PreferredTarget, startMessage);
					return RouteResult::Driving;
				}

				if (!m_ArrivalLatched
				    && std::chrono::steady_clock::now() - m_TargetLostAt >= target_loss_grace_period)
				{
					StartWanderTask(driver, vehicle, startMessage);
					return RouteResult::Driving;
				}

				if (speedChanged)
				{
					TASK::SET_DRIVE_TASK_CRUISE_SPEED(m_DriverHandle, GetCruiseSpeed());
					m_LastSpeedKph = GetCruiseSpeedKph();
				}

				if (styleChanged)
				{
					m_LastDrivingStyle = GetDrivingStyle();
					TASK::SET_DRIVE_TASK_DRIVING_STYLE(
					    m_DriverHandle,
					    ResolveDrivingStyle(m_LastDrivingStyle));
				}

				return RouteResult::Driving;
			}
		}

		if (targets.m_HasPreferredTarget)
		{
			const auto targetChanged = m_Mode == Mode::Idle || m_Mode == Mode::Wander;
			if (targetChanged)
			{
				StartNavigationTask(driver, vehicle, targets.m_PreferredTarget, startMessage);
				return RouteResult::Driving;
			}

			if (styleChanged && m_Mode == Mode::Navigation)
			{
				StartNavigationTask(
				    driver,
				    vehicle,
				    targets.m_HasTrackedTarget ? targets.m_TrackedTarget : targets.m_PreferredTarget,
				    startMessage);
				return RouteResult::Driving;
			}

			if (speedChanged && m_HasTask)
			{
				TASK::SET_DRIVE_TASK_CRUISE_SPEED(m_DriverHandle, GetCruiseSpeed());
				m_LastSpeedKph = GetCruiseSpeedKph();
			}

			return RouteResult::Driving;
		}

		if (m_Mode != Mode::Wander || styleChanged)
		{
			StartWanderTask(driver, vehicle, startMessage);
			return RouteResult::Driving;
		}

		if (speedChanged)
		{
			TASK::SET_DRIVE_TASK_CRUISE_SPEED(m_DriverHandle, GetCruiseSpeed());
			m_LastSpeedKph = GetCruiseSpeedKph();
		}

		return RouteResult::Driving;
	}

	bool IsSupportedRoadVehicle(Vehicle vehicle)
	{
		const auto model = ENTITY::GET_ENTITY_MODEL(vehicle.GetHandle());
		return VEHICLE::IS_THIS_MODEL_A_CAR(model)
		    || VEHICLE::IS_THIS_MODEL_A_BIKE(model)
		    || VEHICLE::IS_THIS_MODEL_A_BICYCLE(model)
		    || VEHICLE::IS_THIS_MODEL_A_QUADBIKE(model);
	}

	bool IsSupportedNpcVehicle(Vehicle vehicle)
	{
		return VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(vehicle.GetHandle()));
	}

	int GetCruiseSpeedKph()
	{
		return _AutoDriveSpeed.GetState();
	}

	int GetDrivingStyle()
	{
		return _AutoDriveStyle.GetState();
	}
}

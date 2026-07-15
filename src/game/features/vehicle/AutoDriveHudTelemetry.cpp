#include "AutoDriveHudTelemetry.hpp"

#include "core/commands/BoolCommand.hpp"
#include "core/util/Joaat.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/Pools.hpp"

#include <algorithm>
#include <array>
#include <atomic>
#include <cmath>
#include <limits>
#include <memory>
#include <unordered_map>

namespace YimMenu::Features::AutoDriveInternal
{
	using namespace std::chrono_literals;

	static BoolCommand _AutoDriveHud{
	    "autodrivehud",
	    "Auto Drive HUD",
	    "Shows a Tesla-style road and traffic visualization while Auto Drive is active",
	    true};

	namespace
	{
		constexpr float kForwardRange = 90.0f;
		constexpr float kRearRange = 30.0f;
		constexpr float kLateralRange = 45.0f;
		constexpr float kVerticalRange = 12.0f;
		constexpr float kLaneWidth = 3.5f;
		constexpr float kPi = 3.14159265358979323846f;

		constexpr std::array kTrafficLights = {
		    "prop_traffic_01a"_J, "prop_traffic_01b"_J, "prop_traffic_01d"_J,
		    "prop_traffic_02a"_J, "prop_traffic_02b"_J, "prop_traffic_03a"_J,
		    "prop_traffic_03b"_J, "prop_traffic_lightset_01"_J};
		constexpr std::array kCones = {
		    "prop_roadcone01a"_J, "prop_roadcone01b"_J, "prop_roadcone01c"_J,
		    "prop_roadcone02a"_J, "prop_roadcone02b"_J, "prop_roadcone02c"_J,
		    "prop_mp_cone_01"_J, "prop_mp_cone_02"_J};
		constexpr std::array kBarriers = {
		    "prop_barrier_work01a"_J, "prop_barrier_work01b"_J, "prop_barrier_work01c"_J,
		    "prop_barrier_work02a"_J, "prop_barrier_work04a"_J, "prop_barrier_work05"_J,
		    "prop_mp_barrier_01"_J, "prop_mp_barrier_02"_J, "prop_road_memorial_01"_J};
		constexpr std::array kBarrels = {
		    "prop_barrel_01a"_J, "prop_barrel_02a"_J, "prop_barrel_02b"_J,
		    "prop_barrel_03a"_J, "prop_barrel_exp_01a"_J, "prop_traffic_barrel_01"_J};
		constexpr std::array kBollards = {
		    "prop_bollard_01a"_J, "prop_bollard_01b"_J, "prop_bollard_01c"_J,
		    "prop_bollard_03a"_J, "prop_bollard_04"_J, "prop_bollard_05"_J};
		constexpr std::array kTrees = {
		    "prop_tree_birch_01"_J, "prop_tree_birch_02"_J, "prop_tree_cedar_02"_J,
		    "prop_tree_cedar_03"_J, "prop_tree_cedar_04"_J, "prop_tree_cedar_s_01"_J,
		    "prop_tree_cypress_01"_J, "prop_tree_eng_oak_01"_J, "prop_tree_eucalip_01"_J,
		    "prop_tree_fallen_01"_J, "prop_tree_jacada_01"_J, "prop_tree_jacada_02"_J,
		    "prop_tree_lficus_02"_J, "prop_tree_lficus_03"_J, "prop_tree_lficus_05"_J,
		    "prop_tree_maple_02"_J, "prop_tree_mquite_01"_J, "prop_tree_oak_01"_J,
		    "prop_tree_olive_01"_J, "prop_tree_pine_01"_J, "prop_tree_pine_02"_J,
		    "prop_tree_stump_01"_J, "prop_tree_sycamore_01"_J, "prop_tree_willow_01"_J};

		template<std::size_t N>
		bool Contains(const std::array<Hash, N>& values, Hash model)
		{
			return std::find(values.begin(), values.end(), model) != values.end();
		}

		float Length2D(float x, float y)
		{
			return std::sqrt(x * x + y * y);
		}

		float NormalizeRadians(float value)
		{
			while (value > kPi)
				value -= 2.0f * kPi;
			while (value < -kPi)
				value += 2.0f * kPi;
			return value;
		}

		bool IsFinite(const Vector3& value)
		{
			return std::isfinite(value.x) && std::isfinite(value.y) && std::isfinite(value.z);
		}

		bool SameToken(SessionToken first, SessionToken second)
		{
			return first.m_Owner == second.m_Owner && first.m_Generation == second.m_Generation;
		}

		struct Basis
		{
			Vector3 m_Position{};
			Vector3 m_Forward{};
			Vector3 m_Right{};
			float m_HeadingRadians = 0.0f;
		};

		HudPoint ToLocal(const Basis& basis, const Vector3& position)
		{
			const auto dx = position.x - basis.m_Position.x;
			const auto dy = position.y - basis.m_Position.y;
			return {
			    dx * basis.m_Right.x + dy * basis.m_Right.y,
			    dx * basis.m_Forward.x + dy * basis.m_Forward.y};
		}

		HudPoint VectorToLocal(const Basis& basis, const Vector3& vector)
		{
			return {
			    vector.x * basis.m_Right.x + vector.y * basis.m_Right.y,
			    vector.x * basis.m_Forward.x + vector.y * basis.m_Forward.y};
		}

		Vector3 OffsetWorld(const Vector3& origin, const Vector3& forward, const Vector3& right, float along, float across)
		{
			return {
			    origin.x + forward.x * along + right.x * across,
			    origin.y + forward.y * along + right.y * across,
			    origin.z};
		}

		bool WithinBroadRange(const Vector3& ego, const rage::fvector3& position)
		{
			const auto dx = position.x - ego.x;
			const auto dy = position.y - ego.y;
			return dx * dx + dy * dy <= 120.0f * 120.0f && std::abs(position.z - ego.z) <= kVerticalRange;
		}

		HudEntityKind ClassifyObject(Hash model)
		{
			if (Contains(kTrafficLights, model)) return HudEntityKind::TrafficLight;
			if (Contains(kCones, model)) return HudEntityKind::Cone;
			if (Contains(kBarriers, model)) return HudEntityKind::Barrier;
			if (Contains(kBarrels, model)) return HudEntityKind::Barrel;
			if (Contains(kBollards, model)) return HudEntityKind::Bollard;
			if (Contains(kTrees, model)) return HudEntityKind::Tree;
			return HudEntityKind::Obstacle;
		}

		struct WorldEntity
		{
			std::uint32_t m_TrackId = 0;
			HudEntityKind m_Kind = HudEntityKind::Obstacle;
			Vector3 m_Position{};
			Vector3 m_Velocity{};
			HudPoint m_Footprint{1.0f, 1.0f};
			float m_HeadingRadians = 0.0f;
		};

		struct RoadCache
		{
			bool m_Valid = false;
			bool m_Stable = false;
			Vector3 m_Center{};
			Vector3 m_Tangent{};
			Vector3 m_Right{};
			std::vector<float> m_LaneCenters;
			std::vector<std::vector<Vector3>> m_Boundaries;
		};

		struct RouteCache
		{
			bool m_Reliable = false;
			bool m_Calculating = false;
			bool m_Predicted = false;
			std::vector<Vector3> m_Points;
		};

		struct LaneChangeState
		{
			HudManeuver m_Active = HudManeuver::None;
			std::chrono::steady_clock::time_point m_LastSample{};
			std::chrono::steady_clock::time_point m_CandidateSince{};
			std::chrono::steady_clock::time_point m_ActiveSince{};
			std::chrono::steady_clock::time_point m_StableSince{};
			float m_LastOffset = 0.0f;
			float m_CandidateStart = 0.0f;
			float m_FilteredVelocity = 0.0f;
			int m_CandidateDirection = 0;
		};

		class TelemetryService
		{
			std::atomic<std::shared_ptr<const AutoDriveHudSnapshot>> m_Published;
			SessionToken m_ActiveToken{};
			std::vector<WorldEntity> m_Vehicles;
			std::vector<WorldEntity> m_Peds;
			std::vector<WorldEntity> m_Objects;
			RoadCache m_Road;
			RouteCache m_Route;
			LaneChangeState m_LaneChange;
			std::unordered_map<Hash, HudPoint> m_DimensionCache;
			std::chrono::steady_clock::time_point m_LastPublish{};
			std::chrono::steady_clock::time_point m_LastVehiclePedScan{};
			std::chrono::steady_clock::time_point m_LastObjectScan{};
			std::chrono::steady_clock::time_point m_LastRoadScan{};
			std::chrono::steady_clock::time_point m_LastRouteScan{};
			std::chrono::steady_clock::time_point m_LastVehicleSuccess{};
			std::chrono::steady_clock::time_point m_LastPedSuccess{};
			std::chrono::steady_clock::time_point m_LastObjectSuccess{};
			bool m_VehicleScanHealthy = false;
			bool m_PedScanHealthy = false;
			bool m_ObjectScanHealthy = false;

			HudPoint GetFootprint(Hash model, HudEntityKind kind)
			{
				if (const auto found = m_DimensionCache.find(model); found != m_DimensionCache.end())
					return found->second;

				Vector3 minimum{};
				Vector3 maximum{};
				MISC::GET_MODEL_DIMENSIONS(model, &minimum, &maximum);
				auto width = std::abs(maximum.x - minimum.x);
				auto length = std::abs(maximum.y - minimum.y);
				if (!std::isfinite(width) || width < 0.1f)
					width = kind == HudEntityKind::Pedestrian ? 0.7f : 1.0f;
				if (!std::isfinite(length) || length < 0.1f)
					length = kind == HudEntityKind::Pedestrian ? 0.7f : 1.0f;

				HudPoint result{std::clamp(width, 0.35f, 8.0f), std::clamp(length, 0.35f, 16.0f)};
				m_DimensionCache.emplace(model, result);
				return result;
			}

			static Basis GetBasis(Vehicle vehicle)
			{
				const auto position = vehicle.GetPosition();
				auto forward = ENTITY::GET_ENTITY_FORWARD_VECTOR(vehicle.GetHandle());
				const auto magnitude = Length2D(forward.x, forward.y);
				if (magnitude > 0.001f)
				{
					forward.x /= magnitude;
					forward.y /= magnitude;
				}
				else
				{
					forward = {0.0f, 1.0f, 0.0f};
				}

				return {
				    {position.x, position.y, position.z},
				    forward,
				    {forward.y, -forward.x, 0.0f},
				    std::atan2(-forward.x, forward.y)};
			}

			void ResetForToken(SessionToken token)
			{
				m_ActiveToken = token;
				m_Vehicles.clear();
				m_Peds.clear();
				m_Objects.clear();
				m_Road = {};
				m_Route = {};
				m_LaneChange = {};
				m_LastPublish = {};
				m_LastVehiclePedScan = {};
				m_LastObjectScan = {};
				m_LastRoadScan = {};
				m_LastRouteScan = {};
				m_LastVehicleSuccess = {};
				m_LastPedSuccess = {};
				m_LastObjectSuccess = {};
				m_VehicleScanHealthy = false;
				m_PedScanHealthy = false;
				m_ObjectScanHealthy = false;
			}

			void ScanVehiclesAndPeds(const Basis& basis, Vehicle egoVehicle, std::chrono::steady_clock::time_point now)
			{
				std::vector<WorldEntity> vehicles;
				if (auto pool = GetVehiclePool())
				{
					vehicles.reserve(std::min<std::uint32_t>(pool->m_Size, 96));
					for (auto vehicle : Pools::GetVehicles())
					{
						const auto position = vehicle.GetPosition();
						if (!WithinBroadRange(basis.m_Position, position))
							continue;
						const auto handle = vehicle.GetHandle();
						if (!handle || handle == egoVehicle.GetHandle() || !ENTITY::DOES_ENTITY_EXIST(handle))
							continue;
						const auto model = ENTITY::GET_ENTITY_MODEL(handle);
						const auto velocity = ENTITY::GET_ENTITY_VELOCITY(handle);
						vehicles.push_back({
						    static_cast<std::uint32_t>(handle), HudEntityKind::Vehicle,
						    {position.x, position.y, position.z}, velocity,
						    GetFootprint(model, HudEntityKind::Vehicle),
						    ENTITY::GET_ENTITY_HEADING(handle) * kPi / 180.0f});
					}
					m_Vehicles = std::move(vehicles);
					m_LastVehicleSuccess = now;
					m_VehicleScanHealthy = true;
				}
				else
					m_VehicleScanHealthy = false;

				std::vector<WorldEntity> peds;
				if (auto pool = GetPedPool())
				{
					peds.reserve(std::min<std::uint32_t>(pool->m_Size, 80));
					for (auto ped : Pools::GetPeds())
					{
						const auto position = ped.GetPosition();
						if (!WithinBroadRange(basis.m_Position, position))
							continue;
						const auto handle = ped.GetHandle();
						if (!handle || !ENTITY::DOES_ENTITY_EXIST(handle) || PED::IS_PED_A_PLAYER(handle)
						    || ENTITY::IS_ENTITY_DEAD(handle, false) || !PED::IS_PED_HUMAN(handle)
						    || PED::IS_PED_IN_ANY_VEHICLE(handle, false))
							continue;
						const auto model = ENTITY::GET_ENTITY_MODEL(handle);
						peds.push_back({
						    static_cast<std::uint32_t>(handle), HudEntityKind::Pedestrian,
						    {position.x, position.y, position.z}, ENTITY::GET_ENTITY_VELOCITY(handle),
						    GetFootprint(model, HudEntityKind::Pedestrian),
						    ENTITY::GET_ENTITY_HEADING(handle) * kPi / 180.0f});
					}
					m_Peds = std::move(peds);
					m_LastPedSuccess = now;
					m_PedScanHealthy = true;
				}
				else
					m_PedScanHealthy = false;
			}

			void ScanObjects(const Basis& basis, std::chrono::steady_clock::time_point now)
			{
				auto pool = GetObjectPool();
				if (!pool)
				{
					m_ObjectScanHealthy = false;
					return;
				}

				std::vector<WorldEntity> objects;
				objects.reserve(std::min<std::uint32_t>(pool->m_Size, 160));
				for (auto object : Pools::GetObjects())
				{
					const auto position = object.GetPosition();
					if (!WithinBroadRange(basis.m_Position, position))
						continue;
					const auto handle = object.GetHandle();
					if (!handle || !ENTITY::DOES_ENTITY_EXIST(handle))
						continue;

					const auto model = ENTITY::GET_ENTITY_MODEL(handle);
					const auto kind = ClassifyObject(model);
					const auto velocity = ENTITY::GET_ENTITY_VELOCITY(handle);
					if (kind == HudEntityKind::Obstacle)
					{
						const auto local = ToLocal(basis, {position.x, position.y, position.z});
						const auto moving = Length2D(velocity.x, velocity.y) > 0.25f;
						const auto close = Length2D(local.m_X, local.m_Y) < 18.0f;
						const auto inCorridor = local.m_Y > -5.0f && local.m_Y < 50.0f && std::abs(local.m_X) < 7.0f;
						if ((!moving && !close && !inCorridor) || ENTITY::GET_ENTITY_COLLISION_DISABLED(handle))
							continue;
					}

					objects.push_back({
					    static_cast<std::uint32_t>(handle), kind,
					    {position.x, position.y, position.z}, velocity,
					    GetFootprint(model, kind),
					    ENTITY::GET_ENTITY_HEADING(handle) * kPi / 180.0f});
				}
				m_Objects = std::move(objects);
				m_LastObjectSuccess = now;
				m_ObjectScanHealthy = true;
			}

			void ExpireFailedScans(std::chrono::steady_clock::time_point now)
			{
				if (!m_VehicleScanHealthy && m_LastVehicleSuccess != std::chrono::steady_clock::time_point{} && now - m_LastVehicleSuccess > 500ms)
					m_Vehicles.clear();
				if (!m_PedScanHealthy && m_LastPedSuccess != std::chrono::steady_clock::time_point{} && now - m_LastPedSuccess > 500ms)
					m_Peds.clear();
				if (!m_ObjectScanHealthy && m_LastObjectSuccess != std::chrono::steady_clock::time_point{} && now - m_LastObjectSuccess > 500ms)
					m_Objects.clear();
			}

			void RefreshRoad(const Basis& basis)
			{
				Vector3 first{};
				Vector3 second{};
				int lanesForward = 0;
				int lanesBackward = 0;
				float medianWidth = 0.0f;
				if (!PATH::GET_CLOSEST_ROAD(
				        basis.m_Position.x, basis.m_Position.y, basis.m_Position.z,
				        1.0f, 1, &first, &second,
				        &lanesForward, &lanesBackward, &medianWidth, false)
				    || !IsFinite(first) || !IsFinite(second))
				{
					m_Road = {};
					return;
				}

				auto tx = second.x - first.x;
				auto ty = second.y - first.y;
				const auto length = Length2D(tx, ty);
				if (length < 2.0f)
				{
					m_Road = {};
					return;
				}
				tx /= length;
				ty /= length;
				if (tx * basis.m_Forward.x + ty * basis.m_Forward.y < 0.0f)
				{
					tx = -tx;
					ty = -ty;
				}

				const auto previousTangent = m_Road.m_Tangent;
				const auto hadPrevious = m_Road.m_Valid;
				const auto edgeX = basis.m_Position.x - first.x;
				const auto edgeY = basis.m_Position.y - first.y;
				const auto projection = edgeX * tx + edgeY * ty;
				const Vector3 center{first.x + tx * projection, first.y + ty * projection, basis.m_Position.z};
				const Vector3 tangent{tx, ty, 0.0f};
				const Vector3 right{ty, -tx, 0.0f};

				RoadCache road;
				road.m_Valid = true;
				road.m_Center = center;
				road.m_Tangent = tangent;
				road.m_Right = right;
				const auto vehicleAlignment = std::abs(tx * basis.m_Forward.x + ty * basis.m_Forward.y);
				const auto previousAlignment = hadPrevious
				    ? std::abs(tx * previousTangent.x + ty * previousTangent.y)
				    : 1.0f;
				road.m_Stable = vehicleAlignment > 0.57f && previousAlignment > 0.94f;

				lanesForward = std::clamp(lanesForward, 0, 8);
				lanesBackward = std::clamp(lanesBackward, 0, 8);
				const auto totalLanes = std::clamp(lanesForward + lanesBackward, 1, 8);
				medianWidth = std::clamp(medianWidth, 0.0f, 8.0f);
				std::vector<float> boundaries;
				if (lanesForward > 0 && lanesBackward > 0)
				{
					for (int lane = 0; lane <= lanesForward; ++lane)
						boundaries.push_back(medianWidth * 0.5f + lane * kLaneWidth);
					for (int lane = 0; lane <= lanesBackward; ++lane)
						boundaries.push_back(-medianWidth * 0.5f - lane * kLaneWidth);
				}
				else
				{
					for (int lane = 0; lane <= totalLanes; ++lane)
						boundaries.push_back((lane - totalLanes * 0.5f) * kLaneWidth);
				}
				std::sort(boundaries.begin(), boundaries.end());
				boundaries.erase(std::unique(boundaries.begin(), boundaries.end()), boundaries.end());

				for (std::size_t lane = 1; lane < boundaries.size(); ++lane)
				{
					const auto gap = boundaries[lane] - boundaries[lane - 1];
					if (gap <= kLaneWidth * 1.6f)
						road.m_LaneCenters.push_back((boundaries[lane] + boundaries[lane - 1]) * 0.5f);
				}

				for (const auto offset : boundaries)
				{
					auto& line = road.m_Boundaries.emplace_back();
					line.reserve(10);
					for (float distance = -25.0f; distance <= 110.0f; distance += 15.0f)
						line.push_back(OffsetWorld(center, tangent, right, distance, offset));
				}

				m_Road = std::move(road);
			}

			void RefreshRoute(const Basis& basis, const RoadDriveStatus& status)
			{
				RouteCache route;
				if (status.m_Phase == RoutePhase::Wander)
				{
					route.m_Predicted = true;
					route.m_Reliable = m_Road.m_Valid && m_Road.m_Stable;
					if (route.m_Reliable)
					{
						for (float distance = 0.0f; distance <= 70.0f; distance += 7.0f)
							route.m_Points.push_back(OffsetWorld(m_Road.m_Center, m_Road.m_Tangent, m_Road.m_Right, distance, 0.0f));
					}
					m_Route = std::move(route);
					return;
				}

				if (status.m_Phase != RoutePhase::Navigation
				    && status.m_Phase != RoutePhase::TargetLost
				    && status.m_Phase != RoutePhase::Arrived)
				{
					m_Route = {};
					return;
				}

				route.m_Calculating = status.m_Phase == RoutePhase::TargetLost || !PATH::GET_GPS_BLIP_ROUTE_FOUND();
				const auto slot = status.m_TargetSource == NavigationTargetSource::UserWaypoint ? 0 : 1;
				if (!route.m_Calculating)
				{
					Vector3 previous{};
					bool hasPrevious = false;
					for (float distance = 0.0f; distance <= 160.0f; distance += 8.0f)
					{
						Vector3 point{};
						if (!PATH::GET_POS_ALONG_GPS_TYPE_ROUTE(&point, true, distance, slot) || !IsFinite(point))
							break;
						if (hasPrevious && Length2D(point.x - previous.x, point.y - previous.y) > 30.0f)
							break;
						route.m_Points.push_back(point);
						previous = point;
						hasPrevious = true;
					}
				}

				route.m_Reliable = route.m_Points.size() >= 2;
				if (!route.m_Reliable)
				{
					route.m_Points.clear();
					route.m_Calculating = true;
				}
				m_Route = std::move(route);
			}

			bool RouteIsTurning(const Basis& basis) const
			{
				if (!m_Route.m_Reliable || m_Route.m_Predicted || m_Route.m_Points.size() < 3)
					return false;
				const auto first = ToLocal(basis, m_Route.m_Points.front());
				for (std::size_t index = 2; index < m_Route.m_Points.size(); ++index)
				{
					const auto current = ToLocal(basis, m_Route.m_Points[index]);
					if (current.m_Y > 40.0f)
						break;
					const auto dx = current.m_X - first.m_X;
					const auto dy = current.m_Y - first.m_Y;
					const auto length = Length2D(dx, dy);
					if (length > 8.0f && std::abs(dx / length) > 0.34f)
						return true;
				}
				return false;
			}

			float CurrentLateralOffset(const Basis& basis) const
			{
				const auto dx = basis.m_Position.x - m_Road.m_Center.x;
				const auto dy = basis.m_Position.y - m_Road.m_Center.y;
				return dx * m_Road.m_Right.x + dy * m_Road.m_Right.y;
			}

			float NearestLaneCenterDistance(float offset) const
			{
				float nearest = std::numeric_limits<float>::max();
				for (const auto center : m_Road.m_LaneCenters)
					nearest = std::min(nearest, std::abs(offset - center));
				return nearest;
			}

			HudManeuver UpdateLaneChange(const Basis& basis, float speed, std::chrono::steady_clock::time_point now)
			{
				const auto eligible = speed >= 5.0f && m_Road.m_Valid && m_Road.m_Stable && !RouteIsTurning(basis);
				if (!eligible)
				{
					m_LaneChange = {};
					return HudManeuver::None;
				}

				const auto offset = CurrentLateralOffset(basis);
				if (m_LaneChange.m_LastSample == std::chrono::steady_clock::time_point{})
				{
					m_LaneChange.m_LastSample = now;
					m_LaneChange.m_LastOffset = offset;
					return HudManeuver::None;
				}

				const auto elapsed = std::chrono::duration<float>(now - m_LaneChange.m_LastSample).count();
				if (elapsed <= 0.001f || elapsed > 0.5f)
				{
					m_LaneChange.m_LastSample = now;
					m_LaneChange.m_LastOffset = offset;
					m_LaneChange.m_FilteredVelocity = 0.0f;
					return m_LaneChange.m_Active;
				}

				const auto rawVelocity = (offset - m_LaneChange.m_LastOffset) / elapsed;
				m_LaneChange.m_FilteredVelocity = m_LaneChange.m_FilteredVelocity * 0.7f + rawVelocity * 0.3f;
				m_LaneChange.m_LastOffset = offset;
				m_LaneChange.m_LastSample = now;

				if (m_LaneChange.m_Active == HudManeuver::None)
				{
					const auto direction = m_LaneChange.m_FilteredVelocity > 0.5f ? 1
					    : m_LaneChange.m_FilteredVelocity < -0.5f            ? -1
					                                                        : 0;
					if (!direction)
					{
						m_LaneChange.m_CandidateDirection = 0;
						m_LaneChange.m_CandidateSince = {};
						return HudManeuver::None;
					}

					if (direction != m_LaneChange.m_CandidateDirection)
					{
						m_LaneChange.m_CandidateDirection = direction;
						m_LaneChange.m_CandidateStart = offset;
						m_LaneChange.m_CandidateSince = now;
						return HudManeuver::None;
					}

					if (now - m_LaneChange.m_CandidateSince >= 250ms
					    && std::abs(offset - m_LaneChange.m_CandidateStart) > 0.35f)
					{
						m_LaneChange.m_Active = direction > 0 ? HudManeuver::LaneChangeRight : HudManeuver::LaneChangeLeft;
						m_LaneChange.m_ActiveSince = now;
						m_LaneChange.m_StableSince = {};
					}
					return m_LaneChange.m_Active;
				}

				if (now - m_LaneChange.m_ActiveSince >= 4s)
				{
					m_LaneChange = {};
					return HudManeuver::None;
				}

				const auto settled = std::abs(m_LaneChange.m_FilteredVelocity) < 0.2f
				    && NearestLaneCenterDistance(offset) < 0.45f;
				if (settled)
				{
					if (m_LaneChange.m_StableSince == std::chrono::steady_clock::time_point{})
						m_LaneChange.m_StableSince = now;
					else if (now - m_LaneChange.m_StableSince >= 500ms)
					{
						m_LaneChange = {};
						return HudManeuver::None;
					}
				}
				else
				{
					m_LaneChange.m_StableSince = {};
				}
				return m_LaneChange.m_Active;
			}

			static bool InHudRange(const HudPoint& point)
			{
				return point.m_Y >= -kRearRange && point.m_Y <= kForwardRange && std::abs(point.m_X) <= kLateralRange;
			}

			void AppendEntities(
			    std::vector<HudEntitySnapshot>& output,
			    const std::vector<WorldEntity>& source,
			    const Basis& basis,
			    std::size_t maximum) const
			{
				std::vector<std::pair<float, HudEntitySnapshot>> sorted;
				sorted.reserve(source.size());
				for (const auto& entity : source)
				{
					const auto local = ToLocal(basis, entity.m_Position);
					if (!InHudRange(local) || std::abs(entity.m_Position.z - basis.m_Position.z) > kVerticalRange)
						continue;
					HudEntitySnapshot snapshot;
					snapshot.m_TrackId = entity.m_TrackId;
					snapshot.m_Kind = entity.m_Kind;
					snapshot.m_Position = local;
					snapshot.m_Velocity = VectorToLocal(basis, entity.m_Velocity);
					snapshot.m_Footprint = entity.m_Footprint;
					snapshot.m_RelativeHeadingRadians = NormalizeRadians(entity.m_HeadingRadians - basis.m_HeadingRadians);
					sorted.emplace_back(local.m_X * local.m_X + local.m_Y * local.m_Y, snapshot);
				}
				std::sort(sorted.begin(), sorted.end(), [](const auto& left, const auto& right) {
					return left.first < right.first;
				});
				for (std::size_t index = 0; index < std::min(maximum, sorted.size()); ++index)
					output.push_back(std::move(sorted[index].second));
			}

			void InferRedTrafficLight(std::vector<HudEntitySnapshot>& entities, bool stoppedAtLight) const
			{
				if (!stoppedAtLight)
					return;
				HudEntitySnapshot* nearest = nullptr;
				float nearestDistance = std::numeric_limits<float>::max();
				for (auto& entity : entities)
				{
					if (entity.m_Kind != HudEntityKind::TrafficLight || entity.m_Position.m_Y < 0.0f
					    || entity.m_Position.m_Y > 35.0f || std::abs(entity.m_Position.m_X) > 6.0f)
						continue;
					const auto distance = Length2D(entity.m_Position.m_X, entity.m_Position.m_Y);
					if (distance < nearestDistance)
					{
						nearest = &entity;
						nearestDistance = distance;
					}
				}
				if (nearest)
					nearest->m_TrafficLightState = TrafficLightState::RedInferred;
			}

		public:
			TelemetryService()
			{
				m_Published.store(std::make_shared<const AutoDriveHudSnapshot>());
			}

			void Update(SessionToken token, Ped driver, Vehicle vehicle, const RoadDriveStatus& status)
			{
				if (!Coordinator::Owns(token) || !driver || !vehicle)
					return;
				if (!SameToken(m_ActiveToken, token))
					ResetForToken(token);

				const auto now = std::chrono::steady_clock::now();
				if (m_LastPublish != std::chrono::steady_clock::time_point{} && now - m_LastPublish < 50ms)
					return;
				const auto basis = GetBasis(vehicle);

				if (m_LastVehiclePedScan == std::chrono::steady_clock::time_point{} || now - m_LastVehiclePedScan >= 100ms)
				{
					ScanVehiclesAndPeds(basis, vehicle, now);
					m_LastVehiclePedScan = now;
				}
				if (m_LastObjectScan == std::chrono::steady_clock::time_point{} || now - m_LastObjectScan >= 333ms)
				{
					ScanObjects(basis, now);
					m_LastObjectScan = now;
				}
				if (m_LastRoadScan == std::chrono::steady_clock::time_point{} || now - m_LastRoadScan >= 200ms)
				{
					RefreshRoad(basis);
					m_LastRoadScan = now;
				}
				if (m_LastRouteScan == std::chrono::steady_clock::time_point{} || now - m_LastRouteScan >= 250ms)
				{
					RefreshRoute(basis, status);
					m_LastRouteScan = now;
				}
				ExpireFailedScans(now);

				auto snapshot = std::make_shared<AutoDriveHudSnapshot>();
				snapshot->m_Visible = status.m_HasTask && _AutoDriveHud.GetState();
				snapshot->m_Suppressed = CAMERA::IS_SCREEN_FADED_OUT() || CAMERA::IS_SCREEN_FADING_OUT() || CAMERA::IS_SCREEN_FADING_IN()
				    || HUD::IS_PAUSE_MENU_ACTIVE() || HUD::IS_WARNING_MESSAGE_ACTIVE()
				    || CUTSCENE::IS_CUTSCENE_ACTIVE() || CUTSCENE::IS_CUTSCENE_PLAYING();
				snapshot->m_Owner = token.m_Owner;
				snapshot->m_Phase = status.m_Phase;
				snapshot->m_SpeedKph = std::max(0, static_cast<int>(std::lround(vehicle.GetSpeed() * 3.6f)));
				snapshot->m_TargetSpeedKph = GetCruiseSpeedKph();
				snapshot->m_Maneuver = UpdateLaneChange(basis, vehicle.GetSpeed(), now);
				snapshot->m_RouteReliable = m_Route.m_Reliable;
				snapshot->m_RouteCalculating = m_Route.m_Calculating;
				snapshot->m_RoutePredicted = m_Route.m_Predicted;
				for (const auto& point : m_Route.m_Points)
				{
					const auto local = ToLocal(basis, point);
					if (local.m_Y >= -10.0f && local.m_Y <= 170.0f && std::abs(local.m_X) <= 70.0f)
						snapshot->m_RoutePoints.push_back(local);
				}
				if (m_Road.m_Valid && m_Road.m_Stable)
				{
					for (const auto& worldLine : m_Road.m_Boundaries)
					{
						auto& line = snapshot->m_LaneBoundaries.emplace_back();
						line.reserve(worldLine.size());
						for (const auto& point : worldLine)
							line.push_back(ToLocal(basis, point));
					}
				}

				snapshot->m_Entities.reserve(240);
				AppendEntities(snapshot->m_Entities, m_Vehicles, basis, 64);
				AppendEntities(snapshot->m_Entities, m_Peds, basis, 48);
				AppendEntities(snapshot->m_Entities, m_Objects, basis, 128);
				InferRedTrafficLight(snapshot->m_Entities, VEHICLE::IS_VEHICLE_STOPPED_AT_TRAFFIC_LIGHTS(vehicle.GetHandle()));
				snapshot->m_CapturedAt = now;

				m_LastPublish = now;
				m_Published.store(std::move(snapshot), std::memory_order_release);
			}

			void Clear(SessionToken token)
			{
				if (!SameToken(m_ActiveToken, token))
					return;
				ResetForToken({});
				m_Published.store(std::make_shared<const AutoDriveHudSnapshot>(), std::memory_order_release);
			}

			std::shared_ptr<const AutoDriveHudSnapshot> GetSnapshot() const
			{
				return m_Published.load(std::memory_order_acquire);
			}
		};

		TelemetryService& GetTelemetryService()
		{
			static TelemetryService service;
			return service;
		}
	}

	void AutoDriveHudTelemetry::Update(SessionToken token, Ped driver, Vehicle vehicle, const RoadDriveStatus& status)
	{
		GetTelemetryService().Update(token, driver, vehicle, status);
	}

	void AutoDriveHudTelemetry::Clear(SessionToken token)
	{
		GetTelemetryService().Clear(token);
	}

	std::shared_ptr<const AutoDriveHudSnapshot> AutoDriveHudTelemetry::GetSnapshot()
	{
		return GetTelemetryService().GetSnapshot();
	}

	bool AutoDriveHudTelemetry::IsEnabled()
	{
		return _AutoDriveHud.GetState();
	}
}

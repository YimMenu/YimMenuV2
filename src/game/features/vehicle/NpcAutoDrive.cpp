#include "AutoDriveShared.hpp"
#include "AutoDriveHudTelemetry.hpp"

#include "core/commands/BoolCommand.hpp"
#include "core/commands/Commands.hpp"
#include "core/commands/LoopedCommand.hpp"
#include "core/frontend/Notifications.hpp"
#include "core/util/Joaat.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "types/ped/PedConfigFlag.hpp"

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>

namespace YimMenu::Features
{
	class NpcAutoDrive : public LoopedCommand
	{
		enum class FailureReason
		{
			None,
			NoVehicle,
			PlayerDead,
			NotDriver,
			UnsupportedVehicle,
			NoPassengerSeat,
			VehicleUndriveable,
			NoControl
		};

		static constexpr Hash taxi_driver_model = "s_m_m_gentransport"_J;

		AutoDriveInternal::RoadDriveController m_Route;
		AutoDriveInternal::SessionToken m_Session;
		FailureReason m_FailureReason = FailureReason::None;
		int m_PlayerHandle = 0;
		int m_VehicleHandle = 0;
		int m_DriverHandle = 0;
		std::uint16_t m_DriverNetworkId = 0;
		bool m_PreviousPreventAutoShuffle = false;
		bool m_HasSavedPlayerFlag = false;

		static std::optional<int> FindPassengerSeat(Vehicle vehicle)
		{
			const auto passengerCount = VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(vehicle.GetHandle());
			for (int seat = 0; seat < passengerCount; ++seat)
			{
				if (vehicle.IsSeatFree(seat))
					return seat;
			}

			return std::nullopt;
		}

		void SetFailure(FailureReason reason, std::string_view message = {})
		{
			if (reason == m_FailureReason)
				return;

			m_FailureReason = reason;
			if (reason != FailureReason::None)
				Notifications::Show("NPC Auto Drive", std::string(message), NotificationType::Warning);
		}

		bool IsOwnedDriver(Ped driver) const
		{
			if (!driver
			    || driver.GetHandle() != m_DriverHandle
			    || !ENTITY::IS_ENTITY_A_PED(driver.GetHandle())
			    || PED::IS_PED_A_PLAYER(driver.GetHandle())
			    || ENTITY::GET_ENTITY_MODEL(driver.GetHandle()) != taxi_driver_model)
				return false;

			return !m_DriverNetworkId
			    || (driver.IsNetworked() && driver.GetNetworkObjectId() == m_DriverNetworkId);
		}

		void ResetSessionState()
		{
			m_PlayerHandle = 0;
			m_VehicleHandle = 0;
			m_DriverHandle = 0;
			m_DriverNetworkId = 0;
			m_PreviousPreventAutoShuffle = false;
			m_HasSavedPlayerFlag = false;
			m_FailureReason = FailureReason::None;
		}

		void ClearOwnedSession()
		{
			AutoDriveInternal::AutoDriveHudTelemetry::Clear(m_Session);
			Vehicle vehicle(0);
			if (m_VehicleHandle && ENTITY::DOES_ENTITY_EXIST(m_VehicleHandle))
				vehicle = Vehicle(m_VehicleHandle);

			Ped driver(0);
			const auto hasOwnedDriver = m_DriverHandle
			    && ENTITY::DOES_ENTITY_EXIST(m_DriverHandle)
			    && IsOwnedDriver(Ped(m_DriverHandle));
			if (hasOwnedDriver)
				driver = Ped(m_DriverHandle);

			const auto ownsDriverSeat = vehicle
			    && driver
			    && VEHICLE::GET_PED_IN_VEHICLE_SEAT(vehicle.GetHandle(), -1, false) == driver.GetHandle();
			const auto driverSeatIsFree = vehicle
			    && VEHICLE::IS_VEHICLE_SEAT_FREE(vehicle.GetHandle(), -1, false);
			const auto canControlDriver = driver && driver.RequestControl(0);
			const auto canControlVehicle = vehicle && vehicle.RequestControl(0);
			const auto canClearVehicleTask = canControlVehicle && (ownsDriverSeat || driverSeatIsFree);
			m_Route.ClearTask(canControlDriver, canClearVehicleTask);

			Ped player(0);
			if (m_PlayerHandle && ENTITY::DOES_ENTITY_EXIST(m_PlayerHandle) && PED::IS_PED_A_PLAYER(m_PlayerHandle))
				player = Ped(m_PlayerHandle);

			const auto playerStillInVehicle = player
			    && vehicle
			    && PED::IS_PED_IN_VEHICLE(player.GetHandle(), vehicle.GetHandle(), false);
			const auto playerCanTakeControl = playerStillInVehicle
			    && !player.IsDead()
			    && VEHICLE::IS_VEHICLE_DRIVEABLE(vehicle.GetHandle(), false);
			if (!playerCanTakeControl && vehicle && canClearVehicleTask)
				vehicle.BringToHalt(5.0f, 1);

			if (driver)
				driver.Delete();

			if (playerCanTakeControl && (driverSeatIsFree || ownsDriverSeat))
				player.SetInVehicle(vehicle, -1);

			if (player && m_HasSavedPlayerFlag)
				player.SetConfigFlag(PedConfigFlag::PreventAutoShuffleToDriversSeat, m_PreviousPreventAutoShuffle);

			ResetSessionState();
		}

		void DisableWithNotification(std::string_view message, NotificationType type = NotificationType::Warning)
		{
			AutoDriveInternal::Coordinator::Release(m_Session);
			if (GetState())
				SetState(false);

			Notifications::Show("NPC Auto Drive", std::string(message), type);
		}

		bool ValidateSetupCandidate(Ped player, Vehicle vehicle, std::optional<int>& passengerSeat)
		{
			if (!player || !vehicle)
			{
				SetFailure(FailureReason::NoVehicle, "Enter the driver seat of a supported car.");
				return false;
			}

			if (player.IsDead())
			{
				SetFailure(FailureReason::PlayerDead, "NPC Auto Drive is waiting for the player to respawn.");
				return false;
			}

			if (VEHICLE::GET_PED_IN_VEHICLE_SEAT(vehicle.GetHandle(), -1, false) != player.GetHandle())
			{
				SetFailure(FailureReason::NotDriver, "Move to the driver seat to start NPC Auto Drive.");
				return false;
			}

			if (!AutoDriveInternal::IsSupportedNpcVehicle(vehicle))
			{
				SetFailure(FailureReason::UnsupportedVehicle, "NPC Auto Drive only supports cars with a passenger seat.");
				return false;
			}

			if (!VEHICLE::IS_VEHICLE_DRIVEABLE(vehicle.GetHandle(), false))
			{
				SetFailure(FailureReason::VehicleUndriveable, "The current vehicle cannot be driven.");
				return false;
			}

			passengerSeat = FindPassengerSeat(vehicle);
			if (!passengerSeat)
			{
				SetFailure(FailureReason::NoPassengerSeat, "NPC Auto Drive requires an empty passenger seat.");
				return false;
			}

			if (!vehicle.RequestControl(0))
			{
				SetFailure(FailureReason::NoControl, "Waiting for network control of the current vehicle.");
				return false;
			}

			SetFailure(FailureReason::None);
			return true;
		}

		bool SetupDriver()
		{
			auto player = Self::GetPed();
			auto vehicle = Self::GetVehicle();
			std::optional<int> passengerSeat;
			if (!ValidateSetupCandidate(player, vehicle, passengerSeat))
				return false;

			const auto setupSession = m_Session;
			const auto playerHandle = player.GetHandle();
			const auto vehicleHandle = vehicle.GetHandle();
			auto spawnPosition = vehicle.GetPosition();
			spawnPosition.z -= 5.0f;
			auto driver = Ped::Create(taxi_driver_model, spawnPosition, vehicle.GetHeading());
			if (!driver)
			{
				if (AutoDriveInternal::Coordinator::Owns(setupSession) && GetState())
					DisableWithNotification("Unable to create the NPC driver.");
				return false;
			}

			player = Self::GetPed();
			vehicle = Self::GetVehicle();
			if (!AutoDriveInternal::Coordinator::Owns(setupSession)
			    || !GetState()
			    || !player
			    || !vehicle
			    || player.GetHandle() != playerHandle
			    || vehicle.GetHandle() != vehicleHandle
			    || VEHICLE::GET_PED_IN_VEHICLE_SEAT(vehicleHandle, -1, false) != playerHandle
			    || !VEHICLE::IS_VEHICLE_DRIVEABLE(vehicleHandle, false)
			    || !vehicle.IsSeatFree(*passengerSeat)
			    || !vehicle.RequestControl(0))
			{
				driver.Delete();
				return false;
			}

			driver.SetVisible(false);
			driver.SetCollision(false);
			driver.SetInvincible(true);
			driver.SetRagdoll(false);
			PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(driver.GetHandle(), true);
			PED::SET_PED_CAN_BE_DRAGGED_OUT(driver.GetHandle(), false);
			PED::SET_PED_STAY_IN_VEHICLE_WHEN_JACKED(driver.GetHandle(), true);
			PED::SET_PED_KEEP_TASK(driver.GetHandle(), true);
			PED::SET_DRIVER_ABILITY(driver.GetHandle(), 1.0f);

			const auto previousPreventAutoShuffle = player.GetConfigFlag(PedConfigFlag::PreventAutoShuffleToDriversSeat);
			player.SetConfigFlag(PedConfigFlag::PreventAutoShuffleToDriversSeat, true);
			player.SetInVehicle(vehicle, *passengerSeat);
			if (VEHICLE::GET_PED_IN_VEHICLE_SEAT(vehicleHandle, *passengerSeat, false) != playerHandle)
			{
				player.SetConfigFlag(PedConfigFlag::PreventAutoShuffleToDriversSeat, previousPreventAutoShuffle);
				driver.Delete();
				DisableWithNotification("Unable to move the player to a passenger seat.");
				return false;
			}

			driver.SetInVehicle(vehicle, -1);
			if (VEHICLE::GET_PED_IN_VEHICLE_SEAT(vehicleHandle, -1, false) != driver.GetHandle())
			{
				driver.Delete();
				if (VEHICLE::IS_VEHICLE_SEAT_FREE(vehicleHandle, -1, false))
					player.SetInVehicle(vehicle, -1);
				player.SetConfigFlag(PedConfigFlag::PreventAutoShuffleToDriversSeat, previousPreventAutoShuffle);
				DisableWithNotification("Unable to place the NPC in the driver seat.");
				return false;
			}

			driver.SetCollision(true);
			driver.SetVisible(true);
			m_PlayerHandle = playerHandle;
			m_VehicleHandle = vehicleHandle;
			m_DriverHandle = driver.GetHandle();
			m_DriverNetworkId = driver.GetNetworkObjectId();
			m_PreviousPreventAutoShuffle = previousPreventAutoShuffle;
			m_HasSavedPlayerFlag = true;
			SetFailure(FailureReason::None);
			return true;
		}

		bool ValidateActiveSession(Ped player, Vehicle vehicle, Ped driver)
		{
			if (!player || player.GetHandle() != m_PlayerHandle || player.IsDead())
			{
				DisableWithNotification("NPC Auto Drive disabled because the player is unavailable.");
				return false;
			}

			if (!vehicle || vehicle.GetHandle() != m_VehicleHandle
			    || !PED::IS_PED_IN_VEHICLE(player.GetHandle(), m_VehicleHandle, false))
			{
				DisableWithNotification("NPC Auto Drive disabled because the player left the vehicle.");
				return false;
			}

			if (!VEHICLE::IS_VEHICLE_DRIVEABLE(vehicle.GetHandle(), false))
			{
				DisableWithNotification("NPC Auto Drive disabled because the vehicle is no longer driveable.");
				return false;
			}

			if (!IsOwnedDriver(driver) || driver.IsDead()
			    || VEHICLE::GET_PED_IN_VEHICLE_SEAT(vehicle.GetHandle(), -1, false) != driver.GetHandle())
			{
				DisableWithNotification("NPC Auto Drive disabled because the NPC driver is unavailable.");
				return false;
			}

			if (!vehicle.RequestControl(0) || !driver.RequestControl(0))
			{
				SetFailure(FailureReason::NoControl, "Waiting for network control of the vehicle and NPC driver.");
				return false;
			}

			SetFailure(FailureReason::None);
			return true;
		}

		virtual void OnEnable() override
		{
			auto playerAutoDrive = Commands::GetCommand<BoolCommand>("autodrive"_J);
			if (AutoDriveInternal::Coordinator::GetOwner() == AutoDriveInternal::Owner::None
			    && playerAutoDrive
			    && playerAutoDrive->GetState())
			{
				SetState(false);
				return;
			}

			m_Session = AutoDriveInternal::Coordinator::Claim(AutoDriveInternal::Owner::Npc, [this] {
				ClearOwnedSession();
			});

			if (playerAutoDrive && playerAutoDrive->GetState())
				playerAutoDrive->SetState(false);
		}

		virtual void OnTick() override
		{
			if (!AutoDriveInternal::Coordinator::Owns(m_Session))
				return;

			if (!m_DriverHandle)
			{
				if (!SetupDriver())
					return;
			}

			auto player = Self::GetPed();
			auto vehicle = Self::GetVehicle();
			Ped driver(0);
			if (m_DriverHandle && ENTITY::DOES_ENTITY_EXIST(m_DriverHandle))
				driver = Ped(m_DriverHandle);

			if (!ValidateActiveSession(player, vehicle, driver))
			{
				AutoDriveInternal::AutoDriveHudTelemetry::Clear(m_Session);
				return;
			}

			const auto routeResult = m_Route.Tick(driver, vehicle, "NPC Auto Drive started.");
			AutoDriveInternal::AutoDriveHudTelemetry::Update(m_Session, driver, vehicle, m_Route.GetStatus());
			if (routeResult == AutoDriveInternal::RouteResult::DestinationReached)
			{
				AutoDriveInternal::Coordinator::Release(m_Session);
				SetState(false);
				Notifications::Show(
				    "NPC Auto Drive",
				    "Destination reached. NPC Auto Drive disabled; please take control.",
				    NotificationType::Success);
			}
		}

		virtual void OnDisable() override
		{
			// A queued disable callback may run after the command has already been re-enabled.
			if (GetState() && IsReady())
				return;

			AutoDriveInternal::Coordinator::Release(m_Session);
			m_FailureReason = FailureReason::None;
		}

	public:
		using LoopedCommand::LoopedCommand;
	};

	static NpcAutoDrive _NpcAutoDrive{
	    "npcautodrive",
	    "NPC Auto Drive",
	    "Moves you to a passenger seat and lets an NPC drive to your waypoint or roam"};
}

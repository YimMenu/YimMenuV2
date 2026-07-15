#include "AutoDriveShared.hpp"

#include "core/commands/BoolCommand.hpp"
#include "core/commands/Commands.hpp"
#include "core/commands/LoopedCommand.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "types/pad/ControllerInputs.hpp"

#include <cmath>
#include <string>
#include <string_view>

namespace YimMenu::Features
{
	class AutoDrive : public LoopedCommand
	{
		enum class FailureReason
		{
			None,
			NoVehicle,
			PlayerDead,
			NotDriver,
			UnsupportedVehicle,
			VehicleUndriveable,
			NoControl
		};

		static constexpr float manual_input_deadzone = 0.2f;

		AutoDriveInternal::RoadDriveController m_Route;
		AutoDriveInternal::SessionToken m_Session;
		FailureReason m_FailureReason = FailureReason::None;

		static bool HasManualDrivingInput()
		{
			const auto steering = std::abs(PAD::GET_CONTROL_NORMAL(0, static_cast<int>(ControllerInputs::INPUT_VEH_MOVE_LR)));
			const auto accelerate = std::abs(PAD::GET_CONTROL_NORMAL(0, static_cast<int>(ControllerInputs::INPUT_VEH_ACCELERATE)));
			const auto brake = std::abs(PAD::GET_CONTROL_NORMAL(0, static_cast<int>(ControllerInputs::INPUT_VEH_BRAKE)));

			return steering > manual_input_deadzone
			    || accelerate > manual_input_deadzone
			    || brake > manual_input_deadzone
			    || PAD::IS_CONTROL_PRESSED(0, static_cast<int>(ControllerInputs::INPUT_VEH_HANDBRAKE))
			    || PAD::IS_CONTROL_PRESSED(0, static_cast<int>(ControllerInputs::INPUT_VEH_EXIT));
		}

		void SetFailure(FailureReason reason, std::string_view message = {})
		{
			if (reason == m_FailureReason)
				return;

			m_FailureReason = reason;
			if (reason != FailureReason::None)
				Notifications::Show("Auto Drive", std::string(message), NotificationType::Warning);
		}

		void ClearOwnedSession()
		{
			m_Route.ClearTask();
			m_FailureReason = FailureReason::None;
		}

		bool ValidateDriver(Ped driver, Vehicle vehicle)
		{
			if (!driver || !vehicle)
			{
				m_Route.ClearTask();
				SetFailure(FailureReason::NoVehicle, "Enter the driver seat of a supported road vehicle.");
				return false;
			}

			if (driver.IsDead())
			{
				m_Route.ClearTask();
				SetFailure(FailureReason::PlayerDead, "Auto Drive is waiting for the player to respawn.");
				return false;
			}

			if (VEHICLE::GET_PED_IN_VEHICLE_SEAT(vehicle.GetHandle(), -1, false) != driver.GetHandle())
			{
				m_Route.ClearTask();
				SetFailure(FailureReason::NotDriver, "Move to the driver seat to use Auto Drive.");
				return false;
			}

			if (!AutoDriveInternal::IsSupportedRoadVehicle(vehicle))
			{
				m_Route.ClearTask();
				SetFailure(FailureReason::UnsupportedVehicle, "This vehicle type does not support Auto Drive.");
				return false;
			}

			if (!VEHICLE::IS_VEHICLE_DRIVEABLE(vehicle.GetHandle(), false))
			{
				m_Route.ClearTask();
				SetFailure(FailureReason::VehicleUndriveable, "The current vehicle cannot be driven.");
				return false;
			}

			if (!vehicle.RequestControl(0))
			{
				m_Route.ClearTask();
				SetFailure(FailureReason::NoControl, "Waiting for network control of the current vehicle.");
				return false;
			}

			SetFailure(FailureReason::None);
			return true;
		}

		virtual void OnEnable() override
		{
			auto npcAutoDrive = Commands::GetCommand<BoolCommand>("npcautodrive"_J);
			if (AutoDriveInternal::Coordinator::GetOwner() == AutoDriveInternal::Owner::None
			    && npcAutoDrive
			    && npcAutoDrive->GetState())
				npcAutoDrive->SetState(false);

			m_Session = AutoDriveInternal::Coordinator::Claim(AutoDriveInternal::Owner::Player, [this] {
				ClearOwnedSession();
			});

			if (npcAutoDrive && npcAutoDrive->GetState())
				npcAutoDrive->SetState(false);
		}

		virtual void OnTick() override
		{
			if (!AutoDriveInternal::Coordinator::Owns(m_Session))
				return;

			auto driver = Self::GetPed();
			auto vehicle = Self::GetVehicle();
			if (!ValidateDriver(driver, vehicle))
				return;

			if (HasManualDrivingInput())
			{
				AutoDriveInternal::Coordinator::Release(m_Session);
				SetState(false);
				return;
			}

			if (m_Route.Tick(driver, vehicle, "Auto Drive started.") == AutoDriveInternal::RouteResult::DestinationReached)
			{
				AutoDriveInternal::Coordinator::Release(m_Session);
				SetState(false);
				Notifications::Show(
				    "Auto Drive",
				    "Destination reached. Auto Drive disabled; please take control.",
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

	static AutoDrive _AutoDrive{
	    "autodrive",
	    "Auto Drive",
	    "Drives to your waypoint using roads, or roams when no waypoint is set"};
}

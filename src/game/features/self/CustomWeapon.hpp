#pragma once
#include "core/commands/BoolCommand.hpp"
#include "core/commands/ColorCommand.hpp"
#include "core/commands/IntCommand.hpp"
#include "core/commands/ListCommand.hpp"
#include "core/commands/LoopedCommand.hpp"
#include "core/commands/StringCommand.hpp"
#include "core/util/Math.hpp"
#include "core/util/RainbowColor.hpp"
#include "game/gta/Entity.hpp"
#include "game/gta/Natives.hpp"
#include "types/pad/ControllerInputs.hpp"

namespace YimMenu::Features
{
	enum class CustomWeapons
	{
		CAGE_GUN,
		DELETE_GUN,
		GRAVITY_GUN,
		STEAL_VEHICLE_GUN,
		REPAIR_GUN,
		VEHICLE_GUN,
		TELEPORT_GUN,
		PAINT_GUN
	};

	static const ControllerInputs attackControls[] = {
		ControllerInputs::INPUT_WEAPON_WHEEL_NEXT,
		ControllerInputs::INPUT_WEAPON_WHEEL_PREV,
		ControllerInputs::INPUT_ATTACK,
		ControllerInputs::INPUT_ATTACK2,
		ControllerInputs::INPUT_VEH_ATTACK,
		ControllerInputs::INPUT_VEH_ATTACK2,
		ControllerInputs::INPUT_VEH_PASSENGER_ATTACK,
		ControllerInputs::INPUT_VEH_FLY_ATTACK,
		ControllerInputs::INPUT_VEH_FLY_ATTACK2,
	};

	static std::vector<std::pair<int, const char*>> g_CustomWeaponTypes = {
		{static_cast<int>(CustomWeapons::CAGE_GUN), "Cage Gun"},
		{static_cast<int>(CustomWeapons::DELETE_GUN), "Delete Gun"},
		{static_cast<int>(CustomWeapons::GRAVITY_GUN), "Gravity Gun"},
		{static_cast<int>(CustomWeapons::STEAL_VEHICLE_GUN), "Steal Vehicle Gun"},
		{static_cast<int>(CustomWeapons::REPAIR_GUN), "Repair Gun"},
		{static_cast<int>(CustomWeapons::VEHICLE_GUN), "Vehicle Gun"},
		{static_cast<int>(CustomWeapons::TELEPORT_GUN), "Teleport Gun"},
		{static_cast<int>(CustomWeapons::PAINT_GUN), "Paint Gun"},
	};
	static ListCommand _CustomWeaponType{"customweapontype", "Weapon Type", "The type of custom weapon to use", g_CustomWeaponTypes, static_cast<int>(CustomWeapons::CAGE_GUN)};

	static std::vector<std::pair<int, const char*>> g_PaintGunRainbowColorStyles = {
		{static_cast<int>(RainbowColorStyle::Fade), "Fade"},
		{static_cast<int>(RainbowColorStyle::Spasm), "Spasm"}
	};
	static ListCommand _PaintGunRainbowColorStyle{"paintgunrainbowcolorstyle", "Rainbow Color Style", "Style of rainbow color for paint gun", g_PaintGunRainbowColorStyles, static_cast<int>(RainbowColorStyle::Fade)};

	class CustomWeapon : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override;
	};

	static CustomWeapon _CustomWeapon{"customweapon", "Custom Weapon", "Modifies weapon ability"};
	static BoolCommand _CustomWeaponEnabledOnWeaponOut{"customweaponenabledonweaponout", "Enable Only if Weapon is Out", "Enables custom weapon only when weapon is out", true};
	static BoolCommand _GravityGunLaunchOnRelease{"gravitygunlaunchonrelease", "Launch Entity on Release", "Launches entity when released", false};
	static StringCommand _VehicleGunModel{"vehiclegunmodel", "Vehicle Model", "Model of the vehicle"};
	static ColorCommand _PaintGunColor{"paintguncolor", "Paint Gun Color", "Color of the paint gun"};
	static BoolCommand _PaintGunRainbowColorEnabled{"paintgunrainbowcolorenabled", "Rainbow Color", "Enables rainbow color for paint gun", false};
	static IntCommand _PaintGunRainbowColorSpeed{"paintgunrainbowcolorspeed", "Rainbow Color Speed", "Speed of rainbow color for paint gun", 1, 10, 1};
}
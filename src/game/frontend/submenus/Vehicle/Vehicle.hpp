#pragma once
#include "VehicleLSCCategory.hpp"
#include "VehiclePersistCarCategory.hpp"
#include "core/frontend/Notifications.hpp"
#include "core/frontend/manager/Submenu.hpp"
#include "game/features/vehicle/Godmode.hpp"
#include "game/features/vehicle/Seatbelt.hpp"
#include "game/features/vehicle/Simple.hpp"
#include "game/frontend/components/components.hpp"
#include "misc/cpp/imgui_stdlib.h"

namespace YimMenu::Submenus
{
	class VehicleMainCategory : public SubmenuMenuCategory
	{
		using SubmenuMenuCategory::SubmenuMenuCategory;
		void Draw()
		{
			ImGui::BeginGroup();
			{
				components::checkbox(YimMenu::Features::_VehicleGodmode);
				components::checkbox(YimMenu::Features::_Seatbelt);
			}
			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup();
			{
				if (ImGui::Button("Repair Vehicle"))
					YimMenu::Features::RepairVehicle();
				if (ImGui::Button("Fix All Vehicles"))
					YimMenu::Features::FixAllVehicles();
				if (ImGui::Button("Enter Last Vehicle"))
					YimMenu::Features::EnterLastVehicle();
				if (ImGui::Button("Call Mechanic"))
					YimMenu::Features::CallMechanic();
				if (ImGui::Button("Reset Vehicle Delivery Cooldown"))
					YimMenu::Features::ResetVehDeliveryCooldown();
			}
			ImGui::EndGroup();
		}
	};

	class VehicleSpawnCategory : public SubmenuMenuCategory
	{
		using SubmenuMenuCategory::SubmenuMenuCategory;
		void Draw()
		{
			ImGui::BeginGroup();
			{
				ImGui::TextWrapped("Input model of the car. For example Coquette D5 has 'coquette6'. Get 'Model ID' under 'Meta Section' from https://gtacars.net");
				ImGui::TextWrapped("Some vehicle have different models. For example Buccaneer & Buccaneer Custom are different.");
				static std::string veh_model_name;
				ImGui::InputTextWithHint("###veh_model_name", "model", &veh_model_name);
				components::ver_space();
				static bool spawn_in, max_upgrade;
				ImGui::Checkbox("Tp in after spawn", &spawn_in);
				ImGui::Checkbox("Spawn upgraded", &max_upgrade);
				components::ver_space();
				if (ImGui::Button("Spawn Vehicle"))
					YimMenu::Features::SpawnVehicle(veh_model_name, spawn_in, max_upgrade);
			}
			ImGui::EndGroup();
		}
	};

	class VehicleSubmenu : public Submenu
	{
	public:
		VehicleSubmenu() :
		    Submenu("Vehicle")
		{
			auto main       = std::make_shared<VehicleMainCategory>("main");
			auto spawn      = std::make_shared<VehicleSpawnCategory>("spawn");
			auto lsc        = std::make_shared<VehicleLSCCategory>("LSC");
			auto persistCar = std::make_shared<VehiclePersistCarCategory>("persistCar");
			AddCategory(std::move(main));
			AddCategory(std::move(spawn));
			AddCategory(std::move(lsc));
			AddCategory(std::move(persistCar));
		};
	};
}
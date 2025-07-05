#include "SavedVehicles.hpp"

#include "core/backend/FiberPool.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/gta/VehicleModel.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/Vehicle.hpp"
#include "game/gta/data/VehicleValues.hpp"

namespace YimMenu
{
	Folder SavedVehicles::CheckFolder(std::string folderName)
	{
		return FileMgr::GetProjectFolder("./saved_json_vehicles/" + folderName);
	}

	void SavedVehicles::RefreshList(std::string folderName, std::vector<std::string>& folders, std::vector<std::string>& files)
	{
		FiberPool::Push([folderName, &folders, &files] {
			folders.clear();

			const auto file_path = CheckFolder();
			for (const auto& directory_entry : std::filesystem::directory_iterator(file_path.Path()))
				if (directory_entry.is_directory())
					folders.push_back(directory_entry.path().filename().generic_string());

			files.clear();

			const auto file_path2 = CheckFolder(folderName);
			for (const auto& directory_entry : std::filesystem::directory_iterator(file_path2.Path()))
				if (directory_entry.path().extension() == ".json")
					files.push_back(directory_entry.path().filename().generic_string());
		});
	}

	nlohmann::json SavedVehicles::GetJson(Vehicle veh)
	{
		nlohmann::json vehicle_json;
		int primary_color, secondary_color;
		int pearlescent_color, wheel_color;
		auto vehicle = veh.GetHandle();
		Hash vehicle_hash = veh.GetModel();
		std::map<int, int> vehicle_extras;
		auto is_bennys = VehicleModel::IsBennys(vehicle);

		for (int slot = (int)VehicleModType::MOD_SPOILERS; slot <= (int)VehicleModType::MOD_LIGHTBAR; slot++)
			if (VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, slot) > 0)
			{
				auto wheel_custom = VEHICLE::GET_VEHICLE_MOD_VARIATION(vehicle, slot);

				if (wheel_custom && is_bennys)
					wheel_custom = 0;

				int vehicle_mod[2] = {VEHICLE::GET_VEHICLE_MOD(vehicle, slot), wheel_custom};
				vehicle_json[mod_names[slot]] = vehicle_mod;
			}
			else if (VEHICLE::IS_TOGGLE_MOD_ON(vehicle, slot))
			{
				vehicle_json[mod_names[slot]] = "TOGGLE";

				if (slot == (int)VehicleModType::MOD_TYRE_SMOKE)
				{
					int tire_smoke_color[3]{};
					VEHICLE::GET_VEHICLE_TYRE_SMOKE_COLOR(vehicle, &tire_smoke_color[0], &tire_smoke_color[1], &tire_smoke_color[2]);
					vehicle_json[tire_smoke_color_key] = tire_smoke_color;
				}
				else if (slot == (int)VehicleModType::MOD_XENON_LIGHTS)
					vehicle_json[headlight_color_key] = VEHICLE::GET_VEHICLE_XENON_LIGHT_COLOR_INDEX(vehicle);
			}

		for (int extra = (int)CustomVehicleModType::MOD_EXTRA_14; extra <= (int)CustomVehicleModType::MOD_EXTRA_1; ++extra)
			if (auto id = (extra - (int)CustomVehicleModType::MOD_EXTRA_1) * -1; VEHICLE::DOES_EXTRA_EXIST(vehicle, id))
				vehicle_extras[id] = VEHICLE::IS_VEHICLE_EXTRA_TURNED_ON(vehicle, id);

		VEHICLE::GET_VEHICLE_COLOURS(vehicle, &primary_color, &secondary_color);
		VEHICLE::GET_VEHICLE_EXTRA_COLOURS(vehicle, &pearlescent_color, &wheel_color);

		vehicle_json[vehicle_model_hash_key] = vehicle_hash;
		vehicle_json[primary_color_key] = primary_color;
		vehicle_json[secondary_color_key] = secondary_color;

		if (VEHICLE::GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(vehicle))
		{
			int custom_primary_color[3]{};
			VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, &custom_primary_color[0], &custom_primary_color[1], &custom_primary_color[2]);
			vehicle_json[custom_primary_color_key] = custom_primary_color;
		}

		if (VEHICLE::GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(vehicle))
		{
			int custom_secondary_color[3]{};
			VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, &custom_secondary_color[0], &custom_secondary_color[1], &custom_secondary_color[2]);
			vehicle_json[custom_secondary_color_key] = custom_secondary_color;
		}

		vehicle_json[vehicle_window_tint_key] = VEHICLE::GET_VEHICLE_WINDOW_TINT(vehicle);
		vehicle_json[pearlescent_color_key] = pearlescent_color;
		vehicle_json[wheel_color_key] = wheel_color;
		vehicle_json[tire_can_burst] = VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(vehicle);
		vehicle_json[vehicle_extras_key] = vehicle_extras;
		vehicle_json[wheel_type_key] = VEHICLE::GET_VEHICLE_WHEEL_TYPE(vehicle);

		if ((VEHICLE::GET_VEHICLE_LIVERY_COUNT(vehicle) > 1) && VEHICLE::GET_VEHICLE_LIVERY(vehicle) >= 0)
			vehicle_json[vehicle_livery_key] = VEHICLE::GET_VEHICLE_LIVERY(vehicle);

		if (VEHICLE::IS_THIS_MODEL_A_CAR(vehicle_hash) || VEHICLE::IS_THIS_MODEL_A_BIKE(vehicle_hash))
		{
			bool neon_lights[4]{};
			for (int i = (int)NeonLightLocations::NEON_LEFT; i <= (int)NeonLightLocations::NEON_BACK; i++)
				neon_lights[i] = VEHICLE::GET_VEHICLE_NEON_ENABLED(vehicle, i);

			int neon_color[3]{};
			VEHICLE::GET_VEHICLE_NEON_COLOUR(vehicle, &neon_color[0], &neon_color[1], &neon_color[2]);

			int interior_color, dashboard_color;
			VEHICLE::GET_VEHICLE_EXTRA_COLOUR_5(vehicle, &interior_color);
			VEHICLE::GET_VEHICLE_EXTRA_COLOUR_6(vehicle, &dashboard_color);

			vehicle_json[plate_text_key] = VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT(vehicle);
			vehicle_json[plate_text_index_key] = VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(vehicle);
			vehicle_json[drift_tires] = VEHICLE::GET_DRIFT_TYRES_SET(vehicle);
			vehicle_json[neon_color_key] = neon_color;
			vehicle_json[neon_lights_key] = neon_lights;
			vehicle_json[interior_color_key] = interior_color;
			vehicle_json[dash_color_key] = dashboard_color;
		}

		return vehicle_json;
	}

	void SavedVehicles::Save(std::string folderName, std::string fileName)
	{
		FiberPool::Push([folderName, fileName] {
			if (auto veh = Self::GetVehicle(); veh && veh.IsValid())
			{
				const auto file = SavedVehicles::CheckFolder(folderName).GetFile(fileName);
				std::ofstream file_stream(file.Path(), std::ios::out | std::ios::trunc);
				file_stream << SavedVehicles::GetJson(veh).dump(4);
				file_stream.close();
			}
			else
				Notifications::Show("Persist Car", "Tried to save a vehicle which does not exist", NotificationType::Warning);
		});
	}

	void SavedVehicles::Load(std::string folderName, std::string fileName, bool spawnInside)
	{
		if (!fileName.empty())
			FiberPool::Push([folderName, fileName, spawnInside] {
				const auto file = CheckFolder(folderName).GetFile(fileName).Path();

				if (!std::filesystem::exists(file))
				{
					Notifications::Show("Persist Car", "File does not exist.", NotificationType::Error);
					return;
				}

				std::ifstream file_stream(file);
				nlohmann::json vehicle_json;

				try
				{
					file_stream >> vehicle_json;
					auto veh = SpawnFromJson(vehicle_json);

					if (veh)
					{
						if (spawnInside)
							Self::GetPed().SetInVehicle(veh.GetHandle());
						Notifications::Show("Persist Car", std::format("Spawned {}", fileName), NotificationType::Success);
					}
					else
						Notifications::Show("Persist Car", std::format("Unable to spawn {}", fileName), NotificationType::Error);
				}
				catch (std::exception& e)
				{
					LOG(WARNING) << e.what();
				}

				file_stream.close();
			});
		else
			Notifications::Show("Persist Car", "Select a file first", NotificationType::Warning);
	}

	Vehicle SavedVehicles::SpawnFromJson(nlohmann::json vehicle_json)
	{
		const Hash vehicle_hash = vehicle_json[vehicle_model_hash_key];
		auto veh = Vehicle::Create(vehicle_hash, Vehicle::GetSpawnLocRelToPed(Self::GetPed().GetHandle(), vehicle_hash), Self::GetPed().GetHeading());

		if (veh != nullptr)
		{
			ScriptMgr::Yield();

			auto vehicle = veh.GetHandle();

			VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);

			if (!(vehicle_json[primary_color_key].is_null() || vehicle_json[secondary_color_key].is_null()))
				VEHICLE::SET_VEHICLE_COLOURS(vehicle, vehicle_json[primary_color_key], vehicle_json[secondary_color_key]);

			if (!vehicle_json[custom_primary_color_key].is_null())
			{
				std::vector<int> primary_custom_color = vehicle_json[custom_primary_color_key];
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, primary_custom_color[0], primary_custom_color[1], primary_custom_color[2]);
			}
			if (!vehicle_json[custom_secondary_color_key].is_null())
			{
				std::vector<int> secondary_custom_color = vehicle_json[custom_secondary_color_key];
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, secondary_custom_color[0], secondary_custom_color[1], secondary_custom_color[2]);
			}

			if (!vehicle_json[vehicle_window_tint_key].is_null())
				VEHICLE::SET_VEHICLE_WINDOW_TINT(vehicle, vehicle_json[vehicle_window_tint_key]);
			if (!(vehicle_json[pearlescent_color_key].is_null() || vehicle_json[wheel_color_key].is_null()))
				VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle, vehicle_json[pearlescent_color_key], vehicle_json[wheel_color_key]);
			if (!vehicle_json[tire_can_burst].is_null())
				VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(vehicle, vehicle_json[tire_can_burst]);

			if (!vehicle_json[wheel_type_key].is_null())
				VEHICLE::SET_VEHICLE_WHEEL_TYPE(vehicle, vehicle_json[wheel_type_key]);

			if (!vehicle_json[vehicle_livery_key].is_null())
				VEHICLE::SET_VEHICLE_LIVERY(vehicle, vehicle_json[vehicle_livery_key]);

			if (VEHICLE::IS_THIS_MODEL_A_CAR(vehicle_hash) || VEHICLE::IS_THIS_MODEL_A_BIKE(vehicle_hash))
			{
				if (!vehicle_json[neon_color_key].is_null())
				{
					std::vector<int> neon_color = vehicle_json[neon_color_key];
					VEHICLE::SET_VEHICLE_NEON_COLOUR(vehicle, neon_color[0], neon_color[1], neon_color[2]);
				}
				if (!vehicle_json[neon_lights_key].is_null())
				{
					std::vector<bool> neon_lights = vehicle_json[neon_lights_key];
					for (int i = (int)NeonLightLocations::NEON_LEFT; i <= (int)NeonLightLocations::NEON_BACK; i++)
						VEHICLE::SET_VEHICLE_NEON_ENABLED(vehicle, i, neon_lights[i]);
				}
				if (!vehicle_json[plate_text_key].is_null())
					VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(vehicle, vehicle_json[plate_text_key].get<std::string>().c_str());
				if (!vehicle_json[plate_text_index_key].is_null())
					VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(vehicle, vehicle_json[plate_text_index_key]);
				if (!vehicle_json[drift_tires].is_null())
					VEHICLE::SET_DRIFT_TYRES(vehicle, vehicle_json[drift_tires]);

				if (!vehicle_json[interior_color_key].is_null())
					VEHICLE::SET_VEHICLE_EXTRA_COLOUR_5(vehicle, vehicle_json[interior_color_key]);
				if (!vehicle_json[dash_color_key].is_null())
					VEHICLE::SET_VEHICLE_EXTRA_COLOUR_6(vehicle, vehicle_json[dash_color_key]);
			}

			for (int i = (int)VehicleModType::MOD_SPOILERS; i < (int)VehicleModType::MOD_LIGHTBAR; i++)
				if (!vehicle_json[mod_names[i]].is_null())
				{
					if (vehicle_json[mod_names[i]].is_array())
					{
						std::vector<int> mod = vehicle_json[mod_names[i]];
						VEHICLE::SET_VEHICLE_MOD(vehicle, i, mod[0], mod[1]);
					}
					else
					{
						if (i == (int)VehicleModType::MOD_TYRE_SMOKE && !vehicle_json[tire_smoke_color_key].is_null())
						{
							std::vector<int> tire_smoke_color = vehicle_json[tire_smoke_color_key];
							VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(vehicle, tire_smoke_color[0], tire_smoke_color[1], tire_smoke_color[2]);
						}
						else if (i == (int)VehicleModType::MOD_XENON_LIGHTS && !vehicle_json[headlight_color_key].is_null())
							VEHICLE::SET_VEHICLE_XENON_LIGHT_COLOR_INDEX(vehicle, vehicle_json[headlight_color_key]);

						VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, i, TRUE);
					}
				}

			if (!vehicle_json[vehicle_extras_key].is_null())
			{
				std::map<int, int> vehicle_extras = vehicle_json[vehicle_extras_key];
				for (const auto& [extra, extra_enabled] : vehicle_extras)
					VEHICLE::SET_VEHICLE_EXTRA(vehicle, extra, extra_enabled ? 0 : 1);
			}
		}

		return veh;
	}
}

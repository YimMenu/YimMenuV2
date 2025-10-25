#include "VehicleEditor.hpp"

#include "core/backend/FiberPool.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "game/gta/VehicleModel.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/data/VehicleValues.hpp"
#include "game/gta/data/ModNames.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<Category> BuildVehicleEditorMenu()
	{
		static int currentVeh = 0;
		static std::string vehName = "";
		static bool preparingVehicle = false;
		static bool isBennys = false;
		static int selected_slot = -1;
		static char plate[9] = "";

		static std::map<int, int32_t> owned_mods{};
		static std::map<int, std::string> slot_display_names{};
		static std::map<int, std::map<int, std::string>> mod_display_names{};

		static std::map<std::string, std::vector<int>> front_wheel_map{};
		static std::map<std::string, std::vector<int>> rear_wheel_map{};
		static int front_wheel_stock_mod = -1;
		static int rear_wheel_stock_mod = -1;

		static auto prepareVehicle = [] {
			if (currentVeh != -1) // when == -1 dont change selected slot
				selected_slot = -1;

			preparingVehicle = true;

			FiberPool::Push([] {
				currentVeh = Self::GetVehicle().GetHandle();
				auto model = Self::GetVehicle().GetModel();
				front_wheel_stock_mod = -1;
				rear_wheel_stock_mod = -1;
				vehName = Self::GetVehicle().GetFullName();
				owned_mods = Self::GetVehicle().GetOwnedMods();
				isBennys = VehicleModel::IsBennys(currentVeh);
				strcpy(plate, Self::GetVehicle().GetPlateText().c_str());

				if (!HUD::HAS_THIS_ADDITIONAL_TEXT_LOADED("MOD_MNU", 10))
				{
					HUD::CLEAR_ADDITIONAL_TEXT(10, TRUE);
					HUD::REQUEST_ADDITIONAL_TEXT("MOD_MNU", 10);
					ScriptMgr::Yield();
				}

				VEHICLE::SET_VEHICLE_MOD_KIT(currentVeh, 0);

				std::map<int, std::string> tmp_slot_display_names;
				std::map<int, std::map<int, std::string>> tmp_mod_display_names;
				std::map<std::string, std::vector<int>> tmp_front_wheel_map;
				std::map<std::string, std::vector<int>> tmp_rear_wheel_map;

				tmp_slot_display_names[(int)CustomVehicleModType::MOD_PLATE_STYLE] = "Plate Style";
				tmp_slot_display_names[(int)CustomVehicleModType::MOD_WINDOW_TINT] = "Window Tint";
				tmp_slot_display_names[(int)CustomVehicleModType::MOD_WHEEL_TYPE] = "Wheel Type";

				tmp_mod_display_names[(int)CustomVehicleModType::MOD_PLATE_STYLE].insert(lscPlateStyles.begin(),
				    lscPlateStyles.end());
				tmp_mod_display_names[(int)CustomVehicleModType::MOD_WINDOW_TINT].insert(lscWindowTintTypes.begin(),
				    lscWindowTintTypes.end());
				tmp_mod_display_names[(int)CustomVehicleModType::MOD_WHEEL_TYPE].insert(lscWheelStyles.begin(),
				    lscWheelStyles.end());

				for (int slot = (int)VehicleModType::MOD_SPOILERS; slot <= (int)VehicleModType::MOD_LIGHTBAR; slot++)
				{
					int count = VEHICLE::GET_NUM_VEHICLE_MODS(currentVeh, slot);
					if (count > 0)
					{
						int owner_mod = owned_mods[slot];

						std::string slot_name = VehicleModel::GetModSlotName(model, currentVeh, slot);
						if (slot_name.empty())
							continue;

						slot_name.append("##" + std::to_string(slot));
						tmp_slot_display_names[slot] = slot_name;

						std::map<int, std::string> mod_names;

						for (int mod = -1; mod < count; mod++)
						{
							if (VehicleModel::CheckModBlacklist(model, slot, mod))
								continue;

							bool is_repeated = false;

							std::string mod_name = VehicleModel::GetModName(model, currentVeh, slot, mod, count);

							if (mod_name.empty() || mod_name == "NULL")
								continue;

							if (slot == (int)VehicleModType::MOD_FRONTWHEEL)
							{
								if (isBennys && mod_name.rfind("Chrome ", 0) == 0)
								{
									std::string new_mod_name = mod_name.substr(7);

									if (tmp_front_wheel_map[new_mod_name].size() > 0)
										mod_name = new_mod_name;
								}

								tmp_front_wheel_map[mod_name].push_back(mod);

								if (mod == owner_mod)
									front_wheel_stock_mod = tmp_front_wheel_map[mod_name][0];
								if (tmp_front_wheel_map[mod_name].size() > 1)
									is_repeated = true;
							}
							else if (slot == (int)VehicleModType::MOD_REARWHEEL)
							{
								if (isBennys && mod_name.rfind("Chrome ", 0) == 0)
								{
									std::string new_mod_name = mod_name.substr(7);

									if (tmp_rear_wheel_map[new_mod_name].size() > 0)
										mod_name = new_mod_name;
								}

								tmp_rear_wheel_map[mod_name].push_back(mod);

								if (mod == owner_mod)
									rear_wheel_stock_mod = tmp_rear_wheel_map[mod_name][0];
								if (tmp_rear_wheel_map[mod_name].size() > 1)
									is_repeated = true;
							}

							if (!is_repeated)
								mod_names[mod] = mod_name;
						}

						tmp_mod_display_names[slot] = mod_names;
					}
				}

				if (tmp_mod_display_names.count((int)VehicleModType::MOD_HORNS) > 0)
					tmp_mod_display_names[(int)VehicleModType::MOD_HORNS].insert(lscMissingHorns.begin(),
					    lscMissingHorns.end());

				slot_display_names = tmp_slot_display_names;
				mod_display_names = tmp_mod_display_names;
				front_wheel_map = tmp_front_wheel_map;
				rear_wheel_map = tmp_rear_wheel_map;

				preparingVehicle = false;
			});
		};

		auto vehicleEditor = std::make_shared<Category>("Vehicle Editor");

		vehicleEditor->AddItem(std::make_unique<ImGuiItem>([] {
			if (!Self::GetVehicle())
			{
				ImGui::Text("Please enter a vehicle.");
				currentVeh = 0;
				return;
			}

			if (preparingVehicle)
				return;

			if (currentVeh != Self::GetVehicle().GetHandle())
			{
				prepareVehicle();
				return;
			}

			ImGui::BeginGroup();
			{
				ImGui::Text("%s", vehName.c_str());
				ImGui::SameLine();
				if (ImGui::Button("Refresh Current Vehicle"))
					FiberPool::Push([] {
						currentVeh = -1;
					});

				ImGui::Spacing();
				{
					ImGui::SetNextItemWidth(150);
					ImGui::InputTextWithHint("##plate", "Plate Number", plate, sizeof(plate), ImGuiInputTextFlags_None);
					ImGui::SameLine();
					if (ImGui::Button("Change Plate"))
						FiberPool::Push([] {
							Self::GetVehicle().SetPlateText(plate);
						});
					ImGui::SameLine();
					if (ImGui::Button("Max Vehicle"))
						FiberPool::Push([] {
							Self::GetVehicle().Upgrade();
							currentVeh = -1;
						});
				}
				ImGui::SeparatorText("Mod Options");
				{
					if (ImGui::Checkbox("Burstible tires", (bool*)&owned_mods[(int)CustomVehicleModType::MOD_TIRE_CAN_BURST]))
						FiberPool::Push([] {
							VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(currentVeh, owned_mods[(int)CustomVehicleModType::MOD_TIRE_CAN_BURST]);
						});
					ImGui::SameLine();
					if (ImGui::Checkbox("Low Grip Tires", (bool*)&owned_mods[(int)CustomVehicleModType::MOD_DRIFT_TIRE]))

						FiberPool::Push([] {
							VEHICLE::SET_DRIFT_TYRES(currentVeh, owned_mods[(int)CustomVehicleModType::MOD_DRIFT_TIRE]);
						});
					ImGui::SameLine();
					if (ImGui::Checkbox("Turbo", (bool*)&owned_mods[(int)VehicleModType::MOD_TURBO]))

						FiberPool::Push([] {
							VEHICLE::TOGGLE_VEHICLE_MOD(currentVeh, (int)VehicleModType::MOD_TURBO, owned_mods[(int)VehicleModType::MOD_TURBO]);
						});
					ImGui::SameLine();
					if (ImGui::Checkbox("Tire Smoke", (bool*)&owned_mods[(int)VehicleModType::MOD_TYRE_SMOKE]))

						FiberPool::Push([] {
							VEHICLE::TOGGLE_VEHICLE_MOD(currentVeh, (int)VehicleModType::MOD_TYRE_SMOKE, owned_mods[(int)VehicleModType::MOD_TYRE_SMOKE]);
						});
				}
				ImGui::SeparatorText("Mod Slots");
				{
					ImGui::BeginGroup();
					{
						ImGui::Text("Slot");
						if (ImGui::BeginListBox("##slot", ImVec2(200, 200)))
						{
							for (const auto& [slot, name] : slot_display_names)
								if (ImGui::Selectable(name.c_str(), slot == selected_slot))
									selected_slot = slot;

							ImGui::EndListBox();
						}
					}
					ImGui::EndGroup();

					if (selected_slot != -1)
					{
						auto wheel_stock_mod = &front_wheel_stock_mod;
						auto wheel_custom = &owned_mods[(int)CustomVehicleModType::MOD_FRONTWHEEL_VAR];
						bool is_wheel_mod = false;

						if (selected_slot == (int)VehicleModType::MOD_FRONTWHEEL)
							is_wheel_mod = true;
						else if (selected_slot == (int)VehicleModType::MOD_REARWHEEL)
						{
							wheel_stock_mod = &rear_wheel_stock_mod;
							wheel_custom = &owned_mods[(int)CustomVehicleModType::MOD_REARWHEEL_VAR];
							is_wheel_mod = true;
						}
						else
							is_wheel_mod = false;

						ImGui::SameLine();
						ImGui::BeginGroup();
						{
							ImGui::Text("Mod");
							if (ImGui::BeginListBox("##mod", ImVec2(240, 200)))
							{
								for (const auto& it : mod_display_names[selected_slot])
								{
									const auto& mod = it.first;
									const auto& name = it.second;

									bool item_selected = mod == owned_mods[selected_slot];

									if (is_wheel_mod)
										item_selected = mod == *wheel_stock_mod;

									if (ImGui::Selectable(name.c_str(), item_selected))
									{
										FiberPool::Push([&mod, is_wheel_mod, wheel_stock_mod, wheel_custom, name] {
											if (selected_slot >= 0)
											{
												VEHICLE::SET_VEHICLE_MOD(currentVeh, selected_slot, mod, 0);
												owned_mods[selected_slot] = mod;

												if (is_wheel_mod)
												{
													*wheel_stock_mod = mod;
													*wheel_custom = 0;
												}
											}
											else if (selected_slot == (int)CustomVehicleModType::MOD_WINDOW_TINT)
											{
												VEHICLE::SET_VEHICLE_WINDOW_TINT(currentVeh, mod);
												owned_mods[selected_slot] = mod;
											}
											else if (selected_slot == (int)CustomVehicleModType::MOD_WHEEL_TYPE)
											{
												VEHICLE::SET_VEHICLE_WHEEL_TYPE(currentVeh, mod);
												VEHICLE::SET_VEHICLE_MOD(currentVeh, (int)VehicleModType::MOD_FRONTWHEEL, 0, 0);
												VEHICLE::SET_VEHICLE_MOD(currentVeh, (int)VehicleModType::MOD_REARWHEEL, 0, 0);
												currentVeh = -1;
											}
											else if (selected_slot == (int)CustomVehicleModType::MOD_PLATE_STYLE)
											{
												VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(currentVeh, mod);
												owned_mods[selected_slot] = mod;
											}
										});
									}
								}
								ImGui::EndListBox();
							}
						}
						ImGui::EndGroup();

						if (is_wheel_mod && *wheel_stock_mod != -1)
						{
							ImGui::SameLine();
							ImGui::BeginGroup();
							{
								auto wheel_map = selected_slot == (int)VehicleModType::MOD_REARWHEEL ? rear_wheel_map : front_wheel_map;

								ImGui::Text("Style");
								if (ImGui::BeginListBox("##style", ImVec2(200, 200)))
								{
									std::string mod_name = mod_display_names[selected_slot][*wheel_stock_mod];
									auto wheel_mods = wheel_map[mod_name];

									for (int i = 0; i < wheel_mods.size(); i++)
									{
										int& mod = wheel_mods[i];

										int should_custom = 0;

										// bennys fix
										if (!isBennys)
										{
											if (i == 0 && ImGui::Selectable("Stock", mod == owned_mods[selected_slot] && *wheel_custom == 0))
												FiberPool::Push([&mod] {
													VEHICLE::SET_VEHICLE_MOD(currentVeh, selected_slot, mod, 0);
													currentVeh = -1;
												});
											should_custom = 1;
										}

										if (ImGui::Selectable(("Style " + std::to_string(mod)).c_str(), mod == owned_mods[selected_slot] && *wheel_custom == should_custom))
											FiberPool::Push([&mod, should_custom] {
												VEHICLE::SET_VEHICLE_MOD(currentVeh, selected_slot, mod, should_custom);
												currentVeh = -1;
											});
									}
									ImGui::EndListBox();
								}
							}
							ImGui::EndGroup();
						}
					}
				}
				ImGui::SeparatorText("Extras");
				{
					for (int extra = (int)CustomVehicleModType::MOD_EXTRA_1; extra >= (int)CustomVehicleModType::MOD_EXTRA_14; extra--)
						if (owned_mods.find(extra) != owned_mods.end())
						{
							int id = (extra - (int)CustomVehicleModType::MOD_EXTRA_1) * -1;
							bool is_extra_enabled = owned_mods[extra] == 1;
							if (ImGui::Checkbox(std::format("{}###extra{}", id, id).c_str(), &is_extra_enabled))
							{
								owned_mods[extra] = is_extra_enabled;
								FiberPool::Push([id, is_extra_enabled] {
									VEHICLE::SET_VEHICLE_EXTRA(currentVeh, id, !is_extra_enabled);
								});
							}
							ImGui::SameLine();
						}
					ImGui::NewLine();
				}
				ImGui::SeparatorText("Neon Light Options");
				{
					ImGui::PushID("##headlight_en");
					if (ImGui::Checkbox("Headlight", (bool*)&owned_mods[(int)VehicleModType::MOD_XENON_LIGHTS]))
						FiberPool::Push([] {
							VEHICLE::TOGGLE_VEHICLE_MOD(currentVeh, (int)VehicleModType::MOD_XENON_LIGHTS, owned_mods[(int)VehicleModType::MOD_XENON_LIGHTS]);
						});
					ImGui::PopID();
					ImGui::SameLine();
					if (ImGui::Checkbox("Left", (bool*)&owned_mods[(int)CustomVehicleModType::MOD_NEON_LEFT_ON]))
						FiberPool::Push([] {
							VEHICLE::SET_VEHICLE_NEON_ENABLED(currentVeh, (int)NeonLightLocations::NEON_LEFT, owned_mods[(int)CustomVehicleModType::MOD_NEON_LEFT_ON]);
						});
					ImGui::SameLine();
					if (ImGui::Checkbox("Right", (bool*)&owned_mods[(int)CustomVehicleModType::MOD_NEON_RIGHT_ON]))
						FiberPool::Push([] {
							VEHICLE::SET_VEHICLE_NEON_ENABLED(currentVeh, (int)NeonLightLocations::NEON_RIGHT, owned_mods[(int)CustomVehicleModType::MOD_NEON_RIGHT_ON]);
						});
					ImGui::SameLine();
					if (ImGui::Checkbox("Front", (bool*)&owned_mods[(int)CustomVehicleModType::MOD_NEON_FRONT_ON]))
						FiberPool::Push([] {
							VEHICLE::SET_VEHICLE_NEON_ENABLED(currentVeh, (int)NeonLightLocations::NEON_FRONT, owned_mods[(int)CustomVehicleModType::MOD_NEON_FRONT_ON]);
						});
					ImGui::SameLine();
					if (ImGui::Checkbox("Back", (bool*)&owned_mods[(int)CustomVehicleModType::MOD_NEON_BACK_ON]))
						FiberPool::Push([] {
							VEHICLE::SET_VEHICLE_NEON_ENABLED(currentVeh, (int)NeonLightLocations::NEON_BACK, owned_mods[(int)CustomVehicleModType::MOD_NEON_BACK_ON]);
						});
				}
				ImGui::SeparatorText("Color Options");
				{
					static int color_to_change = 0;
					static int color_type = 9;

					if ((color_to_change == 7 && !owned_mods[(int)VehicleModType::MOD_XENON_LIGHTS]) || (color_to_change == 5 && !owned_mods[(int)VehicleModType::MOD_TYRE_SMOKE]))
					{
						color_to_change = 0;
						color_type = 9;
					}

					if (ImGui::BeginListBox("##color_options", ImVec2(120, 254)))
					{
						if (ImGui::Selectable("Primary", color_to_change == 0))
							color_to_change = 0;
						if (ImGui::Selectable("Secondary", color_to_change == 1))
							color_to_change = 1;
						if (ImGui::Selectable("Pearlescent", color_to_change == 2))
						{
							color_to_change = 2;
							color_type = 7;
						}
						if (ImGui::Selectable("Interior", color_to_change == 3))
						{
							color_to_change = 3;
							color_type = 10;
						}
						if (ImGui::Selectable("Dashboard", color_to_change == 4))
						{
							color_to_change = 4;
							color_type = 11;
						}

						if (!owned_mods[(int)VehicleModType::MOD_TYRE_SMOKE])
							ImGui::BeginDisabled();
						if (ImGui::Selectable("Tire Smoke", color_to_change == 5))
						{
							color_to_change = 5;
							color_type = 9;
						}
						if (!owned_mods[(int)VehicleModType::MOD_TYRE_SMOKE])
							ImGui::EndDisabled();

						if (ImGui::Selectable("Wheel Color", color_to_change == 6))
						{
							color_to_change = 6;
							color_type = 8;
						}

						if (!owned_mods[(int)VehicleModType::MOD_XENON_LIGHTS])
							ImGui::BeginDisabled();
						ImGui::PushID("##headlight_col");
						if (ImGui::Selectable("Headlight", color_to_change == 7))
						{
							color_to_change = 7;
							color_type = 12;
						}
						ImGui::PopID();
						if (!owned_mods[(int)VehicleModType::MOD_XENON_LIGHTS])
							ImGui::EndDisabled();

						if (ImGui::Selectable("Neon", color_to_change == 8))
						{
							color_to_change = 8;
							color_type = 9;
						}

						ImGui::EndListBox();
					}

					if (color_to_change == 0 || color_to_change == 1)
					{
						if (color_type > 6)
							color_type = 9;

						// primary and secondary color

						ImGui::SameLine();
						if (ImGui::BeginListBox("##colors", ImVec2(140, 254)))
						{
							if (ImGui::Selectable("Custom", color_type == 9))
								color_type = 9;

							if (ImGui::Selectable("Remove Custom", false))
								FiberPool::Push([] {
									if (color_to_change == 0)
										VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(currentVeh);
									else
										VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(currentVeh);
									VEHICLE::SET_VEHICLE_COLOURS(currentVeh, owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL], owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL]);
								});

							if (ImGui::Selectable("Chrome", color_type == 0))
								color_type = 0;
							if (ImGui::Selectable("Classic", color_type == 1))
								color_type = 1;
							if (ImGui::Selectable("Matte", color_type == 2))
								color_type = 2;
							if (ImGui::Selectable("Metals", color_type == 3))
								color_type = 3;
							if (ImGui::Selectable("Util", color_type == 4))
								color_type = 4;
							if (ImGui::Selectable("Worn", color_type == 5))
								color_type = 5;
							if (ImGui::Selectable("Chameleon", color_type == 6))
								color_type = 6;

							ImGui::EndListBox();
						}
					}
					else if (color_to_change == 7)
						ImGui::SameLine();

					// **********************************************************************************************************************************

					if (color_type == 9)
					{
						// custom color

						static float color[3] = {1, 1, 1};
						auto color_r = &owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL_R];
						auto color_g = &owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL_G];
						auto color_b = &owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL_B];

						if (color_to_change == 1)
						{
							color_r = &owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL_R];
							color_g = &owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL_G];
							color_b = &owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL_B];
						}
						else if (color_to_change == 2)
						{
							color_r = &owned_mods[(int)CustomVehicleModType::MOD_TIRESMOKE_COL_R];
							color_g = &owned_mods[(int)CustomVehicleModType::MOD_TIRESMOKE_COL_G];
							color_b = &owned_mods[(int)CustomVehicleModType::MOD_TIRESMOKE_COL_B];
						}
						else if (color_to_change == 3)
						{
							color_r = &owned_mods[(int)CustomVehicleModType::MOD_NEON_COL_R];
							color_g = &owned_mods[(int)CustomVehicleModType::MOD_NEON_COL_G];
							color_b = &owned_mods[(int)CustomVehicleModType::MOD_NEON_COL_B];
						}

						color[0] = (float)*color_r / 255;
						color[1] = (float)*color_g / 255;
						color[2] = (float)*color_b / 255;

						if (color_to_change == 5)
						{
							ImGui::SameLine();
							if (ImGui::BeginListBox("##tire_smoke_rgb", ImVec2(140, 254)))
							{
								for (const auto& it : lscTireSmokeRgb)
								{
									auto& name = it.first;
									auto& rgb = it.second;

									if (ImGui::Selectable(name, false))
									{
										FiberPool::Push([&rgb] {
											VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(currentVeh, rgb[0], rgb[1], rgb[2]);
										});
										*color_r = rgb[0];
										*color_g = rgb[1];
										*color_b = rgb[2];
									}
								}

								ImGui::EndListBox();
							}
						}
						else if (color_to_change == 8)
						{
							ImGui::SameLine();
							if (ImGui::BeginListBox("##neon_rgb", ImVec2(140, 254)))
							{
								for (const auto& it : lscNeonRgb)
								{
									auto& name = it.first;
									auto& rgb = it.second;

									if (ImGui::Selectable(name, false))
									{
										FiberPool::Push([&rgb] {
											VEHICLE::SET_VEHICLE_NEON_COLOUR(currentVeh, rgb[0], rgb[1], rgb[2]);
										});
										*color_r = rgb[0];
										*color_g = rgb[1];
										*color_b = rgb[2];
									}
								}

								ImGui::EndListBox();
							}
						}

						ImGui::SameLine();
						ImGui::SetNextItemWidth(214);
						if (ImGui::ColorPicker3("Custom Vehicle Color", color, ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_DisplayHSV | ImGuiColorEditFlags_InputHSV | ImGuiColorEditFlags_DisplayHex))
						{
							*color_r = (int)(color[0] * 255);
							*color_g = (int)(color[1] * 255);
							*color_b = (int)(color[2] * 255);

							FiberPool::Push([color_r, color_g, color_b] {
								switch (color_to_change)
								{
								case 0:
									VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(currentVeh, *color_r, *color_g, *color_b);
									break;
								case 1:
									VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(currentVeh, *color_r, *color_g, *color_b);
									break;
								case 5:
									VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(currentVeh, *color_r, *color_g, *color_b);
									break;
								case 8:
									VEHICLE::SET_VEHICLE_NEON_COLOUR(currentVeh, *color_r, *color_g, *color_b);
									break;
								}
							});
						}
					}
					else
					{
						// standard color

						int selected_color = 0;
						switch (color_type)
						{
						case 7: selected_color = owned_mods[(int)CustomVehicleModType::MOD_PEARLESCENT_COL]; break;
						case 8: selected_color = owned_mods[(int)CustomVehicleModType::MOD_WHEEL_COL]; break;
						case 10: selected_color = owned_mods[(int)CustomVehicleModType::MOD_INTERIOR_COL]; break;
						case 11: selected_color = owned_mods[(int)CustomVehicleModType::MOD_DASHBOARD_COL]; break;
						case 12: selected_color = owned_mods[(int)CustomVehicleModType::MOD_XENON_COL]; break;
						default:
							selected_color = (color_to_change == 0) ? owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL] : owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL];
						}

						if (color_type != 12)
							ImGui::SameLine();

						if (ImGui::BeginListBox("##color", ImVec2(180, 254)))
						{
							switch (color_type)
							{
							case 0: //Chrome
							{
								if (ImGui::Selectable("Chrome", selected_color == (int)VehicleColorsChrome::COLOR_CHROME))
								{
									if (color_to_change == 0)
										owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL] = (int)VehicleColorsChrome::COLOR_CHROME;
									else
										owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL] = (int)VehicleColorsChrome::COLOR_CHROME;
									FiberPool::Push([] {
										VEHICLE::SET_VEHICLE_COLOURS(currentVeh, owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL], owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL]);
									});
								}
								break;
							}
							case 1: //Classic
							{
								for (const auto& [color, name] : lscClassicColors)
								{
									if (ImGui::Selectable(name, selected_color == color))
									{
										selected_color = color;
										if (color_to_change == 0)
											owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL] = color;
										else
											owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL] = color;
										FiberPool::Push([] {
											VEHICLE::SET_VEHICLE_COLOURS(currentVeh, owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL], owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL]);
										});
									}
								}
								break;
							}
							case 2: //Matte
							{
								for (const auto& [color, name] : lscMatteColors)
								{
									if (ImGui::Selectable(name, selected_color == color))
									{
										selected_color = color;
										if (color_to_change == 0)
											owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL] = color;
										else
											owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL] = color;
										FiberPool::Push([] {
											VEHICLE::SET_VEHICLE_COLOURS(currentVeh, owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL], owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL]);
										});
									}
								}
								break;
							}
							case 3: //Metals
							{
								for (const auto& [color, name] : lscMetalColors)
								{
									if (ImGui::Selectable(name, selected_color == color))
									{
										selected_color = color;
										if (color_to_change == 0)
											owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL] = color;
										else
											owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL] = color;
										FiberPool::Push([] {
											VEHICLE::SET_VEHICLE_COLOURS(currentVeh, owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL], owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL]);
										});
									}
								}
								break;
							}
							case 4: //Util
							{
								for (const auto& [color, name] : lscUtilColors)
								{
									if (ImGui::Selectable(name, selected_color == color))
									{
										selected_color = color;
										if (color_to_change == 0)
											owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL] = color;
										else
											owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL] = color;
										FiberPool::Push([] {
											VEHICLE::SET_VEHICLE_COLOURS(currentVeh, owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL], owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL]);
										});
									}
								}
								break;
							}
							case 5: //Worn
							{
								for (const auto& [color, name] : lscWornColors)
								{
									if (ImGui::Selectable(name, selected_color == color))
									{
										selected_color = color;
										if (color_to_change == 0)
											owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL] = color;
										else
											owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL] = color;
										FiberPool::Push([] {
											VEHICLE::SET_VEHICLE_COLOURS(currentVeh, owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL], owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL]);
										});
									}
								}
								break;
							}
							case 6: //Chameleon
							{
								for (const auto& [color, name] : lscChameleonColors)
								{
									if (ImGui::Selectable(name, selected_color == color))
									{
										selected_color = color;
										if (color_to_change == 0)
											owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL] = color;
										else
											owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL] = color;
										FiberPool::Push([] {
											VEHICLE::SET_VEHICLE_COLOURS(currentVeh, owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL], owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL]);
										});
									}
								}
								break;
							}
							case 7: //Pearlescent
							{
								for (const auto& [color, name] : lscClassicColors)
								{
									if (ImGui::Selectable(name, selected_color == color))
									{
										selected_color = color;
										owned_mods[(int)CustomVehicleModType::MOD_PEARLESCENT_COL] = color;
										FiberPool::Push([] {
											VEHICLE::SET_VEHICLE_EXTRA_COLOURS(currentVeh, owned_mods[(int)CustomVehicleModType::MOD_PEARLESCENT_COL], owned_mods[(int)CustomVehicleModType::MOD_WHEEL_COL]);
										});
									}
								}
								break;
							}
							case 8: //Wheel Color
							{
								constexpr auto alloy_color = 156;

								if (ImGui::Selectable("Alloy", selected_color == alloy_color))
								{
									selected_color = alloy_color;
									owned_mods[(int)CustomVehicleModType::MOD_WHEEL_COL] = alloy_color;
									FiberPool::Push([] {
										VEHICLE::SET_VEHICLE_EXTRA_COLOURS(currentVeh, owned_mods[(int)CustomVehicleModType::MOD_PEARLESCENT_COL], owned_mods[(int)CustomVehicleModType::MOD_WHEEL_COL]);
									});
								}

								for (const auto& [color, name] : lscClassicColors)
								{
									if (ImGui::Selectable(name, selected_color == color))
									{
										selected_color = color;
										owned_mods[(int)CustomVehicleModType::MOD_WHEEL_COL] = color;
										FiberPool::Push([] {
											VEHICLE::SET_VEHICLE_EXTRA_COLOURS(currentVeh, owned_mods[(int)CustomVehicleModType::MOD_PEARLESCENT_COL], owned_mods[(int)CustomVehicleModType::MOD_WHEEL_COL]);
										});
									}
								}

								for (const auto& [color, name] : lscChameleonColors)
								{
									if (ImGui::Selectable(name, selected_color == color))
									{
										selected_color = color;
										owned_mods[(int)CustomVehicleModType::MOD_WHEEL_COL] = color;
										FiberPool::Push([] {
											VEHICLE::SET_VEHICLE_EXTRA_COLOURS(currentVeh, owned_mods[(int)CustomVehicleModType::MOD_PEARLESCENT_COL], owned_mods[(int)CustomVehicleModType::MOD_WHEEL_COL]);
										});
									}
								}

								break;
							}
							case 10: //Interior Color
							{
								for (const auto& [color, name] : lscClassicColors)
								{
									if (ImGui::Selectable(name, selected_color == color))
									{
										selected_color = color;
										owned_mods[(int)CustomVehicleModType::MOD_INTERIOR_COL] = color;
										FiberPool::Push([] {
											VEHICLE::SET_VEHICLE_EXTRA_COLOUR_5(currentVeh, owned_mods[(int)CustomVehicleModType::MOD_INTERIOR_COL]);
										});
									}
								}
								break;
							}
							case 11: //Dashboard Color
							{
								for (const auto& [color, name] : lscClassicColors)
								{
									if (ImGui::Selectable(name, selected_color == color))
									{
										selected_color = color;
										owned_mods[(int)CustomVehicleModType::MOD_DASHBOARD_COL] = color;
										FiberPool::Push([] {
											VEHICLE::SET_VEHICLE_EXTRA_COLOUR_6(currentVeh, owned_mods[(int)CustomVehicleModType::MOD_DASHBOARD_COL]);
										});
									}
								}
								break;
							}
							case 12: //Headlight Color
							{
								for (const auto& [color, name] : lscHeadlightColors)
								{
									if (ImGui::Selectable(name, selected_color == color))
									{
										selected_color = color;
										owned_mods[(int)CustomVehicleModType::MOD_XENON_COL] = color;
										FiberPool::Push([] {
											VEHICLE::SET_VEHICLE_XENON_LIGHT_COLOR_INDEX(currentVeh, owned_mods[(int)CustomVehicleModType::MOD_XENON_COL]);
										});
									}
								}
								break;
							}
							}

							ImGui::EndListBox();
						}
					}
				}
			}
			ImGui::EndGroup();
		}));

		return vehicleEditor;
	}
}

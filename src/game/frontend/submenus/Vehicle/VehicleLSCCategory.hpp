#include "core/backend/FiberPool.hpp"
#include "core/frontend/manager/SubmenuMenuCategory.hpp"
#include "game/backend/Self.hpp"
#include "game/features/lsc/LSC.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/data/lsc_types.hpp"

namespace YimMenu::Submenus
{
	class VehicleLSCCategory : public SubmenuMenuCategory
	{
		using SubmenuMenuCategory::SubmenuMenuCategory;
		void Draw()
		{
			if (!Self::GetVehicle())
			{
				ImGui::Text("Please enter a vehicle.");
				Features::LSC::current_veh = 0;
				return;
			}

			if (Features::LSC::current_veh != Self::GetVehicle().GetHandle())
			{
				Features::LSC::prepare_vehicle();
				return;
			}

			if (Features::LSC::preparing_veh)
				return;

			ImGui::BeginGroup();
			{
				if (ImGui::Button("Refresh###curr_veh"))
					FiberPool::Push([] {
						Features::LSC::current_veh = -1;
					});

				ImGui::Spacing();
				{
					static char plate[9];
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
							Features::LSC::current_veh = -1;
						});
				}
				ImGui::SeparatorText("Mod Options");
				{
					if (ImGui::Checkbox("Burstible tires", (bool*)&Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_TIRE_CAN_BURST]))
						FiberPool::Push([] {
							VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(Features::LSC::current_veh, Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_TIRE_CAN_BURST]);
						});
					ImGui::SameLine();
					if (ImGui::Checkbox("Low Grip Tires", (bool*)&Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_DRIFT_TIRE]))

						FiberPool::Push([] {
							VEHICLE::SET_DRIFT_TYRES(Features::LSC::current_veh, Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_DRIFT_TIRE]);
						});
					ImGui::SameLine();
					if (ImGui::Checkbox("Turbo", (bool*)&Features::LSC::owned_mods[(int)VehicleModType::MOD_TURBO]))

						FiberPool::Push([] {
							VEHICLE::TOGGLE_VEHICLE_MOD(Features::LSC::current_veh, (int)VehicleModType::MOD_TURBO, Features::LSC::owned_mods[(int)VehicleModType::MOD_TURBO]);
						});
					ImGui::SameLine();
					if (ImGui::Checkbox("Tire Smoke", (bool*)&Features::LSC::owned_mods[(int)VehicleModType::MOD_TYRE_SMOKE]))

						FiberPool::Push([] {
							VEHICLE::TOGGLE_VEHICLE_MOD(Features::LSC::current_veh, (int)VehicleModType::MOD_TYRE_SMOKE, Features::LSC::owned_mods[(int)VehicleModType::MOD_TYRE_SMOKE]);
						});
				}
				ImGui::SeparatorText("Mod Slots");
				{
					ImGui::BeginGroup();
					{
						ImGui::Text("Slot");
						if (ImGui::BeginListBox("##slot", ImVec2(200, 200)))
						{
							for (const auto& [slot, name] : Features::LSC::slot_display_names)
								if (ImGui::Selectable(name.c_str(), slot == Features::LSC::selected_slot))
									Features::LSC::selected_slot = slot;

							ImGui::EndListBox();
						}
					}
					ImGui::EndGroup();

					if (Features::LSC::selected_slot != -1)
					{
						auto wheel_stock_mod = &Features::LSC::front_wheel_stock_mod;
						auto wheel_custom = &Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_FRONTWHEEL_VAR];
						bool is_wheel_mod = false;

						if (Features::LSC::selected_slot == (int)VehicleModType::MOD_FRONTWHEEL)
							is_wheel_mod = true;
						else if (Features::LSC::selected_slot == (int)VehicleModType::MOD_REARWHEEL)
						{
							wheel_stock_mod = &Features::LSC::rear_wheel_stock_mod;
							wheel_custom    = &Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_REARWHEEL_VAR];
							is_wheel_mod    = true;
						}
						else
							is_wheel_mod = false;

						ImGui::SameLine();
						ImGui::BeginGroup();
						{
							ImGui::Text("Mod");
							if (ImGui::BeginListBox("##mod", ImVec2(240, 200)))
							{
								for (const auto& it : Features::LSC::mod_display_names[Features::LSC::selected_slot])
								{
									const auto& mod  = it.first;
									const auto& name = it.second;

									bool item_selected = mod == Features::LSC::owned_mods[Features::LSC::selected_slot];

									if (is_wheel_mod)
										item_selected = mod == *wheel_stock_mod;

									if (ImGui::Selectable(name.c_str(), item_selected))
									{
										FiberPool::Push([&mod, is_wheel_mod, wheel_stock_mod, wheel_custom, name] {
											if (Features::LSC::selected_slot >= 0)
											{
												VEHICLE::SET_VEHICLE_MOD(Features::LSC::current_veh, Features::LSC::selected_slot, mod, 0);
												Features::LSC::owned_mods[Features::LSC::selected_slot] = mod;

												if (is_wheel_mod)
												{
													*wheel_stock_mod = mod;
													*wheel_custom    = 0;
												}
											}
											else if (Features::LSC::selected_slot == (int)CustomVehicleModType::MOD_WINDOW_TINT)
											{
												VEHICLE::SET_VEHICLE_WINDOW_TINT(Features::LSC::current_veh, mod);
												Features::LSC::owned_mods[Features::LSC::selected_slot] = mod;
											}
											else if (Features::LSC::selected_slot == (int)CustomVehicleModType::MOD_WHEEL_TYPE)
											{
												VEHICLE::SET_VEHICLE_WHEEL_TYPE(Features::LSC::current_veh, mod);
												VEHICLE::SET_VEHICLE_MOD(Features::LSC::current_veh, (int)VehicleModType::MOD_FRONTWHEEL, 0, 0);
												VEHICLE::SET_VEHICLE_MOD(Features::LSC::current_veh, (int)VehicleModType::MOD_REARWHEEL, 0, 0);
												Features::LSC::current_veh = -1;
											}
											else if (Features::LSC::selected_slot == (int)CustomVehicleModType::MOD_PLATE_STYLE)
											{
												VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(Features::LSC::current_veh, mod);
												Features::LSC::owned_mods[Features::LSC::selected_slot] = mod;
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
								auto wheel_map = Features::LSC::selected_slot == (int)VehicleModType::MOD_REARWHEEL ? Features::LSC::rear_wheel_map : Features::LSC::front_wheel_map;

								ImGui::Text("Style");
								if (ImGui::BeginListBox("##style", ImVec2(200, 200)))
								{
									std::string mod_name = Features::LSC::mod_display_names[Features::LSC::selected_slot][*wheel_stock_mod];
									auto wheel_mods = wheel_map[mod_name];

									for (int i = 0; i < wheel_mods.size(); i++)
									{
										int& mod = wheel_mods[i];

										int should_custom = 0;

										// bennys fix
										if (!Features::LSC::is_bennys)
										{
											if (i == 0 && ImGui::Selectable("Stock", mod == Features::LSC::owned_mods[Features::LSC::selected_slot] && *wheel_custom == 0))
												FiberPool::Push([&mod] {
													VEHICLE::SET_VEHICLE_MOD(Features::LSC::current_veh, Features::LSC::selected_slot, mod, 0);
													Features::LSC::current_veh = -1;
												});
											should_custom = 1;
										}

										if (ImGui::Selectable(("Style " + std::to_string(mod)).c_str(), mod == Features::LSC::owned_mods[Features::LSC::selected_slot] && *wheel_custom == should_custom))
											FiberPool::Push([&mod, should_custom] {
												VEHICLE::SET_VEHICLE_MOD(Features::LSC::current_veh, Features::LSC::selected_slot, mod, should_custom);
												Features::LSC::current_veh = -1;
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
						if (Features::LSC::owned_mods.find(extra) != Features::LSC::owned_mods.end())
						{
							int id                = (extra - (int)CustomVehicleModType::MOD_EXTRA_1) * -1;
							bool is_extra_enabled = Features::LSC::owned_mods[extra] == 1;
							if (ImGui::Checkbox(std::format("{}###extra{}", id, id).c_str(), &is_extra_enabled))
							{
								Features::LSC::owned_mods[extra] = is_extra_enabled;
								FiberPool::Push([id, is_extra_enabled] {
									VEHICLE::SET_VEHICLE_EXTRA(Features::LSC::current_veh, id, !is_extra_enabled);
								});
							}
							ImGui::SameLine();
						}
					ImGui::NewLine();
				}
				ImGui::SeparatorText("Neon Light Options");
				{
					ImGui::PushID("##headlight_en");
					if (ImGui::Checkbox("Headlight", (bool*)&Features::LSC::owned_mods[(int)VehicleModType::MOD_XENON_LIGHTS]))
						FiberPool::Push([] {
							VEHICLE::TOGGLE_VEHICLE_MOD(Features::LSC::current_veh, (int)VehicleModType::MOD_XENON_LIGHTS, Features::LSC::owned_mods[(int)VehicleModType::MOD_XENON_LIGHTS]);
						});
					ImGui::PopID();
					ImGui::SameLine();
					if (ImGui::Checkbox("Left", (bool*)&Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_NEON_LEFT_ON]))
						FiberPool::Push([] {
							VEHICLE::SET_VEHICLE_NEON_ENABLED(Features::LSC::current_veh, (int)NeonLightLocations::NEON_LEFT, Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_NEON_LEFT_ON]);
						});
					ImGui::SameLine();
					if (ImGui::Checkbox("Right", (bool*)&Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_NEON_RIGHT_ON]))
						FiberPool::Push([] {
							VEHICLE::SET_VEHICLE_NEON_ENABLED(Features::LSC::current_veh, (int)NeonLightLocations::NEON_RIGHT, Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_NEON_RIGHT_ON]);
						});
					ImGui::SameLine();
					if (ImGui::Checkbox("Front", (bool*)&Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_NEON_FRONT_ON]))
						FiberPool::Push([] {
							VEHICLE::SET_VEHICLE_NEON_ENABLED(Features::LSC::current_veh, (int)NeonLightLocations::NEON_FRONT, Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_NEON_FRONT_ON]);
						});
					ImGui::SameLine();
					if (ImGui::Checkbox("Back", (bool*)&Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_NEON_BACK_ON]))
						FiberPool::Push([] {
							VEHICLE::SET_VEHICLE_NEON_ENABLED(Features::LSC::current_veh, (int)NeonLightLocations::NEON_BACK, Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_NEON_BACK_ON]);
						});
				}
				ImGui::SeparatorText("Color Options");
				{
					static int color_to_change = 0;
					static int color_type      = 9;

					if ((color_to_change == 7 && !Features::LSC::owned_mods[(int)VehicleModType::MOD_XENON_LIGHTS]) || (color_to_change == 5 && !Features::LSC::owned_mods[(int)VehicleModType::MOD_TYRE_SMOKE]))
					{
						color_to_change = 0;
						color_type      = 9;
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
							color_type      = 7;
						}
						if (ImGui::Selectable("Interior", color_to_change == 3))
						{
							color_to_change = 3;
							color_type      = 10;
						}
						if (ImGui::Selectable("Dashboard", color_to_change == 4))
						{
							color_to_change = 4;
							color_type      = 11;
						}

						if (!Features::LSC::owned_mods[(int)VehicleModType::MOD_TYRE_SMOKE])
							ImGui::BeginDisabled();
						if (ImGui::Selectable("Tire Smoke", color_to_change == 5))
						{
							color_to_change = 5;
							color_type      = 9;
						}
						if (!Features::LSC::owned_mods[(int)VehicleModType::MOD_TYRE_SMOKE])
							ImGui::EndDisabled();

						if (ImGui::Selectable("Wheel Color", color_to_change == 6))
						{
							color_to_change = 6;
							color_type      = 8;
						}

						if (!Features::LSC::owned_mods[(int)VehicleModType::MOD_XENON_LIGHTS])
							ImGui::BeginDisabled();
						ImGui::PushID("##headlight_col");
						if (ImGui::Selectable("Headlight", color_to_change == 7))
						{
							color_to_change = 7;
							color_type      = 12;
						}
						ImGui::PopID();
						if (!Features::LSC::owned_mods[(int)VehicleModType::MOD_XENON_LIGHTS])
							ImGui::EndDisabled();

						if (ImGui::Selectable("Neon", color_to_change == 8))
						{
							color_to_change = 8;
							color_type      = 9;
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
										VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(Features::LSC::current_veh);
									else
										VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(Features::LSC::current_veh);
									VEHICLE::SET_VEHICLE_COLOURS(Features::LSC::current_veh, Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL], Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL]);
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
						auto color_r = &Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL_R];
						auto color_g = &Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL_G];
						auto color_b = &Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL_B];

						if (color_to_change == 1)
						{
							color_r = &Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL_R];
							color_g = &Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL_G];
							color_b = &Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL_B];
						}
						else if (color_to_change == 2)
						{
							color_r = &Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_TIRESMOKE_COL_R];
							color_g = &Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_TIRESMOKE_COL_G];
							color_b = &Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_TIRESMOKE_COL_B];
						}
						else if (color_to_change == 3)
						{
							color_r = &Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_NEON_COL_R];
							color_g = &Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_NEON_COL_G];
							color_b = &Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_NEON_COL_B];
						}

						color[0] = (float)*color_r / 255;
						color[1] = (float)*color_g / 255;
						color[2] = (float)*color_b / 255;

						if (color_to_change == 5)
						{
							ImGui::SameLine();
							if (ImGui::BeginListBox("##tire_smoke_rgb", ImVec2(140, 254)))
							{
								for (const auto& it : lsc_tire_smoke_rgb)
								{
									auto& name = it.first;
									auto& rgb  = it.second;

									if (ImGui::Selectable(name.c_str(), false))
									{
										FiberPool::Push([&rgb] {
											VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(Features::LSC::current_veh, rgb[0], rgb[1], rgb[2]);
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
								for (const auto& it : lsc_neon_rgb)
								{
									auto& name = it.first;
									auto& rgb  = it.second;

									if (ImGui::Selectable(name.c_str(), false))
									{
										FiberPool::Push([&rgb] {
											VEHICLE::SET_VEHICLE_NEON_COLOUR(Features::LSC::current_veh, rgb[0], rgb[1], rgb[2]);
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
						if (ImGui::ColorPicker3("Custom Vehicle Color", color, ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_DisplayHex))
						{
							*color_r = (int)(color[0] * 255);
							*color_g = (int)(color[1] * 255);
							*color_b = (int)(color[2] * 255);

							FiberPool::Push([color_r, color_g, color_b] {
								switch (color_to_change)
								{
								case 0:
									VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Features::LSC::current_veh, *color_r, *color_g, *color_b);
									break;
								case 1:
									VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Features::LSC::current_veh, *color_r, *color_g, *color_b);
									break;
								case 5:
									VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(Features::LSC::current_veh, *color_r, *color_g, *color_b);
									break;
								case 8:
									VEHICLE::SET_VEHICLE_NEON_COLOUR(Features::LSC::current_veh, *color_r, *color_g, *color_b);
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
						case 7:
							selected_color = Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_PEARLESCENT_COL];
							break;
						case 8:
							selected_color = Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_WHEEL_COL];
							break;
						case 10:
							selected_color = Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_INTERIOR_COL];
							break;
						case 11:
							selected_color = Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_DASHBOARD_COL];
							break;
						case 12:
							selected_color = Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_XENON_COL];
							break;
						default:
							selected_color = (color_to_change == 0) ? Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL] : Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL];
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
										Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL] = (int)VehicleColorsChrome::COLOR_CHROME;
									else
										Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL] = (int)VehicleColorsChrome::COLOR_CHROME;
									FiberPool::Push([] {
										VEHICLE::SET_VEHICLE_COLOURS(Features::LSC::current_veh, Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL], Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL]);
									});
								}
								break;
							}
							case 1: //Classic
							{
								for (const auto& [color, name] : lsc_classic_colors)
								{
									if (ImGui::Selectable(name.c_str(), selected_color == color))
									{
										selected_color = color;
										if (color_to_change == 0)
											Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL] = color;
										else
											Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL] = color;
										FiberPool::Push([] {
											VEHICLE::SET_VEHICLE_COLOURS(Features::LSC::current_veh, Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL], Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL]);
										});
									}
								}
								break;
							}
							case 2: //Matte
							{
								for (const auto& [color, name] : lsc_matte_colors)
								{
									if (ImGui::Selectable(name.c_str(), selected_color == color))
									{
										selected_color = color;
										if (color_to_change == 0)
											Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL] = color;
										else
											Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL] = color;
										FiberPool::Push([] {
											VEHICLE::SET_VEHICLE_COLOURS(Features::LSC::current_veh, Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL], Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL]);
										});
									}
								}
								break;
							}
							case 3: //Metals
							{
								for (const auto& [color, name] : lsc_metal_colors)
								{
									if (ImGui::Selectable(name.c_str(), selected_color == color))
									{
										selected_color = color;
										if (color_to_change == 0)
											Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL] = color;
										else
											Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL] = color;
										FiberPool::Push([] {
											VEHICLE::SET_VEHICLE_COLOURS(Features::LSC::current_veh, Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL], Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL]);
										});
									}
								}
								break;
							}
							case 4: //Util
							{
								for (const auto& [color, name] : lsc_util_colors)
								{
									if (ImGui::Selectable(name.c_str(), selected_color == color))
									{
										selected_color = color;
										if (color_to_change == 0)
											Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL] = color;
										else
											Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL] = color;
										FiberPool::Push([] {
											VEHICLE::SET_VEHICLE_COLOURS(Features::LSC::current_veh, Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL], Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL]);
										});
									}
								}
								break;
							}
							case 5: //Worn
							{
								for (const auto& [color, name] : lsc_worn_colors)
								{
									if (ImGui::Selectable(name.c_str(), selected_color == color))
									{
										selected_color = color;
										if (color_to_change == 0)
											Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL] = color;
										else
											Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL] = color;
										FiberPool::Push([] {
											VEHICLE::SET_VEHICLE_COLOURS(Features::LSC::current_veh, Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL], Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL]);
										});
									}
								}
								break;
							}
							case 6: //Chameleon
							{
								for (const auto& [color, name] : lsc_chameleon_colors)
								{
									if (ImGui::Selectable(name.c_str(), selected_color == color))
									{
										selected_color = color;
										if (color_to_change == 0)
											Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL] = color;
										else
											Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL] = color;
										FiberPool::Push([] {
											VEHICLE::SET_VEHICLE_COLOURS(Features::LSC::current_veh, Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL], Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL]);
										});
									}
								}
								break;
							}
							case 7: //Pearlescent
							{
								for (const auto& [color, name] : lsc_classic_colors)
								{
									if (ImGui::Selectable(name.c_str(), selected_color == color))
									{
										selected_color = color;
										Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_PEARLESCENT_COL] = color;
										FiberPool::Push([] {
											VEHICLE::SET_VEHICLE_EXTRA_COLOURS(Features::LSC::current_veh, Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_PEARLESCENT_COL], Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_WHEEL_COL]);
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
									selected_color                                                      = alloy_color;
									Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_WHEEL_COL] = alloy_color;
									FiberPool::Push([] {
										VEHICLE::SET_VEHICLE_EXTRA_COLOURS(Features::LSC::current_veh, Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_PEARLESCENT_COL], Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_WHEEL_COL]);
									});
								}

								for (const auto& [color, name] : lsc_classic_colors)
								{
									if (ImGui::Selectable(name.c_str(), selected_color == color))
									{
										selected_color                                                      = color;
										Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_WHEEL_COL] = color;
										FiberPool::Push([] {
											VEHICLE::SET_VEHICLE_EXTRA_COLOURS(Features::LSC::current_veh, Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_PEARLESCENT_COL], Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_WHEEL_COL]);
										});
									}
								}

								for (const auto& [color, name] : lsc_chameleon_colors)
								{
									if (ImGui::Selectable(name.c_str(), selected_color == color))
									{
										selected_color                                                      = color;
										Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_WHEEL_COL] = color;
										FiberPool::Push([] {
											VEHICLE::SET_VEHICLE_EXTRA_COLOURS(Features::LSC::current_veh, Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_PEARLESCENT_COL], Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_WHEEL_COL]);
										});
									}
								}

								break;
							}
							case 10: //Interior Color
							{
								for (const auto& [color, name] : lsc_classic_colors)
								{
									if (ImGui::Selectable(name.c_str(), selected_color == color))
									{
										selected_color                                                         = color;
										Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_INTERIOR_COL] = color;
										FiberPool::Push([] {
											VEHICLE::SET_VEHICLE_EXTRA_COLOUR_5(Features::LSC::current_veh, Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_INTERIOR_COL]);
										});
									}
								}
								break;
							}
							case 11: //Dashboard Color
							{
								for (const auto& [color, name] : lsc_classic_colors)
								{
									if (ImGui::Selectable(name.c_str(), selected_color == color))
									{
										selected_color                                                          = color;
										Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_DASHBOARD_COL] = color;
										FiberPool::Push([] {
											VEHICLE::SET_VEHICLE_EXTRA_COLOUR_6(Features::LSC::current_veh, Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_DASHBOARD_COL]);
										});
									}
								}
								break;
							}
							case 12: //Headlight Color
							{
								for (const auto& [color, name] : lsc_headlight_colors)
								{
									if (ImGui::Selectable(name.c_str(), selected_color == color))
									{
										selected_color                                                      = color;
										Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_XENON_COL] = color;
										FiberPool::Push([] {
											VEHICLE::SET_VEHICLE_XENON_LIGHT_COLOR_INDEX(Features::LSC::current_veh, Features::LSC::owned_mods[(int)CustomVehicleModType::MOD_XENON_COL]);
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
		}
	};
}
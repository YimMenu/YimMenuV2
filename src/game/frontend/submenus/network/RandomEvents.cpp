#include "RandomEvents.hpp"
#include "core/backend/FiberPool.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/backend/Self.hpp"
#include "game/backend/Tunables.hpp"
#include "game/gta/Scripts.hpp"
#include "game/gta/ScriptFunction.hpp"
#include "game/pointers/Pointers.hpp"
#include "types/script/globals/GPBD_FM_2.hpp"
#include "types/script/globals/GSBD_RandomEvents.hpp"
#include "types/script/locals/FMRandomEvents.hpp"
#include "types/script/ScriptEvent.hpp"
#include "types/script/GtaThread.hpp"
#include "types/script/CGameScriptHandlerNetComponent.hpp"
#include "types/network/CNetGamePlayer.hpp"

namespace YimMenu::Submenus
{
	enum eRandomEvent
	{
		DRUG_VEHICLE,
		MOVIE_PROPS,
		GOLDEN_GUN,
		VEHICLE_LIST,
		SLASHER,
		PHANTOM_CAR,
		SIGHTSEEING,
		SMUGGLER_TRAIL,
		CERBERUS,
		SMUGGLER_PLANE,
		CRIME_SCENE,
		METAL_DETECTOR,
		CONVOY,
		ROBBERY,
		XMAS_MUGGER,
		BANK_SHOOTOUT,
		ARMOURED_TRUCK,
		POSSESSED_ANIMALS,
		GHOSTHUNT,
		XMAS_TRUCK,
		COMMUNITY_OUTREACH,

		MAX_EVENTS
	};

	static constexpr std::array randomEventNames = {
		"Drug Vehicle",
		"Movie Props",
		"Sleeping Guard",
		"Exotic Exports",
		"The Slashers",
		"Phantom Car",
		"Sightseeing",
		"Smuggler Trail",
		"Cerberus Surprise",
		"Smuggler Plane",
		"Crime Scene",
		"Metal Detector",
		"Finders Keepers",
		"Shop Robbery",
		"The Gooch",
		"Weazel Plaza Shootout",
		"Armored Truck",
		"Possessed Animals",
		"Ghosts Exposed",
		"Happy Holidays Hauler",
		"Community Outreach"
	};

	static constexpr std::array randomEventScripts = {
		"fm_content_drug_vehicle"_J,
		"fm_content_movie_props"_J,
		"fm_content_golden_gun"_J,
		"fm_content_vehicle_list"_J,
		"fm_content_slasher"_J,
		"fm_content_phantom_car"_J,
		"fm_content_sightseeing"_J,
		"fm_content_smuggler_trail"_J,
		"fm_content_cerberus"_J,
		"fm_content_smuggler_plane"_J,
		"fm_content_crime_scene"_J,
		"fm_content_metal_detector"_J,
		"fm_content_convoy"_J,
		"fm_content_robbery"_J,
		"fm_content_xmas_mugger"_J,
		"fm_content_bank_shootout"_J,
		"fm_content_armoured_truck"_J,
		"fm_content_possessed_animals"_J,
		"fm_content_ghosthunt"_J,
		"fm_content_xmas_truck"_J,
		"fm_content_community_outreach"_J
	};

	static constexpr std::array randomEventCooldowns = {
		"SUM22_RE_DRUG_VEHICLE_INACTIVE_TIME"_J,
		"SUM22_RE_MOVIE_PROPS_INACTIVE_TIME"_J,
		"SUM22_RE_GOLDEN_GUN_INACTIVE_TIME"_J,
		"SUM22_RE_VEHICLE_LIST_INACTIVE_TIME"_J,
		"STANDARDCONTROLLERVOLUME_COOLDOWN"_J,
		"STANDARDTARGETTINGTIME_COOLDOWN"_J,
		"SSP2_COOLDOWN"_J,
		"SUM22_RE_SMUGGLER_TRAIL_INACTIVE_TIME"_J,
		"NC_SOURCE_TRUCK_COOLDOWN"_J,
		"SUM22_RE_SMUGGLER_PLANE_INACTIVE_TIME"_J,
		"SUM22_RE_CRIME_SCENE_INACTIVE_TIME"_J,
		"SUM22_RE_METAL_DETECTOR_INACTIVE_TIME"_J,
		"XM22_RE_GANG_CONVOY_INACTIVE_TIME"_J,
		"XM22_RE_ROBBERY_INACTIVE_TIME"_J,
		"STANDARD_KEYBIND_COOLDOWN"_J,
		"XM22_RE_BANK_SHOOTOUT_INACTIVE_TIME"_J,
		(joaat_t)NULL,
		"STANDARDCONTROLLERVOLUME_COOLDOWN"_J,
		"SUM23_RE_GHOSTHUNT_INACTIVE_TIME"_J,
		"XMAS_TRUCK_INACTIVE_TIME"_J,
		"RE_COMMUNITY_OUTREACH_INACTIVE_TIME"_J
	};

	static constexpr std::array randomEventAvailabilities = {
		"SUM22_RE_DRUG_VEHICLE_AVAILABLE_TIME"_J,
		"SUM22_RE_MOVIE_PROPS_AVAILABLE_TIME"_J,
		"SUM22_RE_GOLDEN_GUN_AVAILABLE_TIME"_J,
		"SUM22_RE_VEHICLE_LIST_AVAILABLE_TIME"_J,
		"STANDARDCONTROLLERVOLUME_AVAILABILITY"_J,
		"STANDARDTARGETTINGTIME_AVAILABILITY"_J,
		"SSP2_AVAILABILITY"_J,
		"SUM22_RE_SMUGGLER_TRAIL_AVAILABLE_TIME"_J,
		"NC_SOURCE_TRUCK_AVAILABILITY"_J,
		"SUM22_RE_SMUGGLER_PLANE_AVAILABLE_TIME"_J,
		"SUM22_RE_CRIME_SCENE_AVAILABLE_TIME"_J,
		"SUM22_RE_METAL_DETECTOR_AVAILABLE_TIME"_J,
		"XM22_RE_GANG_CONVOY_AVAILABLE_TIME"_J,
		"XM22_RE_ROBBERY_AVAILABLE_TIME"_J,
		"STANDARD_KEYBIND_AVAILABILITY"_J,
		"XM22_RE_BANK_SHOOTOUT_AVAILABLE_TIME"_J,
		(joaat_t)NULL,
		"STANDARDCONTROLLERVOLUME_AVAILABILITY"_J,
		"SUM23_RE_GHOSTHUNT_AVAILABLE_TIME"_J,
		"XMAS_TRUCK_AVAILABLE_TIME"_J,
		"RE_COMMUNITY_OUTREACH_AVAILABLE_TIME"_J
	};

	static ScriptFunction getNumFMMCVariations("GNFMMCV", "freemode"_J, "5D ? ? ? 01 72 02 39 04", 1, true);
	static GPBD_FM_2* GPBDFM2                          = nullptr;
	static GSBD_RandomEvents* GSBDRandomEvents         = nullptr;
	static RANDOM_EVENTS_FREEMODE_DATA* FMRandomEvents = nullptr;
	static eRandomEvent selectedEvent                  = DRUG_VEHICLE;
	static int selectedSubvariation                    = 0;
	static int numSubvariations                        = 29;
	static int setCooldown                             = 1800000;
	static int setAvailability                         = 900000;
	static bool applyInMinutes                         = false;

	static std::string GetEventTimeLeftStr(int eventTime, int timer)
	{
		int timePassed   = (*Pointers.NetworkTime - timer) < 0 ? -(*Pointers.NetworkTime - timer) : (*Pointers.NetworkTime - timer);
		int diff         = (eventTime - timePassed);
		int totalSeconds = diff / 1000;
		int hours        = totalSeconds / 3600;
		int minutes      = (totalSeconds % 3600) / 60;
		int seconds      = totalSeconds % 60;

		if (hours < 1)
			return std::format("{:02}:{:02}", minutes, seconds);
		else
			return std::format("{:02}:{:02}:{:02}", hours, minutes, seconds);
	}

	static std::string GetEventStateString()
	{
		switch (GSBDRandomEvents->EventData[selectedEvent].State)
		{
		case eRandomEventState::INACTIVE:
			return "Inactive - launching in " + GetEventTimeLeftStr(FMRandomEvents->EventData[selectedEvent].InactiveTime, GSBDRandomEvents->EventData[selectedEvent].TimerState.Time);
		case eRandomEventState::AVAILABLE:
			return "Available - deactivating in " + GetEventTimeLeftStr(FMRandomEvents->EventData[selectedEvent].AvailableTime, GSBDRandomEvents->EventData[selectedEvent].TimerState.Time);
		case eRandomEventState::ACTIVE:
			return "Active";
		case eRandomEventState::CLEANUP:
			return "Cleanup";
		}

		return "N/A";
	}

	static int GetNumLocallyActiveEvents()
	{
		int numEvents{};

		for (int event = DRUG_VEHICLE; event < MAX_EVENTS; event++)
		{
			if (GPBDFM2->Entries[Self::GetPlayer().GetId()].RandomEventsClientData.EventData[event].State != eRandomEventClientState::INACTIVE)
				numEvents++;
		}

		return numEvents;
	}

	static void ResetEventTunables(eRandomEvent event)
	{
		if (event == ARMOURED_TRUCK) // It doesn't have tunables
		{
			setCooldown     = *ScriptGlobal(262145).At(33719).As<int*>();
			setAvailability = *ScriptGlobal(262145).At(33720).As<int*>();
		}
		else
		{
			// Phantom Car's cooldown is actually 2147483647ms if STANDARDTARGETTINGTIME is not enabled
			setCooldown     = *Tunables::GetTunable(randomEventCooldowns[event]).As<int*>();
			setAvailability = *Tunables::GetTunable(randomEventAvailabilities[event]).As<int*>();
		}
	}

	static void OnComboChange()
	{
		selectedSubvariation = 0;
		numSubvariations     = getNumFMMCVariations.Call<int>(FMRandomEvents->MissionData.FMMCData[selectedEvent].FMMCType, 0) - 1;
		ResetEventTunables(selectedEvent);
	}

	std::shared_ptr<Category> BuildRandomEventsMenu()
	{
		auto menu = std::make_shared<Category>("Random Events");

		menu->AddItem(std::make_unique<ImGuiItem>([] {
			GPBDFM2          = GPBD_FM_2::Get();
			GSBDRandomEvents = GSBD_RandomEvents::Get();
			if (!GPBDFM2 || !GSBDRandomEvents)
				return ImGui::Text("Freemode global block is not loaded.");

			if (GPBDFM2->Entries[Self::GetPlayer().GetId()].RandomEventsClientData.InitState != eRandomEventClientInitState::INITIALIZED)
				return ImGui::Text("Random Events are not initialized.");

			if (auto freemode = Scripts::FindScriptThread("freemode"_J))
			{
				FMRandomEvents = RANDOM_EVENTS_FREEMODE_DATA::Get(freemode);
				if (!FMRandomEvents)
					return ImGui::Text("Freemode stack is not valid.");
			}
			else
			{
				return ImGui::Text("Freemode is not running.");
			}

			if (ImGui::BeginCombo("Select Event", randomEventNames[selectedEvent]))
			{
				for (int event = DRUG_VEHICLE; event < MAX_EVENTS; event++)
				{
					switch (GSBDRandomEvents->EventData[event].State)
					{
					case eRandomEventState::INACTIVE:
					case eRandomEventState::CLEANUP:
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
						break;
					case eRandomEventState::AVAILABLE:
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
						break;
					case eRandomEventState::ACTIVE:
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
						break;
					}

					if (ImGui::Selectable(randomEventNames[event], event == selectedEvent))
					{
						FiberPool::Push([event] {
							selectedEvent = (eRandomEvent)event;
							OnComboChange();
						});
					}

					ImGui::PopStyleColor();
				}

				ImGui::EndCombo();
			}

			if (ImGui::InputInt(std::format("Select Location (0-{})", numSubvariations).c_str(), &selectedSubvariation))
			{
				selectedSubvariation = std::clamp(selectedSubvariation, 0, numSubvariations);
			}

			int numActiveEvents = GetNumLocallyActiveEvents();
			int maxActiveEvents = *Tunables::GetTunable("FMREMAXACTIVATEDEVENTS"_J).As<int*>();
			if (numActiveEvents >= maxActiveEvents)
				ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Active Events: %d/%d", numActiveEvents, maxActiveEvents);
			else
				ImGui::Text("Active Events: %d/%d", numActiveEvents, maxActiveEvents);

			if (ImGui::Button("Launch Event"))
			{
				FiberPool::Push([] {
					if (GSBDRandomEvents->EventData[selectedEvent].State != eRandomEventState::ACTIVE)
					{
						SCRIPT_EVENT_REQUEST_RANDOM_EVENT eventData;
						eventData.FMMCType      = FMRandomEvents->MissionData.FMMCData[selectedEvent].FMMCType;
						eventData.Subvariation  = selectedSubvariation;
						eventData.PlayersToSend = 1; // Set FORCE_LAUNCH bit of all players
						eventData.Send();
						ScriptMgr::Yield(100ms);
						if (GSBDRandomEvents->EventData[selectedEvent].State == eRandomEventState::INACTIVE)
						{
							Notifications::Show("Random Events", "Failed to launch event. Are you freemode host?", NotificationType::Error);
						}
					}
					else
					{
						Notifications::Show("Random Events", "Event is already active.", NotificationType::Error);
					}
				});
			}

			ImGui::SameLine();

			if (ImGui::Button("Kill Event"))
			{
				FiberPool::Push([] {
					if (GSBDRandomEvents->EventData[selectedEvent].State == eRandomEventState::AVAILABLE)
					{
						GSBDRandomEvents->EventData[selectedEvent].State = eRandomEventState::CLEANUP;
					}
					else if (GSBDRandomEvents->EventData[selectedEvent].State == eRandomEventState::ACTIVE)
					{
						ScriptFunction terminateFMContentScript("TFMCS", randomEventScripts[(int)selectedEvent], "2D 01 05 00 00 5D");
						terminateFMContentScript.Call<void>(false); // Is it ok to do this when we're not host?
					}
					else
					{
						Notifications::Show("Random Events", "Event is not active.", NotificationType::Error);
					}
				});
			}

			ImGui::SameLine();

			if (ImGui::Button("Teleport to Event"))
			{
				FiberPool::Push([] {
					if (GSBDRandomEvents->EventData[selectedEvent].State >= eRandomEventState::AVAILABLE)
					{
						auto coords = GSBDRandomEvents->EventData[selectedEvent].TriggerPosition;
						if (coords != Vector3(0.f, 0.f, 0.f))
						{
							Self::GetPed().TeleportTo(coords);
						}
						else // Either update event coords TSE not sent yet or event doesn't register a trigger point
						{
							Notifications::Show("Random Events", "Failed to teleport to event. Coordinates are not valid.", NotificationType::Error);
						}
					}
					else
					{
						Notifications::Show("Random Events", "Event is not active.", NotificationType::Error);
					}
				});
			}

			if (GSBDRandomEvents->EventData[selectedEvent].State == eRandomEventState::ACTIVE)
			{
				if (auto eventThread = Scripts::FindScriptThread(randomEventScripts[(int)selectedEvent]))
				{
					if (auto netComponent = reinterpret_cast<GtaThread*>(eventThread)->m_NetComponent)
					{
						if (auto host = netComponent->GetHost())
						{
							ImGui::Text("Host: %s", host->GetName());
						}
						ImGui::SameLine();
						ImGui::BeginDisabled(netComponent->IsLocalPlayerHost());
						if (ImGui::SmallButton("Take Control"))
						{
							FiberPool::Push([eventThread] {
								Scripts::ForceScriptHost(eventThread);
							});
						}
						ImGui::EndDisabled();
					}
				}
			}

			ImGui::Text("State: %s", GetEventStateString().c_str());
			if (GSBDRandomEvents->EventData[selectedEvent].State == eRandomEventState::INACTIVE)
			{
				ImGui::Text("Location: N/A");
				ImGui::Text("Trigger Range: N/A");
			}
			else
			{
				ImGui::Text("Location: %d", GSBDRandomEvents->EventData[selectedEvent].Subvariation);
				ImGui::Text("Trigger Range: %.2f", GSBDRandomEvents->EventData[selectedEvent].TriggerRange); // Default value is 400, it will be updated once the event switches to the available state
			}

			// We should probably put this into a separate group, but I just don't want to do the same safety checks before rendering it
			ImGui::SeparatorText("Cooldown & Availability");

			ImGui::InputInt("##cooldown", &setCooldown);
			ImGui::SameLine();
			if (ImGui::Button("Set Cooldown"))
			{
				int value = applyInMinutes ? (setCooldown * 60000) : setCooldown;
				FMRandomEvents->EventData[selectedEvent].InactiveTime = value;
			}

			ImGui::InputInt("##availability", &setAvailability);
			ImGui::SameLine();
			if (ImGui::Button("Set Availability"))
			{
				int value = applyInMinutes ? (setAvailability * 60000) : setAvailability;
				FMRandomEvents->EventData[selectedEvent].AvailableTime = value;
			}

			ImGui::Checkbox("Apply in Minutes", &applyInMinutes);
		}));

		return menu;
	}
}
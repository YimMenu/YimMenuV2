#include "RandomEvents.hpp"
#include "core/backend/FiberPool.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Scripts.hpp"
#include "game/gta/ScriptFunction.hpp"
#include "game/pointers/Pointers.hpp"
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

	static constexpr std::array RandomEventScripts = {
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

	static YimMenu::ScriptFunction getNumFMMCVariations("GMFV", "freemode"_J, "5D ? ? ? 01 72 02 39 04", 1, true);
	static GSBD_RandomEvents* GSBDRandomEvents         = nullptr;
	static RANDOM_EVENTS_FREEMODE_DATA* FMRandomEvents = nullptr;
	static eRandomEvent selectedEvent                  = DRUG_VEHICLE;
	static int selectedSubvariation                    = 0;
	static int numSubVariations                        = 30;

	std::string GetEventTimeLeftStr(int eventTime, int timer)
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

	std::shared_ptr<Category> BuildRandomEventsMenu()
	{
		auto menu = std::make_shared<Category>("Random Events");

		menu->AddItem(std::make_unique<ImGuiItem>([] {
			GSBDRandomEvents = nullptr;
			FMRandomEvents   = nullptr;

			GSBDRandomEvents = GSBD_RandomEvents::Get();
			if (!GSBDRandomEvents)
				return ImGui::Text("Freemode global block is not loaded yet.");

			if (GSBDRandomEvents->InitState != eRandomEventInitState::INITIALIZED)
				return ImGui::Text("Random Events are not initialized yet.");

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
							selectedEvent    = (eRandomEvent)event;
							numSubVariations = getNumFMMCVariations.Call<int>(FMRandomEvents->MissionData.FMMCData[selectedEvent].FMMCType, 0) - 1;
						});
					}

					ImGui::PopStyleColor();
				}

				ImGui::EndCombo();
			}

			if (ImGui::InputInt(std::format("Select Location (0-{})", numSubVariations).c_str(), &selectedSubvariation))
			{
				selectedSubvariation = std::clamp(selectedSubvariation, 0, numSubVariations);
			}

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
			if (ImGui::IsItemHovered())
			{
				ImGui::SetTooltip("Force launches the event.");
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
						ScriptFunction terminateFMContentScript("TFMCS", RandomEventScripts[(int)selectedEvent], "2D 01 05 00 00 5D ? ? ?");
						terminateFMContentScript.Call<void>(false); // Is it ok to do this when we're not host?
					}
					else
					{
						Notifications::Show("Random Events", "Event is not active.", NotificationType::Error);
					}
				});
			}
			if (ImGui::IsItemHovered())
			{
				ImGui::SetTooltip("Terminates the event.");
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
			if (ImGui::IsItemHovered())
			{
				ImGui::SetTooltip("Teleports to the event.");
			}

			if (GSBDRandomEvents->EventData[selectedEvent].State == eRandomEventState::ACTIVE)
			{
				if (auto eventThread = Scripts::FindScriptThread(RandomEventScripts[(int)selectedEvent]))
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
			ImGui::Text("Location: %d", GSBDRandomEvents->EventData[selectedEvent].Subvariation);
			ImGui::Text("Trigger Range: %.2f", GSBDRandomEvents->EventData[selectedEvent].TriggerRange); // Default value is 400, it will be updated once the event switches to the available state
		}));

		return menu;
	}
}
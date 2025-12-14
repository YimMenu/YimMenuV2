#include "RandomEvents.hpp"
#include "core/backend/FiberPool.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/backend/Self.hpp"
#include "game/backend/Tunables.hpp"
#include "game/backend/ScriptPatches.hpp"
#include "game/gta/data/RandomEvents.hpp"
#include "game/gta/Scripts.hpp"
#include "game/gta/ScriptFunction.hpp"
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
		GETAWAY_DRIVER,
		SURVIVAL_GROUPING,
		VALENTINE_CHEATER,

		MAX_EVENTS
	};

	static std::vector<ScriptPatch> sendUpdateRECoordsTSECooldownPatches{};
	static GPBD_FM_2* GPBDFM2 = nullptr;
	static GSBD_RandomEvents* GSBDRandomEvents = nullptr;
	static RANDOM_EVENTS_FREEMODE_DATA* FMRandomEvents = nullptr;
	static eRandomEvent selectedEvent = DRUG_VEHICLE;
	static int selectedSubvariation = 0;
	static int numSubvariations = 29;
	static int setCooldown = 1800000;
	static int setAvailability = 900000;
	static bool applyInMinutes = false;

	static std::string GetEventStateString()
	{
		switch (GSBDRandomEvents->EventData[selectedEvent].State)
		{
		case eRandomEventState::INACTIVE:
			return "Inactive - launching in " + GSBDRandomEvents->EventData[selectedEvent].TimerState.GetRemainingTimeStr(FMRandomEvents->EventData[selectedEvent].InactiveTime);
		case eRandomEventState::AVAILABLE:
			return "Available - deactivating in " + GSBDRandomEvents->EventData[selectedEvent].TimerState.GetRemainingTimeStr(FMRandomEvents->EventData[selectedEvent].AvailableTime);
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
			setCooldown = *ScriptGlobal(262145).At(33807).As<int*>();
			setAvailability = *ScriptGlobal(262145).At(33808).As<int*>();
		}
		else
		{
			// Phantom Car's cooldown is actually 2147483647ms if STANDARDTARGETTINGTIME is not enabled
			if (auto tunable = Tunables::GetTunable(randomEventCooldowns[event]))
				setCooldown = *tunable->As<int*>();
			if (auto tunable = Tunables::GetTunable(randomEventAvailabilities[event]))
				setAvailability = *tunable->As<int*>();
		}
	}

	static void OnComboChange()
	{
		static ScriptFunction getNumFMMCVariations("freemode"_J, ScriptPointer("GetNumFMMCVariations", "5D ? ? ? 01 72 02 39 04").Add(1).Rip());
		numSubvariations = getNumFMMCVariations.Call<int>(FMRandomEvents->MissionData.FMMCData[selectedEvent].FMMCType, 0) - 1;
		selectedSubvariation = 0;
		ResetEventTunables(selectedEvent);
	}

	static void KillActiveEvent()
	{
		if (auto eventThread = Scripts::FindScriptThread(randomEventScripts[static_cast<int>(selectedEvent)]))
		{
			if (auto NetComponent = reinterpret_cast<GtaThread*>(eventThread)->m_NetComponent)
			{
				if (NetComponent->IsLocalPlayerHost())
				{
					ScriptFunction setFMContentScriptServerState(randomEventScripts[static_cast<int>(selectedEvent)], ScriptPointer("SetFMContentScriptServerState", "5D ? ? ? 55 2E 00 5D").Add(1).Rip());
					setFMContentScriptServerState.Call<void>(3);
				}
				else
				{
					ScriptFunction setFMContentScriptClientState(randomEventScripts[static_cast<int>(selectedEvent)], ScriptPointer("SetFMContentScriptClientState", "5D ? ? ? 55 08 00 74").Add(1).Rip());
					setFMContentScriptClientState.Call<void>(3);
				}
			}
		}
		else
		{
			Notifications::Show("Random Events", "Event script is not active. Are you a participant?", NotificationType::Error);
		}
	}

	std::shared_ptr<Category> BuildRandomEventsMenu()
	{
		if (sendUpdateRECoordsTSECooldownPatches.empty())
		{
			for (int event = DRUG_VEHICLE; event < MAX_EVENTS; event++)
			{
				sendUpdateRECoordsTSECooldownPatches.push_back(ScriptPatches::AddPatch(randomEventScripts[event], ScriptPointer("SendUpdateRECoordsTSECooldownPatch", "43 88 13 2E 00 01"), {0x71, 0x00, 0x00}));
			}
		}

		for (auto& patch : sendUpdateRECoordsTSECooldownPatches)
			patch->Enable();

		auto menu = std::make_shared<Category>("Random Events");

		menu->AddItem(std::make_unique<ImGuiItem>([] {
			GPBDFM2 = GPBD_FM_2::Get();
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
			static Tunable maxEventsTune{"FMREMAXACTIVATEDEVENTS"_J};
			int maxActiveEvents = maxEventsTune.IsReady() ? maxEventsTune.Get<int>() : 0;
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
						eventData.FMMCType = FMRandomEvents->MissionData.FMMCData[selectedEvent].FMMCType;
						eventData.Subvariation = selectedSubvariation;
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
				ImGui::SetTooltip("Requires freemode script host.");

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
						KillActiveEvent();
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
						if (auto coords = GSBDRandomEvents->EventData[selectedEvent].TriggerPosition)
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
				if (auto eventThread = Scripts::FindScriptThread(randomEventScripts[static_cast<int>(selectedEvent)]))
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
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Requires freemode script host.");

			ImGui::InputInt("##availability", &setAvailability);
			ImGui::SameLine();
			if (ImGui::Button("Set Availability"))
			{
				int value = applyInMinutes ? (setAvailability * 60000) : setAvailability;
				FMRandomEvents->EventData[selectedEvent].AvailableTime = value;
			}
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Requires freemode script host.");

			ImGui::Checkbox("Apply in Minutes", &applyInMinutes);
		}));

		return menu;
	}
}
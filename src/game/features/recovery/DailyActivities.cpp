#include "core/commands/ListCommand.hpp"
#include "core/commands/BoolCommand.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/backend/Self.hpp"
#include "game/backend/ScriptPatches.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/Scripts.hpp"
#include "game/gta/Stats.hpp"
#include "game/gta/Vehicle.hpp"
#include "game/gta/ScriptFunction.hpp"
#include "game/gta/ScriptLocal.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "game/pointers/Pointers.hpp"
#include "types/blip/BlipSprite.hpp"
#include "types/script/ScriptEvent.hpp"
#include "types/script/MPScriptData.hpp"
#include "types/script/globals/GPBD_Flow.hpp"
#include "types/script/globals/g_SavedMPGlobals.hpp"
#include "types/script/globals/DailyObjectivesState.hpp"
#include "types/script/globals/WeeklyChallenge.hpp"
#include "types/script/globals/GSBD_RandomEvents.hpp"
#include "types/script/globals/FreemodeGeneral.hpp"
//#include "types/script/globals/FreemodeDelivery.hpp"
#include "types/script/locals/StandardTimeTrialData.hpp"
#include "types/script/locals/RCBanditoTimeTrialData.hpp"
#include "types/script/locals/BikeTimeTrialData.hpp"

namespace YimMenu::Features
{
	static ListCommand hiddenCacheIndex = {
		"hiddencacheindex",
		"Hidden Cache",
		"Selected Hidden Cache",
		{{0, "Hidden Cache 1"}, {1, "Hidden Cache 2"}, {2, "Hidden Cache 3"}, {3, "Hidden Cache 4"}, {4, "Hidden Cache 5"}, {5, "Hidden Cache 6"}, {6, "Hidden Cache 7"}, {7, "Hidden Cache 8"}, {8, "Hidden Cache 9"}, {9, "Hidden Cache 10"}}
	};

	static ListCommand treasureChestIndex = {
		"treasurechestindex",
		"Treasure Chest",
		"Selected Treasure Chest",
		{{0, "Treasure Chest 1"}, {1, "Treasure Chest 2"}}
	};

	static ListCommand buriedStashIndex = {
		"buriedstashindex",
		"Buried Stash",
		"Selected Buried Stash",
		{{0, "Buried Stash 1"}, {1, "Buried Stash 2"}}
	};

	static ListCommand skydiveIndex = {
		"skydiveindex",
		"Skydive",
		"Selected Skydive",
		{{0, "Skydive 1"}, {1, "Skydive 2"}, {2, "Skydive 3"}, {3, "Skydive 4"}, {4, "Skydive 5"}, {5, "Skydive 6"}, {6, "Skydive 7"}, {7, "Skydive 8"}, {8, "Skydive 9"}, {9, "Skydive 10"}}
	};

	static ListCommand timeTrialIndex = {
		"timetrialindex",
		"Time Trial",
		"Selected Time Trial",
		{{0, "Standard Time Trial"}, {1, "RC Bandito Time Trial"}, {2, "Junk Energy Bike Time Trial"}}
	};

	static ListCommand streetDealerIndex = {
		"streetdealerindex",
		"Street Dealer",
		"Selected Street Dealer",
		{{0, "Street Dealer 1"}, {1, "Street Dealer 2"}, {2, "Street Dealer 3"}}
	};

	static ListCommand lsTagIndex = {
		"lstagindex",
		"LS Tag",
		"Selected LS Tag",
		{{0, "LS Tag 1"}, {1, "LS Tag 2"}, {2, "LS Tag 3"}, {3, "LS Tag 4"}, {4, "LS Tag 5"}}
	};

	static void TeleportToCollectable(SCRIPT_EVENT_COLLECT_COLLECTABLE::eCollectables collectable, int index)
	{
		static ScriptFunction getCollectibleCoords("freemode"_J, ScriptPointer("GetCollectibleCoords", "5D ? ? ? 7D 2C 10").Add(1).Rip());
		if (auto coords = getCollectibleCoords.Call<Vector3>(collectable, index))
		{
			Self::GetPed().TeleportTo(coords);
		}
	}

	static void CollectCollectable(SCRIPT_EVENT_COLLECT_COLLECTABLE::eCollectables collectable, int index)
	{
		SCRIPT_EVENT_COLLECT_COLLECTABLE data;
		data.CollectableType     = collectable;
		data.CollectableIndex    = index;
		data.SetCollected        = TRUE;
		data.DisplayNotification = TRUE;
		data.Send();
	}

	static joaat_t GetNextExoticExportsVehicleHash()
	{
		constexpr ScriptGlobal order(1944094);
		for (int i = 1; i <= 10; i++)
		{
			auto offset = *order.At(i).As<int*>();
			if (!GPBD_Flow::Get()->Entries[Self::GetPlayer().GetId()].TunerCBVDeliveredFlags.IsSet(offset))
			{
				auto hash = *ScriptGlobal(1944083 + (offset + 1)).As<joaat_t*>();
				return hash;
			}
		}
		return 0;
	}

	class CompleteAllChallenges : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!Pointers.IsSessionStarted)
				return;

			for (int i = 0; i < 3; i++)
			{
				DailyObjectivesState::Get()->Objective[i] = g_SavedMPGlobals::Get()->Entries[0].GeneralSaved.DOObjectives[i].Objective;
			}
			DailyObjectivesState::Get()->Completed = TRUE;
			WeeklyChallenge::Get()->Entries[0].CurrentObjective = WeeklyChallenge::Get()->Entries[0].ObjectiveCountOverride;
		}
	};

	class TeleportToHiddenCache : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			if (!Stats::GetPackedBool(30297 + hiddenCacheIndex.GetState()))
			{
				TeleportToCollectable(SCRIPT_EVENT_COLLECT_COLLECTABLE::eCollectables::HiddenCaches, hiddenCacheIndex.GetState());
			}
			else
			{
				Notifications::Show("Hidden Caches", "This Hidden Cache has already been collected.", NotificationType::Error);
			}
		}
	};

	class CollectHiddenCache : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			if (!Stats::GetPackedBool(30297 + hiddenCacheIndex.GetState()))
			{
				CollectCollectable(SCRIPT_EVENT_COLLECT_COLLECTABLE::eCollectables::HiddenCaches, hiddenCacheIndex.GetState());
			}
			else
			{
				Notifications::Show("Hidden Caches", "This Hidden Cache has already been collected.", NotificationType::Error);
			}
		}
	};

	class TeleportToTreasureChest : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			if (!Stats::GetPackedBool(30307 + treasureChestIndex.GetState()))
			{
				TeleportToCollectable(SCRIPT_EVENT_COLLECT_COLLECTABLE::eCollectables::TresureChests, treasureChestIndex.GetState());
			}
			else
			{
				Notifications::Show("Treasure Chests", "This Treasure Chest has already been collected.", NotificationType::Error);
			}
		}
	};

	class CollectTreasureChest : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			if (!Stats::GetPackedBool(30307 + treasureChestIndex.GetState()))
			{
				CollectCollectable(SCRIPT_EVENT_COLLECT_COLLECTABLE::eCollectables::TresureChests, treasureChestIndex.GetState());
			}
			else
			{
				Notifications::Show("Treasure Chests", "This Treasure Chest has already been collected.", NotificationType::Error);
			}
		}
	};

	class EnableTreasureChestInLS : public BoolCommand
	{
		using BoolCommand::BoolCommand;

		ScriptPatch m_EnableTreasureChestInLSPatch{};

		virtual void OnEnable() override
		{
			if (!m_EnableTreasureChestInLSPatch)
			{
				m_EnableTreasureChestInLSPatch = ScriptPatches::AddPatch("freemode"_J, ScriptPointer("EnableTreasureChestInLSPatch", "1F 56 ? ? 38 00 47 ? ? 73"), {0x72});
			}
			m_EnableTreasureChestInLSPatch->Enable();
		}

		virtual void OnDisable() override
		{
			if (m_EnableTreasureChestInLSPatch)
			{
				m_EnableTreasureChestInLSPatch->Disable();
			}
		}
	};

	class TeleportToShipwrecked : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			if (!Stats::GetPackedBool(31734))
			{
				TeleportToCollectable(SCRIPT_EVENT_COLLECT_COLLECTABLE::eCollectables::Shipwrecked, 0);
			}
			else
			{
				Notifications::Show("Shipwreck", "Shipwreck has already been collected.", NotificationType::Error);
			}
		}
	};

	class CollectShipwrecked : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			if (!Stats::GetPackedBool(31734))
			{
				CollectCollectable(SCRIPT_EVENT_COLLECT_COLLECTABLE::eCollectables::Shipwrecked, 0);
			}
			else
			{
				Notifications::Show("Shipwreck", "Shipwreck has already been collected.", NotificationType::Error);
			}
		}
	};

	class TeleportToBuriedStash : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			if (!Stats::GetPackedBool(25522 + buriedStashIndex.GetState()))
			{
				TeleportToCollectable(SCRIPT_EVENT_COLLECT_COLLECTABLE::eCollectables::BuriedStash, buriedStashIndex.GetState());
			}
			else
			{
				Notifications::Show("Buried Stashes", "This Buried Stash has already been collected.", NotificationType::Error);
			}
		}
	};

	class CollectBuriedStash : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			if (!Stats::GetPackedBool(25522 + buriedStashIndex.GetState()))
			{
				CollectCollectable(SCRIPT_EVENT_COLLECT_COLLECTABLE::eCollectables::BuriedStash, buriedStashIndex.GetState());
			}
			else
			{
				Notifications::Show("Buried Stashes", "This Buried Stash has already been collected.", NotificationType::Error);
			}
		}
	};

	class EnableBuriedStashInLS : public BoolCommand
	{
		using BoolCommand::BoolCommand;

		ScriptPatch m_EnableBuriedStashInLSPatch{};

		virtual void OnEnable() override
		{
			if (!m_EnableBuriedStashInLSPatch)
			{
				m_EnableBuriedStashInLSPatch = ScriptPatches::AddPatch("freemode"_J, ScriptPointer("EnableBuriedStashInLSPatch", "71 39 02 38 02 06 56 ? ? 2C"), {0x72});
			}
			m_EnableBuriedStashInLSPatch->Enable();
		}

		virtual void OnDisable() override
		{
			if (m_EnableBuriedStashInLSPatch)
			{
				m_EnableBuriedStashInLSPatch->Disable();
			}
		}
	};

	class TeleportToSkydive : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			TeleportToCollectable(SCRIPT_EVENT_COLLECT_COLLECTABLE::eCollectables::Skydives, skydiveIndex.GetState()); // no stat check as you can complete a skydive multiple times
		}
	};

	class CompleteSkydive : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			// TO-DO: Fix this
			MP_SCRIPT_DATA garbage{};
			if (auto thread = Scripts::FindScriptThreadByID(Scripts::StartScript("fm_content_skydive"_J, eStackSizes::MULTIPLAYER_FREEMODE, &garbage, SCR_SIZEOF(garbage))))
			{
				thread->m_Context.m_State = rage::scrThread::State::PAUSED;

				*ScriptLocal(thread, 142).At(1).As<int*>()          = skydiveIndex.GetState();
				*ScriptLocal(thread, 3122).At(146).At(1).As<int*>() = Stats::GetInt("MPX_DAILYCOLLECT_SKYDIVES" + std::to_string(skydiveIndex.GetState()));
				*ScriptLocal(thread, 142).At(2).As<int*>()          = *ScriptLocal(thread, 276).At(143).As<int*>() - 1;
				ScriptLocal(thread, 3307).At(Self::GetPlayer().GetId(), 51).At(43).At(1).As<SCR_BITSET<uint64_t>*>()->Set(7);
				ScriptLocal(thread, 3307).At(Self::GetPlayer().GetId(), 51).At(43).At(1).As<SCR_BITSET<uint64_t>*>()->Set(4);

				static ScriptFunction onSkydiveEnd("fm_content_skydive"_J, ScriptPointer("OnSkydiveEnd", "2D 00 02 00 00 5D ? ? ? 5D ? ? ? 3A"));
				onSkydiveEnd.Call<void>();

				thread->m_Context.m_State = rage::scrThread::State::KILLED;
			}
		}
	};

	class TeleportToTimeTrial : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			std::string stat = "";
			switch (timeTrialIndex.GetState())
			{
			case 0: stat = "MPPLY_TIMETRIAL_COMPLETED_WEEK"; break;
			case 1: stat = "MPPLY_RCTTCOMPLETEDWEEK";        break;
			case 2: stat = "MPPLY_BTTCOMPLETED";             break;
			}

			if (stat.empty() || Stats::GetInt(stat) != -1)
			{
				Notifications::Show("Time Trials", "This Time Trial has already been beaten.", NotificationType::Error);
				return;
			}

			int blip = -1;
			switch (timeTrialIndex.GetState())
			{
			case 0: blip = static_cast<int>(BlipSprite::RADAR_TEMP_2);         break;
			case 1: blip = static_cast<int>(BlipSprite::RADAR_RC_TIME_TRIALS); break;
			case 2: blip = static_cast<int>(BlipSprite::RADAR_BICYCLE_TRIAL);  break;
			}

			if (blip != -1 && HUD::DOES_BLIP_EXIST(blip))
			{
				if (auto coords = HUD::GET_BLIP_COORDS(blip))
				{
					Self::GetPed().TeleportTo(coords);
				}
			}
			else
			{
				Notifications::Show("Time Trials", "Please enable the blip from the Interaction Menu.", NotificationType::Error);
			}
		}
	};

	class BeatTimeTrial : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			std::string stat = "";
			switch (timeTrialIndex.GetState())
			{
			case 0: stat = "MPPLY_TIMETRIAL_COMPLETED_WEEK"; break;
			case 1: stat = "MPPLY_RCTTCOMPLETEDWEEK";        break;
			case 2: stat = "MPPLY_BTTCOMPLETED";             break;
			}

			if (stat.empty() || Stats::GetInt(stat) != -1)
			{
				Notifications::Show("Time Trials", "This Time Trial has already been beaten.", NotificationType::Error);
				return;
			}

			rage::scrThread* thread = nullptr;
			if (timeTrialIndex.GetState() == 2)
			{
				if (Scripts::IsScriptActive("fm_content_bicycle_time_trial"_J))
					return;

				MP_SCRIPT_DATA garbage{};
				thread = Scripts::FindScriptThreadByID(Scripts::StartScript("fm_content_bicycle_time_trial"_J, eStackSizes::MULTIPLAYER_FREEMODE, &garbage, SCR_SIZEOF(garbage)));
			}
			else
			{
				thread = Scripts::FindScriptThread("freemode"_J);
			}

			if (!thread)
				return;

			if (timeTrialIndex.GetState() == 0)
			{
				if (auto ttData = StandardTimeTrialData::Get(thread))
				{
					ttData->Timer1.Time = *Pointers.NetworkTime;
					static ScriptFunction beatStandardTimeTrial("freemode"_J, ScriptPointer("BeatStandardTimeTrial", "2D 01 19 00 00 38"));
					beatStandardTimeTrial.Call<void>(ttData);
				}
			}
			else if (timeTrialIndex.GetState() == 1)
			{
				if (auto rcttData = RCBanditoTimeTrialData::Get(thread))
				{
					rcttData->Timer1.Time = *Pointers.NetworkTime;
					static ScriptFunction beatRCTimeTrial("freemode"_J, ScriptPointer("BeatRCTimeTrial", "2D 01 17 00 00 38 00 40"));
					beatRCTimeTrial.Call<void>(rcttData);
				}
			}
			else if (timeTrialIndex.GetState() == 2)
			{
				thread->m_Context.m_State = rage::scrThread::State::PAUSED;

				*ScriptLocal(thread, 3060).At(130).At(1).As<int*>() = BikeTimeTrialData::Get(thread)->Location; // if we don't init this, the par time duration function will return 0 and the COMPLETED stat will be set to 0, which is bad
				*ScriptLocal(thread, 142).At(4).As<int*>()          = 0;
				static ScriptFunction onBTTEnd("fm_content_bicycle_time_trial"_J, ScriptPointer("OnBTTEnd", "64 ? ? ? 5D ? ? ? 75 77").Add(1).Rip());
				onBTTEnd.Call<void>();

				thread->m_Context.m_State = rage::scrThread::State::KILLED;
			}
		}
	};

	class TeleportToExoticExportsVehicle : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			if (GPBD_Flow::Get()->Entries[Self::GetPlayer().GetId()].TunerCBVDeliveredFlags.Value == 1023)
			{
				Notifications::Show("Exotic Exports", "You have already delivered all the vehicles.", NotificationType::Error);
				return;
			}

			if (GSBD_RandomEvents::Get()->EventData[3].State != eRandomEventState::INACTIVE)
			{
				if (auto coords = GSBD_RandomEvents::Get()->EventData[3].TriggerPosition)
					Self::GetPed().TeleportTo(coords);
			}
		}
	};

	class DeliverNextExoticExportsVehicle : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			if (GPBD_Flow::Get()->Entries[Self::GetPlayer().GetId()].TunerCBVDeliveredFlags.Value == 1023)
			{
				Notifications::Show("Exotic Exports", "You have already delivered all the vehicles.", NotificationType::Error);
				return;
			}

			/*if (!FreemodeDelivery::Get()->DeliveryCooldown1.HasTimePassed(30000))
			{
				Notifications::Show("Exotic Exports", "You have just delivered a vehicle, wait a moment.", NotificationType::Error);
				return;
			}*/

			auto hash = GetNextExoticExportsVehicleHash();
			static ScriptFunction onFreemodeDeliveryEnd("freemode"_J, ScriptPointer("OnFreemodeDeliveryEnd", "2D 0C 2A 00 00"));
			onFreemodeDeliveryEnd.Call<void>(0, Self::GetPlayer().GetId(), 0, 0, 0, 0, 0, 0, 0, 0, hash, 273);
			//FreemodeDelivery::Get()->DeliveryCooldown1.Reset();
		}
	};

	class TeleportToDeadDrop : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			if (!Stats::GetPackedBool(36628))
			{
				TeleportToCollectable(SCRIPT_EVENT_COLLECT_COLLECTABLE::eCollectables::DeadDrop, 0);
			}
			else
			{
				Notifications::Show("G's Cache", "G's Cache has already been collected.", NotificationType::Error);
			}
		}
	};

	class CollectDeadDrop : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			if (!Stats::GetPackedBool(36628))
			{
				CollectCollectable(SCRIPT_EVENT_COLLECT_COLLECTABLE::eCollectables::DeadDrop, 0);
			}
			else
			{
				Notifications::Show("G's Cache", "G's Cache has already been collected.", NotificationType::Error);
			}
		}
	};

	class TeleportToStashHouse : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			if (!Stats::GetPackedBool(36657))
			{
				auto blip = HUD::GET_FIRST_BLIP_INFO_ID(static_cast<int>(BlipSprite::RADAR_STASH_HOUSE));
				if (HUD::DOES_BLIP_EXIST(blip))
				{
					if (auto coords = HUD::GET_BLIP_COORDS(blip))
						Self::GetPed().TeleportTo(coords);
				}
			}
			else
			{
				Notifications::Show("Stash House", "Stash House has already been raided.", NotificationType::Error);
			}
		}
	};

	class EnterStashHouseSafeCode : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			if (auto thread = Scripts::FindScriptThread("fm_content_stash_house"_J))
			{
				for (int i = 0; i < 3; i++)
				{
					int combination = *ScriptLocal(thread, 142).At(22).At(i, 2).At(1).As<int*>();
					*ScriptLocal(thread, 142).At(22).At(i, 2).As<float*>() = combination;
				}
			}
		}
	};

	class TeleportToStreetDealer : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			static ScriptFunction getStreetDealerCoords("freemode"_J, ScriptPointer("GetStreetDealerCoords", "5D ? ? ? 5D ? ? ? 5D ? ? ? 18").Add(1).Rip());
			if (auto coords = getStreetDealerCoords.Call<Vector3>(FreemodeGeneral::Get()->StreetDealers.Dealers[streetDealerIndex.GetState()].Location))
				Self::GetPed().TeleportTo(coords);
		}
	};

	class TeleportToLSTag : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			if (!Stats::GetPackedBool(42252 + lsTagIndex.GetState()))
			{
				TeleportToCollectable(SCRIPT_EVENT_COLLECT_COLLECTABLE::eCollectables::Tagging, lsTagIndex.GetState());
			}
			else
			{
				Notifications::Show("LS Tags", "This LS Tag has already been sprayed.", NotificationType::Error);
			}
		}
	};

	class SprayLSTag : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			if (!Stats::GetPackedBool(42252 + lsTagIndex.GetState()))
			{
				CollectCollectable(SCRIPT_EVENT_COLLECT_COLLECTABLE::eCollectables::Tagging, lsTagIndex.GetState());
			}
			else
			{
				Notifications::Show("LS Tags", "This LS Tag has already been sprayed.", NotificationType::Error);
			}
		}
	};

	class TeleportToMadrazoHit : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			if (Stats::GetInt("MPX_BAIL_OFFICE_OWNED") == 0)
			{
				Notifications::Show("Madrazo Hits", "You must own a Bail Office.", NotificationType::Error);
				return;
			}

			if (!Stats::GetPackedBool(42269))
			{
				auto blip = HUD::GET_FIRST_BLIP_INFO_ID(static_cast<int>(BlipSprite::RADAR_DAILY_BOUNTY));
				if (HUD::DOES_BLIP_EXIST(blip))
				{
					if (auto coords = HUD::GET_BLIP_COORDS(blip))
						Self::GetPed().TeleportTo(coords);
				}
			}
			else
			{
				Notifications::Show("Madrazo Hits", "Madrazo Hit has already been completed.", NotificationType::Error);
			}
		}
	};

	class TeleportToMadrazoHitTarget : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			if (auto thread = Scripts::FindScriptThread("fm_content_daily_bounty"_J))
			{
				if (auto coords = *ScriptLocal(thread, 239).At(434).At(1).At(0, 4).As<Vector3*>())
				{
					Self::GetPed().TeleportTo(coords);
				}
			}
		}
	};

	static CompleteAllChallenges _CompleteAllChallenges{"completeallchallenges", "Complete All Challenges", "Completes all the Daily Objectives and the Weekly Challenge."};

	static TeleportToHiddenCache _TeleportToHiddenCache{"tptohiddencache", "Teleport to Hidden Cache", "Teleports to the selected Hidden Cache."};
	static CollectHiddenCache _CollectHiddenCache{"collecthiddencache", "Collect Hidden Cache", "Collects the selected Hidden Cache."};

	static TeleportToTreasureChest _TeleportToTreasureChest{"tptotreasurechest", "Teleport to Treasure Chest", "Teleports to the selected Treasure Chest."};
	static CollectTreasureChest _CollectTreasureChest{"collecttreasurechest", "Collect Treasure Chest", "Collects the selected Treasure Chest."};
	static EnableTreasureChestInLS _EnableTreasureChestInLS{"enabletreasurechestinls", "Enable Treasure Chests in LS", "Enables Treasure Chests in Los Santos, so you don't have to go to Cayo Perico."};

	static TeleportToShipwrecked _TeleportToShipwrecked{"tptoshipwrecked", "Teleport to Shipwreck", "Teleports to Shipwreck."};
	static CollectShipwrecked _CollectShipwrecked{"collectshipwrecked", "Collect Shipwreck", "Collects Shipwreck."};

	static TeleportToBuriedStash _TeleportToBuriedStash{"tptoburiedstash", "Teleport to Buried Stash", "Teleports to the selected Buried Stash."};
	static CollectBuriedStash _CollectBuriedStash{"collectburiedstash", "Collect Buried Stash", "Collects the selected Buried Stash."};
	static EnableBuriedStashInLS _EnableBuriedStashInLS{"enableburiedstashinls", "Enable Buried Stashes in LS", "Enables Buried Stashes in Los Santos, so you don't have to go to Cayo Perico."};

	static TeleportToSkydive _TeleportToSkydive{"tptoskydive", "Teleport to Skydive", "Teleports to the selected Skydive."};
	static CompleteSkydive _CompleteSkydive{"completeskydive", "Complete Skydive", "Completes the selected Skydive."};

	static TeleportToTimeTrial _TeleportToTimeTrial{"tptotimetrial", "Teleport to Time Trial", "Teleports to the selected Time Trial."};
	static BeatTimeTrial _BeatTimeTrial{"beattimetrial", "Beat Time Trial", "Completes the selected Time Trial."};

	static TeleportToExoticExportsVehicle _TeleportToExoticExportsVehicle{"tptoexoticexportsvehicle", "Teleport to Exotic Exports Vehicle", "Teleports to the next Exotic Exports vehicle."};
	static DeliverNextExoticExportsVehicle _DeliverNextExoticExportsVehicle{"delivernextexoticexportsvehicle", "Deliver Next Exotic Exports Vehicle", "Directly delivers the next Exotic Exports vehicle."};

	static TeleportToDeadDrop _TeleportToDeadDrop{"tptodeaddrop", "Teleport to G's Cache", "Teleports to G's Cache."};
	static CollectDeadDrop _CollectDeadDrop{"collectdeaddrop", "Collect G's Cache", "Collects G's Cache."};

	static TeleportToStashHouse _TeleportToStashHouse{"tptostashhouse", "Teleport to Stash House", "Teleports to Stash House."};
	static EnterStashHouseSafeCode _EnterStashHouseSafeCode{"enterstashhousesafecode", "Enter Stash House Safe Code", "Enters the Stash House safe code."};

	static TeleportToStreetDealer _TeleportToStreetDealer{"tptostreetdealer", "Teleport to Dealer", "Teleports to the selected Street Dealer."};

	static TeleportToLSTag _TeleportToLSTag{"tptolstag", "Teleport to LS Tag", "Teleports to the selected LS Tag."};
	static SprayLSTag _SprayLSTag{"spraylstag", "Spray LS Tag", "Sprays the selected LS Tag."};

	static TeleportToMadrazoHit _TeleportToMadrazoHit{"tptomadrazohit", "Teleport to Madrazo Hit", "Teleports to Madrazo Hit."};
	static TeleportToMadrazoHitTarget _TeleportToMadrazoHitTarget{"tptomadrazohittarget", "Teleport to Madrazo Hit Target", "Teleports to Madrazo Hit Target."};
}
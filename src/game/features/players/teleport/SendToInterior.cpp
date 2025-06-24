#include "game/backend/Self.hpp"
#include "game/commands/PlayerCommand.hpp"
#include "core/commands/ListCommand.hpp"
#include "types/script/globals/GlobalPlayerBD.hpp"
#include "types/script/ScriptEvent.hpp"

namespace YimMenu::Features
{
	static std::vector<std::pair<int, const char*>> g_Interiors = {
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_ARMORY_TRUCK_1, "MOC"},
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_CASINO, "Casino"},
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_CASINO_APT, "Casino Penthouse"},
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_ARCADE_DAVIS, "Arcade (Davis)"},
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_ARCADE_GRAPESEED, "Arcade (Grapeseed)"},
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_ARCADE_LA_MESA, "Arcade (La Mesa)"},
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_ARCADE_PALETO_BAY, "Arcade (Paleto Bay)"},
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_ARCADE_ROCKFORD_HILLS, "Arcade (Rockford Hills)"},
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_ARCADE_WEST_VINEWOOD, "Arcade (West Vinewood)"},
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_CASINO_NIGHTCLUB, "Music Locker"},
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_AUTO_SHOP_BURTON, "Auto Shop (Burton)"},
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_AUTO_SHOP_LA_MESA, "Auto Shop (La Mesa)"},
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_AUTO_SHOP_MISSION_ROW, "Auto Shop (Mission Row)"},
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_AUTO_SHOP_RANCHO, "Auto Shop (Rancho)"},
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_AUTO_SHOP_STRAWBERRY, "Auto Shop (Strawberry)"},
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_CAR_MEET, "Car Meet"}, // requires players to have been there at least once on their own
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_FIXER_HQ_HAWICK, "Agency (Hawick)"},
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_FIXER_HQ_ROCKFORD, "Agency (Rockford)"},
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_FIXER_HQ_SEOUL, "Agency (Little Seoul)"},
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_FIXER_HQ_VESPUCCI, "Agency (Vespucci)"},
	 // {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_ACID_LAB, "Acid Lab"}, stuck in black screen
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_JUGGALO_HIDEOUT, "Freakhouse"},
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_SALVAGE_YARD_LA_PUERTA, "Salvage Yard (La Puerta)"},
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_SALVAGE_YARD_MURIETTA_HEIGHTS, "Salvage Yard (Murietta Heights)"},
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_SALVAGE_YARD_PALETO_BAY, "Salvage Yard (Paleto Bay)"},
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_SALVAGE_YARD_SANDY_SHORES, "Salvage Yard (Sandy Shores)"},
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_SALVAGE_YARD_STRAWBERRY, "Salvage Yard (Strawberry)"},
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_BAIL_OFFICE_DAVIS, "Bail Office (Davis)"},
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_BAIL_OFFICE_DEL_PERRO, "Bail Office (Del Perro)"},
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_BAIL_OFFICE_MISSION_ROW, "Bail Office (Mission Row)"},
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_BAIL_OFFICE_PALETO_BAY, "Bail Office (Paleto Bay)"},
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_BAIL_OFFICE_WEST_VINEWOOD, "Bail Office (West Vinewood)"},
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_HACKER_DEN, "Garment Factory"},
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_FIELD_HANGAR, "Field Hangar"},
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_SMALL_BUSINESS_CAR_WASH, "Car Wash"},
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_SMALL_BUSINESS_WEED_SHOP, "Weed Shop"},
	    {(int)eSimpleInteriorIndex::SIMPLE_INTERIOR_SMALL_BUSINESS_HELI_TOURS, "Heli Tours"},

	};

	static ListCommand _SelectedInterior{"sendtointeriorindex", "Send to Interior Index", "The interior index to send the player(s) to", g_Interiors, (int)eSimpleInteriorIndex::SIMPLE_INTERIOR_ARMORY_TRUCK_1};

	class SendToInterior : public PlayerCommand
	{
		using PlayerCommand::PlayerCommand;

		virtual void OnCall(Player player) override
		{
			OnCall(std::vector{player});
		}

		virtual void OnCall(const std::vector<Player>& players) override
		{
			SCRIPT_EVENT_SEND_TO_INTERIOR message;
			message.Interior = _SelectedInterior.GetState();
			message.EnterOwnerInterior = true;
			message.GoonsOnly = false;
			message.InstanceId = 0;
			message.SubInstanceId = -1;
			message.Owner = Self::GetPlayer().GetId();
			message.Distance = 99999;
			message.Position = {0, 0, 0};
			for (auto& player : players)
				message.SetPlayer(player.GetId());
			message.Send();
		}
	};

	static SendToInterior _SendToInterior{"sendtointerior", "Send to Interior", "Sends the player to the selected interior"};
}
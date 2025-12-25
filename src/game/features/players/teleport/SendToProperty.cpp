#include "game/backend/Self.hpp"
#include "game/commands/PlayerCommand.hpp"
#include "core/commands/ListCommand.hpp"
#include "types/script/ScriptEvent.hpp"

namespace YimMenu::Features
{
	static std::vector<std::pair<int, const char*>> g_Properties = {
	    {1, "Eclipse Towers, Apt 31"},
	    {2, "Eclipse Towers, Apt 9"},
	    {3, "Eclipse Towers, Apt 40"},
	    {4, "Eclipse Towers, Apt 5"},
	    {5, "3 Alta St, Apt 10"},
	    {6, "3 Alta St, Apt 57"},
	    {7, "Del Perro Heights, Apt 20"},
	    {8, "1162 Power St, Apt 3"},
	    {9, "0605 Spanish Ave, Apt 1"},
	    {10, "0604 Las Lagunas Blvd, Apt 4"},
	    {11, "0184 Milton Rd, Apt 13"},
	    {12, "The Royale, Apt 19"},
	    {13, "0504 S Mo Milton Dr"},
	    {14, "0115 Bay City Ave, Apt 45"},
	    {15, "0325 South Rockford Dr"},
	    {16, "Dream Tower, Apt 15"},
	    {17, "2143 Las Lagunas Blvd, Apt 9"},
	    {18, "1561 San Vitas St, Apt 2"},
	    {19, "0112 S Rockford Dr, Apt 13"},
	    {20, "2057 Vespucci Blvd, Apt 1"},
	    {21, "0069 Cougar Ave, Apt 19"},
	    {22, "1237 Prosperity St, Apt 21"},
	    {23, "1115 Blvd Del Perro, Apt 18"},
	    {24, "0120 Murrieta Heights"},
	    {25, "Unit 14 Popular St"},
	    {26, "Unit 2 Popular St"},
	    {27, "331 Supply St"},
	    {28, "Unit 1 Olympic Fwy"},
	    {29, "0754 Roy Lowenstein Blvd"},
	    {30, "12 Little Bighorn Ave"},
	    {31, "Unit 124 Popular St"},
	    {32, "0552 Roy Lowenstein Blvd"},
	    {33, "0432 Davis Ave"},
	    {34, "Del Perro Heights, Apt 7"},
	    {35, "Weazel Plaza, Apt 101"},
	    {36, "Weazel Plaza, Apt 70"},
	    {37, "Weazel Plaza, Apt 26"},
	    {38, "4 Integrity Way, Apt 30"},
	    {39, "4 Integrity Way, Apt 35"},
	    {40, "Richards Majestic, Apt 4"},
	    {41, "Richards Majestic, Apt 51"},
	    {42, "Tinsel Towers, Apt 45"},
	    {43, "Tinsel Towers, Apt 29"},
	    {44, "142 Paleto Blvd"},
	    {45, "1 Strawberry Ave"},
	    {46, "1932 Grapeseed Ave"},
	    {47, "1920 Senora Way"},
	    {48, "2000 Great Ocean Highway"},
	    {49, "197 Route 68"},
	    {50, "870 Route 68 Approach"},
	    {51, "1200 Route 68"},
	    {52, "8754 Route 68"},
	    {53, "1905 Davis Ave"},
	    {54, "1623 South Shambles St"},
	    {55, "4531 Dry Dock St"},
	    {56, "1337 Exceptionalists Way"},
	    {57, "Unit 76 Greenwich Parkway"},
	    {58, "Garage Innocence Blvd"},
	    {59, "634 Blvd Del Perro"},
	    {60, "0897 Mirror Park Blvd"},
	    {61, "Eclipse Towers, Apt 3"},
	    {62, "Del Perro Heights, Apt 4"},
	    {63, "Richards Majestic, Apt 2"},
	    {64, "Tinsel Towers, Apt 42"},
	    {65, "4 Integrity Way, Apt 28"},
	    {66, "4 Hangman Ave"},
	    {67, "12 Sustancia Rd"},
	    {68, "4584 Procopio Dr"},
	    {69, "4401 Procopio Dr"},
	    {70, "0232 Paleto Blvd"},
	    {71, "140 Zancudo Ave"},
	    {72, "1893 Grapeseed Ave"},
	    {73, "3655 Wild Oats Drive"},
	    {74, "2044 North Conker Avenue"},
	    {75, "2868 Hillcrest Avenue"},
	    {76, "2862 Hillcrest Avenue"},
	    {77, "3677 Whispymound Drive"},
	    {78, "2117 Milton Road"},
	    {79, "2866 Hillcrest Avenue"},
	    {80, "2874 Hillcrest Avenue"},
	    {81, "2113 Mad Wayne Thunder Drive"},
	    {82, "2045 North Conker Avenue"},
	    {83, "Eclipse Towers, Penthouse Suite 1"},
	    {84, "Eclipse Towers, Penthouse Suite 2"},
	    {85, "Eclipse Towers, Penthouse Suite 3"},
	    {86, "Private Yacht"},
	    {87, "Lombank West"},
	    {88, "Maze Bank West"},
	    {89, "Arcadius Business Center"},
	    {90, "Maze Bank Tower"},
	    {91, "Rancho Clubhouse"},
	    {92, "Del Perro Beach Clubhouse"},
	    {93, "Pillbox Hill Clubhouse"},
	    {94, "Great Chaparral Clubhouse"},
	    {95, "Paleto Bay Clubhouse"},
	    {96, "Sandy Shores Clubhouse"},
	    {97, "La Mesa Clubhouse"},
	    {98, "Downtown Vinewood Clubhouse"},
	    {99, "Hawick Clubhouse"},
	    {100, "Grapeseed Clubhouse"},
	    {101, "Paleto Bay Clubhouse"},
	    {102, "Vespucci Beach Clubhouse"},
	    {103, "Office Garage 1"},
	    {104, "Office Garage 2"},
	    {105, "Office Garage 3"},
	    {115, "Vehicle Warehouse"},
	};

	static ListCommand _SelectedProperty{"sendtopropertyindex", "Send to Property Index", "The property index to send the player(s) to", g_Properties, 1};

	class SendToProperty : public PlayerCommand
	{
		using PlayerCommand::PlayerCommand;

		virtual void OnCall(Player player) override
		{
			OnCall(std::vector{player});
		}

		virtual void OnCall(const std::vector<Player>& players) override
		{
			SCRIPT_EVENT_SEND_TO_PROPERTY message;
			message.Owner = Self::GetPlayer().GetId();
			message.PropertyIndex = _SelectedProperty.GetState();
			message.SubProperyIndex = 1;
			message.MissionPassNotify1 = true; // skips some checks
			message.PAD_0004 = -1;
			message.Variation = 1;
			message.Flags = 2; // skips some more checks
			for (auto& player : players)
				message.SetPlayer(player.GetId());
			message.Send();
		}
	};

	static SendToProperty _SendToProperty{"sendtoproperty", "Send to Property", "Sends the player to the selected property"};
}
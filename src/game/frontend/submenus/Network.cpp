#include "Network.hpp"
#include "core/backend/FiberPool.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/frontend/items/Items.hpp"
#include "game/frontend/submenus/Network/SavedPlayers.hpp"
#include "game/gta/Network.hpp"
#include "game/frontend/submenus/network/RandomEvents.hpp"

namespace YimMenu::Submenus
{
	Network::Network() :
	    Submenu::Submenu("Network")
	{
		// TODO: this needs a rework
		auto session = std::make_shared<Category>("Session");
		auto joinGroup = std::make_shared<Group>("Join");
		auto bountyGroup = std::make_shared<Group>("Bounty", 1);
		auto toxicGroup = std::make_shared<Group>("Toxic");
		auto teleportGroup = std::make_shared<Group>("Teleport");
		auto trollGroup = std::make_shared<Group>("Troll");
		auto enhancements = std::make_shared<Group>("Enhancements");

		auto joinSession = std::make_shared<Group>("", 1);
		joinSession->AddItem(std::make_shared<ListCommandItem>("joinsessiontype"_J, "Session Type"));
		joinSession->AddItem(std::make_shared<CommandItem>("joinsession"_J, "Join##session"));

		joinGroup->AddItem(joinSession);
		joinGroup->AddItem(std::make_shared<ImGuiItem>([] {
			static std::uint64_t rockstar_id{};
			static char name_buf[24]{};

			ImGui::SetNextItemWidth(150.0f);
			ImGui::InputText("Username", name_buf, sizeof(name_buf));
			ImGui::SameLine();
			if (ImGui::Button("Join##username"))
				FiberPool::Push([] {
					auto rid = YimMenu::Network::ResolveRockstarId(name_buf);
					if (rid)
					{
						YimMenu::Network::JoinRockstarId(*rid);
					}
					else
					{
						Notifications::Show("Joiner", "Failed to get RID from username", NotificationType::Error);
					}
				});

			ImGui::SetNextItemWidth(150.0f);
			ImGui::InputScalar("Rockstar Id", ImGuiDataType_U64, &rockstar_id);
			ImGui::SameLine();
			if (ImGui::Button("Join##rid"))
				FiberPool::Push([] {
					YimMenu::Network::JoinRockstarId(rockstar_id);
				});
		}));

		bountyGroup->AddItem(std::make_shared<IntCommandItem>("bountyamount"_J, "Amount"));
		bountyGroup->AddItem(std::make_shared<BoolCommandItem>("anonymousbounty"_J, "Anonymous"));
		bountyGroup->AddItem(std::make_shared<CommandItem>("setbountyall"_J, "Set Bounties"));

		teleportGroup->AddItem(std::make_shared<CommandItem>("bringall"_J, "Bring All"));
		auto customPlayerTp = std::make_shared<Group>("", 1);
		customPlayerTp->AddItem(std::make_shared<Vector3CommandItem>("playertpcoord"_J, ""));
		customPlayerTp->AddItem(std::make_shared<CommandItem>("tpplayertocoordall"_J, "Teleport Everyone"));
		teleportGroup->AddItem(customPlayerTp);

		trollGroup->AddItem(std::make_shared<CommandItem>("sendsextall"_J, "Send Sexts"));
		trollGroup->AddItem(std::make_shared<BoolCommandItem>("harassplayers"_J));
		trollGroup->AddItem(std::make_shared<BoolCommandItem>("spamkillfeed"_J));
		trollGroup->AddItem(std::make_shared<CommandItem>("deletevehall"_J, "Delete Player Vehicles"));

		toxicGroup->AddItem(std::make_shared<CommandItem>("killall"_J, "Kill All"));
		toxicGroup->AddItem(std::make_shared<CommandItem>("killexploitall"_J, "Permadeath All"));
		toxicGroup->AddItem(std::make_shared<CommandItem>("explodeall"_J, "Explode All"));
		toxicGroup->AddItem(std::make_shared<CommandItem>("ceokickall"_J, "CEO Kick All"));

		enhancements->AddItem(std::make_shared<BoolCommandItem>("fastjoin"_J));
		enhancements->AddItem(std::make_shared<BoolCommandItem>("disabledeathbarriers"_J));
		enhancements->AddItem(std::make_shared<BoolCommandItem>("despawnbypass"_J)); // move this somewhere else?
		enhancements->AddItem(std::make_shared<BoolCommandItem>("bypasscasinogeoblock"_J));
	
		session->AddItem(joinGroup);
		session->AddItem(bountyGroup);
		session->AddItem(trollGroup);
		session->AddItem(teleportGroup);
		session->AddItem(toxicGroup);
		session->AddItem(enhancements);

		auto spoofing = std::make_shared<Category>("Spoofing");
		auto matchmakingGroup = std::make_shared<Group>("Matchmaking");
		auto spoofMMRegion = std::make_shared<Group>("", 1);
		spoofMMRegion->AddItem(std::make_shared<BoolCommandItem>("spoofmmregion"_J, "Spoof Region"));
		spoofMMRegion->AddItem(std::make_shared<ConditionalItem>("spoofmmregion"_J, std::make_shared<ListCommandItem>("mmregion"_J, "##mmregion")));
		matchmakingGroup->AddItem(spoofMMRegion);
		spoofing->AddItem(matchmakingGroup);
	
		AddCategory(std::move(session));
		AddCategory(std::move(spoofing));
		AddCategory(std::move(BuildSavedPlayersMenu()));
		AddCategory(BuildRandomEventsMenu());
	}
}
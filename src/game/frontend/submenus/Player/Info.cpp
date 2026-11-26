#include "Info.hpp"
#include "core/translation/Translation.hpp"

#include "core/frontend/Notifications.hpp"
#include "core/backend/FiberPool.hpp"
#include "game/backend/Players.hpp"
#include "game/backend/SavedPlayers.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "types/network/CNetGamePlayer.hpp"
#include "types/network/rlGamerInfo.hpp"

namespace YimMenu::Submenus
{
	static std::string BuildIPStr(int field1, int field2, int field3, int field4)
	{
		std::ostringstream oss;
		oss << field1 << '.' << field2 << '.' << field3 << '.' << field4;
		return oss.str();
	}

	std::shared_ptr<Category> BuildInfoMenu()
	{
		auto menu = std::make_shared<Category>("Info");

		auto teleportGroup = std::make_shared<Group>("Teleport");
		auto playerOptionsGroup = std::make_shared<Group>("Info");

		playerOptionsGroup->AddItem(std::make_shared<ImGuiItem>([] {
			if (Players::GetSelected().IsValid())
				ImGui::Text("%s", Players::GetSelected().GetName());
		}));
		playerOptionsGroup->AddItem(std::make_shared<BoolCommandItem>("spectate"_J));
		playerOptionsGroup->AddItem(std::make_shared<ImGuiItem>([] {
			if (Players::GetSelected().IsValid())
			{
				ImGui::Text(Translation::Tr("Rank: %d (%d RP)").c_str(), Players::GetSelected().GetRank(), Players::GetSelected().GetRP());
				ImGui::Text(Translation::Tr("Money: %d").c_str(), Players::GetSelected().GetMoney());

				if (Players::GetSelected().GetPed())
				{
					auto health = Players::GetSelected().GetPed().GetHealth();
					auto maxHealth = Players::GetSelected().GetPed().GetMaxHealth();
					std::string healthStr = std::format("HP: {}/{} ({:.2f}%)", health, maxHealth, (float)health / maxHealth * 100.0f);
					ImGui::Text("%s", healthStr.c_str());

					auto coords = Players::GetSelected().GetPed().GetPosition();
					ImGui::Text(Translation::Tr("Coords: %.2f, %.2f, %.2f").c_str(), coords.x, coords.y, coords.z);

					auto distance = Players::GetSelected().GetPed().GetPosition().GetDistance(Self::GetPed().GetPosition());
					ImGui::Text(Translation::Tr("Distance: %.2f").c_str(), distance);
				}
				else
				{
					ImGui::Text("%s", Translation::Tr("Ped missing or deleted").c_str());
				}

				auto rid1 = Players::GetSelected().GetRID();

				std::string ridStr = std::to_string(rid1);

				ImGui::Text("%s", Translation::Tr("RID:").c_str());
				ImGui::SameLine();
				if (ImGui::SmallButton(std::to_string(rid1).c_str()))
				{
					ImGui::SetClipboardText(std::to_string(rid1).c_str());
				}

				auto& platformAccountId = Players::GetSelected().GetHandle()->m_PlatformAccountId;
				switch (platformAccountId.m_Platform)
				{
				case PlatformAccountId::PLATFORM_XBOX:
					ImGui::Text("%s", Translation::Tr("Xbox User ID:").c_str());
					ImGui::SameLine();
					if (ImGui::SmallButton(std::to_string(platformAccountId.m_XboxUserId).c_str()))
					{
						ImGui::SetClipboardText(std::to_string(platformAccountId.m_XboxUserId).c_str());
					}
					break;
				case PlatformAccountId::PLATFORM_STEAM:
					ImGui::Text("%s", Translation::Tr("Steam ID:").c_str());
					ImGui::SameLine();
					if (ImGui::SmallButton(std::to_string(platformAccountId.m_SteamId).c_str()))
					{
						ImGui::SetClipboardText(std::to_string(platformAccountId.m_SteamId).c_str());
					}
					break;
				case PlatformAccountId::PLATFORM_EPIC:
					ImGui::Text("%s", Translation::Tr("Epic Account ID:").c_str());
					ImGui::SameLine();
					if (ImGui::SmallButton(platformAccountId.m_EpicAccountId))
					{
						ImGui::SetClipboardText(platformAccountId.m_EpicAccountId);
					}
					break;
				default:
					break;
				}


				auto ip = Players::GetSelected().GetExternalAddress();

				auto addr2 = BuildIPStr(ip.m_IpAddress.m_Field1, ip.m_IpAddress.m_Field2, ip.m_IpAddress.m_Field3, ip.m_IpAddress.m_Field4);

				ImGui::Text("%s", Translation::Tr("IP Address:").c_str());
				ImGui::SameLine();
				if (ImGui::SmallButton(addr2.c_str()))
				{
					ImGui::SetClipboardText(addr2.c_str());
				}

				if (ImGui::Button(Translation::TrLabel("Add to Saved").c_str()))
					SavedPlayers::GetPlayerData(Players::GetSelected());
				ImGui::SameLine();
				if (ImGui::Button(Translation::TrLabel("View SC Profile").c_str()))
					FiberPool::Push([] {
						uint64_t handle[13];
						NETWORK::NETWORK_HANDLE_FROM_PLAYER(Players::GetSelected().GetId(), handle, std::size(handle));
						NETWORK::NETWORK_SHOW_PROFILE_UI(handle);
					});
				ImGui::SameLine();
				if (ImGui::Button(Translation::TrLabel("Add Friend").c_str()))
					FiberPool::Push([] {
						uint64_t handle[13];
						NETWORK::NETWORK_HANDLE_FROM_PLAYER(Players::GetSelected().GetId(), handle, std::size(handle));
						NETWORK::NETWORK_ADD_FRIEND(handle, "");
					});

				if (ImGui::Button(Translation::TrLabel("More Info").c_str()))
					ImGui::OpenPopup(Translation::Tr("More Info").c_str());

				ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
				if (ImGui::BeginPopupModal(Translation::Tr("More Info").c_str(), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_Modal | ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Text(Translation::Tr("Average Latency: %.2f").c_str(), Players::GetSelected().GetAverageLatency());
					ImGui::Text(Translation::Tr("Packet Loss: %.2f").c_str(), Players::GetSelected().GetAveragePacketLoss());

					ImGui::Spacing();

					if (ImGui::Button(Translation::TrLabel("Close").c_str()) || ((!ImGui::IsWindowHovered() && !ImGui::IsAnyItemHovered()) && ImGui::IsMouseClicked(ImGuiMouseButton_Left)))
						ImGui::CloseCurrentPopup();

					ImGui::EndPopup();
				}
			}
			else
			{
				Players::SetSelected(Self::GetPlayer());
				ImGui::Text("%s", Translation::Tr("No players yet!").c_str());
			}
		}));

		menu->AddItem(playerOptionsGroup);

		
		auto customPlayerTp = std::make_shared<Group>("", 1);
		customPlayerTp->AddItem(std::make_shared<Vector3CommandItem>("playertpcoord"_J, ""));
		customPlayerTp->AddItem(std::make_shared<PlayerCommandItem>("tpplayertocoord"_J, "Teleport"));
		auto tpToProperty = std::make_shared<Group>("", 1);
		tpToProperty->AddItem(std::make_shared<ListCommandItem>("sendtopropertyindex"_J, "##selproperty"));
		tpToProperty->AddItem(std::make_shared<PlayerCommandItem>("sendtoproperty"_J));
		auto tpToInterior = std::make_shared<Group>("", 1);
		tpToInterior->AddItem(std::make_shared<ListCommandItem>("sendtointeriorindex"_J, "##selinterior"));
		tpToInterior->AddItem(std::make_shared<PlayerCommandItem>("sendtointerior"_J));
		teleportGroup->AddItem(tpToProperty);
		teleportGroup->AddItem(tpToInterior);
		teleportGroup->AddItem(std::make_shared<PlayerCommandItem>("tptoplayer"_J, "Teleport To"));
		teleportGroup->AddItem(std::make_shared<PlayerCommandItem>("bring"_J));
		teleportGroup->AddItem(customPlayerTp);

		menu->AddItem(teleportGroup);

		return menu;
	}
}
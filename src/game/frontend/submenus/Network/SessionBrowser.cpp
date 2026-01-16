#include "SavedPlayers.hpp"
#include "core/backend/FiberPool.hpp"
#include "core/frontend/widgets/imgui_colors.h"
#include "core/frontend/Notifications.hpp"
#include "game/backend/CustomMatchmaking.hpp"
#include "game/backend/SavedPlayers.hpp"
#include "game/frontend/items/Items.hpp"
#include "game/gta/Network.hpp"
#include "game/pointers/Pointers.hpp"
#include "imgui.h"

namespace YimMenu::Submenus
{
	static int selected_session_idx = -1;

	std::string GetSessionName(const CustomMatchmaking::Session& session)
	{
		auto host_rid = session.m_Info.m_HostInfo.m_GamerHandle.m_RockstarId;

		const auto player = SavedPlayers::GetPlayerData(host_rid);
		if(player)
			return player->m_Name;

		return std::format("{:X}", session.m_Info.m_SessionToken);
	}

	void RenderSessionBrowser()
	{
		static char name_buf[32];
		static char search[64];
		static char session_info[0x100]{};
		ImGui::Text("Total sessions found: %i", CustomMatchmaking::GetNumFoundSessions());

		if (ImGui::BeginListBox("###sessions", ImVec2(300, -ImGui::GetFrameHeight())))
		{
			if (CustomMatchmaking::GetNumFoundSessions())
			{
				for (int i = 0; i < CustomMatchmaking::GetNumFoundSessions(); i++)
				{
					auto& session = CustomMatchmaking::GetFoundSessions()[i];

					if (!session.m_IsValid)
						continue;

					auto host_rid = session.m_Info.m_HostInfo.m_GamerHandle.m_RockstarId;
					auto player   = SavedPlayers::GetPlayerData(host_rid);

					std::string session_str;
					if (session.m_Attributes.m_MultiplexCount > 1)
						session_str = std::format("{} (x{})", GetSessionName(session), session.m_Attributes.m_MultiplexCount);
					else
						session_str = GetSessionName(session);

					if (ImGui::Selectable(session_str.c_str(), i == selected_session_idx))
					{
						selected_session_idx = i;
						//g_pointers->m_gta.m_encode_session_info(&session.info, session_info, 0xA9, nullptr);
					}

					if (ImGui::IsItemHovered())
					{
						auto tool_tip = std::format("Number of Players: {}\nRegion: {}\nLanguage: {}\nHost Rockstar ID: {}\nDiscriminator: {:X}",
						    session.m_Attributes.m_PlayerCount,
						    Features::g_RegionCodes.at(session.m_Attributes.m_Region).second,
						    Features::g_LanguageTypes.at(session.m_Attributes.m_Language).second,
						    session.m_Info.m_HostInfo.m_GamerHandle.m_RockstarId, // TODO: this is not accurate
						    session.m_Attributes.m_Discriminator);
						ImGui::SetTooltip("%s", tool_tip.c_str());
					}
				}
			}
			else
			{
				ImGui::TextUnformatted("No sessions");
			}

			ImGui::EndListBox();
		}

		if (selected_session_idx != -1)
		{
			ImGui::SameLine();
			if (ImGui::BeginChild("###selected_session", ImVec2(300, -ImGui::GetFrameHeight()), false, ImGuiWindowFlags_NoBackground))
			{
				auto& session = CustomMatchmaking::GetFoundSessions()[selected_session_idx];

				ImGui::Text("Num Players: %d", session.m_Attributes.m_PlayerCount);
				ImGui::Text("Discriminator: 0x%X", session.m_Attributes.m_Discriminator);
				ImGui::Text("Region: %s", Features::g_RegionCodes.at(session.m_Attributes.m_Region).second);
				ImGui::Text("Language: %s", Features::g_LanguageTypes.at(session.m_Attributes.m_Language).second);

				auto& data = session.m_Info.m_HostInfo;
				ImGui::Text("Host Rockstar ID: %llu", data.m_GamerHandle.m_RockstarId);

				if(ImGui::Button("Copy Session Info"))
				{
					FiberPool::Push([] {
						ImGui::SetClipboardText(session_info);
					});
				}

				if(ImGui::Button("Join"))
				{
					FiberPool::Push([session] {
						Network::JoinSessionInfo(&session.m_Info);
					});
				}
			}
			ImGui::EndChild();
		}

		static uint32_t discriminator = 730776930; // 0xA9A8562 for non_cheater pool

		ImGui::InputScalar("Discriminator", ImGuiDataType_U32, &discriminator, nullptr, nullptr, "%08X");

		if(ImGui::Button("Refresh"))
		{
			FiberPool::Push( [] {
				selected_session_idx = -1;

				if (!CustomMatchmaking::Matchmake(discriminator))
					Notifications::Show("Matchmaking", "Matchmaking failed", NotificationType::Error);
			});
		}
	}

	std::shared_ptr<Category> BuildSessionBrowser()
	{
		auto menu = std::make_shared<Category>("Session Browser");
		menu->AddItem(std::make_unique<ImGuiItem>(RenderSessionBrowser));

		auto filters = std::make_shared<Group>("Filters");

		filters->AddItem(std::make_shared<BoolCommandItem>("mmlanguagefilterenabled"_J));
		filters->AddItem(std::make_shared<ListCommandItem>("mmlanguagefilter"_J));
		
		filters->AddItem(std::make_shared<BoolCommandItem>("mmfiltermultiplexedsessions"_J));
		
		filters->AddItem(std::make_shared<BoolCommandItem>("mmplayercountfilterenabled"_J));
		filters->AddItem(std::make_shared<IntCommandItem>("mmplayercountfiltermin"_J));
		filters->AddItem(std::make_shared<IntCommandItem>("mmplayercountfiltermax"_J));

		filters->AddItem(std::make_shared<ListCommandItem>("mmsortmethod"_J));
		filters->AddItem(std::make_shared<ListCommandItem>("mmsortdirection"_J));

		menu->AddItem(filters);

		return menu;
	}
}
#include "SavedPlayers.hpp"
#include "core/backend/FiberPool.hpp"
#include "core/frontend/widgets/imgui_colors.h"
#include "core/frontend/Notifications.hpp"
#include "game/backend/CustomMatchmaking.hpp"
#include "game/backend/SavedPlayers.hpp"
#include "game/gta/Network.hpp"
#include "game/pointers/Pointers.hpp"
#include "imgui.h"

namespace YimMenu::Submenus
{
	static int selected_session_idx = -1;

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

					if (!session.is_valid)
						continue;

					std::string session_str;
					if (session.attributes.multiplex_count > 1)
						session_str = std::format("{:X} (x{})", session.info.m_SessionToken, session.attributes.multiplex_count);
					else
						session_str = std::format("{:X}", session.info.m_SessionToken);

					auto host_rid = session.info.m_HostInfo.m_GamerHandle.m_RockstarId;
					/*
					auto player   = g_player_database_service->get_player_by_rockstar_id(host_rid);

					if ((g.session_browser.exclude_modder_sessions && player && player->block_join)
					    || (g.session_browser.filter_multiplexed_sessions && session.attributes.multiplex_count > 1))
						continue;
					*/

					if (ImGui::Selectable(session_str.c_str(), i == selected_session_idx))
					{
						selected_session_idx = i;
						//g_pointers->m_gta.m_encode_session_info(&session.info, session_info, 0xA9, nullptr);
					}

					if (ImGui::IsItemHovered())
					{
						auto tool_tip = std::format("Number of Players: {}\nRegion: {}\nLanguage: {}\nHost Rockstar ID: {}\nDiscriminator: {:X}\nIndex: {}",
						    session.attributes.player_count,
						    /*regions[*/session.attributes.region/*].name*/,
						    /*languages.at((eGameLanguage)*/session.attributes.language/*)*/,
						    session.info.m_HostInfo.m_GamerHandle.m_RockstarId, // TODO: this is not accurate
						    session.attributes.discriminator,
						    i);
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

				ImGui::Text("Num Players: %d", session.attributes.player_count);
				ImGui::Text("Discriminator: 0x%X", session.attributes.discriminator);
				ImGui::Text("Region: %i", /*regions[*/session.attributes.region/*].name*/);
				ImGui::Text("Language: %i", /*languages.at((eGameLanguage)*/session.attributes.language/*).data()*/);

				auto& data = session.info.m_HostInfo;
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
						LOGF(VERBOSE, "Trying to join session '{:X}' hosted by: {}, at: {}", session.info.m_SessionToken, session.info.m_HostInfo.m_GamerHandle.m_RockstarId, selected_session_idx);
						Network::JoinSessionInfo(&session.info);
					});
				}
			}
			ImGui::EndChild();
		}

		/*
		if (ImGui::TreeNode("Filters"))
		{
			ImGui::Checkbox("Region", &g.session_browser.region_filter_enabled);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("It is highly recommended to keep this filter enabled");

			if (g.session_browser.region_filter_enabled)
			{
				ImGui::SameLine();

				if (ImGui::BeginCombo("###region_select", regions[g.session_browser.region_filter].name))
				{
					for (const auto& region : regions)
					{
						if (ImGui::Selectable(region.name, g.session_browser.region_filter == region.id))
						{
							g.session_browser.region_filter = region.id;
						}
					}
					ImGui::EndCombo();
				}
			}

			ImGui::Checkbox("Language", &g.session_browser.language_filter_enabled);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Setting a correct region filter for the language will help tremendously");

			if (g.session_browser.language_filter_enabled)
			{
				ImGui::SameLine();

				if (ImGui::BeginCombo("###language_select", languages.at(g.session_browser.language_filter).data()))
				{
					for (const auto& [id, language] : languages)
					{
						if (ImGui::Selectable(language.data(), g.session_browser.language_filter == id))
						{
							g.session_browser.language_filter = id;
						};
					}
					ImGui::EndCombo();
				}
			}

			ImGui::Checkbox("Players", &g.session_browser.player_count_filter_enabled);

			if (g.session_browser.player_count_filter_enabled)
			{
				ImGui::InputInt("Minimum", &g.session_browser.player_count_filter_minimum);
				ImGui::InputInt("Maximum", &g.session_browser.player_count_filter_maximum);
			}

			ImGui::Checkbox("Pool Type", &g.session_browser.pool_filter_enabled);
			if (g.session_browser.pool_filter_enabled)
			{
				ImGui::SameLine();
				ImGui::Combo("###pooltype", &g.session_browser.pool_filter, "Normal\0Bad Sport\0");
			}

			ImGui::Checkbox("Filter Multiplexed Sessions", &g.session_browser.filter_multiplexed_sessions);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Removes advertised sessions");

			ImGui::Checkbox("Exclude Modder Sessions", &g.session_browser.exclude_modder_sessions);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Excludes hosts that you have blocked in the Player Database");

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Sorting"))
		{
			ImGui::Combo("Sort By", &g.session_browser.sort_method, "Off\0Player Count\0");
			if (g.session_browser.sort_method != 0)
				ImGui::Combo("Direction", &g.session_browser.sort_direction, "Ascending\0Descending\0");
			ImGui::TreePop();
		}

		ImGui::Checkbox("Replace Game Matchmaking", &g.session_browser.replace_game_matchmaking);
		ImGui::SameLine();
		components::help_marker("This will replace the default game matchmaking with a custom one that will use the filters and sorting set here");
		**/

		static uint32_t discriminator = 730776930;

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

		return menu;
	}
}
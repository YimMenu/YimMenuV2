#include "Network.hpp"
#include "core/backend/FiberPool.hpp"
#include "core/backend/PatternCache.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/backend/AnticheatBypass.hpp"
#include "game/backend/ProtectionTelemetry.hpp"
#include "game/frontend/items/Items.hpp"
#include "game/frontend/submenus/Network/SavedPlayers.hpp"
#include "game/frontend/submenus/Network/RandomEvents.hpp"
#include "game/gta/Network.hpp"
#include "game/pointers/Pointers.hpp"

namespace YimMenu::Submenus
{
	Network::Network() :
		#define ICON_FA_ROUTE "\xef\x9b\xbf"
	    Submenu::Submenu("Network", ICON_FA_ROUTE)
	{
		// TODO: this needs a rework
		auto session = std::make_shared<Category>("Session");
		auto joinGroup = std::make_shared<Group>("Join");
		auto bountyGroup = std::make_shared<Group>("Bounty", 1);
		auto toxicGroup = std::make_shared<Group>("Toxic");
		auto teleportGroup = std::make_shared<Group>("Teleport");
		auto trollGroup = std::make_shared<Group>("Troll");
		auto miscGroup = std::make_shared<Group>("Misc");
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

		auto customPlayerTp = std::make_shared<Group>("", 1);
		customPlayerTp->AddItem(std::make_shared<Vector3CommandItem>("playertpcoord"_J, ""));
		customPlayerTp->AddItem(std::make_shared<CommandItem>("tpplayertocoordall"_J, "Teleport Everyone"));
		auto tpToProperty = std::make_shared<Group>("", 1);
		tpToProperty->AddItem(std::make_shared<ListCommandItem>("sendtopropertyindex"_J, "##selproperty"));
		tpToProperty->AddItem(std::make_shared<CommandItem>("sendtopropertyall"_J, "Send All to Property"));
		auto tpToInterior = std::make_shared<Group>("", 1);
		tpToInterior->AddItem(std::make_shared<ListCommandItem>("sendtointeriorindex"_J, "##selinterior"));
		tpToInterior->AddItem(std::make_shared<CommandItem>("sendtointeriorall"_J, "Send All to Interior"));
		teleportGroup->AddItem(tpToProperty);
		teleportGroup->AddItem(tpToInterior);
		teleportGroup->AddItem(std::make_shared<CommandItem>("bringall"_J, "Bring All"));
		teleportGroup->AddItem(customPlayerTp);

		trollGroup->AddItem(std::make_shared<CommandItem>("sendsextall"_J, "Send Sexts"));
		trollGroup->AddItem(std::make_shared<BoolCommandItem>("harassplayers"_J));
		trollGroup->AddItem(std::make_shared<BoolCommandItem>("spamkillfeed"_J));
		trollGroup->AddItem(std::make_shared<CommandItem>("deletevehall"_J, "Delete Player Vehicles"));

		toxicGroup->AddItem(std::make_shared<CommandItem>("killall"_J, "Kill All"));
		toxicGroup->AddItem(std::make_shared<CommandItem>("killexploitall"_J, "Permadeath All"));
		toxicGroup->AddItem(std::make_shared<CommandItem>("explodeall"_J, "Explode All"));
		toxicGroup->AddItem(std::make_shared<CommandItem>("ceokickall"_J, "CEO Kick All"));
		toxicGroup->AddItem(std::make_shared<CommandItem>("hkickall"_J, "Host Kick All"));

		miscGroup->AddItem(std::make_shared<BoolCommandItem>("forcethunder"_J));

		enhancements->AddItem(std::make_shared<BoolCommandItem>("notifyonplayerjoin"_J));
		enhancements->AddItem(std::make_shared<BoolCommandItem>("fastjoin"_J));
		enhancements->AddItem(std::make_shared<BoolCommandItem>("disabledeathbarriers"_J));
		enhancements->AddItem(std::make_shared<BoolCommandItem>("despawnbypass"_J));
		enhancements->AddItem(std::make_shared<BoolCommandItem>("bypasscasinogeoblock"_J));
		enhancements->AddItem(std::make_shared<BoolCommandItem>("forcescripthost"_J));
		enhancements->AddItem(std::make_shared<BoolCommandItem>("pausegame"_J));
		enhancements->AddItem(std::make_shared<BoolCommandItem>("nocalls"_J));

		session->AddItem(joinGroup);
		session->AddItem(bountyGroup);
		session->AddItem(trollGroup);
		session->AddItem(teleportGroup);
		session->AddItem(toxicGroup);
		session->AddItem(miscGroup);
		session->AddItem(enhancements);

		auto spoofing = std::make_shared<Category>("Spoofing");
		auto matchmakingGroup = std::make_shared<Group>("Matchmaking (Client)");
		matchmakingGroup->AddItem(std::make_shared<BoolCommandItem>("cheaterpool"_J));
		auto spoofMMRegion = std::make_shared<Group>("", 1);
		spoofMMRegion->AddItem(std::make_shared<BoolCommandItem>("spoofmmregion"_J, "Spoof Region"));
		spoofMMRegion->AddItem(std::make_shared<ConditionalItem>("spoofmmregion"_J, std::make_shared<ListCommandItem>("mmregion"_J, "##mmregion")));
		matchmakingGroup->AddItem(std::make_shared<ConditionalItem>("cheaterpool"_J, spoofMMRegion, true));
		matchmakingGroup->AddItem(std::make_shared<BoolCommandItem>("spoofdatahash"_J));
		spoofing->AddItem(matchmakingGroup);

		auto matchmakingSrvGroup = std::make_shared<Group>("Matchmaking (Server)");
		auto srvSpoofRegion = std::make_shared<Group>("", 1);
		srvSpoofRegion->AddItem(std::make_shared<BoolCommandItem>("mmspoofregiontype"_J));
		srvSpoofRegion->AddItem(std::make_shared<ConditionalItem>("mmspoofregiontype"_J, std::make_shared<ListCommandItem>("mmregiontype"_J, "##mmregiontype")));
		auto srvSpoofLanguage = std::make_shared<Group>("", 1);
		srvSpoofLanguage->AddItem(std::make_shared<BoolCommandItem>("mmspooflanguage"_J));
		srvSpoofLanguage->AddItem(std::make_shared<ConditionalItem>("mmspooflanguage"_J, std::make_shared<ListCommandItem>("mmlanguage"_J, "##mmlanguage")));
		auto srvSpoofPlayerCount = std::make_shared<Group>("", 1);
		srvSpoofPlayerCount->AddItem(std::make_shared<BoolCommandItem>("mmspoofplayercount"_J));
		srvSpoofPlayerCount->AddItem(std::make_shared<ConditionalItem>("mmspoofplayercount"_J, std::make_shared<IntCommandItem>("mmplayercount"_J, "##mmplayercount")));
		auto srvMultiplex = std::make_shared<Group>("", 1);
		srvMultiplex->AddItem(std::make_shared<BoolCommandItem>("mmmultiplexsession"_J));
		srvMultiplex->AddItem(std::make_shared<ConditionalItem>("mmmultiplexsession"_J, std::make_shared<IntCommandItem>("mmmultiplexsessioncount"_J, "##mmmultiplexsessioncount")));
		matchmakingSrvGroup->AddItem(std::move(srvSpoofRegion));
		matchmakingSrvGroup->AddItem(std::move(srvSpoofLanguage));
		matchmakingSrvGroup->AddItem(std::move(srvSpoofPlayerCount));
		matchmakingSrvGroup->AddItem(std::move(srvMultiplex));
		spoofing->AddItem(matchmakingSrvGroup);

		auto diagnostics = std::make_shared<Category>("Diagnostics");
		diagnostics->AddItem(std::make_shared<ImGuiItem>([] {
			const auto game_version = Pointers.GameVersion ? Pointers.GameVersion : "Unavailable";
			const auto online_version = Pointers.OnlineVersion ? Pointers.OnlineVersion : "Unavailable";
			const bool session_started = Pointers.IsSessionStarted && *Pointers.IsSessionStarted;
			const auto uptime = ProtectionTelemetry::Uptime();
			const auto hours = std::chrono::duration_cast<std::chrono::hours>(uptime);
			const auto minutes = std::chrono::duration_cast<std::chrono::minutes>(uptime - hours);
			const auto seconds = uptime - hours - minutes;

			ImGui::Text("Game version: %s", game_version);
			ImGui::Text("Online version: %s", online_version);
			ImGui::Text("Pattern cache: %s (%zu entries)", PatternCache::IsInitialized() ? "Ready" : "Unavailable", PatternCache::GetEntryCount());
			ImGui::Text("Session: %s", session_started ? "Online" : "Offline");
			ImGui::Text("BattlEye: %s", AnticheatBypass::IsBattlEyeRunning() ? "Running" : "Not running");
			ImGui::Text("FSL: %s", AnticheatBypass::IsFSLLoaded() ? "Loaded" : "Not loaded");
			if (AnticheatBypass::IsFSLLoaded())
			{
				ImGui::Text("FSL version: %d", AnticheatBypass::GetFSLVersion());
				ImGui::Text("FSL local saves: %s", AnticheatBypass::IsFSLProvidingLocalSaves() ? "Available" : "Unavailable");
				ImGui::Text("FSL BattlEye bypass: %s", AnticheatBypass::IsFSLProvidingBattlEyeBypass() ? "Available" : "Unavailable");
			}
			ImGui::Text("Runtime: %lldh %lldm %llds", hours.count(), minutes.count(), seconds.count());

			if (!Pointers.GameVersion || !Pointers.OnlineVersion)
				ImGui::TextColored(ImVec4(1.0f, 0.65f, 0.2f, 1.0f), "Compatibility warning: version pointers are unavailable.");
			if (AnticheatBypass::IsBattlEyeRunning() && !AnticheatBypass::IsFSLProvidingBattlEyeBypass())
				ImGui::TextColored(ImVec4(1.0f, 0.35f, 0.25f, 1.0f), "Safety warning: BattlEye is running without an FSL bypass.");

			ImGui::SeparatorText("Protection telemetry");
			ImGui::TextDisabled("Aggregate counts only; no player identifiers are retained.");
			const auto snapshot = ProtectionTelemetry::GetSnapshot();
			std::uint64_t total_events{};
			for (const auto& entry : snapshot)
				total_events += entry.m_Count;
			ImGui::Text("Total protection events: %llu", static_cast<unsigned long long>(total_events));

			if (ImGui::BeginTable("protection_telemetry", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_SizingStretchProp))
			{
				ImGui::TableSetupColumn("Event");
				ImGui::TableSetupColumn("Count", ImGuiTableColumnFlags_WidthFixed, 90.0f);
				ImGui::TableSetupColumn("Last seen", ImGuiTableColumnFlags_WidthFixed, 110.0f);
				ImGui::TableHeadersRow();

				for (const auto& entry : snapshot)
				{
					ImGui::TableNextRow();
					ImGui::TableSetColumnIndex(0);
					ImGui::TextUnformatted(entry.m_Name.data(), entry.m_Name.data() + entry.m_Name.size());
					ImGui::TableSetColumnIndex(1);
					ImGui::Text("%llu", static_cast<unsigned long long>(entry.m_Count));
					ImGui::TableSetColumnIndex(2);
					if (entry.m_LastSeenAgo)
						ImGui::Text("%llds ago", entry.m_LastSeenAgo->count());
					else
						ImGui::TextUnformatted("Never");
				}
				ImGui::EndTable();
			}

			if (ImGui::Button("Reset telemetry"))
				ProtectionTelemetry::Reset();
			ImGui::SameLine();
			if (ImGui::Button("Copy diagnostics"))
			{
				std::string report = std::format(
					"YimMenuV2 diagnostics\n"
					"Game version: {}\n"
					"Online version: {}\n"
					"Pattern cache: {} ({} entries)\n"
					"Session: {}\n"
					"BattlEye: {}\n"
					"FSL: {}\n"
					"Runtime: {}h {}m {}s\n"
					"Protection telemetry:\n",
					game_version,
					online_version,
					PatternCache::IsInitialized() ? "Ready" : "Unavailable",
					PatternCache::GetEntryCount(),
					session_started ? "Online" : "Offline",
					AnticheatBypass::IsBattlEyeRunning() ? "Running" : "Not running",
					AnticheatBypass::IsFSLLoaded() ? "Loaded" : "Not loaded",
					hours.count(),
					minutes.count(),
					seconds.count());

				for (const auto& entry : ProtectionTelemetry::GetSnapshot())
					report += std::format(
						"- {}: {} (last seen: {})\n",
						entry.m_Name,
						entry.m_Count,
						entry.m_LastSeenAgo ? std::format("{}s ago", entry.m_LastSeenAgo->count()) : "never");

				ImGui::SetClipboardText(report.c_str());
				Notifications::Show("Diagnostics", "Copied privacy-safe diagnostics to the clipboard", NotificationType::Success);
			}
		}));

		AddCategory(std::move(session));
		AddCategory(std::move(spoofing));
		AddCategory(std::move(diagnostics));
		AddCategory(std::move(BuildSavedPlayersMenu()));
		AddCategory(BuildRandomEventsMenu());
	}
}

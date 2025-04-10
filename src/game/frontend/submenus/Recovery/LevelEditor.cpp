#include "StatEditor.hpp"
#include "core/backend/FiberPool.hpp"
#include "game/backend/AnticheatBypass.hpp"
#include "game/pointers/Pointers.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/Stats.hpp"
#include "core/frontend/Notifications.hpp"
#include "types/stats/CStatsMgr.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "LevelDataStorage.hpp" // Include the new header with the RP table

#include <format>
#include <optional>
#include <array>
#include <functional>
#include <chrono>

namespace YimMenu::Submenus
{
	// --- Constants ---
	namespace LevelData
	{
		// Use the MAX_RANK defined in the storage header
		constexpr int MAX_RANK = MAX_RANK_INTERNAL;
		// Exact MAX_RP is now known from the table
		constexpr int MAX_RP = rpLevelTable[MAX_RANK];

		// Script Globals used for RP Gift (Keep these as they are correct)
		constexpr int GLOBAL_RP_GIFT_TUNABLE = 1575036;
		constexpr int RP_GIFT_TUNABLE_VALUE  = 11;
		constexpr int GLOBAL_SET_RANK_FLAG   = 1574589;

		// Stat Names (Keep these)
		const char* const STAT_RANK = "mpx_CHAR_RANK_FM";
		const char* const STAT_XP = "mpx_CHAR_XP_FM";
		const char* const STAT_RP_GIFT = "mpx_CHAR_SET_RP_GIFT_ADMIN";

        // You can customize this list as desired
		constexpr std::array<int, 11> quickRankValues = {
            10, 25, 50, 100, 120, 200, 500, 1000, 3131, 6666, MAX_RANK
        };

		// RankData struct is no longer needed
		// The sparse rankTable is no longer needed	

	} // namespace LevelData

	// --- Helper Functions ---

	// Get RP directly from the table - REPLACES interpolation
	static int CalculateRPForRank(int targetRank)
	{
		using namespace LevelData;

		// Clamp the requested rank to valid bounds [1, MAX_RANK]
		targetRank = std::clamp(targetRank, 1, MAX_RANK);

		// Direct lookup using the rank as the index (rpLevelTable[0] is for Rank 0)
        // Add bounds check just in case, though clamp should prevent out-of-bounds.
        if (targetRank >= 0 && targetRank <= MAX_RANK) {
		    return rpLevelTable[targetRank];
        }

        // Fallback (should ideally not be reached due to clamping)
        // Log::Warning("LevelEditor", std::format("Invalid targetRank {} requested in CalculateRPForRank after clamp.", targetRank));
        return 0; // Or return rpLevelTable[MAX_RANK] ? Returning 0 is safer.
	}

	// Get current character rank using std::optional (No changes needed)
	static std::optional<int> GetCurrentRank()
	{
		if (!NativeInvoker::AreHandlersCached()) return std::nullopt;
		int rank = Stats::GetInt(LevelData::STAT_RANK);
		return (rank >= 0) ? std::make_optional(rank) : std::nullopt;
	}

	// Get current character RP using std::optional (No changes needed)
	static std::optional<int> GetCurrentRP()
	{
		if (!NativeInvoker::AreHandlersCached()) return std::nullopt;
		int rp = Stats::GetInt(LevelData::STAT_XP);
		return (rp >= 0) ? std::make_optional(rp) : std::nullopt;
	}

	// Set rank via RP Gift method (Logic remains the same, relies on accurate CalculateRPForRank)
	static void SetRankViaGift(int targetRank)
	{
		using namespace LevelData;
		using namespace std::chrono_literals;

		targetRank = std::clamp(targetRank, 1, MAX_RANK); // Clamp target rank

		auto currentRankOpt = GetCurrentRank();
		if (!currentRankOpt)
		{
			Notifications::Show("Level Editor", "Failed to get current Rank.", NotificationType::Error);
			return;
		}
		int currentRank = currentRankOpt.value();

		if (targetRank <= currentRank)
		{
			Notifications::Show("Level Editor", std::format("Target rank ({}) must be higher than current ({}) for RP Gift.", targetRank, currentRank), NotificationType::Info);
			return;
		}

		// Calculate the TOTAL RP required using the new precise lookup
		int requiredRP = CalculateRPForRank(targetRank);

        // Basic check on calculated RP
        if (requiredRP < 0) { // Should only happen if CalculateRPForRank has an issue
            Notifications::Show("Level Editor", "Error calculating required RP.", NotificationType::Error);
            return;
        }

		Stats::SetInt(STAT_RP_GIFT, requiredRP); // Set the gift stat to the total target RP

		FiberPool::Push([targetRank, requiredRP] {
			ScriptGlobal(GLOBAL_RP_GIFT_TUNABLE).As<int&>() = RP_GIFT_TUNABLE_VALUE;
			ScriptGlobal(GLOBAL_SET_RANK_FLAG).As<int&>() = 1;
			ScriptGlobal(GLOBAL_SET_RANK_FLAG).As<int&>() = 0;

			Notifications::Show("Level Editor", std::format("RP Gift initiated for Rank {}. (Set Gift RP to {}) Change session to apply.", targetRank, requiredRP), NotificationType::Success);
		});
	}

	// Set rank directly via XP (Logic remains the same, relies on accurate CalculateRPForRank)
	static void SetRankDirectly(int targetRank)
	{
		using namespace LevelData;
        targetRank = std::clamp(targetRank, 1, MAX_RANK); // Clamp here too
		int requiredRP = CalculateRPForRank(targetRank);

         if (requiredRP < 0) {
			Notifications::Show("Level Editor", "Error calculating required RP for direct set.", NotificationType::Error);
            return;
		}

		FiberPool::Push([requiredRP, targetRank] {
			bool canSetDirectly = AnticheatBypass::IsFSLLoaded();
			// Simplified check - primarily rely on bypass
			if (!canSetDirectly)
			{
                 Notifications::Show("Level Editor", "Bypass not loaded, direct set might fail.", NotificationType::Warning);
                 // Optionally add Pointers.StatsMgr check here if needed
			}

			if (canSetDirectly)
			{
				Stats::SetInt(STAT_XP, requiredRP);
				Notifications::Show("Level Editor", std::format("Directly set XP to {} for Rank {}. May take a moment to update.", requiredRP, targetRank), NotificationType::Success);
			}
			else
			{
				Notifications::Show("Level Editor", "Cannot set rank directly. Bypass inactive or stat protected? Try RP Gift.", NotificationType::Warning);
			}
		});
	}


	// --- UI Helper Functions ---
	namespace UIElements
	{
		// DrawCurrentRankInfo (No changes needed)
        static void DrawCurrentRankInfo()
		{
			if (!NativeInvoker::AreHandlersCached())
			{
				ImGui::TextDisabled("Waiting for game data...");
				return;
			}
			auto currentRank = GetCurrentRank();
			auto currentRP = GetCurrentRP();
			ImGui::Text("Current Rank: %s", currentRank ? std::format("{}", currentRank.value()).c_str() : "Loading...");
			ImGui::Text("Current RP: %s", currentRP ? std::format("{}", currentRP.value()).c_str() : "Loading...");
		}


		// DrawRankInputAndMethod (No changes needed in logic, uses updated CalculateRPForRank)
		static void DrawRankInputAndMethod(int& targetRank, int& selectedMethod)
		{
			ImGui::SetNextItemWidth(200.f);
			if (ImGui::InputInt("Target Rank", &targetRank))
			{
				targetRank = std::clamp(targetRank, 1, LevelData::MAX_RANK);
			}

			int displayRP = CalculateRPForRank(targetRank); // Now uses precise lookup
            ImGui::Text("Required RP: %s", (displayRP >= 0) ? std::format("{}", displayRP).c_str() : "Error");
			ImGui::Separator();

			const char* methods[] = {"RP Gift (Safer - Increase Only)", "Direct XP Set (Risky - Set Exact)"};
			ImGui::SetNextItemWidth(200.f);
			ImGui::Combo("Method", &selectedMethod, methods, IM_ARRAYSIZE(methods));

			if (selectedMethod == 0) {
				ImGui::TextWrapped("Uses the RP Gift stat. Sets the *target total RP* and triggers game globals. Should only work if the target rank is *higher* than current. Requires changing session.");
			} else {
				ImGui::TextWrapped("Attempts to directly overwrite your total RP/XP stat. Can increase or decrease rank. Riskier, may require bypasses, could be detected.");
			}
		}

		// DrawApplyButton (No changes needed in logic)
		static void DrawApplyButton(int targetRank, int selectedMethod)
		{
			if (ImGui::Button("Apply Rank Change"))
			{
                int finalTargetRank = std::clamp(targetRank, 1, LevelData::MAX_RANK);
				if (selectedMethod == 0) {
					SetRankViaGift(finalTargetRank);
				} else {
					SetRankDirectly(finalTargetRank);
				}
			}
		}

		// DrawQuickRankButtons (Uses updated quickRankValues and accurate CalculateRPForRank)
		static void DrawQuickRankButtons(int& targetRankRef, int selectedMethod)
		{
			ImGui::Text("Quick Ranks:");
			// Use columns for better layout if many buttons
            int columns = 4; // Adjust as needed
            int button_count = 0;
            ImGui::Columns(columns, nullptr, false); // No borders


			std::function<void(int)> ApplyRank = [&](int rank) {
                int finalQuickRank = std::clamp(rank, 1, LevelData::MAX_RANK);
				if (selectedMethod == 0) {
					SetRankViaGift(finalQuickRank);
				} else {
					SetRankDirectly(finalQuickRank);
				}
			};

			for (int rank : LevelData::quickRankValues) // Use range-based for loop
			{
				// Push ID to avoid conflicts if labels are the same (though rank numbers make them unique here)
                ImGui::PushID(rank);
                if (ImGui::Button(std::format("Rank {}", rank).c_str(), ImVec2(-FLT_MIN, 0))) // Full width button
				{
					targetRankRef = rank; // Update the input field too
					ApplyRank(rank);
				}
                 ImGui::PopID();
                ImGui::NextColumn();
                button_count++;
			}
            ImGui::Columns(1); // Reset columns
		}

	} // namespace UIElements


	// --- Main Menu Builder --- (No changes needed)
	std::shared_ptr<Category> BuildLevelEditorMenu()
	{
		auto menu = std::make_shared<Category>("Level Editor");
		auto main = std::make_shared<Group>("Rank Settings");

		main->AddItem(std::make_unique<ImGuiItem>([] {
			static int targetRank = 120;
			static int selectedMethod = 0;

			UIElements::DrawCurrentRankInfo();
			ImGui::Separator();
			UIElements::DrawRankInputAndMethod(targetRank, selectedMethod);
			ImGui::Separator();
			UIElements::DrawApplyButton(targetRank, selectedMethod);
			ImGui::Separator();
			UIElements::DrawQuickRankButtons(targetRank, selectedMethod);

		}));

		menu->AddItem(std::move(main));
		return menu;
	}

} // namespace YimMenu::Submenus


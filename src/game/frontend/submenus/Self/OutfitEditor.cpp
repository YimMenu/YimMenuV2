#include "OutfitEditor.hpp"
#include "core/backend/FiberPool.hpp"
#include "OutfitEditorCategory.hpp"
#include "game/frontend/items/Items.hpp"

namespace YimMenu
{
	std::shared_ptr<Category> CreateOutfitsMenu()
	{
		auto category = std::make_shared<OutfitEditorCategory>("Outfit Editor");

		category->AddItem(std::make_shared<ImGuiItem>([category] {
			if (ImGui::Button("Refresh Stats"))
				FiberPool::Push([category] {
					category->RefreshStats();
				});
			ImGui::SameLine();
			if (ImGui::Button("Randomize Outfit"))
				FiberPool::Push([category] {
					Self::GetPed().RandomizeOutfit2();
				});

			category->RenderComponents();
			ImGui::SameLine();
			category->RenderComponentsTextures();
			ImGui::SameLine();
			ImGui::BeginGroup();
			{
				category->RenderProps();
				ImGui::Spacing();
				category->RenderPropsTextures();
			}
			ImGui::EndGroup();

			ImGui::Spacing();

			category->RenderOutfitList();
			ImGui::SameLine();
			category->RenderOutfitListControls();
		}));

		return category;
	}
}

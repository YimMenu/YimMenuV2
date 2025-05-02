#include "TimeChanger.hpp"

#include "core/frontend/manager/UIManager.hpp"
#include "game/backend/Self.hpp"
#include "game/frontend/items/Items.hpp"
#include "game/gta/Natives.hpp"
#include "imgui.h"

namespace YimMenu::Submenus
{
	std::shared_ptr<Category> timechanger()
	{
		auto category = std::make_shared<YimMenu::Category>("Time Control");

		category->AddItem(std::make_shared<ImGuiItem>([] {
			static int hour     = 12;
			static int minute   = 0;
			static int second   = 0;
			static bool enabled = false;

			ImGui::Text("Override Time");

			ImGui::SliderInt("Hour", &hour, 0, 23);
			ImGui::SliderInt("Minute", &minute, 0, 59);
			ImGui::SliderInt("Second", &second, 0, 59);

			if (ImGui::Checkbox("Enable Override", &enabled))
			{
				if (!enabled)
					NETWORK::NETWORK_CLEAR_CLOCK_TIME_OVERRIDE();
			}

			if (enabled)
			{
				NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(hour, minute, second);
			}
		}));

		return category;
	}
}

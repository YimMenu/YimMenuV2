#include "VehicleFun.hpp"

#include "core/backend/FiberPool.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<Category> BuildVehicleFunMenu()
	{
		auto vehicleFun = std::make_shared<Category>("Fun");

		vehicleFun->AddItem(std::make_unique<ImGuiItem>([] {
			if (!Self::GetVehicle())
			{
				ImGui::Text("Please enter a vehicle.");
				return;
			}

			ImGui::Text("Lowrider Controls -");
			ImGui::BeginGroup();
			{
				static float maxWheelRaiseFactor = 2;
				
				ImGui::SetNextItemWidth(150);
				ImGui::SliderFloat("Wheel Raise Factor", &maxWheelRaiseFactor, 1, 3);

				for (int i = 0; i < 4; ++i)
				{
					auto label = "Raise W" + std::to_string(i + 1);
					if (ImGui::Button(label.c_str()))
						FiberPool::Push([=] {
							Self::GetVehicle().RaiseHydraulicWheel(i, maxWheelRaiseFactor);
						});
					ImGui::SameLine();
				}
				ImGui::NewLine();
				for (int i = 0; i < 4; ++i)
				{
					auto label = "Lower W" + std::to_string(i + 1);
					if (ImGui::Button(label.c_str()))
						FiberPool::Push([=] {
							Self::GetVehicle().LowerHydraulicWheel(i, maxWheelRaiseFactor);
						});
					ImGui::SameLine();
				}
			}
			ImGui::EndGroup();
		}));

		return vehicleFun;
	}
}

#include "Menu.hpp"

namespace NewBase
{
	void Menu::Main()
	{
		if (!GUI::IsOpen())
			return;

		if (ImGui::Begin("Test"))
		{
			if (ImGui::Button("Unload"))
				g_Running = false;
		}
		ImGui::End();
	}
}
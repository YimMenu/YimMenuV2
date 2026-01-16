#include "GUISettings.hpp"
#include "core/commands/ColorCommand.hpp"
#include "core/commands/Command.hpp"
#include "core/commands/FloatCommand.hpp"
#include "core/frontend/manager/styles/Themes.hpp"
#include <regex>

namespace YimMenu
{
	static std::vector<std::unique_ptr<ColorCommand>> g_ColorCommands;
	static std::unordered_map<std::string, float> g_RoundingValues;
	static std::unordered_map<std::string, std::unique_ptr<FloatCommand>> g_FloatCommands; // Global map for all FloatCommands
	static bool g_ColorInit = false, g_RoundingInit = false;

	static const std::string kSettingsFile = [] {
		char* path = nullptr;
		size_t len = 0;
		_dupenv_s(&path, &len, "APPDATA");
		std::string full = std::string(path ? path : "") + "\\YimMenuV2\\themes.json";
		free(path);
		return full;
	}();

	static std::string PrettyPrintLabel(const std::string& raw)
	{
		std::string out = raw;
		if (out.size() > 2 && out.compare(out.size() - 2, 2, "_X") == 0)
			out.replace(out.size() - 2, 2, " Horizontal");
		else if (out.size() > 2 && out.compare(out.size() - 2, 2, "_Y") == 0)
			out.replace(out.size() - 2, 2, " Vertical");

		std::string spaced;
		spaced.reserve(out.size() + 10);
		for (size_t i = 0; i < out.size(); ++i)
		{
			if (i > 0 && isupper(out[i]) && islower(out[i - 1]))
				spaced += ' ';
			spaced += out[i];
		}

		std::regex uscore_re("_");
		spaced = std::regex_replace(spaced, uscore_re, " ");

		return spaced;
	}

	void SyncColorCommandsToStyle()
	{
		auto& style = ImGui::GetStyle();
		for (int i = 0; i < ImGuiCol_COUNT; i++)
			style.Colors[i] = g_ColorCommands[i]->GetState();
	}

	static void SyncRoundingToStyle()
	{
		auto& s = ImGui::GetStyle();
		for (auto& [k, v] : g_RoundingValues)
			if (k == "WindowRounding")
				s.WindowRounding = v;
			else if (k == "FrameRounding")
				s.FrameRounding = v;
			else if (k == "GrabRounding")
				s.GrabRounding = v;
			else if (k == "ScrollbarRounding")
				s.ScrollbarRounding = v;
			else if (k == "ChildRounding")
				s.ChildRounding = v;
			else if (k == "PopupRounding")
				s.PopupRounding = v;
			else if (k == "TabRounding")
				s.TabRounding = v;
	}

	static void LoadSettings()
	{
		if (!std::filesystem::exists(kSettingsFile))
			return;
		std::ifstream file(kSettingsFile);
		nlohmann::json json;
		file >> json;

		// Load colors
		for (int i = 0; i < ImGuiCol_COUNT; ++i)
			if (auto it = json.find(ImGui::GetStyleColorName(i)); it != json.end() && it->is_array())
				g_ColorCommands[i]->SetState(ImVec4((*it)[0], (*it)[1], (*it)[2], (*it)[3]));

		// Load rounding values
		for (const char* key : {"WindowRounding", "FrameRounding", "GrabRounding", "ScrollbarRounding", "ChildRounding", "PopupRounding", "TabRounding"})
			if (auto it = json.find(key); it != json.end())
				g_RoundingValues[key] = *it;

		// Load all float command values (except colors and rounding, which are handled)
		for (auto& [key, cmd] : g_FloatCommands)
		{
			if (auto it = json.find(key); it != json.end() && it->is_number())
			{
				cmd->SetState(it->get<float>());
			}
		}
	}

	static void SaveSettings()
	{
		nlohmann::json json;

		// Save colors
		for (int i = 0; i < ImGuiCol_COUNT; ++i)
		{
			auto c = g_ColorCommands[i]->GetState();
			json[ImGui::GetStyleColorName(i)] = {c.x, c.y, c.z, c.w};
		}

		// Save rounding
		for (auto& [k, v] : g_RoundingValues)
			json[k] = v;

		// Save floats
		for (auto& [k, cmd] : g_FloatCommands)
			json[k] = cmd->GetState();

		std::filesystem::create_directories(std::filesystem::path(kSettingsFile).parent_path());
		std::ofstream(kSettingsFile) << json.dump(4);
	}

	void ApplyThemeToImGui()
	{
		auto& style = ImGui::GetStyle();

		for (int i = 0; i < ImGuiCol_COUNT; ++i)
			style.Colors[i] = g_ColorCommands[i]->GetState();

		style.WindowRounding = g_RoundingValues["WindowRounding"];
		style.FrameRounding = g_RoundingValues["FrameRounding"];
		style.GrabRounding = g_RoundingValues["GrabRounding"];
		style.ScrollbarRounding = g_RoundingValues["ScrollbarRounding"];
		style.ChildRounding = g_RoundingValues["ChildRounding"];
		style.PopupRounding = g_RoundingValues["PopupRounding"];
		style.TabRounding = g_RoundingValues["TabRounding"];
	}


	void InitializeColorCommands()
	{
		if (g_ColorInit)
			return;
		auto& style = ImGui::GetStyle();
		for (int i = 0; i < ImGuiCol_COUNT; ++i)
			g_ColorCommands.emplace_back(std::make_unique<ColorCommand>(
			    "ColorCommand." + std::string(ImGui::GetStyleColorName(i)),
			    ImGui::GetStyleColorName(i),
			    "Edit color for " + std::string(ImGui::GetStyleColorName(i)),
			    style.Colors[i]));

		if (!g_RoundingInit)
		{
			g_RoundingInit = true;
			g_RoundingValues = {
			    {"WindowRounding", style.WindowRounding},
			    {"FrameRounding", style.FrameRounding},
			    {"GrabRounding", style.GrabRounding},
			    {"ScrollbarRounding", style.ScrollbarRounding},
			    {"ChildRounding", style.ChildRounding},
			    {"PopupRounding", style.PopupRounding},
			    {"TabRounding", style.TabRounding}};
		}

		LoadSettings();
		SyncColorCommandsToStyle();
		SyncRoundingToStyle();
		g_ColorInit = true;
	}

	static void DrawStyleVec2(const char* label, float& x, float& y, float min, float max)
	{
		std::string nameX = std::string(label) + "_X";
		std::string nameY = std::string(label) + "_Y";

		// Use global float commands map
		if (!g_FloatCommands.count(nameX))
			g_FloatCommands[nameX] = std::make_unique<FloatCommand>(nameX.c_str(), nameX.c_str(), "Adjust " + nameX, min, max, x);
		if (!g_FloatCommands.count(nameY))
			g_FloatCommands[nameY] = std::make_unique<FloatCommand>(nameY.c_str(), nameY.c_str(), "Adjust " + nameY, min, max, y);

		float newX = g_FloatCommands[nameX]->GetState();
		float newY = g_FloatCommands[nameY]->GetState();

		bool changed = false;
		changed |= ImGui::SliderFloat(PrettyPrintLabel(nameX).c_str(), &newX, min, max, "%.1f");
		changed |= ImGui::SliderFloat(PrettyPrintLabel(nameY).c_str(), &newY, min, max, "%.1f");

		if (changed)
		{
			g_FloatCommands[nameX]->SetState(newX);
			g_FloatCommands[nameY]->SetState(newY);
			x = newX;
			y = newY;
			SaveSettings();
		}
	}

	static void DrawStyleFloat(const char* label, float& v, float min, float max)
	{
		std::string name(label);

		if (!g_FloatCommands.count(name))
			g_FloatCommands[name] = std::make_unique<FloatCommand>(name.c_str(), name.c_str(), "Adjust " + name, min, max, v);

		float newVal = g_FloatCommands[name]->GetState();
		if (ImGui::SliderFloat(PrettyPrintLabel(name).c_str(), &newVal, min, max, "%.1f"))
		{
			g_FloatCommands[name]->SetState(newVal);
			v = newVal;
			SaveSettings();
		}
	}

	static void DrawColorsTab()
	{
		bool changed = false;
		ImGui::Text("Modify Colors:");
		ImGui::Separator();
		for (int i = 0; i < ImGuiCol_COUNT; ++i)
		{
			auto& cmd = g_ColorCommands[i];
			auto col = cmd->GetState();

			if (ImGui::ColorEdit4(PrettyPrintLabel(ImGui::GetStyleColorName(i)).c_str(), (float*)&col))
			{
				cmd->SetState(col);
				changed = true;
			}
		}
		if (changed)
		{
			SyncColorCommandsToStyle();
			SaveSettings();
		}
	}

	static void DrawRoundingTab()
	{
		bool changed = false;
		ImGui::Text("Adjust Rounding:");
		ImGui::Separator();
		for (auto& [k, v] : g_RoundingValues)
			if (ImGui::SliderFloat(PrettyPrintLabel(k).c_str(), &v, 0.0f, 20.0f, "%.1f"))
				changed = true;

		if (changed)
		{
			SyncRoundingToStyle();
			SaveSettings();
		}
	}

	static void DrawLayoutTab()
	{
		auto& s = ImGui::GetStyle();
		ImGui::Text("Layout & Alignment:");
		ImGui::Separator();
		DrawStyleVec2("WindowPadding", s.WindowPadding.x, s.WindowPadding.y, 0.f, 32.f);
		DrawStyleVec2("ItemSpacing", s.ItemSpacing.x, s.ItemSpacing.y, 0.f, 32.f);
		DrawStyleVec2("ItemInnerSpacing", s.ItemInnerSpacing.x, s.ItemInnerSpacing.y, 0.f, 32.f);
		DrawStyleVec2("TouchExtraPadding", s.TouchExtraPadding.x, s.TouchExtraPadding.y, 0.f, 32.f);
		DrawStyleVec2("DisplaySafeAreaPadding", s.DisplaySafeAreaPadding.x, s.DisplaySafeAreaPadding.y, 0.f, 32.f);

		DrawStyleFloat("IndentSpacing", s.IndentSpacing, 0.f, 64.f);
		DrawStyleFloat("ColumnsMinSpacing", s.ColumnsMinSpacing, 0.f, 64.f);

		DrawStyleVec2("WindowTitleAlign", s.WindowTitleAlign.x, s.WindowTitleAlign.y, 0.f, 1.f);
		DrawStyleVec2("ButtonTextAlign", s.ButtonTextAlign.x, s.ButtonTextAlign.y, 0.f, 1.f);
		DrawStyleVec2("SelectableTextAlign", s.SelectableTextAlign.x, s.SelectableTextAlign.y, 0.f, 1.f);
	}

	static void DrawBorderTab()
	{
		auto& s = ImGui::GetStyle();
		ImGui::Text("Border Sizes:");
		ImGui::Separator();
		DrawStyleFloat("WindowBorderSize", s.WindowBorderSize, 0.f, 8.f);
		DrawStyleFloat("FrameBorderSize", s.FrameBorderSize, 0.f, 8.f);
		DrawStyleFloat("TabBorderSize", s.TabBorderSize, 0.f, 8.f);
		DrawStyleFloat("PopupBorderSize", s.PopupBorderSize, 0.f, 8.f);
	}

	static void DrawGlobalTab()
	{
		auto& s = ImGui::GetStyle();
		ImGui::Text("Global Settings:");
		ImGui::Separator();
		DrawStyleFloat("GlobalAlpha", s.Alpha, 0.1f, 1.f);
		DrawStyleFloat("DisabledAlpha", s.DisabledAlpha, 0.f, 1.f);
		DrawStyleFloat("MouseCursorScale", s.MouseCursorScale, 0.5f, 2.f);
		DrawStyleFloat("CurveTessellationTol", s.CurveTessellationTol, 0.1f, 10.f);
	}

	static void DrawFontTab()
	{
		ImGuiIO& io = ImGui::GetIO();
		static float scale = io.FontGlobalScale;
		ImGui::Text("Font Configuration:");
		ImGui::Separator();
		ImGui::Text("Current Scale: %.2f", io.FontGlobalScale);
		ImGui::SliderFloat("Font Scale", &scale, 0.5f, 2.0f, "%.2f");
		if (ImGui::Button("Apply Font Scale"))
			io.FontGlobalScale = scale;
	}

	std::shared_ptr<Category> DrawGUISettingsMenu()
	{
		InitializeColorCommands();
		auto imGuiCustomStyle = std::make_shared<Category>("Customize");
		imGuiCustomStyle->AddItem(std::make_unique<ImGuiItem>([] {
			ImGui::Text("ImGui Style Editor");
			ImGui::Separator();
			if (ImGui::BeginTabBar("StyleTabs"))
			{
				if (ImGui::BeginTabItem("Colors"))
				{
					DrawColorsTab();
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Rounding"))
				{
					DrawRoundingTab();
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Layout"))
				{
					DrawLayoutTab();
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Border"))
				{
					DrawBorderTab();
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Global"))
				{
					DrawGlobalTab();
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Fonts"))
				{
					DrawFontTab();
					ImGui::EndTabItem();
				}
				ImGui::EndTabBar();
			}
		}));
		return imGuiCustomStyle;
	}
}

#pragma once
#include "game/backend/SavedVariables.hpp"

namespace YimMenu
{
	static void DrawSavedVariableEdit(const SavedVariableBase& var, void* value)
	{
		if (!value)
		{
			ImGui::BeginDisabled();
			ImGui::Text("Invalid");
			ImGui::EndDisabled();
			return;
		}

		switch (var.type)
		{
		case VariableType::INT:
		{
			ImGui::SetNextItemWidth(200.f);
			ImGui::InputInt("Value", static_cast<int*>(value));
			break;
		}
		case VariableType::BOOL:
		{
			ImGui::Checkbox("Value", static_cast<bool*>(value));
			break;
		}
		case VariableType::FLOAT:
		{
			ImGui::SetNextItemWidth(200.f);
			ImGui::InputFloat("Value", static_cast<float*>(value));
			break;
		}
		case VariableType::INT64:
		{
			ImGui::SetNextItemWidth(200.f);
			ImGui::InputScalar("Value", ImGuiDataType_S64, static_cast<std::int64_t*>(value));
			break;
		}
		}
	}

	static void DrawSavedVariablePreview(const SavedVariableBase& var, void* value)
	{
		if (!value)
		{
			ImGui::Selectable("Invalid", false, ImGuiSelectableFlags_Disabled);
			return;
		}

		switch (var.type)
		{
		case VariableType::INT:
		{
			ImGui::Selectable(std::to_string(*static_cast<int*>(value)).c_str(), false, ImGuiSelectableFlags_Disabled);
			break;
		}
		case VariableType::BOOL:
		{
			ImGui::Selectable(*static_cast<bool*>(value) ? "True" : "False", false, ImGuiSelectableFlags_Disabled);
			break;
		}
		case VariableType::FLOAT:
		{
			ImGui::Selectable(std::to_string(*static_cast<float*>(value)).c_str(), false, ImGuiSelectableFlags_Disabled);
			break;
		}
		case VariableType::INT64:
		{
			ImGui::Selectable(std::to_string(*static_cast<std::int64_t*>(value)).c_str(), false, ImGuiSelectableFlags_Disabled);
			break;
		}
		}
	}

	static void DrawSavedVariable(SavedVariableBase& var)
	{
		ImGui::SetNextItemWidth(175.0f);
		ImGui::InputScalar("Index", ImGuiDataType_U32, &var.base);
		ImGui::SameLine();
		ImGui::SetNextItemWidth(100.0f);
		ImGui::Combo("##var_type", (int*)&var.type, "Int\0Float\0Bool\0Int64\0");

		for (int i = 0; i < var.appendages.size(); i++)
		{
			auto& item = var.appendages[i];
			switch (item.type)
			{
			case VariableAppendage::Type::OFFSET:
				ImGui::SetNextItemWidth(100.f);
				ImGui::InputScalar(std::format("At##{}{}", i, (int)item.type).c_str(), ImGuiDataType_S32, &item.offset);
				ImGui::SameLine();
				ImGui::SetNextItemWidth(100.f);
				ImGui::InputScalar(std::format("Size##{}{}", i, (int)item.type).c_str(), ImGuiDataType_S32, &item.size);
				break;
			case VariableAppendage::Type::PLAYER_ID:
				ImGui::SetNextItemWidth(100.f);
				ImGui::InputScalar(std::format("Size##{}{}", i, (int)item.type).c_str(), ImGuiDataType_S32, &item.size);
				break;
			}
		}

		if (ImGui::Button("Add Offset"))
			var.appendages.push_back({VariableAppendage::Type::OFFSET, 0LL, 0ULL});
		ImGui::SameLine();
		if (ImGui::Button("Add Read Player Id"))
			var.appendages.push_back({VariableAppendage::Type::PLAYER_ID, 0LL, 0ULL});

		if (var.appendages.size() > 0)
		{
			ImGui::SameLine();
			if (ImGui::Button("Remove Offset"))
			{
				var.appendages.pop_back();
			}
		}

		ImGui::SameLine();
		if (ImGui::Button("Clear"))
		{
			var.base = 0;
			var.appendages.clear();
		}
	}
}
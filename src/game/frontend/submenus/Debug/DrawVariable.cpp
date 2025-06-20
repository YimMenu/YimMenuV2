#include "DrawVariable.hpp"
#include "core/frontend/widgets/imgui_bitfield.hpp"
#include "types/script/scrVector.hpp"

namespace YimMenu
{
	void DrawSavedVariableEdit(const SavedVariableBase& var, void* value)
	{
		if (!value)
			return ImGui::TextDisabled("Invalid");

		switch (var.type)
		{
		case VariableType::INT:
		{
			ImGui::SetNextItemWidth(200.f);
			ImGui::InputScalar("Value", ImGuiDataType_S32, static_cast<int*>(value));
			break;
		}
		case VariableType::INT64:
		{
			ImGui::SetNextItemWidth(200.f);
			ImGui::InputScalar("Value", ImGuiDataType_S64, static_cast<std::int64_t*>(value));
			break;
		}
		case VariableType::BITSET:
		{
			ImGui::SetNextItemWidth(200.f);
			ImGui::Bitfield("Value", static_cast<int*>(value));
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
			ImGui::InputScalar("Value", ImGuiDataType_Float, static_cast<float*>(value));
			break;
		}
		case VariableType::VECTOR:
		{
			auto vectorPtr = (rage::scrVector*)value;
			ImGui::PushItemWidth(100.f);
			ImGui::InputScalar("X", ImGuiDataType_Float, &vectorPtr->x);
			ImGui::SameLine();
			ImGui::InputScalar("Y", ImGuiDataType_Float, &vectorPtr->y);
			ImGui::SameLine();
			ImGui::InputScalar("Z", ImGuiDataType_Float, &vectorPtr->z);
			ImGui::PopItemWidth();
			break;
		}
		case VariableType::STRING:
		{
			ImGui::SetNextItemWidth(200.f);
			ImGui::InputText("Value", static_cast<char*>(value), 255);
			break;
		}
		}
	}

	void DrawSavedVariablePreview(const SavedVariableBase& var, void* value)
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
		case VariableType::INT64:
		{
			ImGui::Selectable(std::to_string(*static_cast<std::int64_t*>(value)).c_str(), false, ImGuiSelectableFlags_Disabled);
			break;
		}
		case VariableType::BITSET:
		{
			std::ostringstream bitset;
			bitset << HEX(*static_cast<int*>(value));
			ImGui::Selectable(bitset.str().c_str(), false, ImGuiSelectableFlags_Disabled);
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
		case VariableType::VECTOR:
		{
			auto vectorPtr = (rage::scrVector*)value;
			std::ostringstream vector;
			vector << "X: " << std::fixed << std::setprecision(2) << vectorPtr->x << " Y: " << vectorPtr->y << " Z: " << vectorPtr->z;
			ImGui::Selectable(vector.str().c_str(), false, ImGuiSelectableFlags_Disabled);
			break;
		}
		case VariableType::STRING:
		{
			ImGui::Selectable(static_cast<char*>(value), false, ImGuiSelectableFlags_Disabled);
			break;
		}
		}
	}

	void DrawSavedVariable(SavedVariableBase& var)
	{
		uint32_t step = 1;
		uint32_t step_fast = 100;

		ImGui::SetNextItemWidth(200.0f);
		ImGui::InputScalar("Index", ImGuiDataType_U32, &var.base, &step, &step_fast);
		ImGui::SameLine();
		ImGui::SetNextItemWidth(100.0f);
		ImGui::Combo("##var_type", (int*)&var.type, "Int\0Int64\0Bitset\0Bool\0Float\0Vector\0String\0");

		for (int i = 0; i < var.appendages.size(); i++)
		{
			auto& item = var.appendages[i];
			switch (item.type)
			{
			case VariableAppendage::Type::OFFSET:
				ImGui::SetNextItemWidth(125.f);
				ImGui::InputScalar(std::format("At##{}{}", i, (int)item.type).c_str(), ImGuiDataType_S32, &item.offset, &step, &step_fast);
				ImGui::SameLine();
				ImGui::SetNextItemWidth(125.f);
				ImGui::InputScalar(std::format("Size##{}{}", i, (int)item.type).c_str(), ImGuiDataType_S32, &item.size, &step, &step_fast);
				break;
			case VariableAppendage::Type::PLAYER_ID:
				ImGui::SetNextItemWidth(125.f);
				ImGui::InputScalar(std::format("Size##{}{}", i, (int)item.type).c_str(), ImGuiDataType_S32, &item.size, &step, &step_fast);
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

#pragma once

namespace ImGui
{
	template<typename T>
	bool Bitfield(const char* name, T* param)
	{
		bool ret = false;
		ImGuiDataType type;
		size_t size = sizeof(T);
		std::string format;
		if (size == 1)
		{
			type = ImGuiDataType_U8;
			format = "%02X";
		}
		if (size == 2)
		{
			type = ImGuiDataType_U16;
			format = "%04X";
		}
		if (size == 4)
		{
			type = ImGuiDataType_U32;
			format = "%08X";
		}
		if (size == 8)
		{
			type = ImGuiDataType_U64;
			format = "%p";
		}

		if (ImGui::InputScalar(name, type, param, NULL, NULL, format.c_str(), ImGuiInputTextFlags_CharsHexadecimal))
			ret = true;
		size_t bits = (size * 8) - 1ULL;
		for (size_t i = bits; i < SIZE_MAX; i--)
		{
			if (i % 4 == 0)
				ImGui::BeginGroup();
			if (*param & (1ULL << i))
			{
				ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32_BLACK_TRANS);
				ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(41, 134, 204, 255));
				if (ImGui::Button(std::format("1##{}{}", name, i).c_str(), ImVec2(25, 0)))
				{
					ret = true;
					*param ^= (1ULL << i);
				}
				ImGui::PopStyleColor(2);
			}
			else
			{
				ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32_BLACK_TRANS);
				if (ImGui::Button(std::format("0##{}{}", name, i).c_str(), ImVec2(25, 0)))
				{
					ret = true;
					*param ^= (1ULL << i);
				}
				ImGui::PopStyleColor();
			}
			if (i % 4 == 0)
			{
				ImGui::Text("%lld", i);
				ImGui::EndGroup();
			}
			if (i % 16 != 0)
				ImGui::SameLine();
		}

		return ret;
	}
}
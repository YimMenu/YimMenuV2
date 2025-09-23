#include "core/backend/FiberPool.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "game/gta/Stats.hpp"
#include "game/pointers/Pointers.hpp"
#include "misc/cpp/imgui_stdlib.h"
#include "StatEditor.hpp"
#include "types/script/types.hpp"
#include "types/stats/CStatsMgr.hpp"
#include <print>
#include <utility>
#include <vector>


using stats_vec = std::vector<std::pair<std::string, std::string>>;
using packed_vec = std::vector<std::pair<uint32_t, uint8_t>>;

namespace YimMenu::Submenus
{
	struct StatInfo
	{
		std::string m_Name{};
		std::uint32_t m_NameHash = 0;
		bool m_Normalized = false;
		sStatData* m_Data = nullptr;

		bool IsValid() const
		{
			return m_Data != nullptr;
		}
	};

	struct PackedStatInfo
	{
		int m_Index;
		bool m_IsBoolStat;
		bool m_IsValid;

		bool IsValid() const
		{
			return m_IsValid;
		}
	};

	union StatValue {
		bool m_AsBool{};
		std::uint64_t m_AsU64;
		char m_AsString[40];
		float m_AsFloat[3];
		int m_AsInt;
		Date m_date;
	};

	// https://stackoverflow.com/questions/66897068/can-trim-of-a-string-be-done-inplace-with-c20-ranges
	static std::string_view TrimString(std::string_view string)
	{
		return std::string_view{
		    std::ranges::find_if_not(
		        string,
		        [](auto c) {
			        return std::isspace(c);
		        }),
		    std::ranges::find_if_not(
		        string | std::views::reverse,
		        [](auto c) {
			        return std::isspace(c);
		        })
		        .base()};
	}

	static StatInfo GetStatInfo(std::string_view name_str)
	{
		StatInfo name{};
		name.m_Name = name_str;
		if (std::string_view(name.m_Name).starts_with('$'))
		{
			name.m_Name.erase(0, 1);
			name.m_Normalized = true;
		}
		if (std::string_view(name.m_Name).starts_with("MPX"))
		{
			auto last_char = Pointers.StatsMgr->GetStat("MPPLY_LAST_MP_CHAR"_J);
			auto char_index = last_char ? last_char->GetInt() : 0;
			name.m_Name.replace(0, 3, "MP" + std::to_string(char_index));
			name.m_Normalized = true;
		}
		else if (std::string_view(name.m_Name).starts_with("SPX"))
		{
			// func_174() Global_1574927 online is 145
			auto char_index = *ScriptGlobal(114370).At(2367).At(539).At(4321).As<int*>();
			if (char_index == 0 || char_index == 1 || char_index == 2)
			{
				name.m_Name.replace(0, 3, "SP" + std::to_string(char_index));
				name.m_Normalized = true;
			}
		}

		name.m_NameHash = Joaat(name.m_Name);
		name.m_Data = Pointers.StatsMgr->GetStat(name.m_NameHash);
		return name;
	}

	static std::string ReadStat(std::uint32_t hash, StatValue& value, sStatData* data)
	{
		memset(&value, 0, sizeof(StatValue));

		switch (data->GetType())
		{
		case sStatData::Type::_BOOL:
			value.m_AsBool = data->GetBool();
			return std::format("{}", value.m_AsBool);
		case sStatData::Type::FLOAT:
			value.m_AsFloat[0] = data->GetFloat();
			return std::format("{}", value.m_AsFloat[0]);
		case sStatData::Type::INT:
			value.m_AsInt = data->GetInt();
			return std::format("{}", value.m_AsInt);
		case sStatData::Type::UINT8:
			value.m_AsInt = data->GetUInt8();
			return std::format("{}", value.m_AsInt);
		case sStatData::Type::UINT16:
			value.m_AsInt = data->GetUInt16();
			return std::format("{}", value.m_AsInt);
		case sStatData::Type::UINT32:
			value.m_AsInt = data->GetUInt32();
			return std::format("{}", value.m_AsInt);
		case sStatData::Type::INT64:
			value.m_AsU64 = data->GetInt64();
			return std::format("{}", value.m_AsU64);
		case sStatData::Type::UINT64:
			value.m_AsU64 = data->GetUInt64();
			return std::format("{}", value.m_AsU64);
		case sStatData::Type::STRING:
			strncpy(value.m_AsString, data->GetString(), sizeof(value.m_AsString));
			return std::format("{}", value.m_AsString);
		case sStatData::Type::USERID:
			data->GetUserID(value.m_AsString, sizeof(value.m_AsString));
			return std::format("{}", value.m_AsString);
		case sStatData::Type::DATE:
			STATS::STAT_GET_DATE(hash, &value.m_date, sizeof(Date) / 8, true);
			return std::format("{},{},{},{},{},{},{}", value.m_date.Year, value.m_date.Month, value.m_date.Day, value.m_date.Hour, value.m_date.Minute, value.m_date.Second, value.m_date.Millisecond);
		case sStatData::Type::POS:
			STATS::STAT_GET_POS(hash, &value.m_AsFloat[0], &value.m_AsFloat[1], &value.m_AsFloat[2], true);
			return std::format("{},{},{}", value.m_AsFloat[0], value.m_AsFloat[1], value.m_AsFloat[2]);
		case sStatData::Type::LABEL:
		case sStatData::Type::PACKED:
		case sStatData::Type::PROFILESETTING:
		default:
			return ""; // data type not supported
		}
	}


	static void WriteStat(std::uint32_t hash, StatValue& value, sStatData* data)
	{
		switch (data->GetType())
		{
		case sStatData::Type::_BOOL:
			STATS::STAT_SET_BOOL(hash, value.m_AsBool, true);
			//data->SetBool(value.m_AsBool);
			return;
		case sStatData::Type::FLOAT:
			STATS::STAT_SET_FLOAT(hash, value.m_AsFloat[0], true);
			//data->SetFloat(value.m_AsFloat[0]);
			return;
		case sStatData::Type::INT:
			data->SetInt(value.m_AsInt);
			return;
		case sStatData::Type::UINT8:
			data->SetUInt8(value.m_AsInt);
			return;
		case sStatData::Type::UINT16:
			data->SetUInt16(value.m_AsInt);
			return;
		case sStatData::Type::UINT32:
			STATS::STAT_SET_INT(hash, value.m_AsInt, true);
			//data->SetUInt64(value.m_AsInt);
			return;
		case sStatData::Type::INT64:
			data->SetInt64(value.m_AsU64); // TODO this isn't a good idea! natives can't set this
			return;
		case sStatData::Type::UINT64:
			//STATS::STAT_SET_MASKED_INT(hash, (std::uint32_t)value.m_AsU64, 0, 32, true);
			//STATS::STAT_SET_MASKED_INT(hash, (std::uint32_t)(value.m_AsU64 >> 32), 32, 32, true);
			data->SetUInt64(value.m_AsU64);
			return;
		case sStatData::Type::STRING:
			STATS::STAT_SET_STRING(hash, value.m_AsString, true);
			//data->SetString(value.m_AsString);
			return;
		case sStatData::Type::USERID:
			STATS::STAT_SET_USER_ID(hash, value.m_AsString, true);
			//data->SetUserID(value.m_AsString);
			return;
		case sStatData::Type::DATE:
			STATS::STAT_SET_DATE(hash, &value.m_date, sizeof(Date) / 8, true);
			return;
		case sStatData::Type::POS:
			STATS::STAT_SET_POS(hash, value.m_AsFloat[0], value.m_AsFloat[1], value.m_AsFloat[2], true);
			return;
		case sStatData::Type::LABEL:
		case sStatData::Type::PACKED:
		case sStatData::Type::PROFILESETTING:
		default:
			return; // data type not supported
		}
	}


	bool ChackDate(Date date)
	{
		int &year = date.Year, &Month = date.Month, &day = date.Day, &Hour = date.Hour, &Minute = date.Minute, &Second = date.Second, &Mil = date.Millisecond;
		auto checkfeb = 30 + ((Month % 2) + (Month >= 8)) % 2;
		checkfeb = checkfeb - (2 * (Month == 2));
		checkfeb = checkfeb + ((Month == 2) && ((year % 100) && (year % 4 == 0) || (year % 400 == 0)));
		if (0 <= day && day <= checkfeb && 0 <= Month && Month <= 12 && 0 <= Hour && Hour < 24 && 0 <= Minute && Minute < 60 && 0 <= Second && Second < 60 && 0 <= Mil && Mil < 1000)
			return true;
		else
			return false;
	}

	// TODO: don't call std::string_view::data()
	static void WriteStatWithStringValue(std::uint32_t hash, std::string_view value, sStatData* data)
	{
		switch (data->GetType())
		{
		case sStatData::Type::_BOOL:
		{
			bool _bool = false;
			std::string as_string(value);
			std::transform(as_string.begin(), as_string.end(), as_string.begin(), [](char c) {
				return tolower(c);
			});

			if (as_string != "false" || as_string != "0")
			{
				_bool = true;
			}

			STATS::STAT_SET_BOOL(hash, _bool, true);
			//data->SetBool(_bool);
			return;
		}
		case sStatData::Type::FLOAT:
		{
			auto _float = std::strtof(value.data(), nullptr);
			STATS::STAT_SET_FLOAT(hash, _float, true);
			//data->SetFloat(_float);
			return;
		}
		case sStatData::Type::INT:
		case sStatData::Type::UINT8:
		case sStatData::Type::UINT16:
		case sStatData::Type::UINT32:
		{
			auto _int = std::strtol(value.data(), nullptr, 10);
			STATS::STAT_SET_INT(hash, _int, true);
			//data->SetInt(_int);
			return;
		}
		case sStatData::Type::INT64:
		{
			auto int64_ = std::strtoll(value.data(), nullptr, 10);
			data->SetInt64(int64_); // TODO this isn't a good idea! natives can't set this
			return;
		}
		case sStatData::Type::UINT64:
		{
			auto uint64_ = std::strtoull(value.data(), nullptr, 10);
			data->SetUInt64(uint64_);
			/*STATS::STAT_SET_MASKED_INT(hash, (std::uint32_t)uint64_, 0, 32, true);
			STATS::STAT_SET_MASKED_INT(hash, (std::uint32_t)(uint64_ >> 32), 32, 32, true);*/
			return;
		}
		case sStatData::Type::STRING:
			STATS::STAT_SET_STRING(hash, value.data(), true);
			//data->SetString(value.data());
			return;
		case sStatData::Type::USERID:
			//data->SetUserID(value.data());
			STATS::STAT_SET_USER_ID(hash, value.data(), true);
			return;
		case sStatData::Type::DATE:
		{
			std::string input = value.data();
			std::vector<int> date;
			std::stringstream ss(input);
			std::string token;
			date.clear();
			while (std::getline(ss, token, ','))
			{
				date.emplace_back(std::stoi(token));
			}

			if (date.size() == 7)
			{
				Date temp{
				    date[0], // Year
				    date[1], // Month
				    date[2], // Day
				    date[3], // Hour
				    date[4], // Minute
				    date[5], // Second
				    date[6]  // Millisecond
				};
				if (ChackDate(temp))
				{
					STATS::STAT_SET_DATE(hash, &temp, sizeof(Date) / 8, true);
				}
			}
		}
			return;
		case sStatData::Type::POS:
		{
			std::string input = value.data();
			std::vector<float> pos;
			std::stringstream ss(input);
			std::string token;
			pos.clear();
			while (std::getline(ss, token, ','))
			{
				pos.emplace_back(std::stof(token));
			}
			if (pos.size() == 3)
			{
				STATS::STAT_SET_POS(hash, pos[0], pos[1], pos[2], true);
			}
		}
			return;
		case sStatData::Type::LABEL:
		case sStatData::Type::PACKED:
		case sStatData::Type::PROFILESETTING:
		default:
			return; // data type not supported
		}
	}


	static bool RenderStatEditor(StatValue& value, sStatData* data)
	{
		ImGui::SetNextItemWidth(150.f);
		switch (data->GetType())
		{
		case sStatData::Type::_BOOL:
			return ImGui::Checkbox("Value", &value.m_AsBool);
		case sStatData::Type::FLOAT:
			return ImGui::InputFloat("Value", &value.m_AsFloat[0]);
		case sStatData::Type::INT:
			return ImGui::InputInt("Value", &value.m_AsInt);
		case sStatData::Type::UINT32:
			return ImGui::InputScalar("Value", ImGuiDataType_U32, &value.m_AsInt);
		case sStatData::Type::UINT16:
			return ImGui::InputScalar("Value", ImGuiDataType_U16, &value.m_AsInt);
		case sStatData::Type::UINT8:
			return ImGui::InputScalar("Value", ImGuiDataType_U8, &value.m_AsInt);
		case sStatData::Type::INT64:
			return ImGui::InputScalar("Value", ImGuiDataType_S64, &value.m_AsInt);
		case sStatData::Type::UINT64:
			return ImGui::InputScalar("Value", ImGuiDataType_U64, &value.m_AsInt);
		case sStatData::Type::STRING:
		case sStatData::Type::USERID:
			return ImGui::InputText("Value", value.m_AsString, sizeof(value.m_AsString));
		case sStatData::Type::DATE:
		{
			ImGui::PushItemWidth(60.0f);
			ImGui::InputScalar("Year", ImGuiDataType_U32, &value.m_date.Year);
			ImGui::SameLine();
			ImGui::PopItemWidth();
			ImGui::PushItemWidth(50.0f);
			ImGui::InputScalar("Month", ImGuiDataType_U32, &value.m_date.Month);
			ImGui::SameLine();
			ImGui::InputScalar("Day", ImGuiDataType_U32, &value.m_date.Day);
			ImGui::SameLine();
			ImGui::InputScalar("Hour", ImGuiDataType_U32, &value.m_date.Hour);
			ImGui::SameLine();
			ImGui::InputScalar("Minute", ImGuiDataType_U32, &value.m_date.Minute);
			ImGui::SameLine();
			ImGui::InputScalar("Second", ImGuiDataType_U32, &value.m_date.Second);
			ImGui::SameLine();
			ImGui::InputScalar("Millisecond", ImGuiDataType_U32, &value.m_date.Millisecond);
			ImGui::PopItemWidth();
			if (ChackDate(value.m_date))
				return true;
			else
			{
				ImGui::TextColored(ImVec4(0.957f, 0.643f, 0.376f, 1.00f), "The entered date or time is invalid, please recheck the input data.");
				return false;
			}
		}
		case sStatData::Type::POS:
			ImGui::PushItemWidth(50.0f);
			ImGui::InputFloat("X", &value.m_AsFloat[0]);
			ImGui::SameLine();
			ImGui::InputFloat("Y", &value.m_AsFloat[1]);
			ImGui::SameLine();
			ImGui::InputFloat("Z", &value.m_AsFloat[2]);
			ImGui::PopItemWidth();
			return true;
		case sStatData::Type::PACKED:
			ImGui::BeginDisabled();
			ImGui::TextColored(ImVec4(0.26f, 0.59f, 0.98f, 1.00f), "Please use the packed below to modify the data.");
			ImGui::EndDisabled();
			return false;
		case sStatData::Type::LABEL:
		case sStatData::Type::PROFILESETTING:
		default:
			ImGui::BeginDisabled();
			ImGui::Text("Data type not supported");
			ImGui::EndDisabled();
			return false; // data type not supported
		}
	}

	static PackedStatInfo GetPackedStatInfo(int index)
	{
		PackedStatInfo info{};
		int row;
		bool unk;

		info.m_Index = index;
		Pointers.GetPackedStatData(index, &row, &info.m_IsBoolStat, &unk);

		if (row != 0 || index <= 191)
			info.m_IsValid = true;

		return info;
	}

	static void ReadPackedStat(StatValue& value, const PackedStatInfo& info)
	{
		if (info.m_IsBoolStat)
			value.m_AsBool = STATS::GET_PACKED_STAT_BOOL_CODE(info.m_Index, -1);
		else
			value.m_AsInt = STATS::GET_PACKED_STAT_INT_CODE(info.m_Index, -1);
	}

	static void WritePackedStat(const StatValue& value, const PackedStatInfo& info)
	{
		if (info.m_IsBoolStat)
			STATS::SET_PACKED_STAT_BOOL_CODE(info.m_Index, value.m_AsBool, -1);
		else
			STATS::SET_PACKED_STAT_INT_CODE(info.m_Index, value.m_AsInt, -1);
	}

	static void WritePackedStatRange(int start, int end, int value)
	{
		for (int i = start; i <= end; i++)
		{
			auto info = GetPackedStatInfo(i);
			if (!info.m_IsValid)
				break; // the rest are probably not valid, either

			if (info.m_IsBoolStat)
				STATS::SET_PACKED_STAT_BOOL_CODE(info.m_Index, static_cast<bool>(value), -1);
		}
	}

	void Cmp_Packed_To_Flie(int start, int end, packed_vec& packed_vecs, bool compare)
	{
		if (!compare)
		{
			packed_vecs.clear();
			packed_vecs.reserve(54850);
			for (int i = start; i <= end; i++)
			{
				auto info = GetPackedStatInfo(i);
				if (!info.m_IsValid)
					continue;

				if (info.m_IsBoolStat)
					packed_vecs.emplace_back(info.m_Index, static_cast<int>(Stats::GetPackedBool(info.m_Index)));
				else
					packed_vecs.emplace_back(info.m_Index, Stats::GetPackedInt(info.m_Index));
			}
			packed_vecs.shrink_to_fit();
		}
		else
		{
			if (packed_vecs.size() == 0)
				return;

			FILE* stream = nullptr;
			auto file_path = (std::filesystem::path(std::getenv("appdata")) / "YimMenuV2" / "cmp_packed_date.txt").string();
			if (fopen_s(&stream, file_path.data(), "w+"))
			{
				return;
			}
			for (const auto& [index, value] : packed_vecs)
			{
				auto info = GetPackedStatInfo(index);
				if (!info.m_IsValid)
					continue;

				if (info.m_IsBoolStat)
				{
					if (static_cast<bool>(value) != Stats::GetPackedBool(index))
						std::println(stream, "date type：Packed_bool ||index: {:^10} ||Value before the change: {:^10} ||Current value {:^10}", index, static_cast<bool>(value), Stats::GetPackedBool(index));
				}
				else
				{
					if (value != Stats::GetPackedInt(index))
						std::println(stream, "date type：Packed_int  ||index: {:^10} ||Value before the change: {:^10} ||Current value {:^10}", index, value, Stats::GetPackedInt(index));
				}
			}
			if (stream)
				std::fclose(stream);
		}
	}

	void Cmp_Stat_To_Flie(stats_vec& stats_vecs, bool compare)
	{
		StatInfo current_info;
		StatValue read_value;
		if (!compare)
		{
			//Can the name be read directly from the client?
			std::string filePath = (std::filesystem::path(std::getenv("appdata")) / "YimMenuV2" / "stats.txt").string();
			std::ifstream file(filePath);
			if (!file.is_open())
			{
				LOG(INFO) << "stats.txt file not found";
				return;
			}
			stats_vecs.clear();
			stats_vecs.reserve(21460); //all stats 21405
			std::string line{};
			std::string oldvalue{};
			while (std::getline(file, line))
			{
				if (line.empty() || line.starts_with("//"))
					continue;

				size_t pos = line.find(',');
				if (pos != std::string::npos)
				{
					line = line.substr(0, pos);
				}
				current_info = GetStatInfo(line);
				if (current_info.IsValid())
				{
					oldvalue = ReadStat(current_info.m_NameHash, read_value, current_info.m_Data);
					/*if (oldvalue != "")*/
					stats_vecs.emplace_back(line, oldvalue);
				}
			}
			stats_vecs.shrink_to_fit();
			file.close();
		}
		else
		{
			if (stats_vecs.size() == 0)
				return;
			FILE* stream = nullptr;
			auto file_path = (std::filesystem::path(std::getenv("appdata")) / "YimMenuV2" / "cmp_stats_date.txt").string();
			if (fopen_s(&stream, file_path.data(), "w+"))
			{
				return;
			}
			std::string newvalue{};
			for (const auto& [name, oldvalue] : stats_vecs)
			{
				current_info = GetStatInfo(name);
				newvalue = ReadStat(current_info.m_NameHash, read_value, current_info.m_Data);
				//if (oldvalue != "")
				if (oldvalue != newvalue)
					std::println(stream, "data type：[ {:^10} ]||Name:[ {:^10} ] || Value before the change:[ {:^10} ] || Current value[ {:^10} ]", current_info.m_Data->GetTypeString(), name, oldvalue, newvalue);
			}
			if (stream)
				std::fclose(stream);
		}
	}

	static bool RenderPackedStatEditor(StatValue& value, const PackedStatInfo& info)
	{
		ImGui::SetNextItemWidth(150.f);
		if (info.m_IsBoolStat)
			return ImGui::Checkbox("Value##packed", &value.m_AsBool);
		else
			return ImGui::InputScalar("Value##packed", ImGuiDataType_U8, &value.m_AsInt);
	}

	std::shared_ptr<Category> BuildStatEditorMenu()
	{
		auto menu = std::make_shared<Category>("Stat Editor");
		auto normal = std::make_shared<Group>("Regular");
		auto packed = std::make_shared<Group>("Packed");
		auto packed_range = std::make_shared<Group>("Packed Range");
		auto from_clipboard = std::make_shared<Group>("From Clipboard");
		auto packed_compare = std::make_shared<Group>("packed compare");
		auto stats_compare = std::make_shared<Group>("stats_compare");

		normal->AddItem(std::make_unique<ImGuiItem>([] {
			if (!NativeInvoker::AreHandlersCached())
				return ImGui::TextDisabled("Natives not cached yet");

			static StatInfo current_info;
			static std::string stat_buf{};
			static StatValue value{};

			ImGui::SetNextItemWidth(300.f);
			if (ImGui::InputText("Name", &stat_buf, ImGuiInputTextFlags_CharsUppercase))
			{
				current_info = GetStatInfo(stat_buf);
				if (current_info.IsValid())
					ReadStat(current_info.m_NameHash, value, current_info.m_Data);
			}

			if (!current_info.IsValid())
				return ImGui::TextDisabled("Stat not found");
			else if (current_info.m_Normalized)
			{
				ImGui::Text("Normalized name to: %s", current_info.m_Name.data());
			}

			bool can_edit = RenderStatEditor(value, current_info.m_Data);
			if (can_edit)
				can_edit = !current_info.m_Data->IsControlledByNetshop();

			if (ImGui::Button("Refresh##stat"))
				ReadStat(current_info.m_NameHash, value, current_info.m_Data);
			ImGui::SameLine();
			ImGui::BeginDisabled(!can_edit);
			if (ImGui::Button("Write##stat"))
				FiberPool::Push([] {
					WriteStat(current_info.m_NameHash, value, current_info.m_Data);
				});
			if (ImGui::IsMouseClicked(ImGuiMouseButton_Right) && ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
				FiberPool::Push([] {
					WriteStat(current_info.m_NameHash, value, current_info.m_Data);
				});
			if (!can_edit && ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
				ImGui::SetTooltip("This stat should not be edited by the client. Right-click to force the write anyway");
			ImGui::EndDisabled();
		}));

		packed->AddItem(std::make_unique<ImGuiItem>([] {
			if (!NativeInvoker::AreHandlersCached())
				return ImGui::TextDisabled("Natives not cached yet");

			// TODO: improve packed stat editor
			static PackedStatInfo current_info{0, false, true};
			static StatValue value{};

			ImGui::SetNextItemWidth(200.f);
			if (ImGui::InputInt("Index", &current_info.m_Index))
			{
				current_info = GetPackedStatInfo(current_info.m_Index);
				if (current_info.IsValid())
					ReadPackedStat(value, current_info);
			}

			if (!current_info.IsValid())
				return ImGui::TextDisabled("Index not valid");

			RenderPackedStatEditor(value, current_info);

			if (ImGui::Button("Refresh##packed"))
				ReadPackedStat(value, current_info);
			ImGui::SameLine();
			if (ImGui::Button("Write##packed"))
				FiberPool::Push([] {
					WritePackedStat(value, current_info);
				});
		}));

		packed_range->AddItem(std::make_unique<ImGuiItem>([] {
			if (!NativeInvoker::AreHandlersCached())
				return ImGui::TextDisabled("Natives not cached yet");

			static int start{}, end{}, value{};

			ImGui::SetNextItemWidth(150.f);
			ImGui::InputInt("Start", &start);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(150.f);
			ImGui::InputInt("End", &end);
			ImGui::SetNextItemWidth(150.f);
			ImGui::InputScalar("Value##packed_range", ImGuiDataType_U8, &value);
			ImGui::SameLine();
			if (ImGui::Button("Write##packed_range"))
				FiberPool::Push([] {
					WritePackedStatRange(start, end, value);
				});
		}));

		from_clipboard->AddItem(std::make_unique<ImGuiItem>([] {
			if (!NativeInvoker::AreHandlersCached())
				return ImGui::TextDisabled("Natives not cached yet");

			if (ImGui::Button("Load from Clipboard"))
			{
				auto clip_text = std::string(ImGui::GetClipboardText());
				FiberPool::Push([clip_text] {
					for (auto line : clip_text | std::ranges::views::split('\n'))
					{
						auto components = TrimString(std::string_view{line.begin(), line.end()}) | std::ranges::views::split('=') | std::ranges::to<std::vector<std::string>>();

						if (components.size() != 2)
						{
							LOGF(WARNING, "Load From Clipboard: line \"{}\" is malformed", std::string_view{line.begin(), line.end()});
							continue;
						}

						auto info = GetStatInfo(TrimString(components[0]));
						if (!info.IsValid())
						{
							LOGF(WARNING, "Load From Clipboard: cannot find stat {}", components[0]);
							continue;
						}

						WriteStatWithStringValue(info.m_NameHash, TrimString(components[1]), info.m_Data);
					}
				});
			}
		}));


		packed_compare->AddItem(std::make_unique<ImGuiItem>([] {
			if (!NativeInvoker::AreHandlersCached())
				return ImGui::TextDisabled("Natives not cached yet");

			static packed_vec packed_vec;
			static bool create_pac_b = false;
			if (ImGui::Button("Create packed to save"))
			{
				FiberPool::Push([] {
					Cmp_Packed_To_Flie(1, 54820, packed_vec, false);
					create_pac_b = true;
				});
			}

			ImGui::SameLine();

			if (!create_pac_b)
				return;
			if (ImGui::Button("Compared to the last time##packed"))
			{
				FiberPool::Push([] {
					Cmp_Packed_To_Flie(1, 54820, packed_vec, true);
				});
			}
		}));

		stats_compare->AddItem(std::make_unique<ImGuiItem>([] {
			if (!NativeInvoker::AreHandlersCached())
				return ImGui::TextDisabled("Natives not cached yet");

			static stats_vec stat_vec;
			static bool create_stat_b = false;

			if (ImGui::Button("Create stats to save"))
			{
				FiberPool::Push([] {
					Cmp_Stat_To_Flie(stat_vec, false);
					create_stat_b = true;
				});
			}
			ImGui::SameLine();

			if (!create_stat_b)
				return;
			if (ImGui::Button("Compared to the last time##stats"))
			{
				FiberPool::Push([] {
					Cmp_Stat_To_Flie(stat_vec, true);
				});
			}
		}));

		menu->AddItem(std::move(normal));
		menu->AddItem(std::move(packed));
		menu->AddItem(std::move(packed_range));
		menu->AddItem(std::move(from_clipboard));
		menu->AddItem(std::move(packed_compare));
		menu->AddItem(std::move(stats_compare));
		return menu;
	}
}
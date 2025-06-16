#include "SavedVariables.hpp"

#include "core/filemgr/FileMgr.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/ScriptGlobal.hpp"

#include "types/script/scrThread.hpp"

namespace YimMenu
{
	std::uint32_t SavedVariableBase::CalculateOffset()
	{
		auto offset = base;

		for (auto& appendage : appendages)
		{
			int add;
			if (appendage.type == VariableAppendage::Type::OFFSET)
				add = appendage.offset;
			else
				add = Self::GetPlayer().GetId();

			if (appendage.size)
				offset += 1 + (add * appendage.size);
			else
				offset += add;
		}

		return offset;
	}

	void* SavedLocal::Read(rage::scrThread* thread)
	{
		auto offset = CalculateOffset();

		if (!thread)
			return nullptr;

		if (!thread->m_Stack)
			return nullptr;

		if (thread->m_Context.m_StackSize <= offset)
			return nullptr;

		return reinterpret_cast<void**>(thread->m_Stack) + offset;
	}

	void* SavedGlobal::Read()
	{
		auto global = ScriptGlobal(CalculateOffset());

		if (!global.CanAccess())
			return nullptr;

		return global.As<void*>();
	}

	void SavedVariables::InitImpl()
	{
		if (m_Initialized)
			return;

		m_Initialized = true;

		nlohmann::json vars{};

		auto file = FileMgr::GetProjectFile("./saved_variables.json");
		if (file.Exists())
		{
			try
			{
				std::ifstream iffstream_file(file.Path());
				iffstream_file >> vars;
			}
			catch (std::exception& e)
			{
				LOGF(WARNING, "Failed to read variables.json: {}", e.what());
			}
		}
		else
		{
			return;
		}

		m_SavedGlobals = vars["globals"];
		m_SavedLocals = vars["locals"];
	}

	void SavedVariables::SaveImpl()
	{
		nlohmann::json vars{};

		vars["globals"] = m_SavedGlobals;
		vars["locals"] = m_SavedLocals;
		auto file = FileMgr::GetProjectFile("./saved_variables.json");
		std::ofstream offstream_file(file.Path(), std::ios::out | std::ios::trunc);
		offstream_file << vars.dump(4);
		offstream_file.close();
	}
}
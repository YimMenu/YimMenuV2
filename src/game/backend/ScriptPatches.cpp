#include "ScriptPatches.hpp"

#include "game/backend/ScriptPointers.hpp"
#include "game/pointers/Pointers.hpp"

#include "types/script/scrProgram.hpp"

namespace YimMenu
{
	std::optional<uint32_t> ScriptPatches::Patch::GetPC()
	{
		if (m_Pc.has_value())
			return m_Pc;

		auto data = GetInstance().GetDataImpl(m_Hash);

		if (!data)
			return std::nullopt;

		if (auto address = ScriptPointers::GetPointer(m_Hash, Joaat(m_Pointer.GetName())))
		{
			m_Pc = address;
		}
		else
		{
			m_Pc = m_Pointer.Scan(data).As<std::uint32_t>();
			ScriptPointers::CachePointer(m_Hash, Joaat(m_Pointer.GetName()), m_Pc.value());
		}

		return m_Pc;
	}

	void ScriptPatches::Patch::Apply()
	{
		auto pc = GetPC();
		auto data = GetInstance().GetDataImpl(m_Hash);

		if (!pc || !data)
			return;

		if (m_OriginalBytes.size() == 0)
		{
			m_OriginalBytes.resize(m_PatchedBytes.size());
			memcpy(m_OriginalBytes.data(), ScriptData::GetCodeLocation(data, pc.value()), m_PatchedBytes.size());
		}

		memcpy(ScriptData::GetCodeLocation(data, pc.value()), m_PatchedBytes.data(), m_PatchedBytes.size());
	}

	void ScriptPatches::Patch::Restore()
	{
		if (m_OriginalBytes.size() == 0)
			return; // nothing to restore

		auto pc = GetPC();
		auto data = GetInstance().GetDataImpl(m_Hash);

		if (!pc || !data)
			return;

		memcpy(ScriptData::GetCodeLocation(data, pc.value()), m_OriginalBytes.data(), m_OriginalBytes.size());
	}

	ScriptPatches::Patch::Patch(joaat_t script, ScriptPointer pointer, std::vector<uint8_t> patch) :
	    m_PatchedBytes(patch),
	    m_Pointer(pointer),
	    m_Enabled(false),
	    m_Pc(std::nullopt),
	    m_OriginalBytes({}),
	    m_Hash(script)
	{
	}

	void ScriptPatches::Patch::Enable()
	{
		if (!m_Enabled)
		{
			Apply();
			m_Enabled = true;
		}
	}

	void ScriptPatches::Patch::Disable()
	{
		if (m_Enabled)
		{
			Restore();
			m_Enabled = false;
		}
	}

	void ScriptPatches::Patch::Update()
	{
		if (m_Enabled)
		{
			Apply();
		}
		else
		{
			Restore();
		}
	}

	bool ScriptPatches::Patch::InScope(std::uint32_t hash)
	{
		return m_Hash == hash;
	}

	std::shared_ptr<ScriptPatches::Patch> ScriptPatches::AddPatchImpl(joaat_t script, ScriptPointer pointer, std::vector<uint8_t> patch)
	{
		auto scr_patch = std::make_shared<Patch>(script, pointer, patch);

		// add patch to map
		m_Patches.push_back(scr_patch);

		// find existing programs to register
		for (int i = 0; i < 176; i++)
		{
			if (Pointers.ScriptPrograms[i] && Pointers.ScriptPrograms[i]->m_NameHash == script && Pointers.ScriptPrograms[i]->m_CodeSize && Pointers.ScriptPrograms[i]->m_CodeBlocks)
				RegisterProgram(Pointers.ScriptPrograms[i]);
		}

		return scr_patch;
	}

	void ScriptPatches::RegisterProgramImpl(rage::scrProgram* program)
	{
		if (auto it = m_Datas.find(program->m_NameHash); it != m_Datas.end())
		{
			return;
		}

		// check if this program is in scope

		bool in_scope = false;

		for (auto& patch : m_Patches)
		{
			if (patch->InScope(program->m_NameHash))
			{
				in_scope = true;
				break;
			}
		}

		if (!in_scope)
			return; // avoid polluting memory with unused program bytecode

		m_Datas.emplace(program->m_NameHash, std::move(std::make_unique<ScriptData>(program)));

		// refresh patches so they can enable themselves
		for (auto& patch : m_Patches)
		{
			if (patch->InScope(program->m_NameHash))
			{
				patch->Update();
			}
		}
	}

	void ScriptPatches::UnregisterProgramImpl(rage::scrProgram* program)
	{
		// we currently do not unregister programs
		// this leaks an acceptable amount of memory
	}

	void ScriptPatches::OnScriptVMEnterImpl(rage::scrProgram* program)
	{
		if (m_CurrentlyReplacedBytecode)
		{
			LOG(FATAL) << "We've already shadowed the bytecode of another program!";
			return;
		}

		auto data = GetDataImpl(program->m_NameHash);

		if (!data)
		{
			return; // nothing to do here
		}

		m_CurrentlyReplacedBytecode = program->m_CodeBlocks;
		program->m_CodeBlocks = data->GetData();
	}

	void ScriptPatches::OnScriptVMLeaveImpl(rage::scrProgram* program)
	{
		if (m_CurrentlyReplacedBytecode)
		{
			program->m_CodeBlocks = m_CurrentlyReplacedBytecode;
			m_CurrentlyReplacedBytecode = nullptr;
		}
	}

	ScriptData* ScriptPatches::GetDataImpl(joaat_t script)
	{
		if (auto it = m_Datas.find(script); it != m_Datas.end())
			return it->second.get();

		return nullptr;
	}

	ScriptPatches::ScriptPatches() :
	    m_CurrentlyReplacedBytecode(nullptr)
	{
	}

	ScriptPatches::~ScriptPatches()
	{
		m_Patches.clear();
		m_Datas.clear();
	}
}
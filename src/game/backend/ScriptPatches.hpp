#pragma once
#include "core/util/Joaat.hpp"
#include "game/gta/ScriptData.hpp"
#include "game/gta/ScriptPointer.hpp"

namespace rage
{
	class scrProgram;
}

namespace YimMenu
{
	class ScriptPatches
	{
	public:
		class Patch
		{
			std::vector<uint8_t> m_OriginalBytes;
			std::vector<uint8_t> m_PatchedBytes;
			std::optional<uint32_t> m_Pc;
			ScriptPointer m_Pointer;
			bool m_Enabled;
			std::uint32_t m_Hash;
			std::optional<uint32_t> GetPC();
			void Apply();
			void Restore();

		public:
			Patch(joaat_t script, ScriptPointer pointer, std::vector<uint8_t> patch);
			void Enable();
			void Disable();
			void Update();
			bool InScope(std::uint32_t hash);
		};

		static std::shared_ptr<Patch> AddPatch(joaat_t script, ScriptPointer pointer, std::vector<uint8_t> patch)
		{
			return GetInstance().AddPatchImpl(script, pointer, patch);
		}

		static void RegisterProgram(rage::scrProgram* program)
		{
			GetInstance().RegisterProgramImpl(program);
		}

		static void UnregisterProgram(rage::scrProgram* program)
		{
			GetInstance().UnregisterProgramImpl(program);
		}

		static void OnScriptVMEnter(rage::scrProgram* program)
		{
			GetInstance().OnScriptVMEnterImpl(program);
		}

		static void OnScriptVMLeave(rage::scrProgram* program)
		{
			GetInstance().OnScriptVMLeaveImpl(program);
		}

	private:
		ScriptPatches();
		~ScriptPatches();

		static ScriptPatches& GetInstance()
		{
			static ScriptPatches Instance;
			return Instance;
		}

		std::shared_ptr<Patch> AddPatchImpl(joaat_t script, ScriptPointer pointer, std::vector<uint8_t> patch);
		void RegisterProgramImpl(rage::scrProgram* program);
		void UnregisterProgramImpl(rage::scrProgram* program);
		void OnScriptVMEnterImpl(rage::scrProgram* program);
		void OnScriptVMLeaveImpl(rage::scrProgram* program);
		ScriptData* GetDataImpl(joaat_t script);

		std::vector<std::shared_ptr<Patch>> m_Patches;
		std::unordered_map<joaat_t, std::unique_ptr<ScriptData>> m_Datas;
		std::uint8_t** m_CurrentlyReplacedBytecode;
	};

	using ScriptPatch = std::shared_ptr<ScriptPatches::Patch>;
}
#pragma once

namespace rage
{
	class scrThread
	{
	public:
		enum class State
		{
			IDLE,
			RUNNING,
			KILLED,
			PAUSED,
			UNK4
		};

		class Context
		{
		public:
			std::uint32_t m_ThreadId;       // 0x00
			std::uint64_t m_ScriptHash;     // 0x08 TODO: is this still the script hash in enhanced? why is it an 8-byte value now?
			State m_State;                  // 0x10
			std::uint32_t m_ProgramCounter; // 0x14
			std::uint32_t m_FramePointer;   // 0x18
			std::uint32_t m_StackPointer;   // 0x1C
			float m_TimerA;                 // 0x20
			float m_TimerB;                 // 0x24
			float m_WaitTimer;              // 0x28
			char m_padding1[0x2C];          // 0x2C
			std::uint32_t m_StackSize;      // 0x58
			char m_Pad[0x54];               // 0x2C don't really need this fields after this
		};
		static_assert(sizeof(Context) == 0xB0);


		virtual ~scrThread() = default;
		virtual void Reset(std::uint64_t script_hash, void* args, std::uint32_t arg_count) = 0;
		virtual State RunImpl() = 0;
		virtual State Run() = 0;
		virtual void Kill() = 0;
		virtual void GetInfo(void* info) = 0; // new in Enhanced, more research needed
		                                      // I'm not sure what's going on with this func, best to not touch it

		Context m_Context;             // 0x08
		void* m_Stack;                 // 0xB8
		char m_Pad[0x4];               // 0xC0
		std::uint32_t m_ParameterSize; // 0xC4
		std::uint32_t m_ParameterLoc;  // 0xC8
		char m_Pad2[0x4];              // 0xCC
		char m_ErrorMessage[128];      // 0xD0 finally works now (size 124, 4 padding)
		std::uint32_t m_ScriptHash;    // 0x150
		char m_ScriptName[64];         // 0x154

		static rage::scrThread* GetRunningThread();
	};
	static_assert(sizeof(scrThread) == 0x198);
}
#pragma once

#include "atArray.hpp"
#include <cstdint>

namespace rage
{
	struct gameSkeletonData
	{
		void* m_InitFunc;     // 0x0
		void* m_ShutdownFunc; // 0x8
		uint32_t m_unk1;      // 0x10
		uint32_t m_unk2;      // 0x14
		uint32_t m_unk3;      // 0x18
		uint32_t m_unk4;      // 0x1C
		uint32_t m_Hash;      // 0x20
	};
	static_assert(sizeof(gameSkeletonData) == 0x28);

	struct gameSkeletonUpdateBase
	{
		virtual ~gameSkeletonUpdateBase() = default;
		virtual void Run() = 0;
		virtual bool ShouldIntegrityCheck() = 0;

		uint64_t m_Pad;                 // 0x08
		uint32_t m_Hash;                // 0x10
		gameSkeletonUpdateBase* m_Next; // 0x18
	};
	static_assert(sizeof(gameSkeletonUpdateBase) == 0x20);

	struct gameSkeletonUpdateGroup : gameSkeletonUpdateBase
	{
		gameSkeletonUpdateBase* m_Head; // 0x20
	};
	static_assert(sizeof(gameSkeletonUpdateGroup) == 0x28);

	struct gameSkeletonUpdateElement : gameSkeletonUpdateBase
	{
		void (*m_Function)(); // 0x20
	};
	static_assert(sizeof(gameSkeletonUpdateElement) == 0x28);

	struct gameSkeletonUpdateMode
	{
		int m_Type;                     // 0x00
		gameSkeletonUpdateBase* m_Head; // 0x08
		gameSkeletonUpdateMode* m_Next; // 0x10
	};
	static_assert(sizeof(gameSkeletonUpdateMode) == 0x18);

	struct gameSkeletonInitDependency
	{
		int m_Level;                        // 0x00
		atArray<uint32_t> m_Data;           // 0x08
		gameSkeletonInitDependency* m_Next; // 0x10
	};

	struct gameSkeletonMode
	{
		int m_Type;                         // 0x00
		gameSkeletonInitDependency* m_Head; // 0x08
		gameSkeletonMode* m_Next;           // 0x10
	};
	static_assert(sizeof(gameSkeletonMode) == 0x18);

	struct gameSkeleton
	{
		virtual ~gameSkeleton() = 0;
		uint32_t m_unk1;                       // 0x08
		uint32_t m_unk2;                       // 0x0C
		uint32_t m_unk3;                       // 0x10
		uint32_t m_unk4;                       // 0x14
		atArray<gameSkeletonData> m_SysData;   // 0x18
		uint32_t m_unk5;                       // 0x28
		void* m_unk6[32];                      // 0x30
		gameSkeletonMode* m_InitModes;         // 0x130
		gameSkeletonMode* m_ShutdownModes;     // 0x138
		gameSkeletonUpdateMode* m_UpdateModes; // 0x140
	};
	static_assert(sizeof(gameSkeleton) == 0x148);
}
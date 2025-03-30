#pragma once

class CNetGamePlayer;

namespace rage
{
	class netArrayHandlerBase;
	class netArrayIdentiferBase;
	class netPlayer;
	class datBitBuffer;
}

namespace rage
{
	class netSyncDataUnit_Dynamic
	{
	public:
		virtual ~netSyncDataUnit_Dynamic() = default; // 0x00

		virtual void _0x08() = 0;
		virtual void _0x10() = 0;
		virtual void SetDataCounter(int index, uint16_t counter) = 0; // 0x18
		virtual void ResetDataCounter(int index) = 0; // 0x20

		// ...

		int m_PlayerNeedAck;  // 0x08
		int m_PlayersNeedSync; // 0x0C
	};

	class netSyncData_Dynamic
	{
	public:
		virtual ~netSyncData_Dynamic() = default; // 0x00

		virtual rage::datBitBuffer* _0x08() = 0;
		virtual rage::datBitBuffer* _0x10() = 0;
		virtual int GetNumPlayers() = 0; // 0x18
		virtual int _0x20() = 0;
		virtual void _0x28() = 0;
		virtual netSyncDataUnit_Dynamic* GetSyncUnitForElement(uint32_t element) = 0; // 0x30

		// ...
	};

	struct netSyncElement
	{
		std::uint32_t m_Data[4];
	};
	static_assert(sizeof(netSyncElement) == 0x10);

	class netArrayHandlerBase
	{
	public:
		virtual ~netArrayHandlerBase() = default; // 0x00

		virtual void _0x08() = 0;

		virtual void _0x10() = 0;

		virtual void _0x18() = 0;

		virtual void _0x20() = 0;

		virtual void _0x28() = 0;

		virtual void _0x30() = 0;

		virtual void _0x38() = 0; 

		virtual void _0x40() = 0; 

		virtual int _0x48(CNetGamePlayer* player, int max_size, uint32_t* a3, uint32_t* a4) = 0; 

		virtual int GetSize(CNetGamePlayer* player, int max_size, uint32_t element) = 0; // 0x50

		virtual int PackArrayData(CNetGamePlayer* player, rage::datBitBuffer* bit_buffer, uint16_t counter, uint32_t* elem_start, bool silent) = 0; // 0x58

		virtual void _0x60() = 0; 

		virtual bool ShouldNotSendDataToPlayer(CNetGamePlayer* player) = 0;

		virtual void _0x70() = 0; 

		virtual bool CanSendUpdate(CNetGamePlayer* player) = 0; // 0x78

		virtual void _0x80() = 0; 

		virtual void _0x88(int) = 0; 

		virtual netArrayIdentiferBase* GetIdentifier() = 0; // 0x90

		virtual netArrayIdentiferBase* _0x98() = 0; // same as get_identifier

		virtual void _0xA0() = 0;

		virtual bool CanVerifyArrayData() = 0; // 0xA8

		virtual void _0xB0() = 0;

		virtual void _0xB8() = 0; 

		virtual void ShouldSyncElement(uint32_t element) = 0; // 0xC0

		virtual void _0xC8() = 0; 

		virtual void _0xD0() = 0; 

		virtual bool AreAllElementsInScope() = 0; // 0xD8

		virtual void _0xE0() = 0; 

		virtual void VerifyArrayData() = 0; // 0xE8

		virtual void VerifyArrayDataAck(CNetGamePlayer* player, int checksum) = 0; 

		virtual char* GetDebugName() = 0; // 0xF8

		virtual bool IsLocalPlayerOwnerOfArray() = 0; // 0x100

		virtual CNetGamePlayer* GetOwnerOfArray() = 0; // 0x108

		virtual void _0x110() = 0;

		virtual uint32_t GetArrayChecksum() = 0;

		virtual int _0x120() = 0; // gets array size for hashing

		virtual netSyncData_Dynamic* GetDynamicSyncData() = 0;

		virtual netSyncData_Dynamic* GetDynamicSyncData2() = 0; // 0x130

		virtual void _0x138() = 0;

		virtual bool IsElementInScope(uint32_t element, CNetGamePlayer* player) = 0; // 0x140

		virtual int RecieverIndexFromPlayer(CNetGamePlayer*) = 0; // 0x148

		virtual void _0x150() = 0;

		virtual void _0x158() = 0;

		// pasted from fivem
		virtual bool IsElementEmpty(uint32_t element) = 0; // 0x160

		virtual void SetElementEmpty(uint32_t element) = 0; // 0x168

		virtual void WriteElementIndex(rage::datBitBuffer& buffer, uint32_t element) = 0; // 0x170

		virtual void ReadElementIndex(rage::datBitBuffer& buffer, uint32_t& element) = 0; // 0x178

		virtual bool IsValidIndex(uint32_t) = 0; // 0x180

		virtual void RecalculateDirtyElements() = 0; // 0x188

		virtual void ResetElementSyncData(uint32_t element) = 0; // 0x190

		virtual void DoPostReadProcessing() = 0; // 0x198

		virtual void DoPostElementReadProcessing(uint32_t element) = 0; // 0x1A0

		virtual bool CanApplyElementData(uint32_t element, const rage::netPlayer& sender, bool force) = 0; // 0x1A8

		virtual void ExtractDataForSerializing(uint32_t elem) = 0; // 0x1B0

		virtual void WriteElement(rage::datBitBuffer& buffer, uint32_t elem, void* logger) = 0; // 0x1B8

		virtual void ReadElement(rage::datBitBuffer& buffer, uint32_t elem, void* logger) = 0; // 0x1C0

		virtual void LogElement(uint32_t elem, void* logger) = 0; // 0x1C8

		virtual uint32_t GetCurrentElementSizeInBits(uint32_t elem) = 0; // 0x1D0

		virtual void ApplyElementData(uint32_t element, const rage::netPlayer& sender) = 0; // 0x1D8

		virtual void _0x1E0() = 0;

		virtual void _0x1E8(bool) = 0;

		void* m_Something;                 // 0x8
		netArrayHandlerBase* m_Next;       // 0x10
		uint8_t _m_pad[0x4C];              // 0x18
		uint32_t m_Hash;                   // 0x64?
		uint8_t _m_pad2[0x8C];             // 0x68?
		uint16_t m_ArrayIndex;             // 0xF4
		uint16_t m_MaxElements;            // 0xF6
		uint8_t m_NumElements;             // 0xF8
		uint8_t m_ElementSize;             // 0xF9
		uint8_t m_ElementSize2;            // 0xFA
		uint8_t _m_pad3[13];               // 0xFB
	};
	static_assert(sizeof(netArrayHandlerBase) == 0x108);
}
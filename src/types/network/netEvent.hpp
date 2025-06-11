#pragma once
#include "netAddress.hpp"

namespace rage
{
	class netEvent
	{
	public:
		enum class Type
		{
			ConnectionRequested = 0, // seems to be identical to rage::netConnection::InFrame
			ConnectionError = 2,
			ConnectionClosed = 3,
			FrameReceived = 4, // rage::netConnection::InFrame
			BandwidthExceeded = 6,
			OutOfMemory = 7
		};

		virtual ~netEvent() = default;

		virtual void Destroy() = 0;
		virtual Type GetEventType() = 0;
		virtual uint32_t _0x18() = 0;

		std::uint32_t m_Timestamp; // 0x0008
		char pad_0008[52];         // 0x000C
		std::uint32_t m_MsgId;     // 0x0040
		std::uint32_t m_CxnId;     // 0x0044
		rage::netEvent* m_This;    // 0x0048
		uint32_t m_PeerId;         // 0x0050
		char pad_0084[4];          // 0x0054
	};
	static_assert(sizeof(rage::netEvent) == 0x58);

	// or rage::netConnection::InFrame
	class netEventFrameReceived : public netEvent
	{
	public:
		int m_SecurityId;           // 0x0058
		rage::netAddress m_Address; // 0x0060
		std::uint32_t m_Length;     // 0x0080
		void* m_Data;               // 0x0088
	};
	static_assert(sizeof(netEventFrameReceived) == 0x90);
}
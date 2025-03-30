#pragma once

namespace rage
{
	class netArrayHandlerBase;
}

namespace rage
{
	class netArrayMgr
	{
	public:
		char padding[0x40];
		rage::netArrayHandlerBase* m_Start;
	};
	static_assert(sizeof(netArrayMgr) == 0x48);
}
#pragma once
#include "scrThread.hpp"
#include "scriptId.hpp"

#include <cstdint>

namespace rage
{
	class scriptHandlerObject;
	class scriptHandler
	{
	public:
		virtual ~scriptHandler() = default; //  0 (0x00)

		virtual bool _0x08() = 0; //  1 (0x08)

		virtual void _0x10() = 0; //  2 (0x10)

		virtual void CleanupObjects() = 0; //  3 (0x18)

		virtual scriptId* _0x20() = 0; //  4 (0x20)

		virtual scriptId* GetId() = 0; //  5 (0x28)

		// TODO more fields
	public:
		// TODO
	};
}
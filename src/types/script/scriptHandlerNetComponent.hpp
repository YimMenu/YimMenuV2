#pragma once

namespace rage
{
	class scriptHandler;
	class scriptHandlerNetComponent
	{
	public:
		virtual ~scriptHandlerNetComponent() = default;

	public:
		scriptHandler* m_ScriptHandler; // 0x08
	};
	static_assert(sizeof(scriptHandlerNetComponent) == 0x10);
}
#include "ScriptEvent.hpp"
#include "game/gta/Natives.hpp"

void SCRIPT_EVENT::SendImpl(int size)
{
	SCRIPT::_SEND_TU_SCRIPT_EVENT_NEW(1, this, size / sizeof(std::uint64_t), PlayerBits, EventIndex);
}

#include "common.hpp"

namespace YimMenu
{
	std::atomic<bool> g_Running{true};
	HINSTANCE g_DllInstance{nullptr};
	HANDLE g_MainThread{INVALID_HANDLE_VALUE};
	DWORD g_MainThreadId = -1;
}
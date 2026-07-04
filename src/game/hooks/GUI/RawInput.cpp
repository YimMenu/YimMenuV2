#include "core/hooking/DetourHook.hpp"
#include "game/frontend/GUI.hpp"
#include "game/hooks/Hooks.hpp"

namespace YimMenu::Hooks
{
	UINT RawInput::GetRawInputData(HRAWINPUT hRawInput, UINT uiCommand, LPVOID pData, PUINT pcbSize, UINT cbSizeHeader)
	{
		auto result = BaseHook::Get<RawInput::GetRawInputData, DetourHook<decltype(&RawInput::GetRawInputData)>>()->Original()(hRawInput, uiCommand, pData, pcbSize, cbSizeHeader);

		if (result > 0 && pData && uiCommand == RID_INPUT && GUI::IsOpen())
		{
			auto& raw = *(RAWINPUT*)pData;
			if (raw.header.dwType == RIM_TYPEMOUSE && raw.data.mouse.usButtonFlags)
			{
				// Zero out button flags to prevent game from seeing clicks while menu is open
				raw.data.mouse.usButtonFlags = 0;
			}
		}

		return result;
	}
}

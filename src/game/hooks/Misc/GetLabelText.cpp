#include "core/hooking/DetourHook.hpp"
#include "game/hooks/Hooks.hpp"
#include "game/backend/CustomLabelText.hpp"

namespace YimMenu::Hooks
{
	const char* Misc::GetLabelText(void* unk, const char* label)
	{
		if (const auto text = CustomLabelText::GetText<const char*>(label); text)
			return text;

		return BaseHook::Get<Misc::GetLabelText, DetourHook<decltype(&Misc::GetLabelText)>>()->Original()(unk, label);
	}
}
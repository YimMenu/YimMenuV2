#include "core/hooking/DetourHook.hpp"
#include "game/hooks/Hooks.hpp"
#include "game/backend/CustomLabelText.hpp"

namespace YimMenu::Hooks
{
	const char* Misc::GetLabelTextInternal(void* this_, uint32_t label_hash)
	{
		if (const auto text = CustomLabelText::GetText<uint32_t>(label_hash); text)
			return text;

		return BaseHook::Get<Misc::GetLabelTextInternal, DetourHook<decltype(&Misc::GetLabelTextInternal)>>()->Original()(this_, label_hash);
	}
}
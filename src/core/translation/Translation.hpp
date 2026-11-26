#pragma once

#include <optional>
#include <string>
#include <string_view>

namespace YimMenu::Translation
{
	// Returns the Arabic translation for the supplied English text.
	// If no translation is registered, the original text is returned unchanged.
	std::string Tr(std::string_view text);

	// Same as Tr, but only the visible part of an ImGui label is translated.
	// Everything from the first "##" onwards (the widget ID) is kept verbatim so
	// that ImGui IDs stay stable and unique.
	std::string TrLabel(std::string_view text);

	// Convenience overload for optional label overrides.
	std::optional<std::string> TrOptionalLabel(const std::optional<std::string>& text);
}

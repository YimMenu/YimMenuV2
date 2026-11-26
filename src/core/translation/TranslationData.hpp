#pragma once

#include <span>
#include <string_view>
#include <utility>

namespace YimMenu::Translation
{
	// Embedded English -> Arabic table. The Arabic side is already shaped
	// (Arabic Presentation Forms-B) and reordered for left-to-right rendering,
	// because ImGui does not perform Arabic shaping or bidi reordering.
	std::span<const std::pair<std::string_view, std::string_view>> GetTranslationTable();
}

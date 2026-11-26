#include "Translation.hpp"
#include "TranslationData.hpp"

#include <algorithm>

namespace YimMenu::Translation
{
	std::string Tr(std::string_view text)
	{
		if (text.empty())
			return {};

		const auto table = GetTranslationTable();

		const auto it = std::lower_bound(table.begin(),
		    table.end(),
		    text,
		    [](const auto& entry, std::string_view value) {
			    return entry.first < value;
		    });

		if (it != table.end() && it->first == text)
			return std::string(it->second);

		return std::string(text);
	}

	std::string TrLabel(std::string_view text)
	{
		const auto id_pos = text.find("##");
		if (id_pos == std::string_view::npos)
			return Tr(text);

		auto result = Tr(text.substr(0, id_pos));
		result.append(text.substr(id_pos));
		return result;
	}

	std::optional<std::string> TrOptionalLabel(const std::optional<std::string>& text)
	{
		if (!text.has_value())
			return std::nullopt;

		return TrLabel(text.value());
	}
}

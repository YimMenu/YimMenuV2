#include "core/memory/ModuleMgr.hpp"
#include "Joaat.hpp"

#include <optional>

namespace YimMenu {
    inline std::optional<bool> InWine()
    {
        auto module = ModuleMgr.Get("ntdll.dll"_J);
        if (!module)
            return std::nullopt;
        return module->IsExported("wine_get_version");
    }
}
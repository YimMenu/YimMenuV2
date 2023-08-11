#pragma once
#include "BaseObj.hpp"

namespace YimMenu
{
    class Folder final : public BaseObj
    {
    public:
        Folder(const std::filesystem::path& folder);

    };
}
#pragma once
#include "BaseObj.hpp"

namespace NewBase
{
    class Folder final : public BaseObj
    {
    public:
        Folder(const std::filesystem::path& folder);

    };
}
#pragma once
#include <filesystem>

namespace NewBase
{
    class BaseObj
    {
    public:
        BaseObj(const std::filesystem::path& path);

        [[nodiscard]] bool Exists() const;
        const std::filesystem::path& Path() const;

        operator std::filesystem::path() const
        {
            return m_Path;
        }

    protected:
        const std::filesystem::path m_Path;

    };
}
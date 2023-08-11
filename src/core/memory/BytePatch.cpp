#include "BytePatch.hpp"

namespace YimMenu
{
    BytePatch::~BytePatch()
    {
        Restore();
    }

	void BytePatch::Apply() const
	{
        std::copy_n(m_Patch.get(), m_Size, reinterpret_cast<byte*>(m_Address));
	}

	void BytePatch::Restore() const
	{
        std::copy_n(m_Original.get(), m_Size, reinterpret_cast<byte*>(m_Address));
	}

	void BytePatch::Remove() const
	{
        if (const auto it = std::find(m_Patches.begin(), m_Patches.end(), this); it != m_Patches.end())
		{
			m_Patches.erase(it);
		}
	}

	void BytePatch::RestoreAll()
	{
        m_Patches.clear();
	}

	bool operator==(const std::unique_ptr<BytePatch>& a, const BytePatch* b)
	{
		return a->m_Address == b->m_Address;
	}
}
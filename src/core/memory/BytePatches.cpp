#include "BytePatches.hpp"

namespace YimMenu
{
	BytePatches::Patch::~Patch()
	{
		Restore();
	}

	void BytePatches::Patch::Apply()
	{
		if (m_Applied || !g_Running)
			return;
		memcpy(m_Address, m_Value.get(), m_Size);
		m_Applied = true;
	}

	void BytePatches::Patch::Restore()
	{
		if (!m_Applied)
			return;
		memcpy(m_Address, m_OriginalBytes.get(), m_Size);
		m_Applied = false;
	}

	bool operator==(const std::shared_ptr<BytePatches::Patch>& a, const BytePatches::Patch* b)
	{
		return a->m_Address == b->m_Address;
	}

	void BytePatches::Remove(std::shared_ptr<Patch>& patch)
	{
		if (const auto it = std::find(m_Patches.begin(), m_Patches.end(), patch.get()); it != m_Patches.end())
		{
			m_Patches.erase(it);
		}
		patch.reset();
	}

	void BytePatches::RestoreAll()
	{
		m_Patches.clear();
	}
}
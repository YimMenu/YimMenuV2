#include "BytePatches.hpp"

namespace YimMenu
{
	BytePatches::Patch::~Patch()
	{
	}

	void BytePatches::Patch::Apply()
	{
		if (m_Applied || !g_Running)
			return;

		std::lock_guard lock(m_Mutex); // this function should be thread-safe, but doesn't hurt

		unsigned long old_protect;
		unsigned long temp;
		VirtualProtect(m_Address, m_Size, PAGE_EXECUTE_READWRITE, &old_protect);
		memcpy(m_Address, m_Value.get(), m_Size);
		VirtualProtect(m_Address, m_Size, old_protect, &temp);
		m_Applied = true;
	}

	void BytePatches::Patch::Restore()
	{
		if (!m_Applied)
			return;

		std::lock_guard lock(m_Mutex);

		unsigned long old_protect;
		unsigned long temp;
		VirtualProtect(m_Address, m_Size, PAGE_EXECUTE_READWRITE, &old_protect);
		memcpy(m_Address, m_OriginalBytes.get(), m_Size);
		VirtualProtect(m_Address, m_Size, old_protect, &temp);
		m_Applied = false;
	}

	bool operator==(const std::shared_ptr<BytePatches::Patch>& a, const BytePatches::Patch* b)
	{
		return a->m_Address == b->m_Address;
	}

	void BytePatches::Remove(std::shared_ptr<Patch>& patch)
	{
		patch->Restore();

		if (const auto it = std::find(m_Patches.begin(), m_Patches.end(), patch.get()); it != m_Patches.end())
		{
			m_Patches.erase(it);
		}
		patch.reset();
	}

	void BytePatches::RestoreAll()
	{
		for (auto& patch : m_Patches)
		{
			patch->Restore();
		}

		m_Patches.clear();
	}
}
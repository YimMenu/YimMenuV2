#pragma once

namespace YimMenu
{
	class LuaResource
	{
		int m_Type;

	public:
		int GetType() const { return m_Type; }
		void SetType(int type) { m_Type = type; }
		virtual void OnEnable() {}; // called during resume and also immediately after AddResource
		virtual void OnDisable() {}; // called during pause and before unload
	};

	class LuaResourceType
	{
		int m_Index{};
		std::mutex m_Mutex{};

		void Register();
	public:
		LuaResourceType()
		{
			Register();
		}

		void Lock()
		{
			m_Mutex.lock();
		}

		void Unlock()
		{
			m_Mutex.unlock();
		}

		int GetIndex() const
		{
			return m_Index;
		}
	};
}
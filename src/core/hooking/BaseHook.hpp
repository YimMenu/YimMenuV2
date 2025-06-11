#pragma once
#include <string_view>

namespace YimMenu
{
	class BaseHook
	{
	private:
		const std::string_view m_Name;

	protected:
		bool m_Enabled;

	public:
		BaseHook(const std::string_view name);
		virtual ~BaseHook() = default;
		BaseHook(const BaseHook&) = delete;
		BaseHook(BaseHook&&) noexcept = delete;
		BaseHook& operator=(const BaseHook&) = delete;
		BaseHook& operator=(BaseHook&&) noexcept = delete;

		const std::string_view Name() const
		{
			return m_Name;
		}
		inline bool IsEnabled() const
		{
			return m_Enabled;
		}

		virtual bool Enable() = 0;
		virtual bool Disable() = 0;

	public:
		template<auto HookFunc>
		struct HookHelper
		{
			inline static BaseHook* m_Hook;
		};

		template<auto HookFunc>
		inline static void Add(BaseHook* hook);
		template<auto HookFunc, typename T>
		inline static T* Get();

		static std::vector<BaseHook*>& Hooks();

		static void EnableAll();
		static void DisableAll();

	private:
		inline static std::vector<BaseHook*> m_Hooks;
	};

	template<auto HookFunc>
	inline void BaseHook::Add(BaseHook* hook)
	{
		HookHelper<HookFunc>::m_Hook = hook;
	}

	template<auto HookFunc, typename T>
	inline T* BaseHook::Get()
	{
		return reinterpret_cast<T*>(HookHelper<HookFunc>::m_Hook);
	}
}

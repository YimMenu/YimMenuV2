#pragma once
#include "MinHook.hpp"

namespace YimMenu
{
	class Hooking
	{
	private:
		Hooking();

		MinHook m_MinHook;

	public:
		virtual ~Hooking();
		Hooking(const Hooking&) = delete;
		Hooking(Hooking&&) noexcept = delete;
		Hooking& operator=(const Hooking&) = delete;
		Hooking& operator=(Hooking&&) noexcept = delete;

		static bool Init();
		static void Destroy();

	private:
		bool InitImpl();
		void DestroyImpl();

	private:
		static Hooking& GetInstance()
		{
			static Hooking i{};
			return i;
		}
	};
}
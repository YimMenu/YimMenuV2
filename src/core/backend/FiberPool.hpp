#pragma once

namespace YimMenu
{
	class FiberPool
	{
		FiberPool() = default;

	public:
		FiberPool(const FiberPool&) = delete;
		FiberPool(FiberPool&&) noexcept = delete;
		FiberPool& operator=(const FiberPool&) = delete;
		FiberPool& operator=(FiberPool&&) noexcept = delete;
		virtual ~FiberPool() = default;

		static void Init(int num_fibers)
		{
			GetInstance().InitImpl(num_fibers);
		}

		static void Destroy()
		{
			GetInstance().DestroyImpl();
		}

		static void Push(std::function<void()> callback)
		{
			GetInstance().PushImpl(callback);
		}

	private:
		std::recursive_mutex m_Mutex{};
		std::stack<std::function<void()>> m_Jobs{};

		void InitImpl(int num_fibers);
		void DestroyImpl();
		void PushImpl(std::function<void()> callback);
		void Tick();
		static void ScriptEntry();

		static FiberPool& GetInstance()
		{
			static FiberPool i{};
			return i;
		}
	};
}
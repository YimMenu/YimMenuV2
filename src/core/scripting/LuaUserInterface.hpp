#pragma once

namespace YimMenu
{
	class LuaScript;
	class Command;
	class Submenu;
	class Category;
	class Group;
	class UIItem;
}

namespace YimMenu
{
	struct CallbackArg
	{
		enum class Kind
		{
			None,
			Bool,
			Int,
			Number
		} kind = Kind::None;

		union
		{
			bool b;
			long long i = 0; // wide enough for LuaJIT's 64-bit integers / joaat hashes
			double n;
		};
	};

	struct PendingCoroutine
	{
		int func = -1;
		CallbackArg arg{};
	};

	class LuaUserInterface
	{
		LuaScript* m_Script = nullptr;

		std::string m_MenuName;
		std::string m_MenuIcon;

		std::vector<std::shared_ptr<Submenu>> m_OwnedSubmenus;

		std::vector<std::unique_ptr<Command>> m_OwnedCommands;

		std::vector<std::pair<std::shared_ptr<Submenu>, std::shared_ptr<Category>>> m_AttachedCategories;
		std::vector<std::pair<std::shared_ptr<Category>, std::shared_ptr<UIItem>>> m_AttachedCategoryItems;
		std::vector<std::pair<std::shared_ptr<Group>, std::shared_ptr<UIItem>>>    m_AttachedGroupItems;

		std::vector<std::shared_ptr<Group>> m_OwnedGroups;

		std::vector<int> m_RenderCallbacks;

		std::unordered_set<void*> m_ScriptAllocations;

		std::mutex m_TickFunctionsLock;
		std::unordered_set<int> m_TickFunctions;
		std::deque<PendingCoroutine> m_ThrottledCoroutines;
		std::chrono::system_clock::time_point m_LastThrotlledCoroutinePush;

		bool m_ShutdownCalled = false;

	public:
		LuaUserInterface();
		~LuaUserInterface();

		LuaUserInterface(const LuaUserInterface&)            = delete;
		LuaUserInterface& operator=(const LuaUserInterface&) = delete;

		void Init(LuaScript* script);

		void Shutdown();

		LuaScript* GetScript() { return m_Script; }

		void SetMenuName(std::string_view name);
		void SetMenuIcon(std::string_view icon);
		const std::string& GetMenuName() const { return m_MenuName; }

		std::shared_ptr<Submenu> GetOrCreateSubmenu(std::string_view name);

		template<typename T>
		T* OwnCommand(std::unique_ptr<T>&& command)
		{
			auto* raw = command.get();
			m_OwnedCommands.push_back(std::move(command));
			return raw;
		}

		void TrackAttachedCategory(std::shared_ptr<Submenu> parent, std::shared_ptr<Category> category);
		void TrackAttachedCategoryItem(std::shared_ptr<Category> parent, std::shared_ptr<UIItem> item);
		void TrackAttachedGroupItem(std::shared_ptr<Group> parent, std::shared_ptr<UIItem> item);
		void TrackOwnedGroup(std::shared_ptr<Group> group);
		void TrackRenderCallback(int func_ref);

		void TrackScriptAllocation(void* ptr);
		bool ReleaseScriptAllocation(void* ptr);
		
		void AddTickFunction(int func);
		void RemoveTickFunction(int func);
		void QueueCoroutine(int coro, bool immediate = false, CallbackArg arg = {});

		// must be called from the main thread
		void Tick();
	};
}

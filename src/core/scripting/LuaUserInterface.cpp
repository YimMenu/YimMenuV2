#include "LuaUserInterface.hpp"
#include "LuaScript.hpp"

#include "core/commands/Command.hpp"
#include "core/frontend/manager/Category.hpp"
#include "core/frontend/manager/Submenu.hpp"
#include "core/frontend/manager/UIManager.hpp"
#include "game/frontend/items/Items.hpp"

namespace YimMenu
{
	LuaUserInterface::LuaUserInterface() :
	    m_LastThrotlledCoroutinePush(std::chrono::system_clock::now())
	{
	}

	LuaUserInterface::~LuaUserInterface()
	{
		if (!m_ShutdownCalled)
			Shutdown();
	}

	void LuaUserInterface::Init(LuaScript* script)
	{
		m_Script = script;
	}

	void LuaUserInterface::Shutdown()
	{
		if (m_ShutdownCalled)
			return;
		m_ShutdownCalled = true;

		for (auto& [group, item] : m_AttachedGroupItems)
			if (group)
				group->RemoveItem(item);
		m_AttachedGroupItems.clear();

		for (auto& [cat, item] : m_AttachedCategoryItems)
			if (cat)
				cat->RemoveItem(item);
		m_AttachedCategoryItems.clear();

		for (auto& [sub, cat] : m_AttachedCategories)
			if (sub)
				sub->RemoveCategory(cat);
		m_AttachedCategories.clear();

		for (auto& sub : m_OwnedSubmenus)
			if (sub)
				UIManager::RemoveSubmenu(sub);
		m_OwnedSubmenus.clear();

		m_OwnedGroups.clear();

		if (!m_RenderCallbacks.empty() && m_Script && m_Script->GetState())
		{
			std::lock_guard lock(m_Script->GetExecutionLock());
			for (auto ref : m_RenderCallbacks)
				luaL_unref(m_Script->GetState(), LUA_REGISTRYINDEX, ref);
		}
		m_RenderCallbacks.clear();

		for (auto* ptr : m_ScriptAllocations)
			std::free(ptr);
		m_ScriptAllocations.clear();

		m_OwnedCommands.clear();

		std::lock_guard lock(m_TickFunctionsLock);
		m_TickFunctions.clear();
		m_ThrottledCoroutines.clear();
	}

	void LuaUserInterface::TrackAttachedCategory(std::shared_ptr<Submenu> parent, std::shared_ptr<Category> category)
	{
		m_AttachedCategories.emplace_back(std::move(parent), std::move(category));
	}

	void LuaUserInterface::TrackAttachedCategoryItem(std::shared_ptr<Category> parent, std::shared_ptr<UIItem> item)
	{
		m_AttachedCategoryItems.emplace_back(std::move(parent), std::move(item));
	}

	void LuaUserInterface::TrackAttachedGroupItem(std::shared_ptr<Group> parent, std::shared_ptr<UIItem> item)
	{
		m_AttachedGroupItems.emplace_back(std::move(parent), std::move(item));
	}

	void LuaUserInterface::TrackOwnedGroup(std::shared_ptr<Group> group)
	{
		m_OwnedGroups.push_back(std::move(group));
	}

	void LuaUserInterface::TrackRenderCallback(int func_ref)
	{
		m_RenderCallbacks.push_back(func_ref);
	}

	void LuaUserInterface::TrackScriptAllocation(void* ptr)
	{
		m_ScriptAllocations.insert(ptr);
	}

	bool LuaUserInterface::ReleaseScriptAllocation(void* ptr)
	{
		return m_ScriptAllocations.erase(ptr) > 0;
	}

	void LuaUserInterface::SetMenuName(std::string_view name)
	{
		m_MenuName.assign(name);
	}

	void LuaUserInterface::SetMenuIcon(std::string_view icon)
	{
		m_MenuIcon.assign(icon);
	}

	std::shared_ptr<Submenu> LuaUserInterface::GetOrCreateSubmenu(std::string_view name)
	{
		for (auto& sub : m_OwnedSubmenus)
			if (sub && sub->m_Name == name)
				return sub;

		for (const auto& sub : UIManager::GetSubmenus())
			if (sub && sub->m_Name == name)
				return sub;

		auto sub = std::make_shared<Submenu>(std::string{name}, m_MenuIcon);
		UIManager::AddSubmenu(std::shared_ptr<Submenu>(sub));
		m_OwnedSubmenus.push_back(sub);
		return sub;
	}

	void LuaUserInterface::AddTickFunction(int func)
	{
		std::lock_guard lock(m_TickFunctionsLock);
		m_TickFunctions.insert(func);
	}

	void LuaUserInterface::RemoveTickFunction(int func)
	{
		std::lock_guard lock(m_TickFunctionsLock);
		m_TickFunctions.erase(func);
	}

	void LuaUserInterface::QueueCoroutine(int coro, bool immediate, CallbackArg arg)
	{
		std::lock_guard lock(m_TickFunctionsLock);
		if (immediate)
			m_ThrottledCoroutines.push_front({coro, arg});
		else
			m_ThrottledCoroutines.push_back({coro, arg});
	}

	void LuaUserInterface::Tick()
	{
		if (!m_Script)
			return;

		std::vector<PendingCoroutine> to_run_once;
		std::vector<int> to_tick;
		{
			std::lock_guard lock(m_TickFunctionsLock);

			auto now = std::chrono::system_clock::now();
			// One coroutine push per ~16ms keeps a long-pressed button or a script
			// that spams clicks from flooding the callback list.
			if (!m_ThrottledCoroutines.empty() && now - m_LastThrotlledCoroutinePush >= std::chrono::milliseconds(16))
			{
				to_run_once.push_back(m_ThrottledCoroutines.front());
				m_ThrottledCoroutines.pop_front();
				m_LastThrotlledCoroutinePush = now;
			}

			to_tick.reserve(m_TickFunctions.size());
			for (auto func : m_TickFunctions)
				to_tick.push_back(func);
		}

		for (auto& pending : to_run_once)
			m_Script->AddScriptCallback(pending.func, pending.arg);

		for (auto func : to_tick)
			m_Script->AddScriptCallback(func);
	}
}

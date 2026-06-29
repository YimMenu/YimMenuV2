#include "core/commands/Commands.hpp"
#include "core/frontend/manager/Category.hpp"
#include "core/frontend/manager/Submenu.hpp"
#include "core/frontend/manager/UIManager.hpp"
#include "core/scripting/LuaCommands.hpp"
#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaUserInterface.hpp"
#include "core/scripting/LuaUtils.hpp"
#include "core/util/Joaat.hpp"
#include "game/frontend/items/Items.hpp"
#include "game/frontend/GUI.hpp"
#include "LuaCommandHandle.hpp"

namespace YimMenu::Lua
{
	struct SubmenuHandle
	{
		std::weak_ptr<Submenu> ptr;
	};

	struct CategoryHandle
	{
		std::weak_ptr<Category> ptr;
	};

	struct GroupHandle
	{
		std::weak_ptr<Group> ptr;
	};

	static std::shared_ptr<Submenu> GetSubmenu(lua_State* state, int idx)
	{
		auto& h = GetObject<SubmenuHandle>(state, idx);
		auto ptr = h.ptr.lock();
		if (!ptr)
			luaL_argerror(state, idx, "submenu no longer exists");
		return ptr;
	}

	static std::shared_ptr<Category> GetCategory(lua_State* state, int idx)
	{
		auto& h = GetObject<CategoryHandle>(state, idx);
		auto ptr = h.ptr.lock();
		if (!ptr)
			luaL_argerror(state, idx, "category no longer exists");
		return ptr;
	}

	static std::shared_ptr<Group> GetGroup(lua_State* state, int idx)
	{
		auto& h = GetObject<GroupHandle>(state, idx);
		auto ptr = h.ptr.lock();
		if (!ptr)
			luaL_argerror(state, idx, "group no longer exists");
		return ptr;
	}

	template<typename Handle, typename Sp>
	static void PushHandle(lua_State* state, const Sp& sp)
	{
		auto* h = CreateObject<Handle>(state);
		h->ptr  = sp;
	}

	template<typename CommandT, typename... Args>
	static CommandT* InlineCreateCommand(lua_State* state, std::string_view name, Args&&... args)
	{
		auto& iface = LuaScript::GetScript(state).GetUserInterface();

		if (Commands::GetCommand(Joaat(name)))
			luaL_error(state, "command '%s' already exists", std::string(name).c_str());

		auto cmd = std::make_unique<CommandT>(&iface, std::string(name), std::forward<Args>(args)...);
		return iface.OwnCommand(std::move(cmd));
	}

	static std::shared_ptr<Submenu> FindSubmenuByName(std::string_view name)
	{
		for (const auto& sub : UIManager::GetSubmenus())
			if (sub && sub->m_Name == name)
				return sub;
		return nullptr;
	}

	static std::shared_ptr<Category> FindCategoryByName(const Submenu& sub, std::string_view name)
	{
		for (const auto& cat : sub.m_Categories)
			if (cat && cat->m_Name == name)
				return cat;
		return nullptr;
	}

	static std::shared_ptr<Group> FindGroupByName(const Category& cat, std::string_view name)
	{
		for (const auto& item : cat.GetItems())
		{
			if (auto grp = std::dynamic_pointer_cast<Group>(item))
				if (grp->GetName() == name)
					return grp;
		}
		return nullptr;
	}

	static int MenuSetMenuName(lua_State* state)
	{
		LuaScript::GetScript(state).GetUserInterface().SetMenuName(CheckStringSafe(state, 1));
		return 0;
	}

	static int MenuSetMenuIcon(lua_State* state)
	{
		LuaScript::GetScript(state).GetUserInterface().SetMenuIcon(CheckStringSafe(state, 1));
		return 0;
	}

	static int MenuGetMenuName(lua_State* state)
	{
		const auto& name = LuaScript::GetScript(state).GetUserInterface().GetMenuName();
		lua_pushlstring(state, name.data(), name.size());
		return 1;
	}

	static int MenuGetSubmenu(lua_State* state)
	{
		auto& iface = LuaScript::GetScript(state).GetUserInterface();

		std::string name;
		if (!lua_isnoneornil(state, 1))
		{
			name.assign(CheckStringSafe(state, 1));
		}
		else
		{
			name = iface.GetMenuName();
			if (name.empty())
				name = std::string(LuaScript::GetScript(state).GetName());
		}

		PushHandle<SubmenuHandle>(state, iface.GetOrCreateSubmenu(name));
		return 1;
	}

	static int MenuFindSubmenu(lua_State* state)
	{
		auto name = CheckStringSafe(state, 1);
		if (auto sub = FindSubmenuByName(name))
		{
			PushHandle<SubmenuHandle>(state, sub);
			return 1;
		}
		lua_pushnil(state);
		return 1;
	}

	static int IsOpen(lua_State* state)
	{
		lua_pushboolean(state, GUI::IsOpen());
		return 1;
	}

	static int Toggle(lua_State*)
	{
		GUI::Toggle();
		return 0;
	}

	static int MenuCreateGroup(lua_State* state)
	{
		auto& iface = LuaScript::GetScript(state).GetUserInterface();
		auto name   = CheckStringSafe(state, 1);
		int  per    = lua_isnoneornil(state, 2) ? 7 : static_cast<int>(luaL_checkinteger(state, 2));

		auto grp = std::make_shared<Group>(std::string(name), per);
		iface.TrackOwnedGroup(grp);
		PushHandle<GroupHandle>(state, grp);
		return 1;
	}

	static int SubmenuAddCategory(lua_State* state)
	{
		auto& iface = LuaScript::GetScript(state).GetUserInterface();
		auto sub    = GetSubmenu(state, 1);
		auto name   = CheckStringSafe(state, 2);

		auto cat = std::make_shared<Category>(name);
		sub->AddCategory(std::shared_ptr<Category>(cat));
		iface.TrackAttachedCategory(sub, cat);
		PushHandle<CategoryHandle>(state, cat);
		return 1;
	}

	static int SubmenuFindCategory(lua_State* state)
	{
		auto sub  = GetSubmenu(state, 1);
		auto name = CheckStringSafe(state, 2);
		if (auto cat = FindCategoryByName(*sub, name))
		{
			PushHandle<CategoryHandle>(state, cat);
			return 1;
		}
		lua_pushnil(state);
		return 1;
	}

	static int CategoryAddGroup(lua_State* state)
	{
		auto& iface = LuaScript::GetScript(state).GetUserInterface();
		auto cat    = GetCategory(state, 1);
		auto name   = CheckStringSafe(state, 2);
		int  per    = lua_isnoneornil(state, 3) ? 7 : static_cast<int>(luaL_checkinteger(state, 3));

		auto grp = std::make_shared<Group>(std::string(name), per);
		cat->AddItem(std::shared_ptr<UIItem>(grp));
		iface.TrackAttachedCategoryItem(cat, grp);
		PushHandle<GroupHandle>(state, grp);
		return 1;
	}

	static int CategoryFindGroup(lua_State* state)
	{
		auto cat  = GetCategory(state, 1);
		auto name = CheckStringSafe(state, 2);
		if (auto grp = FindGroupByName(*cat, name))
		{
			PushHandle<GroupHandle>(state, grp);
			return 1;
		}
		lua_pushnil(state);
		return 1;
	}

	static int CategoryImGui(lua_State* state)
	{
		auto* script = &LuaScript::GetScript(state);
		auto cat     = GetCategory(state, 1);
		int  fn      = CaptureFunction(state, 2, true);

		auto item = std::make_shared<ImGuiItem>([script, fn] {
			script->RunRenderCallback(fn);
		});
		cat->AddItem(std::shared_ptr<UIItem>(item));
		script->GetUserInterface().TrackAttachedCategoryItem(cat, item);
		script->GetUserInterface().TrackRenderCallback(fn);
		return 0;
	}

	static void GroupAttach(lua_State* state, const std::shared_ptr<Group>& grp, std::shared_ptr<UIItem> item)
	{
		auto& iface = LuaScript::GetScript(state).GetUserInterface();
		grp->AddItem(std::shared_ptr<UIItem>(item));
		iface.TrackAttachedGroupItem(grp, std::move(item));
	}

	static int GroupDraw(lua_State* state)
	{
		auto grp = GetGroup(state, 1);
		grp->Draw();
		return 0;
	}

	static int GroupImGui(lua_State* state)
	{
		auto* script = &LuaScript::GetScript(state);
		auto grp     = GetGroup(state, 1);
		int  fn      = CaptureFunction(state, 2, true);

		auto item = std::make_shared<ImGuiItem>([script, fn] {
			script->RunRenderCallback(fn);
		});
		GroupAttach(state, grp, item);
		script->GetUserInterface().TrackRenderCallback(fn);
		return 0;
	}

	static int GroupAddCommand(lua_State* state)
	{
		auto grp  = GetGroup(state, 1);
		auto name = CheckStringSafe(state, 2);
		GroupAttach(state, grp, std::make_shared<CommandItem>(Joaat(name)));
		return 0;
	}

	static int GroupAddBoolCommand(lua_State* state)
	{
		auto grp  = GetGroup(state, 1);
		auto name = CheckStringSafe(state, 2);
		GroupAttach(state, grp, std::make_shared<BoolCommandItem>(Joaat(name)));
		return 0;
	}

	static int GroupAddIntCommand(lua_State* state)
	{
		auto grp  = GetGroup(state, 1);
		auto name = CheckStringSafe(state, 2);
		bool slider = lua_isnoneornil(state, 3) ? true : CheckBooleanSafe(state, 3);
		GroupAttach(state, grp, std::make_shared<IntCommandItem>(Joaat(name), std::nullopt, slider));
		return 0;
	}

	static int GroupAddFloatCommand(lua_State* state)
	{
		auto grp  = GetGroup(state, 1);
		auto name = CheckStringSafe(state, 2);
		bool slider = lua_isnoneornil(state, 3) ? true : CheckBooleanSafe(state, 3);
		GroupAttach(state, grp, std::make_shared<FloatCommandItem>(Joaat(name), std::nullopt, slider));
		return 0;
	}

	static int GroupAddListCommand(lua_State* state)
	{
		auto grp  = GetGroup(state, 1);
		auto name = CheckStringSafe(state, 2);
		GroupAttach(state, grp, std::make_shared<ListCommandItem>(Joaat(name)));
		return 0;
	}

	static int GroupAddButton(lua_State* state)
	{
		auto grp   = GetGroup(state, 1);
		auto name  = CheckStringSafe(state, 2);
		auto label = CheckStringSafe(state, 3);
		auto desc  = lua_isnoneornil(state, 4) ? std::string{} : std::string(CheckStringSafe(state, 4));
		int  fn    = CaptureFunction(state, 5, true);
		InlineCreateCommand<LuaCommand>(state, name, std::string(label), desc, fn);
		GroupAttach(state, grp, std::make_shared<CommandItem>(Joaat(name)));
		return PushCommandHandle(state, Joaat(name), LuaCommandHandle::Kind::OneShot);
	}

	static int GroupAddLoopedCheckbox(lua_State* state)
	{
		auto grp   = GetGroup(state, 1);
		auto name  = CheckStringSafe(state, 2);
		auto label = CheckStringSafe(state, 3);
		auto desc  = lua_isnoneornil(state, 4) ? std::string{} : std::string(CheckStringSafe(state, 4));
		int  tick  = CaptureFunction(state, 5, true);
		int  on_en = CaptureFunction(state, 6, false);
		int  on_di = CaptureFunction(state, 7, false);

		InlineCreateCommand<LuaLoopedCommand>(state, name, std::string(label), desc, tick, on_en, on_di);
		GroupAttach(state, grp, std::make_shared<BoolCommandItem>(Joaat(name)));
		return PushCommandHandle(state, Joaat(name), LuaCommandHandle::Kind::Bool);
	}

	static int GroupAddCheckbox(lua_State* state)
	{
		auto grp   = GetGroup(state, 1);
		auto name  = CheckStringSafe(state, 2);
		auto label = CheckStringSafe(state, 3);
		auto desc  = lua_isnoneornil(state, 4) ? std::string{} : std::string(CheckStringSafe(state, 4));
		bool def   = lua_isnoneornil(state, 5) ? false : CheckBooleanSafe(state, 5);
		int  on_en = CaptureFunction(state, 6, false);
		int  on_di = CaptureFunction(state, 7, false);

		InlineCreateCommand<LuaBoolCommand>(state, name, std::string(label), desc, def, on_en, on_di);
		GroupAttach(state, grp, std::make_shared<BoolCommandItem>(Joaat(name)));
		return PushCommandHandle(state, Joaat(name), LuaCommandHandle::Kind::Bool);
	}

	class Menu : LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

		template<typename Handle, typename Setup>
		static void RegisterMethodMetatable(lua_State* state, Setup populate_methods)
		{
			lua_newtable(state);
			populate_methods(state);

			lua_newtable(state);
			lua_pushvalue(state, -2);
			lua_setfield(state, -2, "__index");

			lua_remove(state, -2);
			Metatable<Handle>::Register(state);
		}

		virtual void Register(lua_State* state) override
		{
			RegisterMethodMetatable<SubmenuHandle>(state, [](lua_State* s) {
				SetFunction(s, SubmenuAddCategory, "add_category");
				SetFunction(s, SubmenuFindCategory, "find_category");
			});
			RegisterMethodMetatable<CategoryHandle>(state, [](lua_State* s) {
				SetFunction(s, CategoryAddGroup, "add_group");
				SetFunction(s, CategoryFindGroup, "find_group");
				SetFunction(s, CategoryImGui, "imgui");
			});
			RegisterMethodMetatable<GroupHandle>(state, [](lua_State* s) {
				SetFunction(s, GroupAddCommand, "add_command");
				SetFunction(s, GroupAddBoolCommand, "add_bool_command");
				SetFunction(s, GroupAddIntCommand, "add_int_command");
				SetFunction(s, GroupAddFloatCommand, "add_float_command");
				SetFunction(s, GroupAddListCommand, "add_list_command");
				SetFunction(s, GroupAddButton, "add_button");
				SetFunction(s, GroupAddCheckbox, "add_checkbox");
				SetFunction(s, GroupAddLoopedCheckbox, "add_looped_checkbox");
				SetFunction(s, GroupImGui, "imgui");
				SetFunction(s, GroupDraw, "draw");
			});

			lua_newtable(state);
			SetFunction(state, MenuSetMenuName, "set_menu_name");
			SetFunction(state, MenuSetMenuIcon, "set_menu_icon");
			SetFunction(state, MenuGetMenuName, "get_menu_name");
			SetFunction(state, MenuGetSubmenu, "get_submenu");
			SetFunction(state, MenuFindSubmenu, "find_submenu");
			SetFunction(state, MenuCreateGroup, "create_group");
			SetFunction(state, IsOpen, "is_open");
			SetFunction(state, Toggle, "toggle");
			lua_setglobal(state, "menu");
		}
	};

	Menu _Menu;
}

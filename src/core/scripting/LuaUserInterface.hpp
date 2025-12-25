#pragma once

/*
something like

menu.set_menu_name("Test Interface Menu")
root = menu.get_root()
root:add_button("testbtn", "Test Button", function() 
	notify.info("Test", "Hello")
end)
root:add_looped_checkbox("testbox", "Test Checkbox", function()
	-- on tick
end, function()
	-- on enable
end, function()
	-- on disable
end, [should_serialize=true])
x = root:add_group("Name", 3)
y = root:add_tab_group
*/

namespace YimMenu
{
	class LuaUserInterface;
}

namespace YimMenu::Lua
{
	class UIRoot;

	class UIElementBase
	{
		LuaUserInterface& m_Interface;

	public:
		UIElementBase(LuaUserInterface& _interface);
		virtual void Draw() = 0;
	};

	class UIElementGroup : public UIElementBase
	{
		std::string m_Name;
		int m_NumElems; // num elements per row
		//std::vector<std::unique_ptr<UIElement>> m_Elements;

	public:
		UIElementGroup(LuaUserInterface& _interface, std::string_view name, int num_elems = 7);
		virtual void Draw();
	};

	class UIElement : public UIElementBase
	{
		std::string m_CmdString;
		std::uint32_t m_CmdHash;
		std::string m_Label;

	public:
		virtual void Draw() override = 0;
	};

	class UIElementWithState : public UIElement
	{
		bool m_ShouldSerialize;

	public:
		virtual void Draw() = 0;
	};

	class UIElementButton : public UIElement
	{
		int m_Function;

	public:
		virtual void Draw() = 0;
	};

	class UIButtonCheckbox : public UIElementWithState
	{
		bool m_Value;
		int m_OnChange;

	public:
		virtual void Draw() = 0;
	};

	class UIButtonIntSlider : public UIElementWithState
	{
		int m_Value;
		int m_OnChange;

	public:
		virtual void Draw() = 0;
	};

	class UIRoot
	{

	};
}

namespace YimMenu
{
	class LuaUserInterface
	{
		std::mutex m_TickFunctionsLock;
		std::unordered_set<int> m_TickFunctions;
		std::deque<int> m_ThrottledCoroutines;
		std::chrono::system_clock::time_point m_LastThrotlledCoroutinePush;
		std::unordered_map<std::uint32_t, Lua::UIElement*> m_ElementsById; 

	public:
		void AddTickFunction(int func);
		void RemoveTickFunction(int func);
		void QueueCoroutine(int coro, bool immediate = false);

		// must be called from the main thread
		void Tick();

		// must be called from the DX thread
		void Draw();
	};
}
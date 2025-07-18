#pragma once
#include "core/frontend/manager/UIItem.hpp"
#include "core/util/Joaat.hpp"
#include "game/frontend/GUI.hpp"

namespace YimMenu
{
	class BoolCommand;
	class PlayerCommand;
	class ListCommand;
	class IntCommand;
	class FloatCommand;
	class Vector3Command;
	class Command;
	class ColorCommand;
	class StringCommand;
	class CommandLink;

	class Button : public UIItem
	{
	public:
		explicit Button(const std::string_view& Name, std::function<void()> OnClick, ImVec2 size = {0, 25}, const std::string_view& information = "Empty");
		void Draw() override;

	private:
		std::string_view m_Name;
		std::string_view m_Information;
		std::function<void()> m_OnClick;
		ImVec2 m_Size;
	};

	class CommandItem : public UIItem
	{
	public:
		explicit CommandItem(joaat_t id, std::optional<std::string> label_override = std::nullopt);
		void Draw() override;

	private:
		Command* m_Command;
		std::optional<std::string> m_LabelOverride;
	};

	class PlayerCommandItem : public UIItem
	{
	public:
		explicit PlayerCommandItem(joaat_t id, std::optional<std::string> label_override = std::nullopt);
		void Draw() override;

	private:
		PlayerCommand* m_Command;
		std::optional<std::string> m_LabelOverride;
	};

	class BoolCommandItem : public UIItem
	{
	public:
		explicit BoolCommandItem(joaat_t id, std::optional<std::string> label_override = std::nullopt);
		void Draw() override;

	private:
		BoolCommand* m_Command;
		std::optional<std::string> m_LabelOverride;
	};

	class IntCommandItem : public UIItem
	{
	public:
		explicit IntCommandItem(joaat_t id, std::optional<std::string> label_override = std::nullopt, bool use_slider = true);
		void Draw() override;

	private:
		bool m_useSlider;
		IntCommand* m_Command;
		std::optional<std::string> m_LabelOverride;
	};

	class FloatCommandItem : public UIItem
	{
	public:
		explicit FloatCommandItem(joaat_t id, std::optional<std::string> label_override = std::nullopt, bool use_slider = true);
		void Draw() override;

	private:
		bool m_useSlider;
		FloatCommand* m_Command;
		std::optional<std::string> m_LabelOverride;
	};

	class Vector3CommandItem : public UIItem
	{
	public:
		explicit Vector3CommandItem(joaat_t id, std::optional<std::string> label_override = std::nullopt);
		void Draw() override;

	private:
		Vector3Command* m_Command;
		std::optional<std::string> m_LabelOverride;
		std::string m_CurrentCategory{};
		std::string m_CurrentFilter{};
	};

	class ListCommandItem : public UIItem
	{
	public:
		explicit ListCommandItem(joaat_t id, std::optional<std::string> label_override = std::nullopt);
		void Draw() override;

	private:
		ListCommand* m_Command;
		std::optional<std::string> m_LabelOverride;
		std::optional<int> m_ItemWidth = std::nullopt;
		std::optional<std::string> m_SelectedItem = std::nullopt;
	};

	class ConditionalItem : public UIItem
	{
	public:
		explicit ConditionalItem(joaat_t bool_cmd_id, std::shared_ptr<UIItem> to_draw, bool negate = false);
		explicit ConditionalItem(std::function<bool()> condition_fn, std::shared_ptr<UIItem> to_draw, bool negate = false);
		void Draw() override;
		bool CanDraw() override;

	private:
		BoolCommand* m_Condition;
		std::function<bool()> m_ConditionFn;
		std::shared_ptr<UIItem> m_Item;
		bool m_Negate;
	};

	class ImGuiItem : public UIItem
	{
	public:
		explicit ImGuiItem(std::function<void()> callback);
		void Draw() override;

	private:
		std::function<void()> m_Callback;
	};

	class Group : public UIItem
	{
	public:
		explicit Group(const std::string& name, int items_per_row = 7);
		void Draw() override;

		void AddItem(std::shared_ptr<UIItem>&& item)
		{
			m_Items.push_back(std::move(item));
		}

	private:
		std::string m_Name;
		int m_ItemsPerRow;
		std::vector<std::shared_ptr<UIItem>> m_Items;
	};

	class InputTextWithHint : public UIItem
	{
	public:
		explicit InputTextWithHint(std::string label, std::string hint, std::string* buf, int flags = ImGuiInputTextFlags_None, std::function<void()> cb = nullptr, ImGuiInputTextCallback inputCallback = nullptr);
		void Draw() override;

	private:
		std::string m_Id;
		std::string m_Hint;
		std::string* m_Buf;
		int m_Flags;
		std::function<void()> m_Callback;
		ImGuiInputTextCallback m_ImGuiInputTextCallback;
	};

	class ColorCommandItem : public UIItem
	{
	public:
		explicit ColorCommandItem(joaat_t id, std::optional<std::string> label_override = std::nullopt);
		void Draw() override;

	private:
		ColorCommand* m_Command;
		std::optional<std::string> m_LabelOverride;
	};

	class StringCommandItem : public UIItem
	{
	public:
		explicit StringCommandItem(joaat_t id, std::optional<std::string> label_override = std::nullopt);
		void Draw() override;

	private:
		StringCommand* m_Command;
		std::optional<std::string> m_LabelOverride;
		std::optional<std::string> m_CurrentInput = std::nullopt;
	};

	class TabItem : public UIItem
	{
	public:
		explicit TabItem(const std::string& name);
		void Draw() override;

		void AddItem(std::shared_ptr<UIItem>&& item)
		{
			m_Items.push_back(std::move(item));
		}

	private:
		std::string m_Name;
		std::vector<std::shared_ptr<UIItem>> m_Items;
	};

	class TabBarItem : public UIItem
	{
	public:
		explicit TabBarItem(const std::string& id);
		void Draw() override;

		void AddItem(std::shared_ptr<TabItem>&& tab)
		{
			m_Tabs.push_back(std::move(tab));
		}

	private:
		std::string m_Id;
		std::vector<std::shared_ptr<TabItem>> m_Tabs;
	};

	class CollapsingHeaderItem : public UIItem
	{
	public:
		explicit CollapsingHeaderItem(const std::string& name);
		void Draw() override;

		void AddItem(std::shared_ptr<UIItem>&& item)
		{
			m_Items.push_back(std::move(item));
		}

	private:
		std::string m_Name;
		std::vector<std::shared_ptr<UIItem>> m_Items;
	};
}
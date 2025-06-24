#include "UIManager.hpp"
#include "game/pointers/Pointers.hpp"
#include "game/frontend/Menu.hpp"
#include "core/commands/ListCommand.hpp"

namespace YimMenu::Features
{
	static const std::vector<std::pair<int, const char*>> g_StyleOptions = {
		{0, "Classic"},
		{1, "Modern"},
		{2, "Modern (Vertical)"},
	};

	// Expose as global reference so other code can use it
	static ListCommand _StyleSelector{
		"styleselector",
		"UI Style",
		"Choose the UI style",
		g_StyleOptions,
		0};
}

namespace YimMenu
{
	void UIManager::AddSubmenuImpl(const std::shared_ptr<Submenu>&& submenu)
	{
		if (!m_ActiveSubmenu)
			m_ActiveSubmenu = submenu;

		m_Submenus.push_back(std::move(submenu));
	}

	void UIManager::SetActiveSubmenuImpl(const std::shared_ptr<Submenu> submenu)
	{
		m_ActiveSubmenu = submenu;
	}

	void UIManager::DrawImpl()
	{
		int selectedIndex = Features::_StyleSelector.GetState();

		// Render the selected theme based on the index, append when adding new themes
		switch (static_cast<UITheme>(selectedIndex))
		{
		case UITheme::Classic:
			RenderClassicTheme();
			break;
		case UITheme::Modern:
			RenderModernTheme();
			break;
		case UITheme::ModernV:
			RenderModernVTheme();
			break;
		default:
			RenderClassicTheme(); // Default theme
			break;
		}
	}

	std::shared_ptr<Submenu> UIManager::GetActiveSubmenuImpl()
	{
		return m_ActiveSubmenu;
	}

	std::shared_ptr<Category> UIManager::GetActiveCategoryImpl()
	{
		if (m_ActiveSubmenu)
		{
			return m_ActiveSubmenu->GetActiveCategory();
		}

		return nullptr;
	}
}
#pragma once
#include "Category.hpp"
#include "Submenu.hpp"
#include "core/frontend/manager/styles/Themes.hpp"

namespace YimMenu
{
	// Enum to represent different UI themes, append when adding new themes
	enum class UITheme
	{
		Classic = 0,
		Modern,
		ModernV,
	};

	class UIManager
	{
	public:
		static void AddSubmenu(const std::shared_ptr<Submenu>&& submenu)
		{
			GetInstance().AddSubmenuImpl(std::move(submenu));
		}

		static void SetActiveSubmenu(const std::shared_ptr<Submenu> submenu)
		{
			GetInstance().SetActiveSubmenuImpl(submenu);
		}

		static void Draw()
		{
			GetInstance().DrawImpl();
		}

		static std::shared_ptr<Submenu> GetActiveSubmenu()
		{
			return GetInstance().GetActiveSubmenuImpl();
		}

		static std::shared_ptr<Category> GetActiveCategory()
		{
			return GetInstance().GetActiveCategoryImpl();
		}

		static void SetOptionsFont(ImFont* font)
		{
			GetInstance().m_OptionsFont = font;
		}

		static bool ShowingContentWindow()
		{
			return GetInstance().m_ShowContentWindow;
		}

		static void SetShowContentWindow(bool show)
		{
			GetInstance().m_ShowContentWindow = show;
		}

		static const std::vector<std::shared_ptr<Submenu>>& GetSubmenus()
		{
			return GetInstance().m_Submenus;
		}

		static ImFont* GetOptionsFont()
		{
			return GetInstance().m_OptionsFont;
		}

	private:
		static inline UIManager& GetInstance()
		{
			static UIManager instance;
			return instance;
		}

		void AddSubmenuImpl(const std::shared_ptr<Submenu>&& submenu);
		void SetActiveSubmenuImpl(const std::shared_ptr<Submenu> submenu);
		void DrawImpl();
		std::shared_ptr<Submenu> GetActiveSubmenuImpl();
		std::shared_ptr<Category> GetActiveCategoryImpl();

		std::shared_ptr<Submenu> m_ActiveSubmenu;
		std::vector<std::shared_ptr<Submenu>> m_Submenus;

		ImFont* m_OptionsFont = nullptr;
		bool m_ShowContentWindow = true;
	};
}

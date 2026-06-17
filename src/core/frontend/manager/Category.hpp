#pragma once
#include "UIItem.hpp"

namespace YimMenu
{
	class Category
	{
	public:
		constexpr Category(std::string_view name) :
		    m_Name(name)
		{
		}

		void AddItem(std::shared_ptr<UIItem>&& item)
		{
			m_Items.push_back(std::move(item));
		}

		void PrependItem(std::shared_ptr<UIItem>&& item)
		{
			m_Items.insert(m_Items.begin(), std::move(item));
		}

		void RemoveItem(const std::shared_ptr<UIItem>& item)
		{
			std::erase(m_Items, item);
		}

		const std::vector<std::shared_ptr<UIItem>>& GetItems() const
		{
			return m_Items;
		}

		void Draw();
		int GetLength();

	private:
		std::vector<std::shared_ptr<UIItem>> m_Items;
		std::optional<int> m_Length;

	public:
		std::string m_Name;
	};
}
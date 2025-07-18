#include "Items.hpp"
#include "core/commands/Command.hpp"
#include "core/commands/Commands.hpp"
#include "core/commands/BoolCommand.hpp"
#include "core/frontend/widgets/toggle/imgui_toggle.hpp"

namespace YimMenu
{
	ConditionalItem::ConditionalItem(joaat_t bool_cmd_id, std::shared_ptr<UIItem> to_draw, bool negate) :
		m_Condition(Commands::GetCommand<BoolCommand>(bool_cmd_id)),
		m_ConditionFn(nullptr),
		m_Item(to_draw),
		m_Negate(negate)
	{
	}

	ConditionalItem::ConditionalItem(std::function<bool()> condition_fn, std::shared_ptr<UIItem> to_draw, bool negate) :
		m_Condition(nullptr),
		m_ConditionFn(condition_fn),
		m_Item(to_draw),
		m_Negate(negate)
	{
	}

	void ConditionalItem::Draw()
	{
		if (CanDraw())
			m_Item->Draw();
	}

	bool ConditionalItem::CanDraw()
	{
		if (m_Condition)
			return m_Condition->GetState() ^ m_Negate;
		else if (m_ConditionFn)
			return m_ConditionFn() ^ m_Negate;

		return false;
	}
}
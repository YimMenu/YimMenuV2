#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaUtils.hpp"
#include "core/scripting/LatentFunction.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "game/pointers/Pointers.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/Scripts.hpp"
#include "types/netshop/CNetShopTransaction.hpp"
#include "game/backend/AnticheatBypass.hpp"

namespace YimMenu::Lua
{
	struct BasketItem
	{
		std::uint32_t m_PrimaryItem;
		std::uint32_t m_SecondaryItem;
		int m_Value;
		int m_StatValue;
		int m_Quantity;
	};

	struct BasketTransaction
	{
		std::uint32_t m_Category;
		std::uint32_t m_Action;
		std::vector<BasketItem> m_Items;
	};

	const std::unordered_set<std::uint32_t> BANNED_SERVICES =
	{
	        "SERVICE_EARN_DEBUG"_J,
	        "SERVICE_EARN_JBONUS"_J,
	        "SERVICE_EARN_JBONUS_MODEL"_J,
	        "SERVICE_EARN_JBONUS_NO_DEATH"_J,
	        "SERVICE_EARN_JBONUS_NO_FALL"_J,
	        "SERVICE_EARN_JBONUS_NOT_SEEN"_J,
	        "SERVICE_EARN_JBONUS_SE"_J,
	        "SERVICE_EARN_EVOLVE"_J,
	        "SERVICE_EARN_IMPULSE"_J,
	};

	static bool IsCategoryService(std::uint32_t hash)
	{
		return hash == "CATEGORY_SERVICE"_J || hash == "CATEGORY_SERVICE_WITH_LIMIT"_J || hash == "CATEGORY_SERVICE_WITH_THRESHOLD"_J;
	}

	// but can be used for basket as well
	static bool IsActionService(std::uint32_t hash)
	{
		return hash == "NET_SHOP_ACTION_EARN"_J || hash == "NET_SHOP_ACTION_SPEND"_J;
	}

	class Transactions : LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

		static int BasketAddItem(lua_State* state)
		{
			auto& transaction = GetObject<BasketTransaction>(state, 1);

			if (transaction.m_Items.size() >= 70)
				luaL_error(state, "Too many items in basket");

			BasketItem item{};
			item.m_PrimaryItem = GetHashArgument(state, 2);
			item.m_SecondaryItem = lua_isnoneornil(state, 3) ? 0 : GetHashArgument(state, 3);
			item.m_Value = luaL_checkinteger(state, 4);
			item.m_StatValue = luaL_checkinteger(state, 5);
			item.m_Quantity = luaL_checkinteger(state, 6);

			transaction.m_Items.push_back(item);

			return 0;
		}

		static int BasketRun(lua_State* state)
		{
			int txn_id = 0;
			CNetShopTransaction* txn = nullptr;

			Scripts::RunAsScript(Scripts::FindScriptThread("shop_controller"_J), [&txn_id, &txn, state] {
				auto& basket = GetObject<BasketTransaction>(state, 1);

				if (NETSHOPPING::NET_GAMESERVER_BASKET_IS_ACTIVE())
					NETSHOPPING::NET_GAMESERVER_BASKET_END();

				if (!NETSHOPPING::NET_GAMESERVER_BASKET_START(&txn_id, basket.m_Category, basket.m_Action, 4))
				{
					NETSHOPPING::NET_GAMESERVER_BASKET_END();
					return;
				}

				for (const auto& item : basket.m_Items)
				{
					struct NETSHOPPING_BASKET_ITEM
					{
						SCR_HASH PrimaryHash;
						SCR_HASH SecondaryHash;
						SCR_INT Value;
						SCR_INT StatValue;
					};
					static_assert(sizeof(NETSHOPPING_BASKET_ITEM) == 4 * 8);

					NETSHOPPING_BASKET_ITEM scr_item{};
					scr_item.PrimaryHash = item.m_PrimaryItem;
					scr_item.SecondaryHash = item.m_SecondaryItem;
					scr_item.Value = item.m_Value;
					scr_item.StatValue = item.m_StatValue;

					if (!NETSHOPPING::NET_GAMESERVER_BASKET_ADD_ITEM(&scr_item, item.m_Quantity))
					{
						NETSHOPPING::NET_GAMESERVER_BASKET_END();
						return;
					}
				}

				if (!NETSHOPPING::NET_GAMESERVER_CHECKOUT_START(txn_id))
				{
					NETSHOPPING::NET_GAMESERVER_BASKET_END();
					return;
				}

				txn = Pointers.GetActiveBasket(*Pointers.TransactionMgr, &txn_id);
			});

			if (!txn || !txn->m_Running)
			{
				lua_pushboolean(state, false);
				return 1;
			}

			while (txn->m_Status == 0 || txn->m_Status == 1)
				ScriptMgr::Yield();

			if (txn->m_Status == 3)
			{
			    lua_pushboolean(state, true);
			    return 1;
			}

			lua_pushboolean(state, false);
			return 1;
		}

		static int CreateBasket(lua_State* state)
		{
			auto category = GetHashArgument(state, 1);
			auto action = GetHashArgument(state, 2);
			auto transaction = CreateObject<BasketTransaction>(state);

			transaction->m_Category = category;
			transaction->m_Action = action;
			transaction->m_Items = {};

			return 1;
		}

		// fire and forget
		static int RunService(lua_State* state)
		{
			auto category = GetHashArgument(state, 1);
			auto action = GetHashArgument(state, 2);
			auto item = GetHashArgument(state, 3);
			auto value = luaL_checkinteger(state, 4);

			// run some basic sanity checks on the parameters
			if (BANNED_SERVICES.contains(item))
				luaL_error(state, "This item hash is not allowed to avoid bans");

			if (!IsCategoryService(category))
				luaL_argerror(state, 1, "Invalid category");

			if (!IsActionService(action))
				luaL_argerror(state, 2, "Invalid action");

			Scripts::RunAsScript(Scripts::FindScriptThread("shop_controller"_J), [category, action, item, value, state] {
				int txn_id;

				if (NETSHOPPING::NET_GAMESERVER_BASKET_IS_ACTIVE())
					NETSHOPPING::NET_GAMESERVER_BASKET_END();

				if (!NETSHOPPING::NET_GAMESERVER_BEGIN_SERVICE(&txn_id, category, item, action, value, 4))
				{
					NETSHOPPING::NET_GAMESERVER_BASKET_END();
					lua_pushboolean(state, false);
					return;
				}

				if (!NETSHOPPING::NET_GAMESERVER_CHECKOUT_START(txn_id))
				{
					NETSHOPPING::NET_GAMESERVER_BASKET_END();
					lua_pushboolean(state, false);
					return;
				}

				lua_pushboolean(state, true);
				return;
			});

			return 1; // true = success, false if not
		}

		static int CanUseTransactions(lua_State* state)
		{
			lua_pushboolean(state, !AnticheatBypass::IsFSLProvidingLocalSaves() && NETSHOPPING::NET_GAMESERVER_CATALOG_IS_VALID());
			return 1;
		}

		static int GC(lua_State* state)
		{
			auto& self = GetObject<BasketTransaction>(state, 1);
			self.~BasketTransaction();
			return 0;
		}

		virtual void Register(lua_State* state) override
		{
			luaL_newmetatable(state, "BasketTransaction");
			{
				SetFunction(state, GC, "__gc");

				lua_newtable(state);
				{
					SetFunction(state, BasketAddItem, "add_item");
					SetFunction(state, LatentFunction<BasketRun>, "run");
				}
				lua_setfield(state, -2, "__index"); // prototype
			}
			Metatable<BasketTransaction>::Register(state);

			lua_newtable(state);
			SetFunction(state, RunService, "run_service");
			SetFunction(state, CreateBasket, "create_basket");
			SetFunction(state, CanUseTransactions, "can_use_transactions");
			lua_setglobal(state, "transactions");
		}
	};

	Transactions _Transactions;
}

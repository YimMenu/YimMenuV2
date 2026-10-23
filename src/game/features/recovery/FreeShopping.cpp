#include "core/commands/BoolCommand.hpp"
#include "game/backend/NativeHooks.hpp"
#include "game/gta/Natives.hpp"
#include "types/netshop/netCatalog.hpp"
#include "game/backend/ScriptPatches.hpp"

namespace YimMenu::Features
{
	struct BASKET_ITEM_DATA
	{
		SCR_HASH Key;
		SCR_HASH Item;
		SCR_INT Price;
		SCR_INT StatValue;
	};
	static_assert(SCR_SIZEOF(BASKET_ITEM_DATA) == 4);


	constexpr joaat_t FreePurchaseCoupon = "PO_COUPON_CAR_XMAS2017"_J;
	constexpr int CasinoInteriorId = 275201;


	constexpr joaat_t DiscountModifiers[] = {
	    "PM_CARMOD_BUYNOW"_J,
	    "PM_CARMOD_TUNER_OWNER_DISCOUNT"_J,
	    "PM_CARMOD_VINEWOOD_GARAGE_DISCOUNT"_J,
	    "PM_CLOTHING_BIN"_J,
	    "PM_CLOTHING_DESIGNER_FEE"_J,
	    "PM_COUPON_ADD_VEH_MOD_P"_J,
	    "PM_COUPON_CAR_MEET_VEH_P"_J,
	    "PM_COUPON_CAR_SITE"_J,
	    "PM_COUPON_CASINO_BIKE_SITE"_J,
	    "PM_COUPON_CASINO_BOAT_SITE"_J,
	    "PM_COUPON_CASINO_CAR_SITE"_J,
	    "PM_COUPON_CASINO_CAR_SITE2"_J,
	    "PM_COUPON_CASINO_MIL_SITE"_J,
	    "PM_COUPON_CASINO_PLANE_SITE"_J,
	    "PM_COUPON_MIL_SITE"_J,
	    "PM_COUPON_PLANE_SITE"_J,
	    "PM_TATTOO_DISCOUNT_MANSION"_J,
	    "PM_WEAPON_DISCOUNT_BRONZE_DRIVEBY"_J,
	    "PM_WEAPON_DISCOUNT_BRONZE_HEADSHOT"_J,
	    "PM_WEAPON_DISCOUNT_BRONZE_KILLS"_J,
	    "PM_WEAPON_DISCOUNT_BRONZE_MEDAL"_J,
	    "PM_WEAPON_DISCOUNT_FIXER_ARMORY"_J,
	    "PM_WEAPON_DISCOUNT_GOLD_DRIVEBY"_J,
	    "PM_WEAPON_DISCOUNT_GOLD_HEADSHOT"_J,
	    "PM_WEAPON_DISCOUNT_GOLD_KILLS"_J,
	    "PM_WEAPON_DISCOUNT_GOLD_MEDAL"_J,
	    "PM_WEAPON_DISCOUNT_GUN_VAN_0_0"_J,
	    "PM_WEAPON_DISCOUNT_GUN_VAN_0_1"_J,
	    "PM_WEAPON_DISCOUNT_GUN_VAN_0_2"_J,
	    "PM_WEAPON_DISCOUNT_GUN_VAN_0_3"_J,
	    "PM_WEAPON_DISCOUNT_GUN_VAN_0_4"_J,
	    "PM_WEAPON_DISCOUNT_GUN_VAN_0_5"_J,
	    "PM_WEAPON_DISCOUNT_GUN_VAN_0_6"_J,
	    "PM_WEAPON_DISCOUNT_GUN_VAN_0_7"_J,
	    "PM_WEAPON_DISCOUNT_GUN_VAN_0_8"_J,
	    "PM_WEAPON_DISCOUNT_GUN_VAN_0_9"_J,
	    "PM_WEAPON_DISCOUNT_GUN_VAN_1_0"_J,
	    "PM_WEAPON_DISCOUNT_GUN_VAN_1_1"_J,
	    "PM_WEAPON_DISCOUNT_GUN_VAN_1_2"_J,
	    "PM_WEAPON_DISCOUNT_GUN_VAN_1_3"_J,
	    "PM_WEAPON_DISCOUNT_GUN_VAN_1_4"_J,
	    "PM_WEAPON_DISCOUNT_GUN_VAN_2_0"_J,
	    "PM_WEAPON_DISCOUNT_GUN_VAN_2_1"_J,
	    "PM_WEAPON_DISCOUNT_GUN_VAN_2_2"_J,
	    "PM_WEAPON_DISCOUNT_GUN_VAN_2_3"_J,
	    "PM_WEAPON_DISCOUNT_GUN_VAN_2_4"_J,
	    "PM_WEAPON_DISCOUNT_MANSION_ARMORY"_J,
	    "PM_WEAPON_DISCOUNT_PLAT_DRIVEBY"_J,
	    "PM_WEAPON_DISCOUNT_PLAT_HEADSHOT"_J,
	    "PM_WEAPON_DISCOUNT_PLAT_KILLS"_J,
	    "PM_WEAPON_DISCOUNT_SILVER_DRIVEBY"_J,
	    "PM_WEAPON_DISCOUNT_SILVER_HEADSHOT"_J,
	    "PM_WEAPON_DISCOUNT_SILVER_KILLS"_J,
	    "PM_WEAPON_DISCOUNT_SILVER_MEDAL"_J,
	    "PM_WEAPON_PIM_AMMO_INCREASE"_J
	};

	struct BasketContext
	{
		joaat_t Category = 0;
		joaat_t Action = 0;
	};

	BasketContext _BasketContext{};


	struct CatalogCandidate
	{
		joaat_t Hash{};
		int Price{};
	};

	static bool IsPropertyAction(joaat_t action)
	{
		return action == "NET_SHOP_ACTION_BUY_PROPERTY"_J
		    || action == "NET_SHOP_ACTION_BUY_WAREHOUSE"_J;
	}


	static bool IsWarehouseCategory(joaat_t category)
	{
		return category == "CATEGORY_WAREHOUSE"_J
		    || category == "CATEGORY_INVENTORY_WAREHOUSE"_J
		    || category == "CATEGORY_WAREHOUSE_INTERIOR"_J
		    || category == "CATEGORY_INVENTORY_WAREHOUSE_INTERIOR"_J;
	}

	static bool IsDiscountModifier(joaat_t itemId)
	{
		return std::ranges::contains(DiscountModifiers, itemId);
	}

	static bool IsPlayerInCasino()
	{
		return INTERIOR::GET_INTERIOR_FROM_ENTITY(
		           PLAYER::PLAYER_PED_ID())
		    == CasinoInteriorId;
	}

	static std::optional<std::int32_t> GetStatValue(joaat_t hash)
	{
		auto* catalog = Pointers.NetCatalog;
		if (!catalog)
			return std::nullopt;

		std::optional<std::int32_t> result;
		catalog->ForEachItem([&](const rage::netCatalogBaseItem& entry) {
			if (!result && entry.m_Hash == hash)
				result = entry.m_StatValue;
		});
		return result;
	}

	static std::optional<CatalogCandidate> FindCheapestEntry(
	    std::int32_t statValue, bool warehouseOnly)
	{
		auto* catalog = Pointers.NetCatalog;
		if (!catalog)
			return std::nullopt;

		std::optional<CatalogCandidate> best;
		catalog->ForEachItem([&](const rage::netCatalogBaseItem& entry) {
			if (entry.m_Hash == 0 || entry.m_StatValue != statValue || entry.m_Price < 0)
				return;

			if (warehouseOnly && !IsWarehouseCategory(entry.m_CategoryHash))
				return;

			if (!best || entry.m_Price < best->Price)
				best = CatalogCandidate{entry.m_Hash, entry.m_Price};
		});
		return best;
	}


	static void PropertyReplacement(BASKET_ITEM_DATA& item, int originalPrice)
	{
		const auto statValue = GetStatValue(
		    static_cast<joaat_t>(item.Item));
		if (!statValue)
			return;

		std::optional<CatalogCandidate> candidate;
		if (_BasketContext.Action == "NET_SHOP_ACTION_BUY_WAREHOUSE"_J)
			candidate = FindCheapestEntry(*statValue, true);

		if (!candidate || candidate->Price >= originalPrice)
			candidate = FindCheapestEntry(*statValue, false);

		if (candidate)
		{
			item.Item = candidate->Hash;
			item.Price = candidate->Price;
		}
	}



	static void NetGameServerGetPriceHook(rage::scrNativeCallContext* ctx);
	static void NetGameServerBasketStartHook(rage::scrNativeCallContext* ctx);
	static void NetGameServerBasketAddItemHook(rage::scrNativeCallContext* ctx);
	static void UseFakeMPCashHook(rage::scrNativeCallContext* ctx);
	static void ChangeFakeMPCashHook(rage::scrNativeCallContext* ctx);
	static void NetworkCanSpendMoneyHook(rage::scrNativeCallContext* ctx);

	class FreeShopping : public BoolCommand
	{
		using BoolCommand::BoolCommand;

		ScriptPatch m_PenthouseScriptPatch{};
		ScriptPatch m_CasinoScriptPatch{};

		virtual void OnEnable() override
		{
			static auto initHooks = []() {
				NativeHooks::AddHook(NativeHooks::ALL_SCRIPTS,
				    NativeIndex::NETWORK_CAN_SPEND_MONEY,
				    &NetworkCanSpendMoneyHook);
				NativeHooks::AddHook(NativeHooks::ALL_SCRIPTS,
				    NativeIndex::NET_GAMESERVER_GET_PRICE,
				    &NetGameServerGetPriceHook);
				NativeHooks::AddHook(NativeHooks::ALL_SCRIPTS,
				    NativeIndex::NET_GAMESERVER_BASKET_START,
				    &NetGameServerBasketStartHook);
				NativeHooks::AddHook(NativeHooks::ALL_SCRIPTS,
				    NativeIndex::NET_GAMESERVER_BASKET_ADD_ITEM,
				    &NetGameServerBasketAddItemHook);
				NativeHooks::AddHook(NativeHooks::ALL_SCRIPTS,
				    NativeIndex::USE_FAKE_MP_CASH,
				    &UseFakeMPCashHook);
				NativeHooks::AddHook(NativeHooks::ALL_SCRIPTS,
				    NativeIndex::CHANGE_FAKE_MP_CASH,
				    &ChangeFakeMPCashHook);
				return true;
			}();

			if (!m_PenthouseScriptPatch)
			{
				m_PenthouseScriptPatch = ScriptPatches::AddPatch(
				    "am_mp_casino_apartment"_J,
				    ScriptPointer("PenthouseDecorCashOnly", "37 03 41 0C 71 5C 81 00 38 00 25 11 2C 08 00 EA"),
				    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00});
			}

			m_PenthouseScriptPatch->Enable();

			if (!m_CasinoScriptPatch)
			{
				m_CasinoScriptPatch = ScriptPatches::AddPatch(
				    "am_mp_casino"_J,
				    ScriptPointer("SkipChipTransaction", "38 00 2F 74 82 06 56 3C 00 38 00 78 5D 7E F3 24"),
				    {0x72, 0x00, 0x00, 0x00, 0x00});
			}

			m_CasinoScriptPatch->Enable();
		}
		virtual void OnDisable() override
		{
			if (m_PenthouseScriptPatch)
				m_PenthouseScriptPatch->Disable();
			if (m_CasinoScriptPatch)
				m_CasinoScriptPatch->Disable();
		}
	};


	static FreeShopping _FreeShopping{
	    "freeshopping",
	    "Free Shopping",
	    "Allows you to buy everything for free."};


    static void NetGameServerGetPriceHook(rage::scrNativeCallContext* ctx)
	{
		const auto categoryHash = ctx->GetArg<joaat_t>(1);

		if (_FreeShopping.GetState() && categoryHash == "CATEGORY_CLOTH"_J && IsPlayerInCasino())
		{
			ctx->SetReturnValue(0);
			return;
		}

		NativeInvoker::GetNativeHandler(
		    NativeIndex::NET_GAMESERVER_GET_PRICE)(ctx);
	}

	static void NetGameServerBasketStartHook(rage::scrNativeCallContext* ctx)
	{
		_BasketContext.Category = ctx->GetArg<joaat_t>(1);
		_BasketContext.Action = ctx->GetArg<joaat_t>(2);

		NativeInvoker::GetNativeHandler(
		    NativeIndex::NET_GAMESERVER_BASKET_START)(ctx);
	}


	static void NetGameServerBasketAddItemHook(rage::scrNativeCallContext* ctx)
	{
		auto* item = ctx->GetArg<BASKET_ITEM_DATA*>(0);
		const int quantity = ctx->GetArg<int>(1);

		if (!item)
		{
			ctx->SetReturnValue(FALSE);
			return;
		}

		const auto addItem = [quantity](BASKET_ITEM_DATA* entry) -> BOOL {
			return NETSHOPPING::NET_GAMESERVER_BASKET_ADD_ITEM(entry, quantity);
		};

		const auto forward = [&](BASKET_ITEM_DATA* entry) {
			ctx->SetReturnValue(addItem(entry));
		};

		if (!_FreeShopping.GetState() || _BasketContext.Category == "CATEGORY_CASINO_CHIPS"_J)
		{
			forward(item);
			return;
		}

		const joaat_t itemId = static_cast<joaat_t>(item->Key);
		const int originalPrice = item->Price;

		if (itemId == "SERVICE_SPEND_STYLIST_FEE"_J)
		{
			ctx->SetReturnValue(TRUE);
			return;
		}

		if (originalPrice > 0 && IsPropertyAction(_BasketContext.Action))


        if (_FreeShopping.GetState() && IsPropertyAction(_BasketContext.Action) && originalPrice > 0)
		{
			PropertyReplacement(*item, originalPrice);
			forward(item);
			return;
		}

		if (IsDiscountModifier(itemId))
		{
			ctx->SetReturnValue(TRUE);
			return;
		}

		const bool isCasinoClothing =
		    _BasketContext.Category == "CATEGORY_CLOTH"_J && IsPlayerInCasino();

		const bool applyCoupon = originalPrice > 0 || isCasinoClothing;

		if (applyCoupon)
			item->Price = 0;

		const BOOL itemAdded = addItem(item);

		if (!applyCoupon || !itemAdded)
		{
			ctx->SetReturnValue(itemAdded);
			return;
		}

		BASKET_ITEM_DATA coupon{};
		coupon.Key = FreePurchaseCoupon;
		coupon.Item = itemId;
		coupon.Price = 0;
		coupon.StatValue = item->StatValue;

		ctx->SetReturnValue(addItem(&coupon));

	}


	static void UseFakeMPCashHook(rage::scrNativeCallContext* ctx)
	{
		if (_FreeShopping.GetState())
			return;

		HUD::USE_FAKE_MP_CASH(ctx->GetArg<BOOL>(0));
	}

	static void ChangeFakeMPCashHook(rage::scrNativeCallContext* ctx)
	{
		if (_FreeShopping.GetState())
			return;

		HUD::CHANGE_FAKE_MP_CASH(ctx->GetArg<int>(0), ctx->GetArg<int>(1));
	}
	
	static void NetworkCanSpendMoneyHook(rage::scrNativeCallContext* ctx)
	{
		if (_FreeShopping.GetState())
		{
			ctx->SetReturnValue(TRUE);
			return;
		}

		NativeInvoker::GetNativeHandler(
		    NativeIndex::NETWORK_CAN_SPEND_MONEY)(ctx);
	}
}

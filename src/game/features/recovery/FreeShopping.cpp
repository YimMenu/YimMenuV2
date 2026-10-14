#include "core/commands/BoolCommand.hpp"
#include "game/backend/NativeHooks.hpp"
#include "game/gta/Natives.hpp"
#include "types/netshop/netCatalog.hpp"
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


	static bool IsPropertyAction(joaat_t action)
	{
		return action == "NET_SHOP_ACTION_BUY_PROPERTY"_J
		    || action == "NET_SHOP_ACTION_BUY_WAREHOUSE"_J;
	}

    static int GetStatValueFromHash(joaat_t itemHash)
	{
		auto* catalog = Pointers.NetCatalog;
		if (!catalog)
			return -1;

		int result = -1;

		catalog->ForEachItem([&](const rage::netCatalogBaseItem& item) {
			if (result != -1)
				return;
			if (item.m_Hash == itemHash)
				result = item.m_StatValue;
		});

		return result;
	}


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
	    "PM_WEAPON_PIM_AMMO_INCREASE"_J};

	static bool IsDiscountModifier(joaat_t itemId)
	{
		return std::ranges::contains(DiscountModifiers, itemId);
	}


	static joaat_t CurrentBasketAction = 0;
	static joaat_t CurrentBasketCategory = 0;


	static void NetGameServerBasketStartHook(rage::scrNativeCallContext* ctx);
	static void NetGameServerBasketAddItemHook(rage::scrNativeCallContext* ctx);
	static void UseFakeMPCashHook(rage::scrNativeCallContext* ctx);
	static void ChangeFakeMPCashHook(rage::scrNativeCallContext* ctx);

	class FreeShopping : public BoolCommand
	{
		using BoolCommand::BoolCommand;

		virtual void OnEnable() override
		{
			static auto initHooks = []() {
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
		}
	};

	static FreeShopping _FreeShopping{
	    "freeshopping",
	    "Free Shopping",
	    "Allows you to buy everything for free."};


	static void NetGameServerBasketStartHook(rage::scrNativeCallContext* ctx)
	{
		CurrentBasketCategory = ctx->GetArg<joaat_t>(1);
		CurrentBasketAction = ctx->GetArg<joaat_t>(2);

		NativeInvoker::GetNativeHandler(
		    NativeIndex::NET_GAMESERVER_BASKET_START)(ctx);
	}


	static void NetGameServerBasketAddItemHook(rage::scrNativeCallContext* ctx)
	{
		auto itemData = ctx->GetArg<BASKET_ITEM_DATA*>(0);
		const int quantity = ctx->GetArg<int>(1);

		const auto itemId = static_cast<joaat_t>(itemData->Key);
		const int price = itemData->Price;


		auto callOriginal = [&](BASKET_ITEM_DATA* entry) -> BOOL {
			return NETSHOPPING::NET_GAMESERVER_BASKET_ADD_ITEM(entry, quantity);
		};

		const bool freeShopping = _FreeShopping.GetState();


		if (freeShopping && IsPropertyAction(CurrentBasketAction) && price > 0)
		{
			const int statValue = GetStatValueFromHash(static_cast<joaat_t>(itemData->Item));

			if (statValue >= 0)
			{
				auto* catalog = Pointers.NetCatalog;
				joaat_t bestHash = 0;
				int bestPrice = INT_MAX;

				catalog->ForEachItem([&](const rage::netCatalogBaseItem& entry) {
					if (entry.m_StatValue != statValue)
						return;
					if (entry.m_Price < 0)
						return;
					if (entry.m_Price >= bestPrice)
						return;
					bestHash = entry.m_Hash;
					bestPrice = entry.m_Price;
				});

				if (bestHash)
				{
					itemData->Item = bestHash;
					itemData->Price = bestPrice;
				}
			}

			ctx->SetReturnValue(callOriginal(itemData));
			return;
		}


		if (freeShopping && IsDiscountModifier(itemId))
		{
			ctx->SetReturnValue(TRUE);
			return;
		}


		const bool applyCoupon = freeShopping && price > 0;

		if (applyCoupon)
			itemData->Price = 0;

		const BOOL itemAdded = callOriginal(itemData);

		if (applyCoupon && itemAdded)
		{
			BASKET_ITEM_DATA couponData{};
			couponData.Key = FreePurchaseCoupon;
			couponData.Item = itemId;
			couponData.Price = 0;
			couponData.StatValue = itemData->StatValue;

			const BOOL couponAdded = callOriginal(&couponData);
			ctx->SetReturnValue(couponAdded);
			return;
		}

		ctx->SetReturnValue(itemAdded);
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
}
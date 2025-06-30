#include "StatEditor.hpp"
#include "core/backend/FiberPool.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/frontend/Notifications.hpp"
#include "core/frontend/widgets/imgui_colors.h"
#include "game/backend/AnticheatBypass.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/Scripts.hpp"
#include "game/pointers/Pointers.hpp"
#include "types/netshop/CNetShopTransaction.hpp"
#include "types/netshop/netCatalogBaseItem.hpp"

namespace YimMenu::Submenus
{
	constexpr std::array<std::pair<const char*, std::uint32_t>, 28> NET_SHOP_ACTIONS =
	    {{
	        {"ACQUIRE", "NET_SHOP_ACTION_ACQUIRE"_J},
	        {"ADD_CONTRABAND", "NET_SHOP_ACTION_ADD_CONTRABAND"_J},
	        {"ALLOT", "NET_SHOP_ACTION_ALLOT"_J}, // not used?
	                                              //  {"BONUS", "NET_SHOP_ACTION_BONUS"_J}, I bet someone would use this and get themselves banned
	        {"BUY_CASINO_CHIPS", "NET_SHOP_ACTION_BUY_CASINO_CHIPS"_J},
	        {"BUY_CONTRABAND_MISSION", "NET_SHOP_ACTION_BUY_CONTRABAND_MISSION"_J},
	        {"BUY_ITEM", "NET_SHOP_ACTION_BUY_ITEM"_J},
	        {"BUY_PROPERTY", "NET_SHOP_ACTION_BUY_PROPERTY"_J},
	        {"BUY_UNLOCK", "NET_SHOP_ACTION_BUY_UNLOCK"_J},
	        {"BUY_VEHICLE", "NET_SHOP_ACTION_BUY_VEHICLE"_J},
	        {"BUY_VEHICLE_MODS", "NET_SHOP_ACTION_BUY_VEHICLE_MODS"_J},
	        {"BUY_WAREHOUSE", "NET_SHOP_ACTION_BUY_WAREHOUSE"_J},
	        {"CREATE_PLAYER_APPEARANCE", "NET_SHOP_ACTION_CREATE_PLAYER_APPEARANCE"_J},
	        {"DELETE_CHAR", "NET_SHOP_ACTION_DELETE_CHAR"_J}, // not used
	        {"EARN", "NET_SHOP_ACTION_EARN"_J},
	        {"EARN_LIMITED_SERVICE", "NET_SHOP_ACTION_EARN_LIMITED_SERVICE"_J},
	        {"GIVE", "NET_SHOP_ACTION_GIVE"_J},
	        {"PURCH", "NET_SHOP_ACTION_PURCH"_J},
	        {"RECOUP", "NET_SHOP_ACTION_RECOUP"_J},
	        {"REMOVE_CONTRABAND", "NET_SHOP_ACTION_REMOVE_CONTRABAND"_J},
	        {"RESET_BUSINESS_PROGRESS", "NET_SHOP_ACTION_RESET_BUSINESS_PROGRESS"_J},
	        {"SELL_CASINO_CHIPS", "NET_SHOP_ACTION_SELL_CASINO_CHIPS"_J},
	        {"SELL_VEHICLE", "NET_SHOP_ACTION_SELL_VEHICLE"_J},
	        {"SPEND", "NET_SHOP_ACTION_SPEND"_J},
	        {"SPEND_LIMITED_SERVICE", "NET_SHOP_ACTION_SPEND_LIMITED_SERVICE"_J}, // not used
	        {"UPDATE_BUSINESS_GOODS", "NET_SHOP_ACTION_UPDATE_BUSINESS_GOODS"_J},
	        {"UPDATE_STORAGE_DATA", "NET_SHOP_ACTION_UPDATE_STORAGE_DATA"_J},
	        {"UPDATE_WAREHOUSE_VEHICLE", "NET_SHOP_ACTION_UPDATE_WAREHOUSE_VEHICLE"_J},
	        {"USE", "NET_SHOP_ACTION_USE"_J},
	    }};

	constexpr std::array<std::pair<const char*, std::uint32_t>, 60> NET_SHOP_CATEGORIES =
	    {{
	        {"BEARD", "CATEGORY_BEARD"_J},
	        {"BLUSHER", "CATEGORY_BLUSHER"_J},
	        {"CASINO_CHIP_REASON", "CATEGORY_CASINO_CHIP_REASON"_J},
	        {"CASINO_CHIPS", "CATEGORY_CASINO_CHIPS"_J},
	        {"CHEST_HAIR", "CATEGORY_CHEST_HAIR"_J},
	        {"CLOTH", "CATEGORY_CLOTH"_J},
	        {"CONTACTS", "CATEGORY_CONTACTS"_J},
	        {"CONTRABAND_FLAGS", "CATEGORY_CONTRABAND_FLAGS"_J},
	        {"CONTRABAND_MISSION", "CATEGORY_CONTRABAND_MISSION"_J},
	        {"CONTRABAND_QNTY", "CATEGORY_CONTRABAND_QNTY"_J},
	        {"CURRENCY_TYPE", "CATEGORY_CURRENCY_TYPE"_J},
	        {"DATA_STORAGE", "CATEGORY_DATA_STORAGE"_J},
	        {"DECORATION", "CATEGORY_DECORATION"_J},
	        {"EARN_CURRENCY", "CATEGORY_EARN_CURRENCY"_J},
	        {"EYEBROWS", "CATEGORY_EYEBROWS"_J},
	        {"FACEPAINT", "CATEGORY_FACEPAINT"_J},
	        {"HAIR", "CATEGORY_HAIR"_J},
	        {"INVENTORY_BEARD", "CATEGORY_INVENTORY_BEARD"_J},
	        {"INVENTORY_BLUSHER", "CATEGORY_INVENTORY_BLUSHER"_J},
	        {"INVENTORY_CHEST_HAIR", "CATEGORY_INVENTORY_CHEST_HAIR"_J},
	        {"INVENTORY_CONTACTS", "CATEGORY_INVENTORY_CONTACTS"_J},
	        {"INVENTORY_CONTRABAND_MISSION", "CATEGORY_INVENTORY_CONTRABAND_MISSION"_J},
	        {"INVENTORY_CURRENCY", "CATEGORY_INVENTORY_CURRENCY"_J},
	        {"INVENTORY_EYEBROWS", "CATEGORY_INVENTORY_EYEBROWS"_J},
	        {"INVENTORY_FACEPAINT", "CATEGORY_INVENTORY_FACEPAINT"_J},
	        {"INVENTORY_HAIR", "CATEGORY_INVENTORY_HAIR"_J},
	        {"INVENTORY_ITEM", "CATEGORY_INVENTORY_ITEM"_J}, // unused
	        {"INVENTORY_LIPSTICK", "CATEGORY_INVENTORY_LIPSTICK"_J},
	        {"INVENTORY_MKUP", "CATEGORY_INVENTORY_MKUP"_J},
	        {"INVENTORY_PRICE_PAID", "CATEGORY_INVENTORY_PRICE_PAID"_J},
	        {"INVENTORY_PROPERTY", "CATEGORY_INVENTORY_PROPERTIE"_J},
	        {"INVENTORY_PROPERTY_INTERIOR", "CATEGORY_INVENTORY_PROPERTY_INTERIOR"_J},
	        {"INVENTORY_VEHICLE", "CATEGORY_INVENTORY_VEHICLE"_J},
	        {"INVENTORY_VEHICLE_MOD", "CATEGORY_INVENTORY_VEHICLE_MOD"_J},
	        {"INVENTORY_WAREHOUSE", "CATEGORY_INVENTORY_WAREHOUSE"_J},
	        {"INVENTORY_WAREHOUSE_INTERIOR", "CATEGORY_INVENTORY_WAREHOUSE_INTERIOR"_J},
	        {"LIPSTICK", "CATEGORY_LIPSTICK"_J},
	        {"MART", "CATEGORY_MART"_J},
	        {"MKUP", "CATEGORY_MKUP"_J},
	        {"PRICE_MODIFIER", "CATEGORY_PRICE_MODIFIER"_J},
	        {"PRICE_OVERRIDE", "CATEGORY_PRICE_OVERRIDE"_J},
	        {"PROPERTY", "CATEGORY_PROPERTIE"_J}, // seriously how tf did "propertie" get past code reviews?
	        {"PROPERTY_INTERIOR", "CATEGORY_PROPERTY_INTERIOR"_J},
	        {"SERVICE", "CATEGORY_SERVICE"_J},
	        {"SERVICE_UNLOCKED", "CATEGORY_SERVICE_UNLOCKED"_J},
	        {"SERVICE_WITH_LIMIT", "CATEGORY_SERVICE_WITH_LIMIT"_J},
	        {"SERVICE_WITH_THRESHOLD", "CATEGORY_SERVICE_WITH_THRESHOLD"_J},
	        {"SYSTEM", "CATEGORY_SYSTEM"_J},
	        {"TATTOO", "CATEGORY_TATTOO"_J},
	        {"UNLOCK", "CATEGORY_UNLOCK"_J},
	        {"VEHICLE", "CATEGORY_VEHICLE"_J},
	        {"VEHICLE_MOD", "CATEGORY_VEHICLE_MOD"_J},
	        {"VEHICLE_UPGRADE", "CATEGORY_VEHICLE_UPGRADE"_J},
	        {"VENDING_MACHINE", "CATEGORY_VENDING_MACHINE"_J},
	        {"WAREHOUSE", "CATEGORY_WAREHOUSE"_J},
	        {"WAREHOUSE_INTERIOR", "CATEGORY_WAREHOUSE_INTERIOR"_J},
	        {"WAREHOUSE_VEHICLE_INDEX", "CATEGORY_WAREHOUSE_VEHICLE_INDEX"_J},
	        {"WEAPON", "CATEGORY_WEAPON"_J},
	        {"WEAPON_AMMO", "CATEGORY_WEAPON_AMMO"_J},
	        {"WEAPON_MOD", "CATEGORY_WEAPON_MOD"_J},
	    }};

	// more guardrails to prevent some stupid stuff
	const std::unordered_set<std::uint32_t> BANNED_ITEM_HASHES =
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

	static const char* CategoryNameFromHash(std::uint32_t hash)
	{
		for (auto& cat : NET_SHOP_CATEGORIES)
			if (cat.second == hash)
				return cat.first;

		return "UNKNOWN";
	}

	struct TransactionItemHash
	{
		char m_Name[128]{};
		std::uint32_t m_Hash;
		std::uint32_t m_IntendedCategory;
		int m_IntendedPrice;
		bool m_IsValid;
	};

	struct TransactionCategoryHash
	{
		const char* m_Name = nullptr;
		std::uint32_t m_Hash;
	};

	struct BasketItem
	{
		TransactionItemHash m_PrimaryItem;
		TransactionItemHash m_SecondaryItem;
		std::uint32_t m_Quantity = 1;
		int m_StatValue = 1;
		int m_Price;
	};

	struct TransactionInfo
	{
		enum class Type
		{
			BASKET,
			SERVICE
		};

		Type m_Type = Type::BASKET;
		TransactionCategoryHash m_Category{"PROPERTY", "CATEGORY_PROPERTIE"_J};
		TransactionCategoryHash m_Action{"BUY_PROPERTY", "NET_SHOP_ACTION_BUY_PROPERTY"_J};
		struct
		{
			std::vector<BasketItem> m_BasketItems = {BasketItem{}};
		} m_Basket;
		struct
		{
			TransactionItemHash m_Item;
			int m_Price;
		} m_Service;
	};

	static void ProcessTransaction(const TransactionInfo& info)
	{
		FiberPool::Push([&info] {
			int txn_id{-1};
			bool txn_failed{false};
			CNetShopTransaction* txn{nullptr};

			// set up transaction
			Scripts::RunAsScript(Scripts::FindScriptThread("shop_controller"_J), [&] {
				if (info.m_Type == TransactionInfo::Type::BASKET)
				{
					if (NETSHOPPING::NET_GAMESERVER_BASKET_IS_ACTIVE())
						NETSHOPPING::NET_GAMESERVER_BASKET_END();

					if (!NETSHOPPING::NET_GAMESERVER_BASKET_START(&txn_id, info.m_Category.m_Hash, info.m_Action.m_Hash, 4))
					{
						Notifications::Show("Transactions", "Failed to create basket", NotificationType::Error);
						txn_failed = true;
						NETSHOPPING::NET_GAMESERVER_BASKET_END();
						return;
					}

					struct NETSHOPPING_BASKET_ITEM
					{
						SCR_HASH PrimaryHash;
						SCR_HASH SecondaryHash;
						SCR_INT Value;
						SCR_INT StatValue;
					};
					static_assert(sizeof(NETSHOPPING_BASKET_ITEM) == 4 * 8);

					for (auto& item : info.m_Basket.m_BasketItems)
					{
						NETSHOPPING_BASKET_ITEM scr_item{};
						scr_item.PrimaryHash = item.m_PrimaryItem.m_Hash;
						scr_item.SecondaryHash = item.m_SecondaryItem.m_Hash;
						scr_item.Value = item.m_Price;
						scr_item.StatValue = item.m_StatValue;

						if (!NETSHOPPING::NET_GAMESERVER_BASKET_ADD_ITEM(&scr_item, item.m_Quantity))
						{
							Notifications::Show("Transactions",
							    std::format("Failed to add {} (x{}) to basket", item.m_PrimaryItem.m_Name, item.m_Quantity),
							    NotificationType::Error);
							txn_failed = true;
							NETSHOPPING::NET_GAMESERVER_BASKET_END();
							return;
						}
					}
				}
				else
				{
					if (!NETSHOPPING::NET_GAMESERVER_BEGIN_SERVICE(&txn_id, info.m_Category.m_Hash, info.m_Service.m_Item.m_Hash, info.m_Action.m_Hash, info.m_Service.m_Price, 4))
					{
						Notifications::Show("Transactions", "Failed to create service", NotificationType::Error);
						txn_failed = true;
						return;
					}
				}

				if (info.m_Type == TransactionInfo::Type::BASKET)
				{
					txn = Pointers.GetActiveBasket(*Pointers.TransactionMgr, &txn_id); // TODO: add support for services too
				}

				if (!NETSHOPPING::NET_GAMESERVER_CHECKOUT_START(txn_id))
				{
					Notifications::Show("Transactions", "Failed to begin checkout", NotificationType::Error);
					txn_failed = true;
					return;
				}
			});

			if (txn && txn->m_Running)
			{
				while (txn->m_Status == 0 || txn->m_Status == 1)
					ScriptMgr::Yield();

				if (txn->m_Status == 3)
				{
					Notifications::Show("Transactions", "Transaction complete", NotificationType::Success);
				}
				else
				{
					Notifications::Show("Transactions", "Transaction failed", NotificationType::Error);
				}
			}
		});
	}

	static bool HasGTAPlusMembership()
	{
		if (!NETWORK::NETWORK_HAS_SC_MEMBERSHIP_INFO())
			return false;

		struct SC_MEMBERSHIP_INFO
		{
			SCR_BOOL HasMembership;
			SCR_INT StartTime; // very likely, metric says "s" and "e"
			SCR_INT EndTime;
		};

		SC_MEMBERSHIP_INFO info{};
		NETWORK::NETWORK_GET_SC_MEMBERSHIP_INFO(&info);

		return info.HasMembership;
	}

	static int GetItemPrice(rage::netCatalogBaseItem* item)
	{
		if (item->m_MembershipPrice == -1 || !HasGTAPlusMembership())
			return item->m_Price;
		else
			return item->m_MembershipPrice;
	}

	// and only service
	static bool IsCategoryService(std::uint32_t hash)
	{
		return hash == "CATEGORY_SERVICE"_J || hash == "CATEGORY_SERVICE_WITH_LIMIT"_J || hash == "CATEGORY_SERVICE_WITH_THRESHOLD"_J;
	}

	// but can be used for basket as well
	static bool IsActionService(std::uint32_t hash)
	{
		return hash == "NET_SHOP_ACTION_EARN"_J || hash == "NET_SHOP_ACTION_SPEND"_J;
	}

	static bool IsPriceModifier(std::uint32_t hash)
	{
		return hash == "CATEGORY_PRICE_MODIFIER"_J || hash == "CATEGORY_PRICE_OVERRIDE"_J;
	}

	bool ShouldSwapItemParams(std::uint32_t hash)
	{
		switch (hash)
		{
		case "CATEGORY_INVENTORY_ITEM"_J:
		case "CATEGORY_INVENTORY_VEHICLE"_J:
		case "CATEGORY_INVENTORY_VEHICLE_MOD"_J:
		case "CATEGORY_INVENTORY_PROPERTIE"_J:
		case "CATEGORY_INVENTORY_BEARD"_J:
		case "CATEGORY_INVENTORY_MKUP"_J:
		case "CATEGORY_INVENTORY_HAIR"_J:
		case "CATEGORY_INVENTORY_EYEBROWS"_J:
		case "CATEGORY_INVENTORY_CHEST_HAIR"_J:
		case "CATEGORY_INVENTORY_CONTACTS"_J:
		case "CATEGORY_INVENTORY_FACEPAINT"_J:
		case "CATEGORY_INVENTORY_BLUSHER"_J:
		case "CATEGORY_INVENTORY_LIPSTICK"_J:
		case "CATEGORY_INVENTORY_PROPERTY_INTERIOR"_J:
		case "CATEGORY_INVENTORY_WAREHOUSE"_J:
		case "CATEGORY_INVENTORY_CONTRABAND_MISSION"_J:
		case "CATEGORY_CONTRABAND_MISSION"_J:
		case "CATEGORY_CONTRABAND_QNTY"_J:
		case "CATEGORY_INVENTORY_WAREHOUSE_INTERIOR"_J:
		case "CATEGORY_WAREHOUSE_VEHICLE_INDEX"_J:
			return true;
		}

		return false;
	}

	static void OnTransactionTypeChanged(TransactionInfo& info)
	{
		if (info.m_Type == TransactionInfo::Type::SERVICE)
		{
			if (!IsCategoryService(info.m_Category.m_Hash))
				info.m_Category = {"SERVICE", "CATEGORY_SERVICE"_J};
			if (!IsActionService(info.m_Action.m_Hash))
				info.m_Action = {"EARN", "NET_SHOP_ACTION_EARN"_J};
			info.m_Basket.m_BasketItems.clear();
		}
		else
		{
			if (IsCategoryService(info.m_Category.m_Hash))
				info.m_Category = {"PROPERTY", "NET_SHOP_ACTION_BUY_PROPERTY"_J};
			info.m_Basket.m_BasketItems.push_back({}); // ensure we always have one
		}
	}

	static void SetTransactionError(std::string_view message)
	{
		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Text, ImGui::Colors::Red.Value);
		ImGui::Text("%s", message.data());
		ImGui::PopStyleColor();
	}

	static void SetTransactionWarning(std::string_view message)
	{
		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Text, ImGui::Colors::Yellow.Value);
		ImGui::Text("%s", message.data());
		ImGui::PopStyleColor();
	}

	static bool EditTransactionItem(std::string_view label, TransactionInfo& info, TransactionItemHash& item, bool& is_valid, bool required = true, bool validate_category = true)
	{
		bool modified = false;

		ImGui::SetNextItemWidth(340.0f);
		if (
		    required ?
		        ImGui::InputText(label.data(), item.m_Name, sizeof(item.m_Name)) :
		        ImGui::InputTextWithHint(label.data(), "Optional", item.m_Name, sizeof(item.m_Name)))
		{
			item.m_Hash = Joaat(item.m_Name);
			if (auto cat_item = Pointers.GetCatalogItem(Pointers.NetCatalog, &item.m_Hash))
			{
				modified = true;
				item.m_IsValid = true;
				item.m_IntendedCategory = cat_item->m_CategoryHash;
				item.m_IntendedPrice = GetItemPrice(cat_item);
			}
			else
			{
				item.m_IsValid = false;
			}
		}

		bool empty = item.m_Name[0] == 0 && !required;

		if (!item.m_IsValid && !empty)
		{
			SetTransactionError("Item not found!");
			is_valid = false;
			return false;
		}

		// TODO: maybe not check this every tick?
		if (BANNED_ITEM_HASHES.contains(item.m_Hash))
		{
			SetTransactionError("This item has been blocked for your safety");
			is_valid = false;
			return false;
		}

		if (validate_category && !IsPriceModifier(item.m_IntendedCategory) && item.m_IntendedCategory != info.m_Category.m_Hash && !empty)
		{
			if (info.m_Type == TransactionInfo::Type::SERVICE)
			{
				SetTransactionError(std::format("Item category {} does not match txn category {}", CategoryNameFromHash(item.m_IntendedCategory), info.m_Category.m_Name));
				is_valid = false;
				return false;
			}
			else
			{
				SetTransactionWarning(std::format("Item category {} does not match txn category {}", CategoryNameFromHash(item.m_IntendedCategory), info.m_Category.m_Name));
			}
		}

		return modified;
	}

	static void RenderBasketEditor(TransactionInfo& info, bool& txn_valid)
	{
		std::optional<int> item_to_delete = std::nullopt;

		for (int i = 0; i < info.m_Basket.m_BasketItems.size(); i++)
		{
			auto& item = info.m_Basket.m_BasketItems[i];
			ImGui::PushID(i);
			if (ShouldSwapItemParams(info.m_Category.m_Hash))
			{
				if (EditTransactionItem("Item", info, item.m_SecondaryItem, txn_valid, true, false)) // TODO: validate if this corresponds to the correct non-inventory category
					item.m_Price = item.m_SecondaryItem.m_IntendedPrice;
				EditTransactionItem("Inventory Slot", info, item.m_PrimaryItem, txn_valid, true, true);
			}
			else
			{
				if (EditTransactionItem("Item", info, item.m_PrimaryItem, txn_valid, true, true))
					item.m_Price = item.m_PrimaryItem.m_IntendedPrice;
				EditTransactionItem("Secondary Item", info, item.m_SecondaryItem, txn_valid, false, false); // TODO: is this ever used outside of inventory stuff?
			}

			ImGui::SetNextItemWidth(180.0f);
			if (ImGui::InputScalar("Quantity", ImGuiDataType_U32, &item.m_Quantity))
			{
				if (item.m_Quantity == 0)
					item_to_delete = i; // assume the user wants this item gone
			}

			ImGui::SetNextItemWidth(180.0f);
			ImGui::InputInt("Price", &item.m_Price);

			ImGui::SetNextItemWidth(180.0f);
			ImGui::InputInt("Stat Value", &item.m_StatValue); // I'm not actually sure what this does ngl

			if (info.m_Basket.m_BasketItems.size() > 1 && ImGui::Button("Delete"))
				item_to_delete = i;
			ImGui::PopID();

			if (info.m_Basket.m_BasketItems.size() != (i + 1))
				ImGui::Separator();
		}

		if (item_to_delete.has_value())
			info.m_Basket.m_BasketItems.erase(std::next(info.m_Basket.m_BasketItems.begin(), *item_to_delete));

		if (ImGui::Button("Add Item"))
		{
			info.m_Basket.m_BasketItems.push_back({});
		}
	}

	static void RenderServiceEditor(TransactionInfo& info, bool& txn_valid)
	{
		if (EditTransactionItem("Item", info, info.m_Service.m_Item, txn_valid))
			info.m_Service.m_Price = info.m_Service.m_Item.m_IntendedPrice;
		if (info.m_Service.m_Item.m_IntendedPrice != 0 || info.m_Action.m_Hash != "NET_SHOP_ACTION_EARN"_J)
		{
			ImGui::SetNextItemWidth(180.0f);
			ImGui::InputInt("Price", &info.m_Service.m_Price);
			if (info.m_Service.m_Price > info.m_Service.m_Item.m_IntendedPrice && info.m_Action.m_Hash == "NET_SHOP_ACTION_EARN"_J)
			{
				SetTransactionError(std::format("Item price exceeds maximum allowed ({})", info.m_Service.m_Item.m_IntendedPrice));
				txn_valid = false;
			}
		}
	}

	std::shared_ptr<Category> BuildTransactionsMenu()
	{
		auto menu = std::make_shared<Category>("Transactions");
		auto normal = std::make_shared<Group>("Triggerer");

		normal->AddItem(std::make_unique<ImGuiItem>([] {
			if (!NativeInvoker::AreHandlersCached())
				return ImGui::TextDisabled("Natives not cached yet");

			if (AnticheatBypass::IsFSLProvidingLocalSaves())
				return ImGui::TextDisabled("Transactions are not supported with FSL local saves enabled");

			if (!NETSHOPPING::NET_GAMESERVER_CATALOG_IS_VALID())
				return ImGui::TextDisabled("Catalog not loaded yet");

			ImGui::Text("Warning: You are solely responsible for what you do with this tool. If you don't know what you're doing, you'll likely get banned");

			static TransactionInfo info{};
			bool txn_valid{true};

			ImGui::SetNextItemWidth(180.0f);
			if (ImGui::Combo("Type", reinterpret_cast<int*>(&info.m_Type), "Basket\0Service\0"))
				OnTransactionTypeChanged(info);

			ImGui::SetNextItemWidth(250.0f);
			if (ImGui::BeginCombo("Category", info.m_Category.m_Name))
			{
				for (auto& item : NET_SHOP_CATEGORIES)
				{
					if ((info.m_Type != TransactionInfo::Type::SERVICE) ^ IsCategoryService(item.second))
					{
						if (ImGui::Selectable(item.first, item.second == info.m_Category.m_Hash))
						{
							info.m_Category.m_Name = item.first;
							info.m_Category.m_Hash = item.second;
						}

						if (item.second == info.m_Category.m_Hash)
							ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}

			ImGui::SetNextItemWidth(250.0f);
			if (ImGui::BeginCombo("Action", info.m_Action.m_Name))
			{
				for (auto& item : NET_SHOP_ACTIONS)
				{
					if (info.m_Type != TransactionInfo::Type::SERVICE || IsActionService(item.second))
					{
						if (ImGui::Selectable(item.first, item.second == info.m_Action.m_Hash))
						{
							info.m_Action.m_Name = item.first;
							info.m_Action.m_Hash = item.second;
						}

						if (item.second == info.m_Action.m_Hash)
							ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}

			ImGui::Separator();

			if (info.m_Type == TransactionInfo::Type::BASKET)
			{
				RenderBasketEditor(info, txn_valid);
			}
			else
			{
				RenderServiceEditor(info, txn_valid);
			}

			ImGui::Separator();

			ImGui::BeginDisabled(!txn_valid);
			if (ImGui::Button("Trigger"))
				FiberPool::Push([] {
					ProcessTransaction(info);
				});
			if (!txn_valid && ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
				ImGui::SetTooltip("The transaction isn't valid. Ensure that all fields are filled out correctly");
			ImGui::EndDisabled();
		}));

		menu->AddItem(std::move(normal));
		return menu;
	}
}
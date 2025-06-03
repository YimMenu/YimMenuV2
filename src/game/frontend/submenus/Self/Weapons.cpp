#include "Weapons.hpp"
#include "core/backend/FiberPool.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/data/Weapons.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/Scripts.hpp"
#include "game/gta/ScriptFunction.hpp"
#include "types/script/scrThread.hpp"

namespace YimMenu::Submenus
{
	struct WeaponDisplay
	{
		std::string name;
		std::string desc;
		joaat_t hash;
	};

	static void RenderAmmuNationMenu()
	{
		static std::vector<WeaponDisplay> weaponDisplays;
		static std::string selectedWeapon{"Select"};
		static joaat_t selectedWeaponHash{};
		static char searchWeapon[64];

		static bool init = [] {
			FiberPool::Push([] {
				while (Scripts::IsScriptActive("startup"_J))
					ScriptMgr::Yield();

				if (auto id = Scripts::StartScript("mp_weapons"_J))
				{
					if (auto thread = Scripts::FindScriptThreadByID(id))
					{
						thread->m_Context.m_State = rage::scrThread::State::PAUSED;

						for (const auto& weap : g_WeaponHashes)
						{
							static ScriptFunction getWeaponNameLabel("mp_weapons"_J, ScriptPointer("GetWeaponNameLabel", "2D 02 2B 00 00"));
							static ScriptFunction getWeaponDescLabel("mp_weapons"_J, ScriptPointer("GetWeaponDescLabel", "2D 02 A0 00 00"));

							std::string nameGxt = getWeaponNameLabel.Call<const char*>(weap, false); // second arg is for uppercase
							std::string descGxt = getWeaponDescLabel.Call<const char*>(weap, false);

							std::string nameDisplay = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(nameGxt.c_str());
							std::string descDisplay = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(descGxt.c_str());

							weaponDisplays.push_back({((nameDisplay.empty() || nameDisplay == "NULL" || nameDisplay == "Invalid") ? "" : nameDisplay), ((descDisplay.empty() || descDisplay == "NULL" || descDisplay == "Invalid") ? "" : descDisplay), weap});
						}

						thread->Kill();
						thread->m_Context.m_State = rage::scrThread::State::KILLED;
					}
				}
			});
			return true;
		}();

		ImGui::BeginCombo("Weapons", selectedWeapon.c_str());
		if (ImGui::IsItemActive() && !ImGui::IsPopupOpen("##weaponspopup"))
		{
			ImGui::OpenPopup("##weaponspopup");
			memset(searchWeapon, 0, sizeof(searchWeapon));
		}
		if (ImGui::BeginPopup("##weaponspopup", ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
		{
			ImGui::Text("Search:");
			ImGui::SameLine();
			ImGui::SetNextItemWidth(250.f);
			ImGui::InputText("##searchweapon", searchWeapon, sizeof(searchWeapon));

			std::string searchLower = searchWeapon;
			std::transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);
			for (const auto& weap : weaponDisplays)
			{
				if (weap.name.empty())
					continue;

				std::string weaponLower = weap.name;
				std::transform(weaponLower.begin(), weaponLower.end(), weaponLower.begin(), ::tolower);

				if (weaponLower.find(searchLower) != std::string::npos)
				{
					ImGui::PushID(weap.hash);
					if (ImGui::Selectable(weap.name.c_str()))
					{
						selectedWeapon     = weap.name;
						selectedWeaponHash = weap.hash;
					}
					ImGui::PopID();
					if (ImGui::IsItemHovered() && !weap.desc.empty())
					{
						ImGui::BeginTooltip();
						ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35);
						ImGui::TextUnformatted(weap.desc.c_str());
						ImGui::PopTextWrapPos();
						ImGui::EndTooltip();
					}
				}
			}
			ImGui::EndPopup();
		}

		if (ImGui::Button("Give Weapon"))
		{
			FiberPool::Push([] {
				Self::GetPed().GiveWeapon(selectedWeaponHash, true);
			});
		}
		ImGui::SameLine();
		if (ImGui::Button("Remove Weapon"))
		{
			FiberPool::Push([] {
				Self::GetPed().RemoveWeapon(selectedWeaponHash);
			});
		}
	}

	std::shared_ptr<Category> BuildWeaponsMenu()
	{
		auto weapons = std::make_shared<Category>("Weapons");

		auto weaponsGlobalsGroup    = std::make_shared<Group>("Globals");
		auto weaponsToolsGroup      = std::make_shared<Group>("Tools", 1);
		auto weaponsAmmuNationGroup = std::make_shared<Group>("Ammu-Nation");
		auto weaponsAimbotGroup     = std::make_shared<Group>("Aimbot", 1);

		weaponsGlobalsGroup->AddItem(std::make_shared<BoolCommandItem>("infiniteammo"_J));
		weaponsGlobalsGroup->AddItem(std::make_shared<BoolCommandItem>("infiniteclip"_J));
		weaponsGlobalsGroup->AddItem(std::make_shared<BoolCommandItem>("rapidfire"_J));
		weaponsGlobalsGroup->AddItem(std::make_shared<BoolCommandItem>("infiniteparachutes"_J));
		weaponsGlobalsGroup->AddItem(std::make_shared<BoolCommandItem>("ExplosiveAmmo"_J));

		weaponsToolsGroup->AddItem(std::make_shared<CommandItem>("giveallweapons"_J));
		weaponsToolsGroup->AddItem(std::make_shared<CommandItem>("givemaxammo"_J));
		weaponsToolsGroup->AddItem(std::make_shared<CommandItem>("opengunlocker"_J));

		weaponsAmmuNationGroup->AddItem(std::make_shared<ImGuiItem>([] {
			RenderAmmuNationMenu();
		}));

		weaponsAimbotGroup->AddItem(std::make_shared<BoolCommandItem>("aimbot"_J));
		weaponsAimbotGroup->AddItem(std::make_shared<ConditionalItem>("aimbot"_J, std::make_shared<BoolCommandItem>("aimbotaimforhead"_J)));
		weaponsAimbotGroup->AddItem(std::make_shared<ConditionalItem>("aimbot"_J, std::make_shared<BoolCommandItem>("aimbottargetdrivers"_J)));

		weapons->AddItem(weaponsGlobalsGroup);
		weapons->AddItem(weaponsToolsGroup);
		weapons->AddItem(weaponsAmmuNationGroup);
		weapons->AddItem(weaponsAimbotGroup);
		return weapons;
	}
}
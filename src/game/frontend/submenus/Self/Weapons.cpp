#include "Weapons.hpp"
#include "core/backend/FiberPool.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/data/Weapons.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/Scripts.hpp"
#include "game/gta/ScriptFunction.hpp"
#include "types/script/scrThread.hpp"
#include "core/commands/Commands.hpp"
#include "game/features/self/CustomWeapon.hpp"

namespace YimMenu::Submenus
{
	struct WeaponDisplay
	{
		std::string name;
		std::string desc;
		joaat_t hash;
	};

	static void FetchWeaponStats(joaat_t weaponHash, int& kills, int& deaths, float& kd, int& headshots, int& accuracy)
	{
		uint64_t garbage[4]{};
		if (auto id = Scripts::StartScript("mp_weapons"_J, eStackSizes::PAUSE_MENU_SCRIPT, &garbage, 4))
		{
			if (auto thread = Scripts::FindScriptThreadByID(id))
			{
				thread->m_Context.m_State = rage::scrThread::State::PAUSED;

				static ScriptFunction getWeaponKills("mp_weapons"_J, ScriptPointer("GetWeaponKills", "5D ? ? ? 39 0F 38 00").Add(1).Rip());
				static ScriptFunction getWeaponDeaths("mp_weapons"_J, ScriptPointer("GetWeaponDeaths", "5D ? ? ? 39 10").Add(1).Rip());
				static ScriptFunction getWeaponKDRatio("mp_weapons"_J, ScriptPointer("GetWeaponKDRatio", "5D ? ? ? 39 12").Add(1).Rip());
				static ScriptFunction getWeaponHeadshots("mp_weapons"_J, ScriptPointer("GetWeaponHeadshots", "5D ? ? ? 39 11").Add(1).Rip());
				static ScriptFunction getWeaponAccuracy("mp_weapons"_J, ScriptPointer("GetWeaponAccuracy", "2D 01 09 00 00"));

				kills     = getWeaponKills.Call<int>(weaponHash, -1);
				deaths    = getWeaponDeaths.Call<int>(weaponHash, -1);
				kd        = getWeaponKDRatio.Call<float>(weaponHash, -1);
				headshots = getWeaponHeadshots.Call<int>(weaponHash, -1);
				accuracy  = static_cast<int>(getWeaponAccuracy.Call<float>(weaponHash));

				thread->Kill();
				thread->m_Context.m_State = rage::scrThread::State::KILLED;
			}
		}
	}

	static void RenderAmmuNationMenu()
	{
		static std::vector<WeaponDisplay> weaponDisplays;
		static std::string selectedWeapon{"Select"};
		static joaat_t selectedWeaponHash{};
		static char searchWeapon[64];

		static int kills{};
		static int deaths{};
		static float kdRatio{};
		static int headshots{};
		static int accuracy{};

		static bool init = [] {
			FiberPool::Push([] {
				while (Scripts::IsScriptActive("startup"_J))
					ScriptMgr::Yield();

				uint64_t garbage[4]{};
				if (auto id = Scripts::StartScript("mp_weapons"_J, eStackSizes::PAUSE_MENU_SCRIPT, &garbage, 4))
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
						FiberPool::Push([weap] {
							selectedWeapon = weap.name;
							selectedWeaponHash = weap.hash;
							FetchWeaponStats(selectedWeaponHash, kills, deaths, kdRatio, headshots, accuracy);
						});
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

		if (*Pointers.IsSessionStarted && selectedWeaponHash != 0)
		{
			ImGui::Text("Kills With: %d", kills);
			ImGui::Text("Deaths By: %d", deaths);
			ImGui::Text("K/D Ratio: %.2f", kdRatio);
			ImGui::Text("Headshots: %d", headshots);
			ImGui::Text("Accuracy: %d%%", accuracy);
		}
	}

	static std::shared_ptr<Group> RenderCustomWeaponsMenu()
	{
		auto customWeaponsGroup = std::make_shared<Group>("Custom Weapons");

		auto cutomWeaponTypes = std::make_shared<Group>("", 1);
		auto customWeapons = std::make_shared<Group>("");
		auto paintGunGroup = std::make_shared<Group>("");

		auto cmd = Commands::GetCommand<ListCommand>("customweapontype"_J);
		
		auto isGravityGunEnabled = [cmd] {
			return static_cast<Features::CustomWeapons>(cmd->GetState()) == Features::CustomWeapons::GRAVITY_GUN;
		};

		auto isVehicleGunEnabled = [cmd] {
			return static_cast<Features::CustomWeapons>(cmd->GetState()) == Features::CustomWeapons::VEHICLE_GUN;
		};

		auto isPaintGunEnabled = [cmd] {
			return static_cast<Features::CustomWeapons>(cmd->GetState()) == Features::CustomWeapons::PAINT_GUN;
		};

		cutomWeaponTypes->AddItem(std::make_shared<ListCommandItem>("customweapontype"_J));
		cutomWeaponTypes->AddItem(std::make_shared<ConditionalItem>(isGravityGunEnabled, std::make_shared<BoolCommandItem>("gravitygunlaunchonrelease"_J)));
		cutomWeaponTypes->AddItem(std::make_shared<ConditionalItem>(isVehicleGunEnabled, std::make_shared<StringCommandItem>("vehiclegunmodel"_J)));
		cutomWeaponTypes->AddItem(std::make_shared<ConditionalItem>(isPaintGunEnabled, std::make_shared<ConditionalItem>("paintgunrainbowcolorenabled"_J, std::make_shared<ColorCommandItem>("paintguncolor"_J), true)));

		paintGunGroup->AddItem(std::make_shared<BoolCommandItem>("paintgunrainbowcolorenabled"_J));
		paintGunGroup->AddItem(std::make_shared<ConditionalItem>("paintgunrainbowcolorenabled"_J, std::make_shared<ListCommandItem>("paintgunrainbowcolorstyle"_J)));
		paintGunGroup->AddItem(std::make_shared<ConditionalItem>("paintgunrainbowcolorenabled"_J, std::make_shared<IntCommandItem>("paintgunrainbowcolorspeed"_J)));

		customWeapons->AddItem(std::make_shared<BoolCommandItem>("customweaponenabledonweaponout"_J));
		customWeapons->AddItem(std::move(cutomWeaponTypes));
		customWeapons->AddItem(std::make_shared<ConditionalItem>(isPaintGunEnabled, std::move(paintGunGroup)));

		customWeaponsGroup->AddItem(std::make_shared<BoolCommandItem>("customweapon"_J));
		customWeaponsGroup->AddItem(std::make_shared<ConditionalItem>("customweapon"_J, std::move(customWeapons)));

		return customWeaponsGroup;
	}

	std::shared_ptr<Category> BuildWeaponsMenu()
	{
		auto weapons = std::make_shared<Category>("Weapons");

		auto weaponsGlobalsGroup = std::make_shared<Group>("Globals", 12);
		auto weaponsToolsGroup = std::make_shared<Group>("Tools", 1);
		auto weaponsAmmuNationGroup = std::make_shared<Group>("Ammu-Nation");
		auto weaponsAimbotGroup = std::make_shared<Group>("Aimbot", 1);

		weaponsGlobalsGroup->AddItem(std::make_shared<BoolCommandItem>("infiniteammo"_J));
		weaponsGlobalsGroup->AddItem(std::make_shared<BoolCommandItem>("infiniteclip"_J));
		weaponsGlobalsGroup->AddItem(std::make_shared<BoolCommandItem>("rapidfire"_J));
		weaponsGlobalsGroup->AddItem(std::make_shared<BoolCommandItem>("infiniteparachutes"_J));
		weaponsGlobalsGroup->AddItem(std::make_shared<BoolCommandItem>("ExplosiveAmmo"_J));
		weaponsGlobalsGroup->AddItem(std::make_shared<ConditionalItem>("ExplosiveAmmo"_J, std::make_shared<ListCommandItem>("selectedexplosion"_J)));
		weaponsGlobalsGroup->AddItem(std::make_shared<ConditionalItem>("ExplosiveAmmo"_J, std::make_shared<FloatCommandItem>("explosiondamage"_J, std::nullopt, false)));
		weaponsGlobalsGroup->AddItem(std::make_shared<ConditionalItem>("ExplosiveAmmo"_J, std::make_shared<FloatCommandItem>("explosioncamerashake"_J, std::nullopt, false)));
		weaponsGlobalsGroup->AddItem(std::make_shared<BoolCommandItem>("weapondamage"_J));
		weaponsGlobalsGroup->AddItem(std::make_shared<ConditionalItem>("weapondamage"_J, std::make_shared<FloatCommandItem>("weapondamagescale"_J, std::nullopt, false)));
		weaponsGlobalsGroup->AddItem(std::make_shared<BoolCommandItem>("meleedamage"_J));
		weaponsGlobalsGroup->AddItem(std::make_shared<ConditionalItem>("meleedamage"_J, std::make_shared<FloatCommandItem>("meleedamagescale"_J, std::nullopt, false)));

		weaponsToolsGroup->AddItem(std::make_shared<CommandItem>("giveallweapons"_J));
		weaponsToolsGroup->AddItem(std::make_shared<CommandItem>("givemaxammo"_J));
		weaponsToolsGroup->AddItem(std::make_shared<CommandItem>("opengunlocker"_J));

		weaponsAmmuNationGroup->AddItem(std::make_shared<ImGuiItem>([] {
			RenderAmmuNationMenu();
		}));

		weaponsAimbotGroup->AddItem(std::make_shared<BoolCommandItem>("aimbot"_J));
		weaponsAimbotGroup->AddItem(std::make_shared<ConditionalItem>("aimbot"_J, std::make_shared<BoolCommandItem>("aimbotaimforhead"_J)));
		weaponsAimbotGroup->AddItem(std::make_shared<ConditionalItem>("aimbot"_J, std::make_shared<BoolCommandItem>("aimbottargetdrivers"_J)));
		weaponsAimbotGroup->AddItem(std::make_shared<ConditionalItem>("aimbot"_J, std::make_shared<BoolCommandItem>("aimbotreleasedeadped"_J)));

		weapons->AddItem(weaponsGlobalsGroup);
		weapons->AddItem(weaponsToolsGroup);
		weapons->AddItem(weaponsAmmuNationGroup);
		weapons->AddItem(weaponsAimbotGroup);
		weapons->AddItem(RenderCustomWeaponsMenu());
		return weapons;
	}
}
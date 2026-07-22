#include "core/commands/Command.hpp"
#include "core/commands/BoolCommand.hpp"
#include "core/commands/ListCommand.hpp"
#include "game/gta/Stats.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "game/gta/ScriptLocal.hpp"
#include "game/gta/Scripts.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu::Features
{
	namespace KortzCenterHeist
	{
		// --- Primary Target ---
		static std::vector<std::pair<int, const char*>> kortzCenterTargets = {
		    {0, "最后的放纵"},
		    {1, "兔子独自思考"},
		    {2, "罗马的陨落"},
		    {3, "兄弟兄弟"},
		    {4, "一众角色"},
		    {5, "走向衰败"},
		    {6, "真爱"},
		    {7, "窒息"},
		    {8, "圆满"},
		    {9, "我听到声音"},
		    {10, "冬天，不知何处"},
		    {11, "戴珍珠项链的女孩"},
		    {12, "水果聊天"},
		    {13, "南瓜"},
		    {14, "双重差异"},
		    {15, "堆叠研究V"},
		    {16, "我，水果"},
		    {17, "拐弯抹角"},
		    {18, "成功过剩"},
		    {19, "榨汁"},
		    {20, "回家的曲折之路"},
		    {21, "腊肠犬"},
		    {22, "信任"},
		    {23, "至死不渝"},
		    {24, "什么瓜？"},
		    {25, "奋斗的成果"},
		    {26, "我的近战"}
		};
		static ListCommand _KortzCenterPrimaryTarget{"kortzcenterheistprimarytarget", "主要目标", "主要目标", kortzCenterTargets, 0};

		// --- General Purchases (MPX_K26_GENERAL_BS bits 5-8) ---
		static BoolCommand _KortzCenterGuardRoutes{"kortzcenterheistguardroutes", "守卫路线", "守卫路线已购买", true};
		static BoolCommand _KortzCenterGlassCutter{"kortzcenterheistglasscutter", "玻璃切割器", "玻璃切割器已购买", true};
		static BoolCommand _KortzCenterPowerDrills{"kortzcenterheistpowerdrills", "电钻", "电钻已购买", true};
		static BoolCommand _KortzCenterEMPCharges{"kortzcenterheistempcharges", "EMP电磁脉冲", "EMP电磁脉冲已购买", true};

		// --- Prep Work Items ---
		static BoolCommand _KortzCenterScopeOut{"kortzcenterheistscopeout", "侦查科兹中心", "侦查科兹中心", true};
		static BoolCommand _KortzCenterAlphaMail{"kortzcenterheistalphamail", "阿尔法快递伪装", "阿尔法快递伪装", true};
		static BoolCommand _KortzCenterHazmat{"kortzcenterheisthazmat", "防护服", "防护服", true};
		static BoolCommand _KortzCenterStaffKeycard{"kortzcenterheiststaffkeycard", "员工钥匙卡", "员工钥匙卡", true};
		static BoolCommand _KortzCenterTacticalEquip{"kortzcenterheisttacticalequip", "战术装备", "战术装备", true};
		static BoolCommand _KortzCenterHackingDevice{"kortzcenterheisthackingdevice", "黑客设备", "黑客设备", true};
		static BoolCommand _KortzCenterAccessCode{"kortzcenterheistaccesscode", "访问代码", "访问代码", true};
		static BoolCommand _KortzCenterUnmarkedWeapons{"kortzcenterheistunmarkedweapons", "无标记武器", "无标记武器", true};
		static BoolCommand _KortzCenterCaracara{"kortzcenterheistcaracara", "装甲卡拉卡拉", "装甲卡拉卡拉", true};
		static BoolCommand _KortzCenterAnnihilator{"kortzcenterheistannihilator", "歼灭者隐形直升机", "歼灭者隐形直升机", true};
		static BoolCommand _KortzCenterManchez{"kortzcenterheistmanchez", "曼切斯摩托", "曼切斯摩托", true};
		static BoolCommand _KortzCenterPrepEMP{"kortzcenterheistprepemp", "EMP电磁脉冲(前置)", "EMP电磁脉冲前置任务", true};
		static BoolCommand _KortzCenterGuardShipments{"kortzcenterheistguardshipments", "守卫货物", "守卫货物", true};
		static BoolCommand _KortzCenterGuardRoutesPrep{"kortzcenterheistguardroutesprep", "守卫路线(前置)", "守卫路线前置任务", true};
		static BoolCommand _KortzCenterGlassCutterPrep{"kortzcenterheistglasscutterprep", "玻璃切割器(前置)", "玻璃切割器前置任务", true};
		static BoolCommand _KortzCenterPowerDrillsPrep{"kortzcenterheistpowerdrillsprep", "电钻(前置)", "电钻前置任务", true};
		static BoolCommand _KortzCenterEMPChargesPrep{"kortzcenterheistempchargesprep", "EMP电磁脉冲(前置)", "EMP电磁脉冲前置任务", true};
		static BoolCommand _KortzCenterCaracaraPrep{"kortzcenterheistcaracaraprep", "卡拉卡拉(前置)", "装甲卡拉卡拉前置任务", true};
		static BoolCommand _KortzCenterAnnihilatorPrep{"kortzcenterheistannihilatorprep", "歼灭者(前置)", "歼灭者隐形直升机前置任务", true};
		static BoolCommand _KortzCenterManchezPrep{"kortzcenterheistmanchezprep", "曼切斯(前置)", "曼切斯摩托前置任务", true};

		// --- Scoping ---
		static BoolCommand _KortzCenterScopeSecondary{"kortzcenterheistscopesecondary", "次要目标", "侦查次要目标", true};
		static BoolCommand _KortzCenterScopePOI{"kortzcenterheistscopepoi", "兴趣点", "侦查兴趣点", true};

		// --- In-Heist Shortcuts ---
		class SkipFingerprint : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller_v3"_J))
					*ScriptLocal(thread, 26866).As<int*>() = 5;
			}
		};

		class SkipSignalNodes : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller_v3"_J))
					*ScriptLocal(thread, 27914).As<int*>() = 5;
			}
		};

		class SkipDataCrack : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller_v3"_J))
				{
					for (int i = 0; i <= 7; i++)
						*ScriptLocal(thread, 1388).At(i, 4).As<int*>() = 1;
				}
			}
		};

		class CutGlass : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller_v3"_J))
					*ScriptLocal(thread, 32855).At(4, 13).At(3).As<float*>() = 100.0f;
			}
		};

		class DisableLaserGrid : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller_v3"_J))
				{
					*ScriptLocal(thread, 70416).As<int*>() = 4294784;
					*ScriptGlobal(1935711).As<int*>() |= 1;
				}
			}
		};

		class TakePrimaryTarget : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller_v3"_J))
					*ScriptLocal(thread, 29355).At(11).As<int*>() = 10;
			}
		};

		class TakeSecondaryTarget : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller_v3"_J))
					*ScriptLocal(thread, 29355).At(11).As<int*>() = 3;
			}
		};

		// --- Setup ---
		class Setup : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				int generalBits = -1;
				if (!_KortzCenterGuardRoutes.GetState()) generalBits &= ~(1 << 5);
				if (!_KortzCenterGlassCutter.GetState()) generalBits &= ~(1 << 6);
				if (!_KortzCenterPowerDrills.GetState()) generalBits &= ~(1 << 7);
				if (!_KortzCenterEMPCharges.GetState()) generalBits &= ~(1 << 8);

				int robberyProg = -1;
				if (!_KortzCenterScopeOut.GetState()) robberyProg &= ~(1 << 0);
				if (!_KortzCenterAlphaMail.GetState()) robberyProg &= ~(1 << 1);
				if (!_KortzCenterHazmat.GetState()) robberyProg &= ~(1 << 2);
				if (!_KortzCenterStaffKeycard.GetState()) robberyProg &= ~(1 << 3);
				if (!_KortzCenterTacticalEquip.GetState()) robberyProg &= ~(1 << 4);
				if (!_KortzCenterHackingDevice.GetState()) robberyProg &= ~(1 << 5);
				if (!_KortzCenterAccessCode.GetState()) robberyProg &= ~(1 << 6);
				if (!_KortzCenterUnmarkedWeapons.GetState()) robberyProg &= ~(1 << 7);
				if (!_KortzCenterCaracara.GetState()) robberyProg &= ~(1 << 8);
				if (!_KortzCenterAnnihilator.GetState()) robberyProg &= ~(1 << 9);
				if (!_KortzCenterManchez.GetState()) robberyProg &= ~(1 << 10);
				if (!_KortzCenterPrepEMP.GetState()) robberyProg &= ~(1 << 11);
				if (!_KortzCenterGuardShipments.GetState()) robberyProg &= ~(1 << 12);
				if (!_KortzCenterGuardRoutesPrep.GetState()) robberyProg &= ~(1 << 13);
				if (!_KortzCenterGlassCutterPrep.GetState()) robberyProg &= ~(1 << 14);
				if (!_KortzCenterPowerDrillsPrep.GetState()) robberyProg &= ~(1 << 15);

				int scopingBS = _KortzCenterScopeSecondary.GetState() ? -1 : 0;
				int poiBS = _KortzCenterScopePOI.GetState() ? -1 : 0;
				int caracaraPrepBS = _KortzCenterCaracaraPrep.GetState() ? -1 : 0;
				int annihilatorPrepBS = _KortzCenterAnnihilatorPrep.GetState() ? -1 : 0;
				int manchezPrepBS = _KortzCenterManchezPrep.GetState() ? -1 : 0;
				int empChargesPrepBS = _KortzCenterEMPChargesPrep.GetState() ? -1 : 0;

				Stats::SetInt("MPX_K26_GENERAL_BS", generalBits);
				Stats::SetInt("MPX_K26_GENERAL_BS2", -1);
				Stats::SetInt("MPX_K26_ROBBERY_PROG", robberyProg);
				Stats::SetInt("MPX_K26_SCOPING_BS", scopingBS);
				Stats::SetInt("MPX_K26_POI_BS", poiBS);
				Stats::SetInt("MPX_K26_HEIST_TARGET", _KortzCenterPrimaryTarget.GetState());
			}
		};

		static SkipFingerprint _KortzCenterSkipFingerprint{"kortzcenterheistskipfingerprint", "跳过指纹识别", "跳过电脑室指纹识别小游戏"};
		static SkipSignalNodes _KortzCenterSkipSignalNodes{"kortzcenterheistskipsignalnodes", "跳过信号节点", "跳过保险库键盘信号节点黑客破解"};
		static SkipDataCrack _KortzCenterSkipDataCrack{"kortzcenterheistskipdatacrack", "跳过数据破解", "跳过数据破解小游戏"};
		static CutGlass _KortzCenterCutGlass{"kortzcenterheistcutglass", "切割玻璃", "立即切割展柜玻璃"};
		static DisableLaserGrid _KortzCenterDisableLaser{"kortzcenterheistdisablelaser", "禁用激光网格", "禁用激光安全网格"};
		static TakePrimaryTarget _KortzCenterTakePrimary{"kortzcenterheisttakeprimary", "获取主要目标", "获取主要目标画作(站在画作附近)"};
		static TakeSecondaryTarget _KortzCenterTakeSecondary{"kortzcenterheisttakesecondary", "获取次要目标", "获取次要战利品(站在战利品附近)"};
		static Setup _KortzCenterSetup{"kortzcenterheistsetup", "应用(立即完成前置任务)", "按上述配置跳过科兹中心前置任务"};
	}
}

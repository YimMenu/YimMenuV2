#include "core/commands/Command.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/backend/Self.hpp"
#include "game/backend/ScriptPatches.hpp"
#include "game/backend/NativeHooks.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/Scripts.hpp"
#include "game/gta/ScriptLocal.hpp"
#include "game/pointers/Pointers.hpp"

namespace YimMenu::Features
{
	struct WARDROBE_LAUNCH_DATA
	{
		SCR_INT Type;
		SCR_VEC3 Position;
		SCR_FLOAT Heading;
	};
	static_assert(sizeof(WARDROBE_LAUNCH_DATA) == 5 * 8);

	static bool startedByUs{};
	static ScriptPatch shouldCleanupWardrobePatch{};
	static ScriptPatch isWardrobeOpenedPatch{};
	static ScriptPatch doesPlayerOwnItemPatch{};
	static ScriptPatch isItemLockedByStatPatch1{};
	static ScriptPatch isItemLockedByStatPatch2{};
	static ScriptPatch isItemLockedByStatPatch3{};
	static void GetDistanceBetweenCoordsHook(rage::scrNativeCallContext* ctx);

	class OpenWardrobe : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted || Scripts::IsScriptActive("wardrobe_mp"_J))
			{
				Notifications::Show("Wardrobe", "Not safe to open the wardrobe at the moment.", NotificationType::Error);
				return;
			}

			WARDROBE_LAUNCH_DATA launchData;
			launchData.Type = 7;
			launchData.Position = Self::GetPed().GetPosition();
			launchData.Heading = Self::GetPed().GetHeading();
			if (!Scripts::StartScript("wardrobe_mp"_J, eStackSizes::SHOP, &launchData, SCR_SIZEOF(launchData)))
			{
				Notifications::Show("Wardrobe", "Failed to open the wardrobe.", NotificationType::Error);
				return;
			}

			if (!shouldCleanupWardrobePatch)
			{
				shouldCleanupWardrobePatch = ScriptPatches::AddPatch("wardrobe_mp"_J, ScriptPointer("ShouldCleanupWardrobePatch", "2C ? ? ? 2C ? ? ? 06 56 ? ? 2C ? ? ? 56 ? ? 2C"), {0x72, 0x2E, 0x05, 0x01});
			}
			shouldCleanupWardrobePatch->Enable();

			if (!isWardrobeOpenedPatch)
			{
				isWardrobeOpenedPatch = ScriptPatches::AddPatch("wardrobe_mp"_J, ScriptPointer("IsWardrobeOpenedPatch", "56 22 00 71"), {0x2B, 0x00, 0x00});
			}
			isWardrobeOpenedPatch->Enable();

			if (!doesPlayerOwnItemPatch)
			{
				doesPlayerOwnItemPatch = ScriptPatches::AddPatch("wardrobe_mp"_J, ScriptPointer("DoesPlayerOwnItemPatch", "57 D2 00 38 08"), {0x55});
			}
			doesPlayerOwnItemPatch->Enable();

			if (!isItemLockedByStatPatch1)
			{
				isItemLockedByStatPatch1 = ScriptPatches::AddPatch("wardrobe_mp"_J, ScriptPointer("IsItemLockedByStatPatch1", "38 00 65 02 F7 B6 C6 31 09 00 31 46 A9 B0 28 04"), {0x71, 0x2E, 0x03, 0x01});
			}
			isItemLockedByStatPatch1->Enable();

			if (!isItemLockedByStatPatch2)
			{
				isItemLockedByStatPatch2 = ScriptPatches::AddPatch("wardrobe_mp"_J, ScriptPointer("IsItemLockedByStatPatch2", "38 00 65 04 90 44 B3 80 15 00 CB C8 CF 72 0F 00 87 81 38 F6 1C 00 31 48 DE 94 16 00"), {0x72, 0x2E, 0x03, 0x01});
			}
			isItemLockedByStatPatch2->Enable();

			if (!isItemLockedByStatPatch3)
			{
				isItemLockedByStatPatch3 = ScriptPatches::AddPatch("wardrobe_mp"_J, ScriptPointer("IsItemLockedByStatPatch3", "38 00 65 01 34 ED 23 4E 03 00"), {0x72, 0x2E, 0x03, 0x01});
			}
			isItemLockedByStatPatch3->Enable();

			static bool initNativeHook = [] {
				NativeHooks::AddHook("wardrobe_mp"_J, NativeIndex::GET_DISTANCE_BETWEEN_COORDS, &GetDistanceBetweenCoordsHook);
				return true;
			}();

			startedByUs = true;
		}
	};

	static OpenWardrobe _OpenWardrobe{"openwardrobe", "Open Wardrobe", "Allows you to access your wardrobe remotely."};

	static void GetDistanceBetweenCoordsHook(rage::scrNativeCallContext* ctx)
	{
		auto distance = MISC::GET_DISTANCE_BETWEEN_COORDS(ctx->GetArg<float>(0), ctx->GetArg<float>(1), ctx->GetArg<float>(2), ctx->GetArg<float>(3), ctx->GetArg<float>(4), ctx->GetArg<float>(5), ctx->GetArg<BOOL>(6));

		if (startedByUs)
		{
			if (auto thread = Scripts::FindScriptThread("wardrobe_mp"_J))
			{
				if (*ScriptLocal(thread, 191).At(46).At(9).As<int*>() == 4)
				{
					shouldCleanupWardrobePatch->Disable();
					isWardrobeOpenedPatch->Disable();
					doesPlayerOwnItemPatch->Disable();
					isItemLockedByStatPatch1->Disable();
					isItemLockedByStatPatch2->Disable();
					isItemLockedByStatPatch3->Disable();

					startedByUs = false;
					distance = 9999.f;
				}
			}
		}

		ctx->SetReturnValue<float>((float)distance);
	}
}
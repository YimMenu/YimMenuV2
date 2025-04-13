#include "core/commands/BoolCommand.hpp"
#include "core/hooking/DetourHook.hpp"
#include "game/backend/NativeHooks.hpp"
#include "game/hooks/Hooks.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/Stats.hpp"

namespace YimMenu
{
	namespace Features
	{
		static void ScaleformAddIntHook(rage::scrNativeCallContext* ctx);

		class FormatMoney : public BoolCommand
		{
			using BoolCommand::BoolCommand;

			virtual void OnEnable() override
			{
				NativeHooks::AddHook("shop_controller"_J, NativeIndex::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT, &ScaleformAddIntHook);
			}
		};

		static FormatMoney _FormatMoney{"formatmoney", "Format Money", "Formats HUD money with commas."};

		static void ScaleformAddIntHook(rage::scrNativeCallContext* ctx)
		{
			int value = ctx->GetArg<int>(0);
			if (_FormatMoney.GetState())
			{
				int chips = Stats::GetInt("MPX_CASINO_CHIPS");
				if (value == chips && chips >= 1000)
				{
					auto formatted = std::to_string(value);
					for (int i = formatted.size() - 3; i > 0; i -= 3)
					{
						formatted.insert(i, ",");
					}
					return GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING(formatted.c_str());
				}
			}

			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(value);
		}
	}

	namespace Hooks
	{
		void Features::FormatInt(int64_t integer, char* str, size_t strSize, bool insertCommas)
		{
			auto retnAddr  = _ReturnAddress();
			auto retnBytes = static_cast<unsigned char*>(retnAddr);
			if (YimMenu::Features::_FormatMoney.GetState() && retnBytes[0] == 0x0F && retnBytes[1] == 0x28 && retnBytes[2] == 0x05)
			{
				insertCommas = true;
			}

			BaseHook::Get<Hooks::Features::FormatInt, DetourHook<decltype(&Hooks::Features::FormatInt)>>()->Original()(integer, str, strSize, insertCommas);
		}
	}
}
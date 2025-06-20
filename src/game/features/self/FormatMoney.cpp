#include "core/commands/BoolCommand.hpp"
#include "core/hooking/CallHook.hpp"
#include "game/backend/NativeHooks.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/Stats.hpp"

namespace YimMenu::Features
{
	static CallHook formatIntCaller1Hook{};
	static CallHook formatIntCaller2Hook{};
	static void FormatIntHook(int64_t integer, char* str, size_t strSize, bool insertCommas);
	static void ScaleformAddIntHook(rage::scrNativeCallContext* ctx);

	class FormatMoney : public BoolCommand
	{
		using BoolCommand::BoolCommand;

		virtual void OnEnable() override
		{
			if (!formatIntCaller1Hook)
			{
				formatIntCaller1Hook = CallSiteHook::AddHook(Pointers.FormatIntCaller1, reinterpret_cast<void*>(FormatIntHook));
			}
			formatIntCaller1Hook->Enable();
			if (!formatIntCaller2Hook)
			{
				formatIntCaller2Hook = CallSiteHook::AddHook(Pointers.FormatIntCaller2, reinterpret_cast<void*>(FormatIntHook));
			}
			formatIntCaller2Hook->Enable();
			static auto hooked = []()
			{
				NativeHooks::AddHook("shop_controller"_J, NativeIndex::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT, &ScaleformAddIntHook);
				return true;
			}();
		}

		virtual void OnDisable() override
		{
			if (formatIntCaller1Hook)
			{
				formatIntCaller1Hook->Disable();
			}
			if (formatIntCaller2Hook)
			{
				formatIntCaller2Hook->Disable();
			}
		}
	};

	static FormatMoney _FormatMoney{"formatmoney", "Format Money", "Formats HUD money with commas."};

	static void FormatIntHook(int64_t integer, char* str, size_t strSize, bool insertCommas)
	{
		insertCommas = true;

		auto original = formatIntCaller1Hook->GetOriginal<void (*)(int64_t, char*, size_t, bool)>();
		original(integer, str, strSize, insertCommas);
	}

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
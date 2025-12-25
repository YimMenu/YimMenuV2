#include "core/commands/BoolCommand.hpp"
#include "core/hooking/DetourHook.hpp"
#include "game/backend/NativeHooks.hpp"
#include "game/gta/Natives.hpp"
#include "game/hooks/Hooks.hpp"
#include "game/pointers/Pointers.hpp"
#include "types/game_files/CGameDataHash.hpp"

namespace YimMenu::Features
{
	class DumpDataHash : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			auto log = LOG(VERBOSE);
			log << "DLC Hash: "
			    << BaseHook::Get<Hooks::Network::GetDLCHash, DetourHook<decltype(&Hooks::Network::GetDLCHash)>>()->Original()(
			           *Pointers.DLCManager,
			           0)
			    << "\n";
			if (auto hashes = Pointers.GameDataHash)
			{
				log << "validHashes = {" << "\n";
				for (int i = 0; i < hashes->m_Data.size(); i++)
					log << hashes->m_Data[i].getData() << ", // " << i << "\n";
				log << "};";
			}
		}
	};
	static DumpDataHash _DumpDataHash{"dumpdatahash", "Dump Data Hash", "Dumps the current data hash into the console"};

	static void PackOrderHook(rage::scrNativeCallContext* ctx);
	class SpoofDataHash : public BoolCommand
	{
		using BoolCommand::BoolCommand;

		std::array<std::uint32_t, 16> origHashes;

		virtual void OnEnable() override
		{
			NativeHooks::AddHook(NativeHooks::ALL_SCRIPTS, NativeIndex::GET_EVER_HAD_BAD_PACK_ORDER, &PackOrderHook);

			constexpr std::array<std::uint32_t, 16> validHashes = {
			    1222354255, // 0
			    1017,       // 1
			    2008403316, // 2
			    472,        // 3
			    0,          // 4
			    0,          // 5
			    1061472380, // 6
			    0,          // 7
			    0,          // 8
			    1731098795, // 9
			    234493012,  // 10
			    19919,      // 11
			    4002619495, // 12
			    307143837,  // 13
			    2941593772, // 14
			    200299391,  // 15
			};
			if (auto hashes = Pointers.GameDataHash)
			{
				for (int i = 0; i < hashes->m_Data.size(); i++)
					origHashes[i] = hashes->m_Data[i];

				for (int i = 0; i < validHashes.size(); i++)
					hashes->m_Data[i] = validHashes[i];
			}
		}

		virtual void OnDisable() override
		{
			if (auto hashes = Pointers.GameDataHash)
			{
				for (int i = 0; i < origHashes.size(); i++)
					hashes->m_Data[i] = origHashes[i];
			}
		}
	};

	static SpoofDataHash _SpoofDataHash{"spoofdatahash", "Spoof Data Hash", "Allows you to join players with rpf mods (or a half installed game)."};

	static void PackOrderHook(rage::scrNativeCallContext* ctx)
	{
		return ctx->SetReturnValue(FALSE);
	}
}

namespace YimMenu::Hooks
{
	uint32_t Network::GetDLCHash(void* manager, uint32_t seed)
	{
		if (YimMenu::Features::_SpoofDataHash.GetState())
			return 2784221708;

		return BaseHook::Get<Network::GetDLCHash, DetourHook<decltype(&Network::GetDLCHash)>>()->Original()(manager, seed);
	}
}
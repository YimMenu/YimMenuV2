#include "core/commands/BoolCommand.hpp"
#include "game/backend/ScriptPatches.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include <thread>

namespace YimMenu::Features
{
	class NightClubSafeLoop : public BoolCommand
	{
		using BoolCommand::BoolCommand;

	private:
		bool m_is_running = false;
		std::thread m_loop_thread;

		// Constants from Lua script
		const int SAFE_AMOUNT = 250000;
		const int SAFE_CAPACITY = 23680;
		const int INCOME_START = 23657;
		const int INCOME_END = 23676;

		// Helper function to get current MP character (0 for MP0_, 1 for MP1_)
		std::string GetCurrentCharacterPrefix()
		{
			int character_id = 0;
			Hash stat_hash = MISC::GET_HASH_KEY("MPPLY_LAST_MP_CHAR");
			if (STATS::STAT_GET_INT(stat_hash, &character_id, true))
			{
				return "MP" + std::to_string(character_id) + "_";
			}
			return "MP0_"; // Default to first character if stat read fails
		}

		void SafeLoop()
		{
			while (m_is_running)
			{
				// Set income values for all popularity levels
				for (int i = INCOME_START; i <= INCOME_END; i++)
				{
					if (auto global = ScriptGlobal(262145).At(i); global.CanAccess())
					{
						*global.As<int*>() = SAFE_AMOUNT;
					}
				}

				// Set safe capacity
				if (auto global = ScriptGlobal(262145).At(SAFE_CAPACITY); global.CanAccess())
				{
					*global.As<int*>() = SAFE_AMOUNT;
				}

				// Set club pay time for current character only
				std::string club_time = GetCurrentCharacterPrefix() + "CLUB_PAY_TIME_LEFT";
				STATS::STAT_SET_INT(MISC::GET_HASH_KEY(club_time.c_str()), -1, true);

				// Calculate safe value (equivalent to SafeValue in Lua)
				int safe_value = 1845221 + PLAYER::PLAYER_ID() + 268 + 360 + 6;
				if (auto safe_global = ScriptGlobal(safe_value); safe_global.CanAccess())
				{
					if (*safe_global.As<int*>() != 0)
					{
						// Reset specific globals
						const int reset_globals[] = {4538089, 4538090, 4538091};
						for (int global_id : reset_globals)
						{
							if (auto global = ScriptGlobal(global_id); global.CanAccess())
							{
								*global.As<int*>() = 0;
							}
						}
					}
				}

				// Sleep timing matches Lua script (2.5s + 1s = 3.5s total)
				std::this_thread::sleep_for(std::chrono::milliseconds(2500));
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			}
		}

	public:
		virtual void OnEnable() override
		{
			m_is_running = true;
			if (m_loop_thread.joinable())
				m_loop_thread.join();
			
			m_loop_thread = std::thread(&NightClubSafeLoop::SafeLoop, this);
		}

		virtual void OnDisable() override
		{
			m_is_running = false;
			if (m_loop_thread.joinable())
				m_loop_thread.join();
		}

		virtual ~NightClubSafeLoop()
		{
			OnDisable();
		}
	};

	static NightClubSafeLoop _nightclub_safe_loop{"nightclubsafeloop", "Nightclub Safe Loop", "Makes you collect 300k/2 every 3s."};
}
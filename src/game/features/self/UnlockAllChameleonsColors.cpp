#include "core/commands/Command.hpp"
#include "game/gta/Stats.hpp"

namespace YimMenu::Features
{
	class Chameleons : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			Stats::SetInt("MPPLY_XMASLIVERIES0", 1);
			Stats::SetInt("MPPLY_XMASLIVERIES1", 1);
			Stats::SetInt("MPPLY_XMASLIVERIES2", 1);
			Stats::SetInt("MPPLY_XMASLIVERIES3", 1);
			Stats::SetInt("MPPLY_XMASLIVERIES4", 1);
			Stats::SetInt("MPPLY_XMASLIVERIES5", 1);
			Stats::SetInt("MPPLY_XMASLIVERIES6", 1);
			Stats::SetInt("MPPLY_XMASLIVERIES7", 1);
			Stats::SetInt("MPPLY_XMASLIVERIES8", 1);
			Stats::SetInt("MPPLY_XMASLIVERIES9", 1);
			Stats::SetInt("MPPLY_XMASLIVERIES10", 1);
			Stats::SetInt("MPPLY_XMASLIVERIES11", 1);
			Stats::SetInt("MPPLY_XMASLIVERIES12", 1);
			Stats::SetInt("MPPLY_XMASLIVERIES13", 1);
			Stats::SetInt("MPPLY_XMASLIVERIES14", 1);
			Stats::SetInt("MPPLY_XMASLIVERIES15", 1);
			Stats::SetInt("MPPLY_XMASLIVERIES16", 1);
			Stats::SetInt("MPPLY_XMAS22CPAINT0", 1);
			Stats::SetInt("MPPLY_XMAS22CPAINT1", 1);
			Stats::SetInt("MPPLY_SUM23WHEELCPAINT0", 1);
			Stats::SetInt("MPPLY_SUM23WHEELCPAINT1", 1);
		}
	};

	static Chameleons _Chameleons{"UnlockChameleons", "Unlock all Chameleons", "get all New Chameleons Colors."};
}
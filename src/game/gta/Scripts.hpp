#pragma once
#include "core/util/Joaat.hpp"

namespace rage
{
	class scrThread;
	class scrProgram;
}

class SimplePattern;

namespace YimMenu::Scripts
{
	extern rage::scrThread* FindScriptThread(joaat_t hash);
	extern rage::scrProgram* FindScriptProgram(joaat_t hash);
	extern void RunAsScript(rage::scrThread* thread, std::function<void()> callback);
	extern void RunWithSpoofedThreadName(std::uint32_t name, std::function<void()> callback); // consider using RunAsScript if possible
	extern bool SafeToModifyFreemodeBroadcastGlobals(); // TODO: find a better method for this that works for all scripts
	extern std::optional<std::uint32_t> GetCodeLocationByPattern(rage::scrProgram* program, SimplePattern pattern);
	extern void ForceScriptHost(rage::scrThread* thread); // likely unstable, beware!
}
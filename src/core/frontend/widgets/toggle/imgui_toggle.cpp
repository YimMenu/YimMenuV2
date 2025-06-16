#include "imgui_toggle.hpp"

#include "imgui.h"
#include "imgui_toggle_math.hpp"
#include "imgui_toggle_palette.hpp"
#include "imgui_toggle_renderer.hpp"

#ifndef IMGUI_DEFINE_MATH_OPERATORS
	#define IMGUI_DEFINE_MATH_OPERATORS
#endif // IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"

using namespace ImGuiToggleConstants;
using namespace ImGuiToggleMath;

namespace
{
	bool ToggleInternal(const char* label, bool* value, const ImGuiToggleConfig& config);

	// sets the given config structure's values to the
	// default ones used by the `Toggle()` overloads.
	inline void SetToAliasDefaults(ImGuiToggleConfig& config)
	{
		config.Flags = ImGuiToggleFlags_Default;
		config.AnimationDuration = AnimationDurationDisabled;
		config.FrameRounding = FrameRoundingDefault;
		config.KnobRounding = KnobRoundingDefault;
	}

	// thread-local data for the `Toggle()` functions to easily call `ToggleInternal()`.
	static thread_local ImGuiToggleConfig _internalConfig;
} // namespace

bool ImGui::Toggle(const char* label, bool* v, const ImVec2& size /*= ImVec2()*/)
{
	::SetToAliasDefaults(::_internalConfig);
	return ::ToggleInternal(label, v, ::_internalConfig);
}

bool ImGui::Toggle(const char* label, bool* v, ImGuiToggleFlags flags, const ImVec2& size /*= ImVec2()*/)
{
	::SetToAliasDefaults(::_internalConfig);
	::_internalConfig.Flags = flags;
	::_internalConfig.Size = size;

	// if the user is using any animation flags,
	// set the default animation duration.
	if ((flags & ImGuiToggleFlags_Animated) != 0)
	{
		_internalConfig.AnimationDuration = AnimationDurationDefault;
	}

	return ::ToggleInternal(label, v, ::_internalConfig);
}

bool ImGui::Toggle(const char* label, bool* v, ImGuiToggleFlags flags, float animation_duration, const ImVec2& size /*= ImVec2()*/)
{
	// this overload implies the toggle should be animated.
	if (animation_duration > 0 && (flags & ImGuiToggleFlags_Animated) != 0)
	{
		// if the user didn't specify ImGuiToggleFlags_Animated, enable it.
		flags = flags | (ImGuiToggleFlags_Animated);
	}

	::SetToAliasDefaults(::_internalConfig);
	::_internalConfig.Flags = flags;
	::_internalConfig.AnimationDuration = animation_duration;
	::_internalConfig.Size = size;

	return ::ToggleInternal(label, v, ::_internalConfig);
}

bool ImGui::Toggle(const char* label, bool* v, ImGuiToggleFlags flags, float frame_rounding, float knob_rounding, const ImVec2& size /*= ImVec2()*/)
{
	::SetToAliasDefaults(::_internalConfig);
	::_internalConfig.Flags = flags;
	::_internalConfig.FrameRounding = frame_rounding;
	::_internalConfig.KnobRounding = knob_rounding;
	::_internalConfig.Size = size;

	return ::ToggleInternal(label, v, ::_internalConfig);
}

bool ImGui::Toggle(const char* label, bool* v, ImGuiToggleFlags flags, float animation_duration, float frame_rounding, float knob_rounding, const ImVec2& size /*= ImVec2()*/)
{
	// this overload implies the toggle should be animated.
	if (animation_duration > 0 && (flags & ImGuiToggleFlags_Animated) != 0)
	{
		// if the user didn't specify ImGuiToggleFlags_Animated, enable it.
		flags = flags | (ImGuiToggleFlags_Animated);
	}

	::_internalConfig.Flags = flags;
	::_internalConfig.AnimationDuration = animation_duration;
	::_internalConfig.FrameRounding = frame_rounding;
	::_internalConfig.KnobRounding = knob_rounding;
	::_internalConfig.Size = size;

	return ::ToggleInternal(label, v, ::_internalConfig);
}

bool ImGui::Toggle(const char* label, bool* v, const ImGuiToggleConfig& config)
{
	return ::ToggleInternal(label, v, config);
}

namespace
{
	bool ToggleInternal(const char* label, bool* v, const ImGuiToggleConfig& config)
	{
		static thread_local ImGuiToggleRenderer renderer;
		renderer.SetConfig(label, v, config);
		return renderer.Render();
	}
}

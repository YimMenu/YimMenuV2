#pragma once

#include "imgui.h"

#ifndef IMGUI_DEFINE_MATH_OPERATORS
	#define IMGUI_DEFINE_MATH_OPERATORS
#endif // IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"

namespace ImGuiToggleMath
{
	// lerp, but backwards!
	template<typename T>
	constexpr inline T ImInvLerp(T a, T b, float value)
	{
		return (T)((value - a) / (b - a));
	}

	// float comparison w/tolerance - can't constexper as ImFabs isn't constexpr.
	inline bool ImApproximately(float a, float b, float tolerance = 0.0001f)
	{
		return ImAbs(a - b) < tolerance;
	}

	// helpers for checking if an ImVec4 is zero or not.
	constexpr inline bool IsZero(const ImVec4& v)
	{
		return v.w == 0 && v.x == 0 && v.y == 0 && v.z == 0;
	}
	constexpr inline bool IsNonZero(const ImVec4& v)
	{
		return v.w != 0 || v.x != 0 || v.y != 0 || v.z != 0;
	}
} // namespace

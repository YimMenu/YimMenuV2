#include "imgui_toggle_palette.hpp"
#include "imgui_toggle_math.hpp"

#include "imgui.h"
#ifndef IMGUI_DEFINE_MATH_OPERATORS
	#define IMGUI_DEFINE_MATH_OPERATORS
#endif // IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"

using namespace ImGuiToggleMath;

void ImGui::UnionPalette(ImGuiTogglePalette* target, const ImGuiTogglePalette* candidate, const ImVec4 colors[], bool v)
{
	target->Knob = colors[ImGuiCol_Text];
	target->KnobHover = colors[ImGuiCol_Text];
	target->Frame = colors[!v ? ImGuiCol_FrameBg : ImGuiCol_Button];
	target->FrameHover = colors[!v ? ImGuiCol_FrameBgHovered : ImGuiCol_ButtonHovered];
	target->FrameBorder = colors[ImGuiCol_Border];
	target->FrameShadow = colors[ImGuiCol_BorderShadow];
	target->KnobBorder = colors[ImGuiCol_Border];
	target->KnobShadow = colors[ImGuiCol_BorderShadow];
	target->A11yGlyph = colors[!v ? ImGuiCol_FrameBg : ImGuiCol_Text];

	// if the user didn't provide a candidate, just provide the theme colored palette.
	if (candidate == nullptr)
	{
		return;
	}

	// if the user did provide a candidate, populate all non-zero colors
#define GET_PALETTE_POPULATE_NONZERO(member)    \
	do                                          \
	{                                           \
		if (IsNonZero(candidate->member))       \
		{                                       \
			target->member = candidate->member; \
		}                                       \
	} while (0)

	GET_PALETTE_POPULATE_NONZERO(Knob);
	GET_PALETTE_POPULATE_NONZERO(KnobHover);
	GET_PALETTE_POPULATE_NONZERO(Frame);
	GET_PALETTE_POPULATE_NONZERO(FrameHover);
	GET_PALETTE_POPULATE_NONZERO(FrameBorder);
	GET_PALETTE_POPULATE_NONZERO(FrameShadow);
	GET_PALETTE_POPULATE_NONZERO(KnobBorder);
	GET_PALETTE_POPULATE_NONZERO(KnobShadow);
	GET_PALETTE_POPULATE_NONZERO(A11yGlyph);

#undef GET_PALETTE_POPULATE_NONZERO
}

void ImGui::BlendPalettes(ImGuiTogglePalette* result, const ImGuiTogglePalette& a, const ImGuiTogglePalette& b, float blend_amount)
{
	// a quick out for if we are at either end of the blend.
	if (ImApproximately(blend_amount, 0.0f))
	{
		*result = a;
		return;
	}
	else if (ImApproximately(blend_amount, 1.0f))
	{
		*result = b;
		return;
	}


#define BLEND_PALETTES_LERP(member)                                \
	do                                                             \
	{                                                              \
		result->member = ImLerp(a.member, b.member, blend_amount); \
	} while (0)

	BLEND_PALETTES_LERP(Knob);
	BLEND_PALETTES_LERP(KnobHover);
	BLEND_PALETTES_LERP(Frame);
	BLEND_PALETTES_LERP(FrameHover);
	BLEND_PALETTES_LERP(FrameBorder);
	BLEND_PALETTES_LERP(FrameShadow);
	BLEND_PALETTES_LERP(KnobBorder);
	BLEND_PALETTES_LERP(KnobShadow);
	BLEND_PALETTES_LERP(A11yGlyph);

#undef BLEND_PALETTES_LERP
}

#pragma once

#include "imgui.h"

// ImGuiTogglePalette: A collection of colors used to customize the rendering of a toggle widget.
//   Leaving any ImVec4 as default (zero) will allow the theme color to be used for that member.
struct ImGuiTogglePalette
{
	// The default knob color.
	ImVec4 Knob;

	// The default knob color, used when when the knob is hovered.
	ImVec4 KnobHover;

	// The background color of the toggle frame.
	ImVec4 Frame;

	// The background color of the toggle frame when the toggle is hovered.
	ImVec4 FrameHover;

	// The background color of the toggle frame's border used when ImGuiToggleFlags_BorderedFrame is specified.
	ImVec4 FrameBorder;

	// The shadow color of the toggle frame.
	ImVec4 FrameShadow;

	// The background color of the toggle knob's border used when ImGuiToggleFlags_BorderedKnob is specified.
	ImVec4 KnobBorder;

	// The shadow color of the toggle knob.
	ImVec4 KnobShadow;

	// The color of the accessibility label or glyph.
	ImVec4 A11yGlyph;
};

namespace ImGui
{
	void UnionPalette(ImGuiTogglePalette* target, const ImGuiTogglePalette* candidate, const ImVec4 colors[], bool v);
	void BlendPalettes(ImGuiTogglePalette* result, const ImGuiTogglePalette& a, const ImGuiTogglePalette& b, float blend_amount);
}

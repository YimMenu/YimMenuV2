#pragma once

#include "imgui.h"
#include "imgui_toggle.hpp"
#include "imgui_toggle_palette.hpp"

#ifndef IMGUI_DEFINE_MATH_OPERATORS
	#define IMGUI_DEFINE_MATH_OPERATORS
#endif // IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"

class ImGuiToggleRenderer
{
public:
	ImGuiToggleRenderer();
	ImGuiToggleRenderer(const char* label, bool* value, const ImGuiToggleConfig& user_config);
	void SetConfig(const char* label, bool* value, const ImGuiToggleConfig& user_config);
	bool Render();

private:
	// toggle state & context
	ImGuiToggleConfig _config;
	ImGuiToggleStateConfig _state;
	ImGuiTogglePalette _palette;

	bool _isMixedValue;
	bool _isHovered;
	bool _isLastActive;
	float _lastActiveTimer;
	float _animationPercent;

	// imgui specific context
	const ImGuiContext* g;
	const ImGuiStyle* _style;
	ImDrawList* _drawList;
	ImGuiID _id;

	// raw ui value & label
	const char* _label;
	bool* _value;

	// calculated values
	ImRect _boundingBox;
	ImVec4 _colorA11yGlyphOff;
	ImVec4 _colorA11yGlyphOn;

	// inline accessors
	inline float GetWidth() const
	{
		return _boundingBox.GetWidth();
	}
	inline float GetHeight() const
	{
		return _boundingBox.GetHeight();
	}
	inline ImVec2 GetPosition() const
	{
		return _boundingBox.Min;
	}
	inline ImVec2 GetToggleSize() const
	{
		return _boundingBox.GetSize();
	}
	inline bool IsAnimated() const
	{
		return (_config.Flags & ImGuiToggleFlags_Animated) != 0 && _config.AnimationDuration > 0;
	}
	inline bool HasBorderedFrame() const
	{
		return (_config.Flags & ImGuiToggleFlags_BorderedFrame) != 0 && _state.FrameBorderThickness > 0;
	}
	inline bool HasShadowedFrame() const
	{
		return (_config.Flags & ImGuiToggleFlags_ShadowedKnob) != 0 && _state.FrameShadowThickness > 0;
	}
	inline bool HasBorderedKnob() const
	{
		return (_config.Flags & ImGuiToggleFlags_BorderedKnob) != 0 && _state.KnobBorderThickness > 0;
	}
	inline bool HasShadowedKnob() const
	{
		return (_config.Flags & ImGuiToggleFlags_ShadowedKnob) != 0 && _state.KnobShadowThickness > 0;
	}
	inline bool HasA11yGlyphs() const
	{
		return (_config.Flags & ImGuiToggleFlags_A11y) != 0;
	}
	inline bool HasCircleKnob() const
	{
		return _config.KnobRounding >= 1.0f;
	}
	inline bool HasRectangleKnob() const
	{
		return _config.KnobRounding < 1.0f;
	}

	// behavior
	void ValidateConfig();
	bool ToggleBehavior(const ImRect& interaction_bounding_box);

	// drawing - general
	void DrawToggle();

	// drawing - frame
	void DrawFrame(ImU32 color_frame);

	// drawing a11y
	void DrawA11yDot(const ImVec2& pos, ImU32 color);
	void DrawA11yGlyph(ImVec2 pos, ImU32 color, bool state, float radius, float thickness);
	void DrawA11yLabel(ImVec2 pos, ImU32 color, const char* label);
	void DrawA11yFrameOverlay(float knob_radius, bool state);
	void DrawA11yFrameOverlays(float knob_radius);

	// drawing - knob
	void DrawCircleKnob(float radius, ImU32 color_knob);
	void DrawRectangleKnob(float radius, ImU32 color_knob);

	// drawing - label
	void DrawLabel(float x_offset);

	// state updating
	void UpdateAnimationPercent();
	void UpdateStateConfig();
	void UpdatePalette();

	// helpers
	ImVec2 CalculateKnobCenter(float radius, float animation_percent, const ImVec2& offset = ImVec2()) const;
	ImRect CalculateKnobBounds(float radius, float animation_percent, const ImVec2& offset = ImVec2()) const;
	void DrawRectBorder(ImRect bounds, ImU32 color_border, float rounding, float thickness);
	void DrawCircleBorder(const ImVec2& center, float radius, ImU32 color_border, float thickness);
	void DrawRectShadow(ImRect bounds, ImU32 color_shadow, float rounding, float thickness);
	void DrawCircleShadow(const ImVec2& center, float radius, ImU32 color_shadow, float thickness);
};

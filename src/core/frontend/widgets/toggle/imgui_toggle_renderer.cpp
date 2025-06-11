#include "imgui_toggle_renderer.hpp"
#include "imgui_toggle_palette.hpp"
#include "imgui_toggle_math.hpp"

using namespace ImGuiToggleConstants;
using namespace ImGuiToggleMath;

namespace
{
	// a small helper to quickly check the mixed value flag.
	inline bool IsItemMixedValue()
	{
		return (GImGui->LastItemData.ItemFlags & ImGuiItemFlags_MixedValue) != 0;
	}
} // namespace

ImGuiToggleRenderer::ImGuiToggleRenderer()
{
	SetConfig(nullptr, nullptr, ImGuiToggleConfig());
}

ImGuiToggleRenderer::ImGuiToggleRenderer(const char* label, bool* value, const ImGuiToggleConfig& user_config) :
    _style(nullptr),
    _label(label),
    _value(value)
{
	SetConfig(label, value, user_config);
}

void ImGuiToggleRenderer::SetConfig(const char* label, bool* value, const ImGuiToggleConfig& user_config)
{
	// store mandatory settings
	_label = label;
	_value = value;

	// copy our user's config and ensure it's valid.
	_config = user_config;
	ValidateConfig();
}

bool ImGuiToggleRenderer::Render()
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	IM_ASSERT(window);
	IM_ASSERT(_label != nullptr);
	IM_ASSERT(_value != nullptr);

	if (window->SkipItems)
	{
		return false;
	}

	// update igui context
	g = GImGui;
	_id = window->GetID(_label);
	_drawList = ImGui::GetWindowDrawList();
	_style = &ImGui::GetStyle();

	// calculate the size of the toggle portion
	const float height = _config.Size.y > 0 ? _config.Size.y : ImGui::GetFrameHeight();
	const float width = _config.Size.x > 0 ? _config.Size.x : height * _config.WidthRatio;

	// get the position of the widget and how large the label should be
	ImVec2 widget_position = window->DC.CursorPos;
	ImVec2 label_size = ImGui::CalcTextSize(_label, nullptr, true);

	// if the knob is offset horizontally outside of the frame in the on state, we want to bump our label over.
	const float label_x_offset = ImMax(0.0f, -_config.On.KnobOffset.x / 2.0f);

	// calculate bounding boxes for the toggle, and the whole widget including the label for interaction
	_boundingBox = ImRect(widget_position, widget_position + ImVec2(width, height));
	ImRect total_bounding_box = ImRect(widget_position,
	    widget_position
	        + ImVec2(
	            width + (label_size.x > 0.0f ? _style->ItemInnerSpacing.x + label_size.x : 0.0f) + label_x_offset,
	            ImMax(height, label_size.y) + _style->FramePadding.y * 2.0f));

	// handle the toggle input behavior
	bool pressed = ToggleBehavior(total_bounding_box);
	_isMixedValue = ::IsItemMixedValue();

	// draw the toggle itself and the label
	DrawToggle();
	DrawLabel(label_x_offset);

	IMGUI_TEST_ENGINE_ITEM_INFO(_id, _label, g.LastItemData.StatusFlags | ImGuiItemStatusFlags_Checkable | (*_value ? ImGuiItemStatusFlags_Checked : 0));
	return pressed;
}


void ImGuiToggleRenderer::ValidateConfig()
{
	IM_ASSERT_USER_ERROR(_config.Size.x >= 0, "Size.x specified was negative.");
	IM_ASSERT_USER_ERROR(_config.Size.y >= 0, "Size.y specified was negative.");

	// if no flags were specified, use defaults.
	if (_config.Flags == ImGuiToggleFlags_None)
	{
		_config.Flags = ImGuiToggleFlags_Default;
	}

	// a zero or negative duration would prevent animation.
	_config.AnimationDuration = ImMax(_config.AnimationDuration, AnimationDurationMinimum);

	// keep our size/scale and rounding numbers sane.
	_config.FrameRounding = ImClamp(_config.FrameRounding, FrameRoundingMinimum, FrameRoundingMaximum);
	_config.KnobRounding = ImClamp(_config.KnobRounding, KnobRoundingMinimum, KnobRoundingMaximum);
	_config.WidthRatio = ImClamp(_config.WidthRatio, WidthRatioMinimum, WidthRatioMaximum);

	// Make sure our a11y labels have values.
	if (_config.On.Label == nullptr)
	{
		_config.On.Label = LabelA11yOnDefault;
	}

	if (_config.Off.Label == nullptr)
	{
		_config.Off.Label = LabelA11yOffDefault;
	}
}

bool ImGuiToggleRenderer::ToggleBehavior(const ImRect& interaction_bounding_box)
{
	ImGui::ItemSize(interaction_bounding_box, _style->FramePadding.y);
	if (!ImGui::ItemAdd(interaction_bounding_box, _id))
	{
		IMGUI_TEST_ENGINE_ITEM_INFO(_id, _label, g.LastItemData.StatusFlags | ImGuiItemStatusFlags_Checkable | (*_value ? ImGuiItemStatusFlags_Checked : 0));
		return false;
	}

	// the meat and potatoes: the actual toggle button
	const ImGuiButtonFlags button_flags = ImGuiButtonFlags_PressedOnClick;
	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(interaction_bounding_box, _id, &hovered, &held, button_flags);
	if (pressed)
	{
		*_value = !(*_value);
		ImGui::MarkItemEdited(_id);
	}

	return pressed;
}

void ImGuiToggleRenderer::DrawToggle()
{
	const float height = GetHeight();
	const float width = GetWidth();

	// update imgui state
	_isHovered = g->HoveredId == _id;
	_isLastActive = g->LastActiveId == _id;
	_lastActiveTimer = g->LastActiveIdTimer;

	// radius is by default half the diameter
	const float knob_radius = height * DiameterToRadiusRatio;

	// update the toggle's animation timer, state, and palette.
	UpdateAnimationPercent();
	UpdateStateConfig();
	UpdatePalette();

	// get colors modified by hover.
	const ImU32 color_frame = ImGui::GetColorU32((_isHovered || *_value) ? _palette.FrameHover : _palette.Frame);
	const ImU32 color_knob = ImGui::GetColorU32((_isHovered || *_value) ? _palette.KnobHover : _palette.Knob);


	// draw the background frame
	DrawFrame(color_frame);

	// draw accessibility labels, if enabled.
	if (HasA11yGlyphs())
	{
		DrawA11yFrameOverlays(knob_radius);
	}

	// draw the knob
	if (HasCircleKnob())
	{
		DrawCircleKnob(knob_radius, color_knob);
	}
	else if (HasRectangleKnob())
	{
		DrawRectangleKnob(knob_radius, color_knob);
	}
	else
	{
		// user didn't specify a knob mode, they get no knob.
		IM_ASSERT_USER_ERROR(false, "No toggle knob type to draw.");
	}
}

void ImGuiToggleRenderer::DrawFrame(ImU32 color_frame)
{
	const float height = GetHeight();
	const float frame_rounding = _config.FrameRounding >= 0 ? height * _config.FrameRounding : height * 0.5f;

	// draw frame shadow, if enabled
	if (HasShadowedFrame())
	{
		const ImU32 color_frame_shadow = ImGui::GetColorU32(_palette.FrameShadow);
		DrawRectShadow(_boundingBox, color_frame_shadow, frame_rounding, _state.FrameShadowThickness);
	}

	// draw frame background
	_drawList->AddRectFilled(_boundingBox.Min, _boundingBox.Max, color_frame, frame_rounding);

	// draw frame border, if enabled
	if (HasBorderedFrame())
	{
		const ImU32 color_frame_border = ImGui::GetColorU32(_palette.FrameBorder);
		DrawRectBorder(_boundingBox, color_frame_border, frame_rounding, _state.FrameBorderThickness);
	}
}

void ImGuiToggleRenderer::DrawA11yDot(const ImVec2& pos, ImU32 color)
{
	ImGui::RenderBullet(_drawList, pos, color);
}

void ImGuiToggleRenderer::DrawA11yGlyph(ImVec2 pos, ImU32 color, bool state, float radius, float thickness)
{
	if (state)
	{
		// draw the I bar
		const float half_thickness = thickness * 0.5f;
		const ImVec2 offset(half_thickness, radius);
		_drawList->AddRectFilled(pos - offset, pos + offset, color);
	}
	else
	{
		// draw the O ring
		const float o_adjustment = 1.0f;
		const float o_radius = radius - o_adjustment;
		const float o_thickness = thickness + o_adjustment;
		pos.x += o_adjustment;
		_drawList->AddCircle(pos, o_radius, color, 0, o_thickness);
	}
}

void ImGuiToggleRenderer::DrawA11yLabel(ImVec2 pos, ImU32 color, const char* label)
{
	// subtract out half the sizes of the text to center them
	const ImVec2 text_size = ImGui::CalcTextSize(label);
	pos.x -= (text_size.x * 0.5f);
	pos.y -= (text_size.y * 0.5f);

	// draw the label.
	_drawList->AddText(pos, color, label);
}

void ImGuiToggleRenderer::DrawA11yFrameOverlay(float knob_radius, bool state)
{
	const float AnimationPercentOff = 0.0f;
	const float AnimationPercentOn = 1.0f;

	// notice we swap the animation percents as compared to the labels/glyphs, as we want to draw the
	// a11y labels where the knob *isn't* when it's in a given state.
	ImVec2 pos = CalculateKnobCenter(knob_radius, state ? AnimationPercentOff : AnimationPercentOn);

	// next, we want to adjust the position to move to a more pleasing spot in the toggle.
	// this is just some tinkering that got to a nice looking area based on the sizes,
	// but this is subject to change.
	const float diameter = ImMax(1.0f, GetHeight() / 3.0f);
	const float radius = diameter * 0.5f;
	const float thickness = ImCeil(radius * 0.2f);
	const ImVec2 adjustment = ImVec2(radius - thickness, 0.0f)
	    * (state ? -1.0f : 1.0f); // if state is true, we want to subtract rather than add.

	pos += adjustment;

	const ImU32 color = state ? ImGui::GetColorU32(_colorA11yGlyphOn) : ImGui::GetColorU32(_colorA11yGlyphOff);

	switch (_config.A11yStyle)
	{
	case ImGuiToggleA11yStyle_Label:
		DrawA11yLabel(pos, color, state ? _config.On.Label : _config.Off.Label);
		break;
	case ImGuiToggleA11yStyle_Glyph:
		DrawA11yGlyph(pos, color, state, radius, thickness);
		break;
	case ImGuiToggleA11yStyle_Dot:
		DrawA11yDot(pos, color);
		break;
	default:
		break;
	}
}

void ImGuiToggleRenderer::DrawA11yFrameOverlays(float knob_radius)
{
	DrawA11yFrameOverlay(knob_radius, true);
	DrawA11yFrameOverlay(knob_radius, false);
}

void ImGuiToggleRenderer::DrawCircleKnob(float radius, ImU32 color_knob)
{
	const float inset_size = ImMin(_state.KnobInset.GetAverage(), radius);
	IM_ASSERT_USER_ERROR(inset_size <= radius, "Inset size needs to be smaller or equal to the knob's radius for circular knobs.");

	const ImVec2 knob_center = CalculateKnobCenter(radius, _animationPercent, _state.KnobOffset);
	const float knob_radius = radius - inset_size;

	// draw knob shadow, if enabled
	if (HasShadowedKnob())
	{
		const ImU32 color_knob_shadow = ImGui::GetColorU32(_palette.KnobShadow);
		DrawCircleShadow(knob_center, knob_radius, color_knob_shadow, _state.KnobShadowThickness);
	}

	// draw circle knob
	_drawList->AddCircleFilled(knob_center, knob_radius, color_knob);

	// draw knob border, if enabled
	if (HasBorderedKnob())
	{
		const ImU32 color_knob_border = ImGui::GetColorU32(_palette.KnobBorder);
		DrawCircleBorder(knob_center, knob_radius, color_knob_border, _state.KnobBorderThickness);
	}
}

void ImGuiToggleRenderer::DrawRectangleKnob(float radius, ImU32 color_knob)
{
	const ImRect bounds = CalculateKnobBounds(radius, _animationPercent, _state.KnobOffset);

	const float knob_diameter_total = bounds.GetHeight();
	const float knob_rounded_radius = (knob_diameter_total * 0.5f) * _config.KnobRounding;

	// draw knob shadow, if enabled
	if (HasShadowedKnob())
	{
		const ImU32 color_knob_shadow = ImGui::GetColorU32(_palette.KnobShadow);
		DrawRectShadow(bounds, color_knob_shadow, _config.KnobRounding, _state.KnobShadowThickness);
	}

	// draw rectangle/squircle knob
	_drawList->AddRectFilled(bounds.Min, bounds.Max, color_knob, knob_rounded_radius);

	// draw knob border, if enabled
	if (HasBorderedKnob())
	{
		const ImU32 color_knob_border = ImGui::GetColorU32(_palette.KnobBorder);
		DrawRectBorder(bounds, color_knob_border, knob_rounded_radius, _state.KnobBorderThickness);
	}
}

void ImGuiToggleRenderer::DrawLabel(float x_offset)
{
	const ImVec2 label_size = ImGui::CalcTextSize(_label, nullptr, true);

	const float half_height = GetHeight() * 0.5f;
	const float label_x = _boundingBox.Max.x + _style->ItemInnerSpacing.x + x_offset;
	const float label_y = _boundingBox.Min.y + half_height - (label_size.y * 0.5f);
	const ImVec2 label_pos = ImVec2(label_x, label_y);

	if (g->LogEnabled)
	{
		ImGui::LogRenderedText(&label_pos, _isMixedValue ? "[~]" : *_value ? "[x]" :
		                                                                     "[ ]");
	}

	if (label_size.x > 0.0f)
	{
		ImGui::RenderText(label_pos, _label);
	}
}

void ImGuiToggleRenderer::UpdateAnimationPercent()
{
	// calculate the lerp percentage for animation,
	// but default to 1/0 for if we aren't animating at all,
	// or 0.5f if we have a mixed value. Also, trying to keep parity with
	// undocumented tristate/mixed/indeterminate checkbox (#2644)

	float t = _isMixedValue ? 0.5f : (*_value ? 1.0f : 0.0f);

	if (IsAnimated() && _isLastActive)
	{
		const float t_anim = ImSaturate(ImInvLerp(0.0f, _config.AnimationDuration, _lastActiveTimer));
		t = *_value ? (t_anim) : (1.0f - t_anim);
	}

	_animationPercent = t;
}

void ImGuiToggleRenderer::UpdateStateConfig()
{
	if (!IsAnimated())
	{
		_state = *_value ? _config.On : _config.Off;
		return;
	}

	_state.FrameBorderThickness = ImLerp(_config.Off.FrameBorderThickness, _config.On.FrameBorderThickness, _animationPercent);
	_state.KnobBorderThickness = ImLerp(_config.Off.KnobBorderThickness, _config.On.KnobBorderThickness, _animationPercent);
	_state.KnobInset = ImLerp(_config.Off.KnobInset, _config.On.KnobInset, _animationPercent);
	_state.KnobOffset = ImLerp(_config.Off.KnobOffset, _config.On.KnobOffset, _animationPercent);
}

void ImGuiToggleRenderer::UpdatePalette()
{
	const ImGuiTogglePalette* on_candidate = _config.On.Palette;
	const ImGuiTogglePalette* off_candidate = _config.Off.Palette;

	if (!IsAnimated())
	{
		ImGui::UnionPalette(
		    &_palette,
		    *_value ? on_candidate : off_candidate,
		    _style->Colors,
		    *_value);

		// store specific colors that shouldn't blend.
		_colorA11yGlyphOff = _palette.A11yGlyph;
		_colorA11yGlyphOn = _palette.A11yGlyph;

		return;
	}

	ImGuiTogglePalette off_unioned;
	ImGuiTogglePalette on_unioned;
	ImGui::UnionPalette(&off_unioned, off_candidate, _style->Colors, false);
	ImGui::UnionPalette(&on_unioned, on_candidate, _style->Colors, true);

	// otherwise, lets lerp them!
	ImGui::BlendPalettes(&_palette, off_unioned, on_unioned, _animationPercent);

	// store specific colors that shouldn't blend.
	_colorA11yGlyphOff = off_unioned.A11yGlyph;
	_colorA11yGlyphOn = on_unioned.A11yGlyph;
}

ImVec2 ImGuiToggleRenderer::CalculateKnobCenter(float radius, float animation_percent, const ImVec2& offset /*= ImVec2()*/) const
{
	const ImVec2 pos = GetPosition();
	const float double_radius = radius * 2.0f;
	const float animation_percent_inverse = 1.0f - animation_percent;

	const float knob_x = (pos.x + radius)
	    + animation_percent * (GetWidth() - double_radius - offset.x)
	    + (animation_percent_inverse * offset.x);
	const float knob_y = pos.y + radius + offset.y;
	return ImVec2(knob_x, knob_y);
}

ImRect ImGuiToggleRenderer::CalculateKnobBounds(float radius, float animation_percent, const ImVec2& offset /*= ImVec2()*/) const
{
	const ImVec2 position = GetPosition();
	const float double_radius = radius * 2.0f;
	const float animation_percent_inverse = 1.0f - animation_percent;

	const float knob_left = (animation_percent * (GetWidth() - double_radius - offset.x))
	    + (animation_percent_inverse * offset.x)
	    + _state.KnobInset.Left;
	const float knob_top = _state.KnobInset.Top + _state.KnobOffset.y;
	const float knob_bottom = GetHeight() - _state.KnobInset.Bottom + _state.KnobOffset.y;
	const float knob_right = (knob_left - _state.KnobInset.Left) + double_radius - _state.KnobInset.Right;

	// if our offsets in the x or y are close to 0,
	// we will just skip drawing the whole thing.
	if (ImApproximately(knob_left, knob_right) || ImApproximately(knob_top, knob_bottom))
	{
		return ImRect();
	}

	const ImVec2 knob_min = position + ImVec2(knob_left, knob_top);
	const ImVec2 knob_max = position + ImVec2(knob_right, knob_bottom);

	return ImRect(knob_min, knob_max);
}

void ImGuiToggleRenderer::DrawRectBorder(ImRect bounds, ImU32 color_border, float rounding, float thickness)
{
	// the border should only grow "inside" the bounding box,
	// so we need to shrink the bounds used to prevent it from puffing out.
	const float half_thickness = thickness * 0.5f;
	bounds.Expand(-half_thickness);

	_drawList->AddRect(bounds.Min, bounds.Max, color_border, rounding, ImDrawFlags_None, thickness);
}

void ImGuiToggleRenderer::DrawCircleBorder(const ImVec2& center, float radius, ImU32 color_border, float thickness)
{
	// the border should only grow "inside" the bounding box,
	// so we need to shrink the radius used to prevent it from puffing out.
	const float half_thickness = thickness * 0.5f;
	radius -= half_thickness;

	_drawList->AddCircle(center, radius, color_border, 0, thickness);
}


void ImGuiToggleRenderer::DrawRectShadow(ImRect bounds, ImU32 color_shadow, float rounding, float thickness)
{
	// the shadow should only grow "outside" the bounding box,
	// so we need to expand the bounds used to puff it out.
	const float half_thickness = thickness * 0.5f;
	bounds.Expand(half_thickness);

	_drawList->AddRect(bounds.Min, bounds.Max, color_shadow, rounding, ImDrawFlags_None, thickness);
}

void ImGuiToggleRenderer::DrawCircleShadow(const ImVec2& center, float radius, ImU32 color_border, float thickness)
{
	// the shadow should only grow "outside" the bounding box,
	// so we need to expand the radius used to puff it out.
	const float half_thickness = thickness * 0.5f;
	radius += half_thickness;

	_drawList->AddCircle(center, radius, color_border, 0, thickness);
}

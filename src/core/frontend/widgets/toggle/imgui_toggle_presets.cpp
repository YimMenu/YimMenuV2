#include "imgui_toggle_presets.hpp"
#include "imgui_toggle_palette.hpp"

namespace
{
	// some color values shared between styles
	const ImVec4 White(1.0f, 1.0f, 1.0f, 1.0f);
	const ImVec4 Black(0.0f, 0.0f, 0.0f, 1.0f);
	const ImVec4 Green(0.24f, 0.52f, 0.15f, 1.0f);
	const ImVec4 GreenBorder(0.39f, 0.62f, 0.32f, 1.0f);
	const ImVec4 GreenHighlight(0.3f, 1.0f, 0.0f, 0.75f);
	const ImVec4 RedHighlight(1.0f, 0.3f, 0.0f, 0.75f);

} // namespace

ImGuiToggleConfig ImGuiTogglePresets::DefaultStyle()
{
	return ImGuiToggleConfig();
}

ImGuiToggleConfig ImGuiTogglePresets::RectangleStyle()
{
	ImGuiToggleConfig config;
	config.Flags |= ImGuiToggleFlags_Animated;
	config.FrameRounding = 0.1f;
	config.KnobRounding = 0.3f;
	config.AnimationDuration = 0.5f;

	return config;
}

ImGuiToggleConfig ImGuiTogglePresets::GlowingStyle()
{
	static ImGuiTogglePalette palette_on;
	palette_on.FrameShadow = ::GreenHighlight;
	palette_on.KnobShadow = ::GreenHighlight;

	static ImGuiTogglePalette palette_off;
	palette_off.FrameShadow = ::RedHighlight;
	palette_off.KnobShadow = ::RedHighlight;

	ImGuiToggleConfig config;
	config.Flags |= ImGuiToggleFlags_Animated | ImGuiToggleFlags_Shadowed;
	config.On.Palette = &palette_on;
	config.Off.Palette = &palette_off;

	return config;
}

ImGuiToggleConfig ImGuiTogglePresets::iOSStyle(const float size_scale /*= 1.0f*/, bool light_mode /*= false*/)
{
	const ImVec4 frame_on(0.3f, 0.85f, 0.39f, 1.0f);
	const ImVec4 frame_on_hover(0.0f, 1.0f, 0.57f, 1.0f);
	const ImVec4 dark_mode_frame_off(0.22f, 0.22f, 0.24f, 1.0f);
	const ImVec4 light_mode_frame_off(0.91f, 0.91f, 0.92f, 1.0f);
	const ImVec4 dark_mode_frame_off_hover(0.4f, 0.4f, 0.4f, 1.0f);
	const ImVec4 light_mode_frame_off_hover(0.7f, 0.7f, 0.7f, 1.0f);
	const ImVec4 light_gray(0.89f, 0.89f, 0.89f, 1.0f);
	const ImVec4 a11y_glyph_on(1.0f, 1.0f, 1.0f, 1.0f);
	const ImVec4 a11y_glyph_off(0.4f, 0.4f, 0.4f, 1.0f);

	const float ios_width = 153 * size_scale;
	const float ios_height = 93 * size_scale;
	const float ios_frame_border_thickness = 0.0f * size_scale;
	const float ios_border_thickness = 0.0f * size_scale;
	const float ios_offset = 0.0f * size_scale;
	const float ios_inset = 6.0f * size_scale;

	// setup 'on' colors
	static ImGuiTogglePalette ios_palette_on;
	ios_palette_on.Knob = ::White;
	ios_palette_on.Frame = frame_on;
	ios_palette_on.FrameHover = frame_on_hover;
	ios_palette_on.KnobBorder = light_gray;
	ios_palette_on.FrameBorder = light_gray;
	ios_palette_on.A11yGlyph = a11y_glyph_on;

	// setup 'off' colors
	static ImGuiTogglePalette ios_palette_off;
	ios_palette_off.Knob = ::White;
	ios_palette_off.Frame = light_mode ? light_mode_frame_off : dark_mode_frame_off;
	ios_palette_off.FrameHover = light_mode ? light_mode_frame_off_hover : light_mode_frame_off_hover;
	ios_palette_off.KnobBorder = light_gray;
	ios_palette_off.FrameBorder = light_gray;
	ios_palette_off.A11yGlyph = a11y_glyph_off;

	// setup config
	ImGuiToggleConfig config;
	config.Size = ImVec2(ios_width, ios_height);
	config.Flags |= ImGuiToggleFlags_A11y
	    | ImGuiToggleFlags_Animated
	    | (light_mode ? ImGuiToggleFlags_Bordered : 0);
	config.A11yStyle = ImGuiToggleA11yStyle_Glyph;

	// setup 'on' config
	config.On.FrameBorderThickness = 0;
	config.On.KnobBorderThickness = ios_border_thickness;
	config.On.KnobOffset = ImVec2(ios_offset, 0);
	config.On.KnobInset = ios_inset;
	config.On.Palette = &ios_palette_on;

	// setup 'off' config
	config.Off.FrameBorderThickness = ios_frame_border_thickness;
	config.Off.KnobBorderThickness = ios_border_thickness;
	config.Off.KnobOffset = ImVec2(ios_offset, 0);
	config.Off.KnobInset = ios_inset;
	config.Off.Palette = &ios_palette_off;

	return config;
}

ImGuiToggleConfig ImGuiTogglePresets::MaterialStyle(float size_scale /*= 1.0f*/)
{
	const ImVec4 purple(0.4f, 0.08f, 0.97f, 1.0f);
	const ImVec4 purple_dim(0.78f, 0.65f, 0.99f, 1.0f);
	const ImVec4 purple_hover(0.53f, 0.08f, 1.0f, 1.0f);

	const ImVec2 material_size(37 * size_scale, 16 * size_scale);
	const float material_inset = -2.5f * size_scale;

	static ImGuiTogglePalette material_palette_on;
	material_palette_on.Frame = purple_dim;
	material_palette_on.FrameHover = purple_dim;
	material_palette_on.Knob = purple;
	material_palette_on.KnobHover = purple_hover;

	// setup config
	ImGuiToggleConfig config;
	config.Flags |= ImGuiToggleFlags_Animated;
	config.Size = material_size;
	config.On.KnobInset = config.Off.KnobInset = material_inset;
	config.On.KnobOffset = config.Off.KnobOffset = ImVec2(-material_inset, 0);
	config.On.Palette = &material_palette_on;

	return config;
}

ImGuiToggleConfig ImGuiTogglePresets::MinecraftStyle(float size_scale /*= 1.0f*/)
{
	const ImVec4 gray(0.35f, 0.35f, 0.35f, 1.0f);
	const ImVec4 dark_gray(0.12f, 0.12f, 0.12f, 1.0f);
	const ImVec4 frame_border_off(0.6f, 0.6f, 0.61f, 1.0f);
	const ImVec4 toggle_frame_off(0.55f, 0.55f, 0.56f, 1.0f);
	const ImVec4 gray_knob(0.82f, 0.82f, 0.83f, 1.0f);

	const ImVec2 minecraft_knob_size(56.0f * size_scale, 40.0f * size_scale);
	const ImVec2 minecraft_size(104.0f * size_scale, 40.0f * size_scale); // 112x48
	const float minecraft_borders = 4.0f * size_scale;
	const ImVec2 minecraft_offset(0.0f * size_scale, -minecraft_borders * 2.0f);
	const ImOffsetRect minecraft_inset(
	    0.0f * size_scale,   // top
	    -16.0f * size_scale, // left
	    0.0f * size_scale,   // bottom
	    0.0f * size_scale    // right
	);
	const float minecraft_rounding = 0.0f; // disable rounding
	const float minecraft_shadows = 4.0f * size_scale;

	// set up the "on" palette.
	static ImGuiTogglePalette minecraft_palette_on;
	minecraft_palette_on.Frame = ::Green;
	minecraft_palette_on.FrameHover = ::Green;
	minecraft_palette_on.FrameBorder = ::GreenBorder;
	minecraft_palette_on.FrameShadow = ::Black;
	minecraft_palette_on.Knob = gray_knob;
	minecraft_palette_on.KnobHover = gray_knob;
	minecraft_palette_on.A11yGlyph = ::White;
	minecraft_palette_on.KnobBorder = ::White;
	minecraft_palette_on.KnobShadow = ::Black;

	// start the "off" palette as a copy of the on
	static ImGuiTogglePalette minecraft_palette_off;
	minecraft_palette_off = minecraft_palette_on;

	// make changes to the off palette
	minecraft_palette_off.Frame = toggle_frame_off;
	minecraft_palette_off.FrameHover = toggle_frame_off;
	minecraft_palette_off.FrameBorder = frame_border_off;

	// setup config
	ImGuiToggleConfig config;
	config.Flags |= ImGuiToggleFlags_A11y | ImGuiToggleFlags_Bordered | ImGuiToggleFlags_Shadowed;
	config.Size = minecraft_size;
	config.FrameRounding = minecraft_rounding;
	config.KnobRounding = minecraft_rounding;
	config.A11yStyle = ImGuiToggleA11yStyle_Glyph;

	// set up the "on" state configuration
	config.On.KnobInset = minecraft_inset;
	config.On.KnobOffset = minecraft_offset;
	config.On.FrameBorderThickness = minecraft_borders;
	config.On.FrameShadowThickness = minecraft_shadows;
	config.On.KnobBorderThickness = minecraft_borders;
	config.On.KnobShadowThickness = minecraft_shadows;
	config.On.Palette = &minecraft_palette_on;

	// duplicate the "on" config to the "off", then make changes.
	config.Off = config.On;
	config.Off.KnobInset = minecraft_inset.MirrorHorizontally();
	config.Off.Palette = &minecraft_palette_off;

	return config;
}

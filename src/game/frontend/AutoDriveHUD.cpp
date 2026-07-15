#include "AutoDriveHUD.hpp"

#include "game/features/vehicle/AutoDriveHudTelemetry.hpp"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <unordered_map>
#include <vector>

namespace YimMenu
{
	using namespace Features::AutoDriveInternal;
	using namespace std::chrono_literals;

	namespace
	{
		constexpr ImU32 kPanel = IM_COL32(15, 22, 31, 224);
		constexpr ImU32 kPanelBorder = IM_COL32(93, 120, 143, 140);
		constexpr ImU32 kBlue = IM_COL32(35, 144, 255, 255);
		constexpr ImU32 kBlueShadow = IM_COL32(3, 25, 48, 230);
		constexpr ImU32 kLane = IM_COL32(176, 195, 210, 118);
		constexpr ImU32 kText = IM_COL32(235, 244, 250, 255);
		constexpr ImU32 kMuted = IM_COL32(143, 163, 178, 255);
		struct Projection
		{
			ImVec2 m_PanelMin{};
			ImVec2 m_PanelMax{};
			float m_CenterX = 0.0f;
			float m_EgoY = 0.0f;
			float m_RoadTop = 0.0f;
			float m_Width = 0.0f;

			ImVec2 Project(HudPoint point) const
			{
				if (point.m_Y >= 0.0f)
				{
					const auto normalized = std::clamp(point.m_Y / 90.0f, 0.0f, 1.0f);
					const auto depth = std::pow(normalized, 0.72f);
					const auto horizontalScale = std::lerp(m_Width / 34.0f, m_Width / 120.0f, depth);
					return {m_CenterX + point.m_X * horizontalScale, m_EgoY - depth * (m_EgoY - m_RoadTop)};
				}

				const auto behind = std::clamp(-point.m_Y / 30.0f, 0.0f, 1.0f);
				return {m_CenterX + point.m_X * (m_Width / 34.0f), m_EgoY + behind * (m_PanelMax.y - 18.0f - m_EgoY)};
			}

			float HorizontalScale(float forward) const
			{
				const auto depth = std::pow(std::clamp(std::max(0.0f, forward) / 90.0f, 0.0f, 1.0f), 0.72f);
				return std::lerp(m_Width / 34.0f, m_Width / 120.0f, depth);
			}

			float DepthFade(float forward) const
			{
				return std::clamp(1.15f - std::max(0.0f, forward) / 120.0f, 0.25f, 1.0f);
			}
		};

		struct RenderEntity
		{
			HudEntitySnapshot m_Data{};
			std::chrono::steady_clock::time_point m_LastSeen{};
		};

		ImU32 WithAlpha(ImU32 color, float alpha)
		{
			const auto original = static_cast<float>((color >> IM_COL32_A_SHIFT) & 0xFF) / 255.0f;
			const auto value = static_cast<ImU32>(std::clamp(original * alpha, 0.0f, 1.0f) * 255.0f);
			return (color & ~IM_COL32_A_MASK) | (value << IM_COL32_A_SHIFT);
		}

		const char* PhaseLabel(const AutoDriveHudSnapshot& snapshot)
		{
			if (snapshot.m_RouteCalculating)
				return "CALCULATING";
			switch (snapshot.m_Phase)
			{
			case RoutePhase::Navigation: return "NAVIGATING";
			case RoutePhase::TargetLost: return "CALCULATING";
			case RoutePhase::Wander: return "ROAMING";
			case RoutePhase::Arrived: return "ARRIVING";
			default: return "STANDBY";
			}
		}

		void DrawPolyline(ImDrawList* drawList, const Projection& projection, const std::vector<HudPoint>& points, ImU32 color, float thickness)
		{
			std::vector<ImVec2> projected;
			projected.reserve(points.size());
			for (const auto& point : points)
			{
				if (point.m_Y >= -30.0f && point.m_Y <= 170.0f)
					projected.push_back(projection.Project(point));
			}
			if (projected.size() >= 2)
				drawList->AddPolyline(projected.data(), static_cast<int>(projected.size()), color, ImDrawFlags_None, thickness);
		}

		void DrawRoute(ImDrawList* drawList, const Projection& projection, const AutoDriveHudSnapshot& snapshot, float scale)
		{
			if (!snapshot.m_RouteReliable || snapshot.m_RoutePoints.size() < 2)
				return;

			if (!snapshot.m_RoutePredicted)
			{
				DrawPolyline(drawList, projection, snapshot.m_RoutePoints, kBlueShadow, 8.0f * scale);
				DrawPolyline(drawList, projection, snapshot.m_RoutePoints, kBlue, 4.0f * scale);
				return;
			}

			for (std::size_t index = 1; index < snapshot.m_RoutePoints.size(); ++index)
			{
				if (index % 2 == 0)
					continue;
				const auto from = projection.Project(snapshot.m_RoutePoints[index - 1]);
				const auto to = projection.Project(snapshot.m_RoutePoints[index]);
				drawList->AddLine(from, to, kBlueShadow, 7.0f * scale);
				drawList->AddLine(from, to, WithAlpha(kBlue, 0.85f), 3.5f * scale);
			}
		}

		void DrawVehicle(ImDrawList* drawList, const Projection& projection, const HudEntitySnapshot& entity, float alpha)
		{
			const auto center = projection.Project(entity.m_Position);
			const auto pxPerMeter = projection.HorizontalScale(entity.m_Position.m_Y);
			const auto halfWidth = std::clamp(entity.m_Footprint.m_X * pxPerMeter * 0.5f, 2.5f, 15.0f);
			const auto halfLength = std::clamp(entity.m_Footprint.m_Y * pxPerMeter * 0.38f, 4.0f, 22.0f);
			const auto direction = ImVec2(std::sin(entity.m_RelativeHeadingRadians), -std::cos(entity.m_RelativeHeadingRadians));
			const auto right = ImVec2(-direction.y, direction.x);
			ImVec2 corners[4] = {
			    center + direction * halfLength + right * halfWidth,
			    center + direction * halfLength - right * halfWidth,
			    center - direction * halfLength - right * halfWidth,
			    center - direction * halfLength + right * halfWidth};
			drawList->AddConvexPolyFilled(corners, 4, WithAlpha(IM_COL32(166, 181, 193, 245), alpha));
			drawList->AddPolyline(corners, 4, WithAlpha(IM_COL32(233, 241, 246, 235), alpha), ImDrawFlags_Closed, 1.0f);
			drawList->AddLine(corners[0], corners[1], WithAlpha(IM_COL32(235, 248, 255, 245), alpha), 2.0f);
		}

		void DrawPedestrian(ImDrawList* drawList, const Projection& projection, const HudEntitySnapshot& entity, float alpha)
		{
			const auto center = projection.Project(entity.m_Position);
			const auto size = std::clamp(projection.HorizontalScale(entity.m_Position.m_Y) * 0.42f, 2.5f, 7.0f);
			const auto color = WithAlpha(IM_COL32(255, 184, 88, 255), alpha);
			drawList->AddCircleFilled({center.x, center.y - size}, size * 0.45f, color);
			drawList->AddLine({center.x, center.y - size * 0.45f}, {center.x, center.y + size}, color, std::max(1.0f, size * 0.35f));
		}

		void DrawTrafficLight(ImDrawList* drawList, const Projection& projection, const HudEntitySnapshot& entity, float alpha)
		{
			const auto center = projection.Project(entity.m_Position);
			const auto size = std::clamp(projection.HorizontalScale(entity.m_Position.m_Y) * 0.55f, 3.0f, 9.0f);
			drawList->AddLine({center.x, center.y + size * 2.5f}, {center.x, center.y}, WithAlpha(IM_COL32(126, 139, 148, 255), alpha), 1.5f);
			drawList->AddRectFilled({center.x - size * 0.55f, center.y - size * 1.7f}, {center.x + size * 0.55f, center.y}, WithAlpha(IM_COL32(35, 41, 46, 255), alpha), 2.0f);
			const auto lamp = entity.m_TrafficLightState == TrafficLightState::RedInferred
			    ? IM_COL32(255, 65, 65, 255)
			    : IM_COL32(132, 142, 150, 255);
			drawList->AddCircleFilled({center.x, center.y - size * 1.15f}, size * 0.31f, WithAlpha(lamp, alpha));
		}

		void DrawObject(ImDrawList* drawList, const Projection& projection, const HudEntitySnapshot& entity, float alpha)
		{
			const auto center = projection.Project(entity.m_Position);
			const auto pxPerMeter = projection.HorizontalScale(entity.m_Position.m_Y);
			const auto size = std::clamp(pxPerMeter * std::max(0.5f, entity.m_Footprint.m_X), 3.0f, 22.0f);
			switch (entity.m_Kind)
			{
			case HudEntityKind::Cone:
			{
				const ImVec2 points[3] = {{center.x, center.y - size}, {center.x - size * 0.65f, center.y + size * 0.55f}, {center.x + size * 0.65f, center.y + size * 0.55f}};
				drawList->AddConvexPolyFilled(points, 3, WithAlpha(IM_COL32(255, 126, 35, 255), alpha));
				break;
			}
			case HudEntityKind::Barrier:
				drawList->AddRectFilled({center.x - size, center.y - size * 0.28f}, {center.x + size, center.y + size * 0.28f}, WithAlpha(IM_COL32(242, 153, 53, 255), alpha), 1.0f);
				drawList->AddLine({center.x - size * 0.7f, center.y + size * 0.25f}, {center.x - size * 0.3f, center.y - size * 0.25f}, WithAlpha(IM_COL32(244, 244, 235, 255), alpha), 2.0f);
				drawList->AddLine({center.x + size * 0.1f, center.y + size * 0.25f}, {center.x + size * 0.5f, center.y - size * 0.25f}, WithAlpha(IM_COL32(244, 244, 235, 255), alpha), 2.0f);
				break;
			case HudEntityKind::Barrel:
				drawList->AddCircleFilled(center, size * 0.55f, WithAlpha(IM_COL32(210, 116, 46, 255), alpha));
				break;
			case HudEntityKind::Bollard:
				drawList->AddRectFilled({center.x - size * 0.22f, center.y - size}, {center.x + size * 0.22f, center.y + size * 0.35f}, WithAlpha(IM_COL32(224, 208, 93, 255), alpha), size * 0.18f);
				break;
			case HudEntityKind::Tree:
				drawList->AddLine({center.x, center.y + size * 0.7f}, {center.x, center.y}, WithAlpha(IM_COL32(113, 82, 51, 255), alpha), std::max(1.0f, size * 0.2f));
				drawList->AddCircleFilled({center.x, center.y - size * 0.45f}, size * 0.72f, WithAlpha(IM_COL32(67, 151, 99, 235), alpha));
				break;
			default:
				drawList->AddRectFilled({center.x - size * 0.45f, center.y - size * 0.45f}, {center.x + size * 0.45f, center.y + size * 0.45f}, WithAlpha(IM_COL32(152, 162, 169, 220), alpha), 2.0f);
				break;
			}
		}

		void DrawEntity(ImDrawList* drawList, const Projection& projection, const HudEntitySnapshot& entity, float alpha)
		{
			alpha *= projection.DepthFade(entity.m_Position.m_Y);
			switch (entity.m_Kind)
			{
			case HudEntityKind::Vehicle: DrawVehicle(drawList, projection, entity, alpha); break;
			case HudEntityKind::Pedestrian: DrawPedestrian(drawList, projection, entity, alpha); break;
			case HudEntityKind::TrafficLight: DrawTrafficLight(drawList, projection, entity, alpha); break;
			default: DrawObject(drawList, projection, entity, alpha); break;
			}
		}

		void DrawEgoVehicle(ImDrawList* drawList, const Projection& projection, float scale)
		{
			const auto center = projection.Project({0.0f, 0.0f});
			const auto halfWidth = 12.0f * scale;
			const auto halfLength = 22.0f * scale;
			ImVec2 points[4] = {
			    {center.x - halfWidth * 0.7f, center.y - halfLength},
			    {center.x + halfWidth * 0.7f, center.y - halfLength},
			    {center.x + halfWidth, center.y + halfLength},
			    {center.x - halfWidth, center.y + halfLength}};
			drawList->AddConvexPolyFilled(points, 4, IM_COL32(235, 242, 247, 255));
			drawList->AddPolyline(points, 4, IM_COL32(35, 144, 255, 255), ImDrawFlags_Closed, 2.0f * scale);
			drawList->AddRectFilled({center.x - halfWidth * 0.55f, center.y - halfLength * 0.45f}, {center.x + halfWidth * 0.55f, center.y + halfLength * 0.1f}, IM_COL32(78, 104, 125, 255), 3.0f * scale);
		}

		void DrawHeader(ImDrawList* drawList, const Projection& projection, const AutoDriveHudSnapshot& snapshot, float scale)
		{
			const auto font = ImGui::GetFont();
			char speed[16]{};
			std::snprintf(speed, sizeof(speed), "%d", snapshot.m_SpeedKph);
			drawList->AddText(font, 30.0f * scale, {projection.m_PanelMin.x + 20.0f * scale, projection.m_PanelMin.y + 14.0f * scale}, kText, speed);
			drawList->AddText(font, 12.0f * scale, {projection.m_PanelMin.x + 22.0f * scale, projection.m_PanelMin.y + 47.0f * scale}, kMuted, "km/h");

			char target[32]{};
			std::snprintf(target, sizeof(target), "TARGET %d", snapshot.m_TargetSpeedKph);
			drawList->AddText(font, 12.0f * scale, {projection.m_PanelMin.x + 88.0f * scale, projection.m_PanelMin.y + 21.0f * scale}, kMuted, target);
			drawList->AddText(font, 13.0f * scale, {projection.m_PanelMin.x + 88.0f * scale, projection.m_PanelMin.y + 42.0f * scale}, kText, PhaseLabel(snapshot));

			const auto owner = snapshot.m_Owner == Owner::Npc ? "NPC AUTO" : "AUTO";
			const auto ownerSize = ImGui::CalcTextSize(owner);
			drawList->AddText({projection.m_PanelMax.x - ownerSize.x - 18.0f * scale, projection.m_PanelMin.y + 22.0f * scale}, kBlue, owner);
			drawList->AddLine({projection.m_PanelMin.x + 16.0f * scale, projection.m_PanelMin.y + 70.0f * scale}, {projection.m_PanelMax.x - 16.0f * scale, projection.m_PanelMin.y + 70.0f * scale}, IM_COL32(112, 139, 158, 80), 1.0f);

			if (snapshot.m_Maneuver == HudManeuver::None)
				return;
			const auto changingRight = snapshot.m_Maneuver == HudManeuver::LaneChangeRight;
			const auto label = changingRight ? "CHANGING LANE RIGHT" : "CHANGING LANE LEFT";
			const auto labelSize = ImGui::CalcTextSize(label);
			const auto labelY = projection.m_PanelMin.y + 78.0f * scale;
			drawList->AddText({projection.m_CenterX - labelSize.x * 0.5f, labelY}, kBlue, label);
			const auto pulse = static_cast<int>(ImGui::GetTime() * 4.0) % 3;
			for (int index = 0; index < 3; ++index)
			{
				const auto x = projection.m_CenterX + (index - 1) * 12.0f * scale;
				const auto alpha = index == pulse ? 1.0f : 0.38f;
				const auto direction = changingRight ? 1.0f : -1.0f;
				const ImVec2 tip{x + direction * 5.0f * scale, labelY + 23.0f * scale};
				drawList->AddLine({x - direction * 3.0f * scale, tip.y - 5.0f * scale}, tip, WithAlpha(kBlue, alpha), 2.0f * scale);
				drawList->AddLine(tip, {x - direction * 3.0f * scale, tip.y + 5.0f * scale}, WithAlpha(kBlue, alpha), 2.0f * scale);
			}
		}
	}

	void AutoDriveHUD::Draw()
	{
		static std::unordered_map<std::uint32_t, RenderEntity> renderEntities;
		static std::chrono::steady_clock::time_point lastSnapshotTime{};

		const auto snapshot = AutoDriveHudTelemetry::GetSnapshot();
		const auto now = std::chrono::steady_clock::now();
		if (!snapshot || !AutoDriveHudTelemetry::IsEnabled() || !snapshot->m_Visible || snapshot->m_Suppressed
		    || snapshot->m_CapturedAt == std::chrono::steady_clock::time_point{} || now - snapshot->m_CapturedAt > 500ms)
		{
			renderEntities.clear();
			lastSnapshotTime = {};
			return;
		}

		if (snapshot->m_CapturedAt != lastSnapshotTime)
		{
			for (const auto& entity : snapshot->m_Entities)
				renderEntities[entity.m_TrackId] = {entity, now};
			lastSnapshotTime = snapshot->m_CapturedAt;
		}
		for (auto iterator = renderEntities.begin(); iterator != renderEntities.end();)
		{
			if (now - iterator->second.m_LastSeen > 150ms)
				iterator = renderEntities.erase(iterator);
			else
				++iterator;
		}

		const auto viewport = ImGui::GetMainViewport();
		const auto workWidth = viewport->WorkSize.x;
		const auto workHeight = viewport->WorkSize.y;
		const auto scale = std::clamp(std::min(workWidth / 1920.0f, workHeight / 1080.0f), 0.70f, 1.25f);
		const auto width = std::clamp(420.0f * scale, 280.0f, 480.0f);
		const auto maximumHeight = std::max(240.0f, std::min(680.0f, workHeight - 40.0f));
		const auto height = std::clamp(600.0f * scale, std::min(360.0f, maximumHeight), maximumHeight);
		const ImVec2 position{
		    viewport->WorkPos.x + workWidth - width - 20.0f * scale,
		    viewport->WorkPos.y + (workHeight - height) * 0.5f};

		ImGui::SetNextWindowPos(position, ImGuiCond_Always);
		ImGui::SetNextWindowSize({width, height}, ImGuiCond_Always);
		ImGui::SetNextWindowBgAlpha(0.0f);
		const auto flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
		    | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar
		    | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoInputs
		    | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBringToFrontOnFocus;
		if (!ImGui::Begin("##autodrive-fsd-hud", nullptr, flags))
		{
			ImGui::End();
			return;
		}

		auto drawList = ImGui::GetWindowDrawList();
		const ImVec2 panelMin = ImGui::GetWindowPos();
		const ImVec2 panelMax = panelMin + ImGui::GetWindowSize();
		drawList->AddRectFilled(panelMin, panelMax, kPanel, 16.0f * scale);
		drawList->AddRect(panelMin, panelMax, kPanelBorder, 16.0f * scale, ImDrawFlags_None, 1.0f);
		drawList->PushClipRect(panelMin, panelMax, true);

		const Projection projection{
		    panelMin,
		    panelMax,
		    (panelMin.x + panelMax.x) * 0.5f,
		    panelMin.y + height * 0.78f,
		    panelMin.y + 108.0f * scale,
		    width};

		for (const auto& boundary : snapshot->m_LaneBoundaries)
			DrawPolyline(drawList, projection, boundary, kLane, std::max(1.0f, 1.25f * scale));
		DrawRoute(drawList, projection, *snapshot, scale);

		std::vector<std::pair<float, RenderEntity*>> sorted;
		sorted.reserve(renderEntities.size());
		for (auto& [id, entity] : renderEntities)
			sorted.emplace_back(entity.m_Data.m_Position.m_Y, &entity);
		std::sort(sorted.begin(), sorted.end(), [](const auto& left, const auto& right) {
			return left.first > right.first;
		});
		for (const auto& [depth, renderEntity] : sorted)
		{
			auto entity = renderEntity->m_Data;
			const auto extrapolation = std::clamp(std::chrono::duration<float>(now - snapshot->m_CapturedAt).count(), 0.0f, 0.1f);
			entity.m_Position.m_X += entity.m_Velocity.m_X * extrapolation;
			entity.m_Position.m_Y += entity.m_Velocity.m_Y * extrapolation;
			const auto fade = 1.0f - std::clamp(std::chrono::duration<float>(now - renderEntity->m_LastSeen - 50ms).count() / 0.1f, 0.0f, 1.0f);
			DrawEntity(drawList, projection, entity, fade);
		}

		DrawEgoVehicle(drawList, projection, scale);
		DrawHeader(drawList, projection, *snapshot, scale);
		drawList->PopClipRect();
		ImGui::End();
	}
}

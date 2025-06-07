#include "ESP.hpp"
#include "game/gta/Object.hpp"
#include "common.hpp"
#include "core/commands/BoolCommand.hpp"
#include "core/commands/ColorCommand.hpp"
#include "core/util/Math.hpp"
#include "game/backend/Players.hpp"
#include "game/backend/Self.hpp"
#include "game/pointers/Pointers.hpp"
#include "game/gta/Pools.hpp"
#include "game/gta/Scripts.hpp"
//#include "game/gta/data/PedModels.hpp"
#include "game/gta/data/RandomEvents.hpp"
#include "game/gta/invoker/Invoker.hpp"
#include "game/gta/Natives.hpp"
#include "types/script/globals/GPBD_FM_2.hpp"
#include "types/script/globals/GSBD_RandomEvents.hpp"
#include "types/script/locals/FMRandomEvents.hpp"

namespace
{
	// Human
	constexpr int headBone          = 31086;
	constexpr int neckBone          = 39317;
	constexpr int torsoBone         = 23553;
	constexpr int leftHandBone      = 18905;
	constexpr int rightHandBone     = 57005;
	constexpr int leftFootBone      = 14201;
	constexpr int rightFootBone     = 52301;
	constexpr int leftElbowBone     = 22711;
	constexpr int rightElbowBone    = 2992;
	constexpr int leftKneeBone      = 46078;
	constexpr int rightKneeBone     = 16335;
	constexpr int leftShoulderBone  = 61163; // TODO verify all the bones
	constexpr int rightShoulderBone = 28252;
}

namespace YimMenu::Features
{
	// Players
	BoolCommand _ESPDrawPlayers("espdrawplayers", "Draw Players", "Should the ESP draw players?");
	BoolCommand _ESPDrawDeadPlayers("espdrawdeadplayers", "Draw Dead Players", "Should the ESP draw dead players?");

	BoolCommand _ESPName("espnameplayers", "Show Player Name", "Should the ESP draw player names?");
	BoolCommand _ESPDistance("espdistanceplayers", "Show Player Distance", "Should the ESP draw player distance?");
	BoolCommand _ESPSkeleton("espskeletonplayers", "Show Player Skeleton", "Should the ESP draw player skeletons?");

	ColorCommand _NameColorPlayers("namecolorplayers", "Player Name Color", "Changes the color of the name ESP for players", ImVec4{1.0f, 1.0f, 1.0f, 1.0f});
	ColorCommand _DistanceColorPlayers("distancecolorplayers", "Player Distance Color", "Changes the color of the distance ESP for players", ImVec4{1.0f, 1.0f, 1.0f, 1.0f});
	ColorCommand _SkeletonColorPlayers("skeletoncolorplayers", "Player Skeleton Color", "Changes the color of the skeleton ESP for players", ImVec4{1.0f, 1.0f, 1.0f, 1.0f});

	// Peds
	BoolCommand _ESPDrawPeds("espdrawpeds", "Draw Peds", "Should the ESP draw peds?");
	BoolCommand _ESPDrawDeadPeds("espdrawdeadpeds", "Draw Dead Peds", "Should the ESP draw dead peds?");

	BoolCommand _ESPModelPeds("espmodelspeds", "Show Ped Model", "Should the ESP draw ped models?");
	BoolCommand _ESPNetworkInfoPeds("espnetinfopeds", "Show Ped Network Info", "Should the ESP draw network info?");
	BoolCommand _ESPScriptInfoPeds("espscriptinfopeds", "Show Ped Script Info", "Should the ESP draw script info?");
	BoolCommand _ESPDistancePeds("espdistancepeds", "Show Ped Distance", "Should the ESP draw distance?");
	BoolCommand _ESPSkeletonPeds("espskeletonpeds", "Show Ped Skeleton", "Should the ESP draw the skeleton?");

	ColorCommand _HashColorPeds("hashcolorpeds", "Ped Hash Color", "Changes the color of the hash ESP for peds", ImVec4{1.0f, 1.0f, 1.0f, 1.0f});
	ColorCommand _DistanceColorPeds("distancecolorpeds", "Ped Distance Color", "Changes the color of the distance ESP for peds", ImVec4{1.0f, 1.0f, 1.0f, 1.0f});
	ColorCommand _SkeletonColorPeds("skeletoncolorpeds", "Ped Skeleton Color", "Changes the color of the skeleton ESP for peds", ImVec4{1.0f, 1.0f, 1.0f, 1.0f});

	// Random Events
	BoolCommand _ESPDrawRandomEvents("esprandomevents", "Random Events ESP", "Should the ESP draw Random Events?");

	// objects
	BoolCommand _ESPDrawObjects("espdrawobjects", "Show Object Model", "Should the ESP draw objects model?");
	BoolCommand _ESPDrawCameras("espdrawcameras", "Show Cameras", "Should the ESP draw Camera cameras?");
	BoolCommand _ESPDrawCache("espdrawcache", "Show G's Cache", "Should the ESP draw G's Cache?");
	BoolCommand _ESPDrawSignalJammers("espdrawsignaljammers", "Show Signal Jammers", "Should the ESP draw Signal Jammers?");
}

namespace YimMenu
{
	static ImVec4 death_bg         = ImVec4(0.117f, 0.113f, 0.172f, .75f);
	static ImVec4 armor_blue_bg    = ImVec4(0.36f, 0.71f, 0.89f, .75f);
	static ImVec4 armor_blue       = ImVec4(0.36f, 0.71f, 0.89f, 1.f);
	static ImVec4 health_green_bg  = ImVec4(0.29f, 0.69f, 0.34f, .75f);
	static ImVec4 health_green     = ImVec4(0.29f, 0.69f, 0.34f, 1.f);
	static ImVec4 health_yellow_bg = ImVec4(0.69f, 0.49f, 0.29f, .75f);
	static ImVec4 health_yellow    = ImVec4(0.69f, 0.49f, 0.29f, 1.f);
	static ImVec4 health_red_bg    = ImVec4(0.69f, 0.29f, 0.29f, .75f);
	static ImVec4 health_red       = ImVec4(0.69f, 0.29f, 0.29f, 1.f);
	static ImVec4 Green            = ImVec4(0.29f, 0.69f, 0.34f, 1.f);
	static ImVec4 Orange           = ImVec4(0.69f, 0.49f, 0.29f, 1.f);
	static ImVec4 Red              = ImVec4(0.69f, 0.29f, 0.29f, 1.f);
	static ImVec4 Blue             = ImVec4(0.36f, 0.71f, 0.89f, 1.f);
	static ImVec4 White            = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

	static auto worldToScreen = [](rage::fvector3 coords) 
	{
		float screen_x{}, screen_y{};

		GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(coords.x, coords.y, coords.z, &screen_x, &screen_y);

		return ImVec2{screen_x * (*Pointers.ScreenResX), screen_y * (*Pointers.ScreenResY)};
	};

	void DrawSkeleton(Ped ped, ImDrawList* drawList, ImColor color)
	{
		if (!ped.IsValid())
			return;
		drawList->AddLine(worldToScreen(ped.GetBonePosition(headBone)), worldToScreen(ped.GetBonePosition(neckBone)), color, 1.5f);

		drawList->AddLine(worldToScreen(ped.GetBonePosition(neckBone)), worldToScreen(ped.GetBonePosition(leftShoulderBone)), color, 1.5f);
		drawList->AddLine(worldToScreen(ped.GetBonePosition(leftShoulderBone)), worldToScreen(ped.GetBonePosition(leftElbowBone)), color, 1.5f);
		drawList->AddLine(worldToScreen(ped.GetBonePosition(leftElbowBone)), worldToScreen(ped.GetBonePosition(leftHandBone)), color, 1.5f);

		drawList->AddLine(worldToScreen(ped.GetBonePosition(neckBone)), worldToScreen(ped.GetBonePosition(rightShoulderBone)), color, 1.5f);
		drawList->AddLine(worldToScreen(ped.GetBonePosition(rightShoulderBone)), worldToScreen(ped.GetBonePosition(rightElbowBone)), color, 1.5f);
		drawList->AddLine(worldToScreen(ped.GetBonePosition(rightElbowBone)), worldToScreen(ped.GetBonePosition(rightHandBone)), color, 1.5f);

		drawList->AddLine(worldToScreen(ped.GetBonePosition(neckBone)), worldToScreen(ped.GetBonePosition(torsoBone)), color, 1.5f);

		drawList->AddLine(worldToScreen(ped.GetBonePosition(torsoBone)), worldToScreen(ped.GetBonePosition(leftKneeBone)), color, 1.5f);
		drawList->AddLine(worldToScreen(ped.GetBonePosition(leftKneeBone)), worldToScreen(ped.GetBonePosition(leftFootBone)), color, 1.5f);

		drawList->AddLine(worldToScreen(ped.GetBonePosition(torsoBone)), worldToScreen(ped.GetBonePosition(rightKneeBone)), color, 1.5f);
		drawList->AddLine(worldToScreen(ped.GetBonePosition(rightKneeBone)), worldToScreen(ped.GetBonePosition(rightFootBone)), color, 1.5f);
	}

	//TODO : Very bare bones currently, expand and possibly refactor
	void ESP::DrawPlayer(Player plyr, ImDrawList* drawList)
	{
		if (!plyr.IsValid() || !plyr.GetPed().IsValid() || plyr == Self::GetPlayer()
		    || worldToScreen(plyr.GetPed().GetBonePosition(torsoBone)).x == 0
		    || (plyr.GetPed().IsDead() && !Features::_ESPDrawDeadPlayers.GetState()))
			return;

		float distanceToPlayer   = Self::GetPed().GetPosition().GetDistance(plyr.GetPed().GetBonePosition(torsoBone));
		int alphaBasedOnDistance = 255;
		ImColor colorBasedOnDistance = Red;

		if (distanceToPlayer < 100.f)
			colorBasedOnDistance = Green, alphaBasedOnDistance = 255;
		else if (distanceToPlayer > 100.f && distanceToPlayer < 300.f)
			colorBasedOnDistance = Orange, alphaBasedOnDistance = 200;
		else if (distanceToPlayer > 300.f)
			colorBasedOnDistance = Red, alphaBasedOnDistance = 125;

		const auto originalFontSize = ImGui::GetFont()->Scale;
		auto* currentFont           = ImGui::GetFont();
		currentFont->Scale *= 1.2;
		ImGui::PushFont(ImGui::GetFont());

		if (Features::_ESPName.GetState())
		{
			drawList->AddText(worldToScreen(plyr.GetPed().GetBonePosition(headBone)),
			    plyr == Players::GetSelected() ? ImGui::ColorConvertFloat4ToU32(Blue) :
			                                     ImGui::ColorConvertFloat4ToU32(Features::_NameColorPlayers.GetState()),
			    plyr.GetName());
		}

		if (Features::_ESPDistance.GetState())
		{
			std::string distanceStr = std::to_string((int)Self::GetPed().GetPosition().GetDistance(plyr.GetPed().GetBonePosition(torsoBone))) + "m";
			drawList->AddText({worldToScreen(plyr.GetPed().GetBonePosition(headBone)).x, worldToScreen(plyr.GetPed().GetBonePosition(headBone)).y + 20}, colorBasedOnDistance, distanceStr.c_str());
		}

		currentFont->Scale = originalFontSize;
		ImGui::PopFont();

		//TODO Boxes, Distance colors, Friendlies, Tracers, Health bars

		if (Features::_ESPSkeleton.GetState() /* && !plyr.GetPed().IsAnimal() */) // yes, this is neccesary.
		{
			if (distanceToPlayer < 250.f)
			{
				DrawSkeleton(plyr.GetPed(), drawList, ImGui::ColorConvertFloat4ToU32(Features::_SkeletonColorPlayers.GetState()));
			}
		}
	}

	void ESP::DrawPed(Ped ped, ImDrawList* drawList)
	{
		if (!ped.IsValid() || ped.IsPlayer() || ped == Self::GetPlayer().GetPed() || worldToScreen(ped.GetBonePosition(torsoBone)).x == 0 || (ped.IsDead() && !Features::_ESPDrawDeadPeds.GetState()))
			return;

		float distanceToPed = 0.0f;

		if (auto local = Self::GetPed())
			distanceToPed = local.GetPosition().GetDistance(ped.GetBonePosition(torsoBone));

		int alphaBasedOnDistance     = 255;
		ImColor colorBasedOnDistance = Red;

		if (distanceToPed < 100.f)
			colorBasedOnDistance = Green, alphaBasedOnDistance = 255;
		else if (distanceToPed > 100.f && distanceToPed < 300.f)
			colorBasedOnDistance = Orange, alphaBasedOnDistance = 200;
		else if (distanceToPed > 300.f)
			colorBasedOnDistance = Red, alphaBasedOnDistance = 125;

		const auto originalFontSize = ImGui::GetFont()->Scale;
		auto* currentFont           = ImGui::GetFont();
		currentFont->Scale *= 1.2;
		ImGui::PushFont(ImGui::GetFont());

		std::string info = "";

		if (Features::_ESPModelPeds.GetState())
		{
			//if (auto it = Data::g_PedModels.find(ped.GetModel()); it != Data::g_PedModels.end())
			//	info += std::format("{} ", it->second);
			//else
				info += std::format("0x{:08X} ", (joaat_t)ped.GetModel());
		}

		if (Features::_ESPNetworkInfoPeds.GetState() && ped.IsNetworked())
		{
			auto owner = Player(ped.GetOwner());
			auto id    = ped.GetNetworkObjectId();

			info += std::format("{} {} ", id, owner.GetName());
		}

		if (Features::_ESPScriptInfoPeds.GetState())
		{
			if (auto script = ENTITY::GET_ENTITY_SCRIPT(ped.GetHandle(), nullptr))
			{
				info += std::format("{} ", script);
			}
		}

		if (!info.empty())
			drawList->AddText(worldToScreen(ped.GetBonePosition(headBone)), ImGui::ColorConvertFloat4ToU32(Features::_HashColorPeds.GetState()), info.c_str());

		if (Features::_ESPDistancePeds.GetState())
		{
			std::string distanceStr = std::to_string((int)distanceToPed) + "m";
			drawList->AddText(
			    {worldToScreen(ped.GetBonePosition(headBone)).x, worldToScreen(ped.GetBonePosition(headBone)).y + 20},
			    colorBasedOnDistance,
			    distanceStr.c_str());
		}

		currentFont->Scale = originalFontSize;
		ImGui::PopFont();

		//TODO Boxes, Distance colors, Tracers, Health bars

		if (Features::_ESPSkeletonPeds.GetState() /* && !ped.IsAnimal() */)
		{
			if (distanceToPed < 250.f)
			{
				DrawSkeleton(ped, drawList, Features::_SkeletonColorPeds.GetState());
			}
		}
	}

	void ESP::DrawRandomEvent(int event, ImDrawList* drawList)
	{
		if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH("freemode"_J) == 0 || HUD::IS_PAUSE_MENU_ACTIVE() || NETWORK::NETWORK_IS_IN_MP_CUTSCENE())
			return;

		if (GPBD_FM_2::Get()->Entries[Self::GetPlayer().GetId()].RandomEventsClientData.InitState != eRandomEventClientInitState::INITIALIZED)
			return;

		auto state        = GSBD_RandomEvents::Get()->EventData[event].State;
		auto coords       = GSBD_RandomEvents::Get()->EventData[event].TriggerPosition;
		auto range        = GSBD_RandomEvents::Get()->EventData[event].TriggerRange;
		auto timer        = GSBD_RandomEvents::Get()->EventData[event].TimerState;
		auto availability = RANDOM_EVENTS_FREEMODE_DATA::Get(Scripts::FindScriptThread("freemode"_J))->EventData[event].AvailableTime;
		auto timeLeft     = GSBD_RandomEvents::Get()->EventData[event].TimerState.GetRemainingTimeStr(availability);
		if (state != eRandomEventState::INACTIVE && coords != Vector3(0.0f, 0.0f, 0.0f))
		{
			float distance          = Self::GetPed().GetPosition().GetDistance(coords);
			float formattedDistance = (distance < 1000.0f) ? distance : (distance / 1000.0f);
			std::string unit        = (distance < 1000.0f) ? "m" : "km";
			std::string text        = std::format("{}\n{:.2f}{} {}", randomEventNames[event], formattedDistance, unit, (state == eRandomEventState::AVAILABLE ? timeLeft : ""));
			ImColor color           = (state == eRandomEventState::ACTIVE) ? Green : White;

			drawList->AddText({worldToScreen(coords).x, worldToScreen(coords).y}, color, text.c_str());
		}
	}

	void ESP::DrawObject(Entity object, ImDrawList* drawList, ObjectType objectType)
	{
		if (HUD::IS_PAUSE_MENU_ACTIVE() || NETWORK::NETWORK_IS_IN_MP_CUTSCENE())
			return;

		if (!object.IsValid())
			return;

		int objectHash = object.GetModel();

		if (objectType == Camera && !Object::IsCamera(objectHash))
			return;

		if (objectType == Cache && !Object::IsCache(objectHash))
			return;

		if (objectType == SignalJammer && !Object::IsSignalJammer(objectHash))
			return;

		Vector3 coords = object.GetPosition();
		float distance   = Self::GetPed().GetPosition().GetDistance(coords);
		float formattedDistance = (distance < 1000.0f) ? distance : (distance / 1000.0f);
		ImColor color = Green;
		std::string unit        = (distance < 1000.0f) ? "m" : "km";
		std::string objectName = std::to_string(objectHash);
		if (Object::IsCamera(objectHash))
		{
			objectName += " (Camera)";
		}
		else if (Object::IsCache(objectHash))
		{
			objectName += " (G's Cache)";
		}
		else if (Object::IsSignalJammer(objectHash))
		{
			objectName += " (Signal Jammer)";
		}
		else if (object.IsMissionEntity())
		{
			objectName += " (Mission Object)";
		}
		std::string text = std::format("{}\n{:.2f}{} ", objectName, formattedDistance, unit);
		
		drawList->AddText({worldToScreen(coords).x, worldToScreen(coords).y}, color, text.c_str());
	}

	void ESP::Draw()
	{
		if (!NativeInvoker::AreHandlersCached() || CAM::IS_SCREEN_FADED_OUT() || HUD::IS_WARNING_MESSAGE_ACTIVE())
			return;

		if (const auto drawList = ImGui::GetBackgroundDrawList())
		{
			if (Features::_ESPDrawPlayers.GetState())
			{
				for (auto& [id, player] : Players::GetPlayers())
				{
					DrawPlayer(player, drawList);
				}
			}
			if (Features::_ESPDrawPeds.GetState() && GetPedPool())
			{
				for (Ped ped : Pools::GetPeds())
				{
					if (ped && ped.GetPointer<void*>())
						DrawPed(ped, drawList);
				}
			}
			if (Features::_ESPDrawRandomEvents.GetState())
			{
				for (int event = 0; event < 21; event++)
				{
					DrawRandomEvent(event, drawList);
				}
			}
			if (Features::_ESPDrawObjects.GetState())
			{
				for (auto obj : Pools::GetObjects())
				{
					if (obj)
						DrawObject(obj, drawList);
				}
			}
			if (Features::_ESPDrawCameras.GetState())
			{
				for (auto obj : Pools::GetObjects())
				{
					if (obj && Object::IsCamera(obj.GetModel()))
						DrawObject(obj, drawList, Camera);
				}
			}
			if (Features::_ESPDrawCache.GetState())
			{
				for (auto obj : Pools::GetObjects())
				{
					if (obj && Object::IsCache(obj.GetModel()))
						DrawObject(obj, drawList, Cache);
				}
			}
			if (Features::_ESPDrawSignalJammers.GetState())
			{
				for (auto obj : Pools::GetObjects())
				{
					if (obj && Object::IsSignalJammer(obj.GetModel()))
						DrawObject(obj, drawList, SignalJammer);
				}
			}
		}
	}

}
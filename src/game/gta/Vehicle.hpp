#pragma once
#include "Entity.hpp"
#include "types/script/types.hpp"
#include "core/util/Joaat.hpp"

namespace YimMenu
{
	class Vehicle : public Entity
	{
	public:
		using Entity::Entity;

		static Vehicle Create(std::uint32_t model, rage::fvector3 coords, float heading = 0.0f, bool setOnGroundProperly = true);

		// health
		void Fix();

		// gears
		int GetGear();
		float GetRevRatio();

		// motion
		float GetMaxSpeed();
		void BringToHalt(float distance = 1.0f, int duration = 1);

		// mods
		void Upgrade();
		std::string GetPlateText();
		void SetPlateText(std::string_view text);
		std::map<int, int32_t> GetOwnedMods();

		// seats
		bool IsSeatFree(int seat);

		// rocket boost
		bool SupportsBoost();
		bool IsBoostActive();
		void SetBoostCharge(int percentage = 100);

		// stance
		void LowerStance(bool lower);

		// position
		bool SetOnGroundProperly();
		static Vector3 GetSpawnLocRelToPed(int ped, joaat_t hash);

		// description
		std::string GetFullName();
	};
}
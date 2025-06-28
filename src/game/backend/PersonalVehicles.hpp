#pragma once
#include "core/util/Joaat.hpp"

#include <set>

struct MPSV_Entry;

namespace YimMenu
{
	class PersonalVehicles
	{
	public:
		class PersonalVehicle
		{
			int m_Id;
			MPSV_Entry* m_Data;
			joaat_t m_Model;
			std::string m_Plate;
			std::string m_Name;
			std::string m_Garage;

		public:
			PersonalVehicle(int id, MPSV_Entry* data);

			int GetId();
			MPSV_Entry* GetData();
			joaat_t GetModel();
			std::string GetPlate();
			std::string GetName();
			std::string GetGarage();
			void SetGarage();

			static int GetCurrentId();
			static int GetCurrentHandle();
			static bool DespawnCurrent();

			bool Repair();
			bool Summon(bool bring = false);
			void ApplyOwnedMods(int handle);
		};

		static std::map<std::string, std::unique_ptr<PersonalVehicle>>& GetPersonalVehicles()
		{
			return GetInstance().m_PersonalVehicles;
		}

		static std::set<std::string>& GetGarages()
		{
			return GetInstance().m_Garages;
		}

		static void RefreshPersonalVehicles()
		{
			GetInstance().RefreshPersonalVehiclesImpl();
		}

		static void RefreshGarages()
		{
			GetInstance().RefreshGaragesImpl();
		}

		static void RegisterVehicles()
		{
			GetInstance().RegisterVehiclesImpl();
		}

	private:
		static PersonalVehicles& GetInstance()
		{
			static PersonalVehicles instance;
			return instance;
		}

		void RefreshPersonalVehiclesImpl();
		void RefreshGaragesImpl();
		void RegisterVehiclesImpl();

		std::map<std::string, std::unique_ptr<PersonalVehicle>> m_PersonalVehicles;
		std::map<int, std::string> m_PVLookup;
		std::set<std::string> m_Garages;
		std::chrono::time_point<std::chrono::steady_clock> m_LastUpdate;
	};
}
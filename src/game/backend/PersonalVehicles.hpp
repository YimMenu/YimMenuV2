#pragma once
#include "core/util/Joaat.hpp"
#include "game/gta/Vehicle.hpp"

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

			int GetId() const;
			MPSV_Entry* GetData();
			joaat_t GetModel() const;
			std::string GetPlate();
			std::string GetName();
			std::string GetGarage();
			void SetGarage();

			bool Despawn();
			bool Repair();
			bool Request(bool bring = false);
			Vehicle Clone(rage::fvector3 coords, float heading);
		};

		static std::unique_ptr<PersonalVehicle> GetCurrent()
		{
			return GetInstance().GetCurrentImpl();
		}

		static Vehicle GetCurrentHandle()
		{
			return GetInstance().GetCurrentHandleImpl();
		}

		static std::map<std::string, std::unique_ptr<PersonalVehicle>>& GetPersonalVehicles()
		{
			return GetInstance().m_PersonalVehicles;
		}

		static std::set<std::string>& GetGarages()
		{
			return GetInstance().m_Garages;
		}

		static void Update()
		{
			GetInstance().UpdateImpl();
		}

		static void RegisterGarages()
		{
			GetInstance().RegisterGaragesImpl();
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

		std::unique_ptr<PersonalVehicle> GetCurrentImpl();
		Vehicle GetCurrentHandleImpl();
		void UpdateImpl();
		void RegisterVehiclesImpl();
		void RegisterGaragesImpl();

		std::map<std::string, std::unique_ptr<PersonalVehicle>> m_PersonalVehicles;
		std::map<int, std::string> m_PVLookup;
		std::set<std::string> m_Garages;
		std::chrono::time_point<std::chrono::steady_clock> m_LastUpdate;
	};
}
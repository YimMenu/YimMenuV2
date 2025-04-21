#include "core/commands/BoolCommand.hpp"
#include "game/backend/ScriptPatches.hpp"

namespace YimMenu::Features
{
	class DLCVehicles : public BoolCommand
	{
		using BoolCommand::BoolCommand;

		ScriptPatch m_VehiclePOSIXPatch{};
		ScriptPatch m_GetVehiclePricePatch{};
		ScriptPatch m_BuyVehiclePatch{};

		virtual void OnEnable() override
		{
			if (!m_VehiclePOSIXPatch)
			{
				m_VehiclePOSIXPatch = ScriptPatches::AddPatch("appinternet"_J, ScriptPointer("VehiclePOSIXPatch", "59 ? ? 72 2E 02 01"), {0x2B, 0x00, 0x00});
			}
			m_VehiclePOSIXPatch->Enable();

			if (!m_GetVehiclePricePatch)
			{
				m_GetVehiclePricePatch = ScriptPatches::AddPatch("appinternet"_J, ScriptPointer("GetVehiclePricePatch", "56 ? ? 70 2E 04 01 38 01"), {0x55});
			}
			m_GetVehiclePricePatch->Enable();

			if (!m_BuyVehiclePatch)
			{
				m_BuyVehiclePatch = ScriptPatches::AddPatch("appinternet"_J, ScriptPointer("BuyVehiclePatch", "5D ? ? ? 06 56 ? ? 38 00 25 ? 50").Add(5), {0x55});
			}
			m_BuyVehiclePatch->Enable();
		}

		virtual void OnDisable() override
		{
			if (m_VehiclePOSIXPatch)
			{
				m_VehiclePOSIXPatch->Disable();
			}

			if (m_GetVehiclePricePatch)
			{
				m_GetVehiclePricePatch->Disable();
			}

			if (m_BuyVehiclePatch)
			{
				m_BuyVehiclePatch->Disable();
			}
		}
	};

	static DLCVehicles _DLCVehicles{"dlcvehicles", "Enable All DLC Vehicles", "Enables all the DLC vehicles on websites."};
}
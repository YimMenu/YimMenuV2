#pragma once
#include "game/gta/Vehicle.hpp"
#include "core/commands/BoolCommand.hpp"
#include "core/commands/FloatCommand.hpp"
#include "core/commands/IntCommand.hpp"

namespace YimMenu
{
    class VehiclePreview
    {
    public:
        static VehiclePreview& Get();
        
        void ShowPreview(joaat_t modelHash, const std::string& vehicleName);
        void HidePreview();
        void Update();
        bool IsShowing() const { return m_Active; }
        const std::string& GetCurrentVehicleName() const { return m_CurrentVehicleName; }
        joaat_t GetCurrentModelHash() const { return m_CurrentModelHash; }
        void UpdateRotationSpeed(float newSpeed);
        bool IsPreviewEnabled() const { return enableVehiclePreview.GetState(); }
        
    private:
        VehiclePreview() = default;
        
        Vehicle m_PreviewVehicle;
        bool m_Active = false;
        bool m_NetworkedPreview = false;
        float m_RotationSpeed = 15.0f; // degrees per second
        std::string m_CurrentVehicleName;
        joaat_t m_CurrentModelHash = 0;
    };
    
    // Command declarations - these will be defined in the .cpp file
    extern BoolCommand enableVehiclePreview;
    extern FloatCommand previewRotationSpeed;
    extern IntCommand previewAlpha;
}
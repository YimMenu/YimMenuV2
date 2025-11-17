#include "VehiclePreview.hpp"
#include "game/backend/Self.hpp"
#include "core/backend/FiberPool.hpp"
#include "game/pointers/Pointers.hpp"
#include "game/gta/Natives.hpp"
#include "imgui.h"

namespace YimMenu
{
    // Command definitions (must be declared before use)
    BoolCommand enableVehiclePreview{"enablevehiclepreview", "Vehicle Preview", "Enable vehicle preview before spawning", true};
    FloatCommand previewRotationSpeed{"previewrotationspeed", "Preview Rotation Speed", "Rotation speed for vehicle previews", 15.0f, 1.0f, 60.0f, 1.0f};
    IntCommand previewAlpha{"previewalpha", "Preview Opacity", "Opacity of preview vehicles (0-255)", 128, 32, 255, 1};

    VehiclePreview& VehiclePreview::Get()
    {
        static VehiclePreview instance;
        return instance;
    }

    void VehiclePreview::ShowPreview(joaat_t modelHash, const std::string& vehicleName)
    {
        if (!enableVehiclePreview.GetState())
            return;

        if (m_Active && m_CurrentModelHash == modelHash)
            return; // Already showing this preview

        // Hide existing preview before showing new one
        HidePreview();

        m_CurrentModelHash = modelHash;
        m_CurrentVehicleName = vehicleName;
        
        FiberPool::Push([this, modelHash] {
            // Ensure we're in a valid state for online compatibility
            bool isOnline = *Pointers.IsSessionStarted && NETWORK::NETWORK_IS_IN_SESSION();
            
            // Get spawn position directly in front of player (always updates)
            auto playerPed = Self::GetPed().GetHandle();
            auto playerPos = ENTITY::GET_ENTITY_COORDS(playerPed, false);
            auto playerHeading = ENTITY::GET_ENTITY_HEADING(playerPed);
            
            // Calculate position in front of player (offset based on heading)
            float forwardX = sin(playerHeading * (3.14159f / 180.0f));
            float forwardY = cos(playerHeading * (3.14159f / 180.0f));
            
            rage::fvector3 spawnPos;
            spawnPos.x = playerPos.x + (forwardX * 5.0f); // 5 units in front
            spawnPos.y = playerPos.y + (forwardY * 5.0f);
            spawnPos.z = playerPos.z + 1.0f; // Slightly elevated
            
            // Create preview vehicle
            m_PreviewVehicle = Vehicle::Create(modelHash, spawnPos, playerHeading);
            
            if (m_PreviewVehicle)
            {
                auto handle = m_PreviewVehicle.GetHandle();
                
                // Set transparency using SET_ENTITY_ALPHA (0-255 range)
                ENTITY::SET_ENTITY_ALPHA(handle, previewAlpha.GetState(), false);
                
                // Make non-collidable to prevent interference with online gameplay
                ENTITY::SET_ENTITY_COLLISION(handle, false, false);
                
                // Don't freeze position - we want to continuously update it
                // ENTITY::FREEZE_ENTITY_POSITION(handle, true);
                
                // Disable physics for preview stability
                PHYSICS::ACTIVATE_PHYSICS(handle);
                
                // Set as invisible to other players in online mode
                if (isOnline)
                {
                    NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(NETWORK::VEH_TO_NET(handle), false);
                }
                
                m_Active = true;
                m_NetworkedPreview = isOnline;
            }
        });
    }

    void VehiclePreview::HidePreview()
    {
        if (!m_Active)
            return;

        if (m_PreviewVehicle)
        {
            // Reset alpha before deletion
            ENTITY::RESET_ENTITY_ALPHA(m_PreviewVehicle.GetHandle());
            m_PreviewVehicle.Delete();
            m_PreviewVehicle = nullptr;
        }
        
        m_Active = false;
        m_CurrentVehicleName.clear();
        m_CurrentModelHash = 0;
        m_NetworkedPreview = false;
    }

    void VehiclePreview::Update()
    {
        if (!m_Active || !m_PreviewVehicle)
            return;

        auto handle = m_PreviewVehicle.GetHandle();
        
        // Always update position to stay in front of player
        auto playerPed = Self::GetPed().GetHandle();
        auto playerPos = ENTITY::GET_ENTITY_COORDS(playerPed, false);
        auto playerHeading = ENTITY::GET_ENTITY_HEADING(playerPed);
        
        // Calculate position in front of player
        float forwardX = sin(playerHeading * (3.14159f / 180.0f));
        float forwardY = cos(playerHeading * (3.14159f / 180.0f));
        
        rage::fvector3 newPos;
        newPos.x = playerPos.x + (forwardX * 5.0f); // 5 units in front
        newPos.y = playerPos.y + (forwardY * 5.0f);
        newPos.z = playerPos.z + 1.0f;
        
        // Update position to follow player
        ENTITY::SET_ENTITY_COORDS(handle, newPos.x, newPos.y, newPos.z, false, false, false, false);
        
        // Smooth rotation
        float currentHeading = ENTITY::GET_ENTITY_HEADING(handle);
        float newHeading = currentHeading + (previewRotationSpeed.GetState() * ImGui::GetIO().DeltaTime);
        
        if (newHeading >= 360.0f)
            newHeading -= 360.0f;
            
        // Use SET_ENTITY_ROTATION with proper rotation order
        ENTITY::SET_ENTITY_ROTATION(handle, 0.0f, 0.0f, newHeading, 2, true);
    }

    void VehiclePreview::UpdateRotationSpeed(float newSpeed)
    {
        m_RotationSpeed = newSpeed;
    }
}
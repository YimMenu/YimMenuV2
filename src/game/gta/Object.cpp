#include "Object.hpp"
#include "Natives.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "game/pointers/Pointers.hpp"
#include "core/util/Joaat.hpp"


namespace YimMenu
{
	static std::unordered_set<joaat_t> cameraHashes = {
	    "p_cctv_s"_J,
	    "prop_cctv_cam_01a"_J,
	    "prop_cctv_cam_01b"_J,
	    "prop_cctv_cam_02a"_J,
	    "prop_cctv_cam_03a"_J,
	    "prop_cctv_cam_04a"_J,
	    "prop_cctv_cam_04b"_J,
	    "prop_cctv_cam_04c"_J,
	    "prop_cctv_cam_05a"_J,
	    "prop_cctv_cam_06a"_J,
	    "prop_cctv_cam_07a"_J,
	    "prop_cctv_pole_01a"_J,
	    "prop_cctv_pole_02"_J,
	    "prop_cctv_pole_03"_J,
	    "prop_cctv_pole_04"_J,
	    "prop_cctv_cam_07a"_J,
	    "prop_cs_cctv"_J,
	    "hei_prop_bank_cctv_01"_J,
	    "hei_prop_bank_cctv_02"_J,
	    "ch_prop_ch_cctv_cam_02a"_J,
	    "xm_prop_x17_server_farm_cctv_01"_J,
	};

	Object Object::Create(uint32_t model, rage::fvector3 coords)
	{
		ENTITY_ASSERT_SCRIPT_CONTEXT();
		if (!STREAMING::IS_MODEL_IN_CDIMAGE(model))
		{
#ifdef ENTITY_DEBUG
			LOGF(WARNING, "Invalid model passed to Object::Create: 0x{:X}", model);
#endif
			return nullptr;
		}

		for (int i = 0; !STREAMING::HAS_MODEL_LOADED(model); i++)
		{
			STREAMING::REQUEST_MODEL(model);
			ScriptMgr::Yield();

			if (i > 30)
			{
#ifdef ENTITY_DEBUG
				LOGF(WARNING, "Model 0x{:X} failed to load after 30 ticks, bailing out", model);
#endif
				return nullptr;
			}
		}

		Pointers.SpectatePatch->Apply();
		Pointers.WorldModelSpawnBypass->Apply();
		auto obj = Object(OBJECT::CREATE_OBJECT(model, coords.x, coords.y, coords.z, true, false, true));
		Pointers.WorldModelSpawnBypass->Restore();
		Pointers.SpectatePatch->Restore();

		if (!obj)
		{
#ifdef ENTITY_DEBUG
			LOGF(WARNING, "CREATE_OBJECT failed when creating an object with model {:X}", model);
#endif
			return nullptr;
		}

		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);

		return obj;
	}

	bool Object::IsCamera()
	{
		return cameraHashes.contains(GetModel());
	}

	bool Object::IsSignalJammer()
	{
		return GetModel() == -305186631;
	}
}
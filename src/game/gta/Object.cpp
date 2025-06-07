#include "Object.hpp"
#include "Natives.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "game/pointers/Pointers.hpp"
#include "core/util/Joaat.hpp"


namespace YimMenu
{
	static std::unordered_set<joaat_t> cameraHashes = {
	    Joaat("p_cctv_s"),
	    Joaat("prop_cctv_cam_01a"),
	    Joaat("prop_cctv_cam_01b"),
	    Joaat("prop_cctv_cam_02a"),
	    Joaat("prop_cctv_cam_03a"),
	    Joaat("prop_cctv_cam_04a"),
	    Joaat("prop_cctv_cam_04b"),
	    Joaat("prop_cctv_cam_04c"),
	    Joaat("prop_cctv_cam_05a"),
	    Joaat("prop_cctv_cam_06a"),
	    Joaat("prop_cctv_cam_07a"),
	    Joaat("prop_cs_cctv"),
	    Joaat("hei_prop_bank_cctv_01"),
	    Joaat("hei_prop_bank_cctv_02"),
	    Joaat("ch_prop_ch_cctv_cam_02a"),
	    Joaat("xm_prop_x17_server_farm_cctv_01"),
	};

	static std::unordered_set<int> cameraHashesInt = {
	    -1007354661,
	    -1842407088,
	    289451089,
	    548760764,
	    -354221800,
	    -1159421424,
	    1449155105,
	    -1095296451,
	    1919058329,
	    -1884701657,
	    -173206916,
	    168901740,
	    -1340405475,
	    1927491455,
	    299608302,
	    -6978462,
		2135655372,
		-1233322078,
		-247409812,
	};

	static std::unordered_set<int> cacheHashes = {
		528555233,
		-1620734287,
		138777325,
		765087784,
		188023466,
		-413608921,
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
			LOGF(WARNING, "CREATE_PED failed when creating a ped with model {:X}", model);
#endif
			return nullptr;
		}

		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);

		return obj;
	}

	bool Object::IsCamera(int objectHash)
	{
		return cameraHashes.contains(objectHash)
		    || cameraHashesInt.contains(objectHash);
	}

	bool Object::IsCache(int objectHash)
	{
		return cacheHashes.contains(objectHash);
	}

	bool Object::IsSignalJammer(int objectHash)
	{
		return objectHash == -305186631;
	}
}
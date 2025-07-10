#include "RayCast.hpp"
#include "game/gta/Natives.hpp"
#include "core/util/Math.hpp"

namespace YimMenu
{
	RayCast::RayCast(Entity* entity, Vector3* coords) :
	    m_Entity(entity),
	    m_Coords(coords)
	{
	}

	RayCast::RayCast(Entity* entity) :
	    m_Entity(entity),
	    m_Coords()
	{
	}

	RayCast::RayCast(Vector3* coords) :
	    m_Entity(nullptr),
	    m_Coords(coords)
	{
	}

	bool RayCast::Cast()
	{
		Vector3 camCoords = CAM::GET_GAMEPLAY_CAM_COORD();
		Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
		Vector3 dir = Math::RotationToDirection(rot);
		Vector3 farCoords;

		farCoords.x = camCoords.x + dir.x * 1000;
		farCoords.y = camCoords.y + dir.y * 1000;
		farCoords.z = camCoords.z + dir.z * 1000;

		int shapeTestHandle = SHAPETEST::START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(camCoords.x,
		    camCoords.y,
		    camCoords.z,
		    farCoords.x,
		    farCoords.y,
		    farCoords.z,
		    -1,
		    0,
		    7);

		BOOL hit;
		Vector3 endCoords;
		Vector3 surfaceNormal;
		int entityHit;

		int testResult = SHAPETEST::GET_SHAPE_TEST_RESULT(shapeTestHandle, &hit, &endCoords, &surfaceNormal, &entityHit);

		if (testResult == 2 && hit == TRUE)
		{
			if (m_Entity)
				*m_Entity = Entity(entityHit);

			if (m_Coords)
				*m_Coords = endCoords;

			return true;
		}

		return false;
	}
}
#include "game/pointers/Pointers.hpp"
#include "World2Screen.hpp"

namespace YimMenu
{
	bool World2Screen::W2S(const rage::vector3 entityCoords, rage::vector2& screen)
	{
		if (!Pointers.GameViewport)
			return false;

		const auto& viewmatrix = Pointers.GameViewport->ViewMatrix; // The view matrix describes the position and orientation of the camera
		const auto& projectionmatrix = Pointers.GameViewport->ProjectionMatrix; // The projection matrix scales objects based on distance

		// W2S is a two-step process if you're dealing with a view matrix and projection matrix
		// Step 1: Transform the entity's world coordinates (xyz) into camera space
		rage::vector3 tVec{
			entityCoords.x * viewmatrix.rows[0].x + entityCoords.y * viewmatrix.rows[1].x + entityCoords.z * viewmatrix.rows[2].x + viewmatrix.rows[3].x,
			entityCoords.x * viewmatrix.rows[0].y + entityCoords.y * viewmatrix.rows[1].y + entityCoords.z * viewmatrix.rows[2].y + viewmatrix.rows[3].y,
			entityCoords.x * viewmatrix.rows[0].z + entityCoords.y * viewmatrix.rows[1].z + entityCoords.z * viewmatrix.rows[2].z + viewmatrix.rows[3].z};

		// Step 2: Transform the camera space coordinates into clip space using the projection matrix (this is where the "w" translation parameter comes in) 
		rage::vector4 cVec{
			tVec.x * projectionmatrix.rows[0].x + tVec.y * projectionmatrix.rows[1].x + tVec.z * projectionmatrix.rows[2].x + projectionmatrix.rows[3].x,
			tVec.x * projectionmatrix.rows[0].y + tVec.y * projectionmatrix.rows[1].y + tVec.z * projectionmatrix.rows[2].y + projectionmatrix.rows[3].y,
		    tVec.x * projectionmatrix.rows[0].z + tVec.y * projectionmatrix.rows[1].z + tVec.z * projectionmatrix.rows[2].z + projectionmatrix.rows[3].z,
		    tVec.x * projectionmatrix.rows[0].w + tVec.y * projectionmatrix.rows[1].w + tVec.z * projectionmatrix.rows[2].w + projectionmatrix.rows[3].w};
		
		// cVec.z, which is the "w" parameter, is used here to verify whether the entity is in front of the camera or behind
		if (cVec.w <= 0.0f)
		{
			screen.x = 0.0f;
			screen.y = 0.0f;
			return false;
		}

		// Normalize our clip space coordinates so we can apply them to our screen position calculation coming up...
		rage::vector2 nVec{cVec.x / cVec.w, cVec.y / cVec.w};

		rage::vector2 gameres{static_cast<float>(*Pointers.ScreenResX), static_cast<float>(*Pointers.ScreenResY)};

		// Normalize the screen coordinates here
		screen.x = (gameres.x / 2.0f) + (0.5f * nVec.x * gameres.x + 0.5f);
		screen.y = (gameres.y / 2.0f) - (0.5f * nVec.y * gameres.y + 0.5f);

		// Like the native version of W2S, we want to return false if the screen coordinates are outside the screen
		if (screen.x > gameres.x || screen.x < 0.0f || screen.y > gameres.y || screen.y < 0.0f)
			return false;

		return true;
	}
}

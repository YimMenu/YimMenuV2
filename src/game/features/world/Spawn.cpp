#include "core/commands/StringCommand.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Object.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	static StringCommand _PedModelName{"pedmodelname", "Ped Model", "The model name of the ped you wish to spawn."};
	static StringCommand _ObjectModelName{"objectmodelname", "Object Model", "The model name of the object you wish to spawn."};


	class SpawnPed : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			auto model = _PedModelName.GetString();
			if (!model.length())
			{
				Notifications::Show("Spawn Ped", "No model name provided.", NotificationType::Error);
				return;
			}

			auto modelHash = Joaat(model);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(modelHash))
			{
				Ped::Create(modelHash, Self::GetPed().GetPosition(), Self::GetPed().GetHeading());
			}
			else
			{
				Notifications::Show("Spawn Ped", "Invalid model name provided.", NotificationType::Error);
			}
		}
	};

	class SpawnObject : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			auto model = _ObjectModelName.GetString();
			if (!model.length())
			{
				Notifications::Show("Spawn Object", "No model name provided.", NotificationType::Error);
				return;
			}

			auto modelHash = Joaat(model);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(modelHash))
			{
				Object::Create(modelHash, Self::GetPed().GetPosition());
			}
			else
			{
				Notifications::Show("Spawn Object", "Invalid model name provided.", NotificationType::Error);
			}
		}
	};

	static SpawnPed _SpawnPed{"spawnped", "Spawn Ped", "Spawns a ped at your current location."};
	static SpawnObject _SpawnObject{"spawnobject", "Spawn Object", "Spawns an object at your current location."};
}

#include <vector>
#include "JSON.h"

namespace JSON {

	std::vector<uint8_t> LoadFile(const std::string i_pFileName) {
		assert(!i_pFileName.empty());

		std::vector<uint8_t> contents;

		FILE* pFile = NULL;

		errno_t fopenError = fopen_s(&pFile, i_pFileName.c_str(), "rb");

		if (fopenError == 0) {

			assert(pFile != NULL);

			int FileIOError = fseek(pFile, 0, SEEK_END);
			assert(FileIOError == 0);

			long FileSize = ftell(pFile);
			assert(FileSize >= 0);

			FileIOError = fseek(pFile, 0, SEEK_SET);
			assert(FileIOError == 0);

			contents.reserve(FileSize);
			contents.resize(FileSize);

			size_t FileRead = fread(&contents[0], 1, FileSize, pFile);
			assert(FileRead == FileSize);

			fclose(pFile);
		}

		return contents;
	}

	SmartPtr<GameObject> CreateGameObjectFromJSONObject(nlohmann::json& i_JSONData)
	{
		Vector3 InitialPosition(0.0f, 0.0f, 0.0f);
		std::string Name = "unknown";

		// parse name
		if (i_JSONData.contains("name"))
		{
			nlohmann::json name = i_JSONData["name"];
			assert(name.is_string());
			Name = name;
		}

		// parse position
		if (i_JSONData.contains("initial_position"))
		{
			nlohmann::json position = i_JSONData["initial_position"];
			assert(position.is_array());
			assert(position.size() == 3);
			assert(position[0].is_number() && position[1].is_number() && position[2].is_number());
			InitialPosition = Vector3(position[0], position[1], position[2]);
		}

		// create gameobject
		SmartPtr<GameObject> NewGameObject = GameObject::CreateGameObject(InitialPosition, Name);

		// parse components
		if (i_JSONData.contains("components"))
		{
			assert(i_JSONData["components"].is_object());

			for (nlohmann::json::iterator it = i_JSONData["components"].begin(); it != i_JSONData["components"].end(); ++it)
			{
				if (it.key() == "moveable")
				{
					nlohmann::json Moveable = it.value();

					// Create Physics Observer
					WeakPtr<GameObject> newGameObjectObserver(NewGameObject);

					Engine::PhysicsSystem::AddMoveable(newGameObjectObserver, Moveable);
				}

				if (it.key() == "renderable")
				{
					nlohmann::json Renderable = it.value();

					// Create Render Observer
					WeakPtr<GameObject> newGameObjectObserver(NewGameObject);

					Engine::Renderer::AddRenderables(newGameObjectObserver, Renderable);
				}

				if (it.key() == "collideable")
				{
					nlohmann::json Collideable = it.value();

					// Create Collider Observer
					WeakPtr<GameObject> newGameObjectObserver(NewGameObject);

					Engine::CollisionSystem::AddCollideable(newGameObjectObserver, Collideable);
				}
			}
		}

		return NewGameObject;
	}

	SmartPtr<GameObject> CreateGameObjectFromJSONFile(const std::string& i_JSONFileName)
	{

		SmartPtr<GameObject> NewObject;

		std::vector<uint8_t> Contents = JSON::LoadFile(i_JSONFileName);

		if (!Contents.empty()) {
			nlohmann::json JSONObject = nlohmann::json::parse(Contents);
			NewObject = JSON::CreateGameObjectFromJSONObject(JSONObject);
		}

		return NewObject;
	}

}

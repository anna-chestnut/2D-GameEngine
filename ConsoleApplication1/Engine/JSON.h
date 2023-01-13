#pragma once
#include "nlohmann/json.hpp"
//#include "GameObject.h"
#include "PhysicsSystem.h"
#include "Renderer.h"
#include "Collision.h"

using namespace Engine;

namespace JSON {

	std::vector<uint8_t> LoadFile(const std::string i_pFileName);
	SmartPtr<GameObject> CreateGameObjectFromJSONObject(nlohmann::json& JSONObject);
	SmartPtr<GameObject> CreateGameObjectFromJSONFile(const std::string& i_JSONFileName);
}
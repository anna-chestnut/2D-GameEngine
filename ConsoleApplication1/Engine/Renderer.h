#pragma once

#include <vector>
#include "GameObject.h"
#include "GLib.h"
#include <assert.h>
#include "Pointers.h"
#include "nlohmann/json.hpp"

namespace Engine {

	struct Renderable {
		WeakPtr<GameObject> pGameObject;
		GLib::Sprite* pSprite;
	};

	class Renderer {

	public:
		Renderer();
		~Renderer();
		static void AddRenderables(WeakPtr<GameObject> gameobject, nlohmann::json i_JSONData);
		static void DrawAllSprites();
		static void Update(float i_dt);
		static void* LoadFile(const char* i_pFilename, size_t& o_sizeFile);
		static GLib::Sprite* CreateSprite(const char* i_pFilename);

	private:
		static std::vector<Renderable> AllRenderables;
		
	};

}
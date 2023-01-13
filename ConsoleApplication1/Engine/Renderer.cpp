#include "Renderer.h"
#include "nlohmann/json.hpp"
#include <DirectXColors.h>

namespace Engine {

	std::vector<Renderable> Renderer::AllRenderables = std::vector<Renderable>();

	Renderer::Renderer() {

	}
	Renderer::~Renderer() {

		//GLib::Release(m_sprite);
		//free(m_sprite);
	}
	void Renderer::AddRenderables(WeakPtr<GameObject> gameobject, nlohmann::json i_JSONData) {

		//std::vector<Renderable> AllRenderables = std::vector<Renderable>();
		std::string i_pFilename;

		// parse sprite texture file name
		if (i_JSONData.contains("sprite_texture")) {
			nlohmann::json spriteFileName = i_JSONData["sprite_texture"];
			assert(spriteFileName.is_string());
			i_pFilename = spriteFileName;
		}

		GLib::Sprite* i_pSprite = CreateSprite(i_pFilename.c_str());
		struct Renderable newRenderalble = { gameobject, i_pSprite };
		Renderer::AllRenderables.push_back(newRenderalble);

	}

	void Renderer::DrawAllSprites() {
		
		for (auto renderable : AllRenderables) {

			SmartPtr<GameObject> smartptrTmp(renderable.pGameObject);

			if (smartptrTmp) {

				GLib::Point2D pos = { smartptrTmp->GetPosition().X(),smartptrTmp->GetPosition().Y() };
				GLib::Render(*renderable.pSprite, pos, 0.0f, smartptrTmp->GetRotation());
			}
			else {
				//remove from renderables
			}
		}
	}

	void Renderer::Update(float i_dt) { // const Vector3& i_Forces

		// IMPORTANT: Tell GLib that we want to start rendering
		GLib::BeginRendering(DirectX::Colors::LavenderBlush);
		// Tell GLib that we want to render some sprites
		GLib::Sprites::BeginRendering();

		Engine::Renderer::DrawAllSprites();

		// Tell GLib we're done rendering sprites
		GLib::Sprites::EndRendering();
		// IMPORTANT: Tell GLib we're done rendering
		GLib::EndRendering();
		
	}

	GLib::Sprite* Renderer::CreateSprite(const char* i_pFilename)
	{
		assert(i_pFilename);

		size_t sizeTextureFile = 0;

		// Load the source file (texture data)
		void* pTextureFile = LoadFile(i_pFilename, sizeTextureFile);

		// Ask GLib to create a texture out of the data (assuming it was loaded successfully)
		GLib::Texture* pTexture = pTextureFile ? GLib::CreateTexture(pTextureFile, sizeTextureFile) : nullptr;

		// exit if something didn't work
		// probably need some debug logging in here!!!!
		if (pTextureFile)
			delete[] pTextureFile;

		if (pTexture == nullptr)
			return nullptr;

		unsigned int width = 0;
		unsigned int height = 0;
		unsigned int depth = 0;

		// Get the dimensions of the texture. We'll use this to determine how big it is on screen
		bool result = GLib::GetDimensions(*pTexture, width, height, depth);
		assert(result == true);
		assert((width > 0) && (height > 0));

		// Define the sprite edges
		GLib::SpriteEdges	Edges = { -float(width / 2.0f), float(height), float(width / 2.0f), 0.0f };
		GLib::SpriteUVs	UVs = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f } };
		GLib::RGBA							Color = { 255, 255, 255, 255 };

		// Create the sprite
		GLib::Sprite* pSprite = GLib::CreateSprite(Edges, 0.1f, Color, UVs, pTexture);

		// release our reference on the Texture
		GLib::Release(pTexture);

		return pSprite;
	}

	void* Renderer::LoadFile(const char* i_pFilename, size_t& o_sizeFile)
	{
		assert(i_pFilename != NULL);

		FILE* pFile = NULL;

		errno_t fopenError = fopen_s(&pFile, i_pFilename, "rb");
		if (fopenError != 0)
			return NULL;

		assert(pFile != NULL);

		int FileIOError = fseek(pFile, 0, SEEK_END);
		assert(FileIOError == 0);

		long FileSize = ftell(pFile);
		assert(FileSize >= 0);

		FileIOError = fseek(pFile, 0, SEEK_SET);
		assert(FileIOError == 0);

		uint8_t* pBuffer = new uint8_t[FileSize];
		assert(pBuffer);

		size_t FileRead = fread(pBuffer, 1, FileSize, pFile);
		assert(FileRead == FileSize);

		fclose(pFile);

		o_sizeFile = FileSize;

		return pBuffer;
	}
}
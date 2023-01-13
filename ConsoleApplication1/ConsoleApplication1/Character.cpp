#include "Character.h"
#include <iostream>
#include<conio.h> 
#include <stdio.h>  
#include <assert.h>


	Character::Character() {

		m_Name = nullptr;
		m_sprite = nullptr;
		//m_Position = (Point2D*)malloc(sizeof(Point2D));

		//p = new Point2D();
	}

	Character::Character(const char* i_pFilenam) {

		m_sprite = CreateSprite(i_pFilenam);
	}

	Character::~Character() {
		//free(m_Position);
		free(m_Name);
		GLib::Release(m_sprite);
		free(m_sprite);
	}
	void Character::SetPos(const Point2D& position) {
		//m_Position = const_cast <Point2D*> (position);
		m_Pos = position;
	}

	Point2D Character::GetPos() {
		return m_Pos;
	}

	void Character::Move(const Point2D& m_Movement) {
		//m_Position += m_Movement;
	}


	GLib::Sprite* Character::CreateSprite(const char* i_pFilename)
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

	void* Character::LoadFile(const char* i_pFilename, size_t& o_sizeFile)
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

	GLib::Sprite* Character::GetSprite(){
		return m_sprite;
	}

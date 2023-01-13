#pragma once
#include "Math\Point2D.h"
#include "GLib.h"

#include <string>

using namespace Engine;


class Character {

public:
	Character();
	Character(const char* i_pFilenam);
	~Character();
	void SetPos(const Point2D& position);
	Point2D GetPos();
	void Move(const Point2D& m_Movement);
	void* LoadFile(const char* i_pFilename, size_t& o_sizeFile);
	GLib::Sprite* CreateSprite(const char* i_pFilename);
	GLib::Sprite* GetSprite();

private:
	//Point2D* m_Position;
	char* m_Name;
	Point2D m_Pos;
	GLib::Sprite* m_sprite;

};

#include "GameObject.h"
#include <iostream>
#include<conio.h> 
#include <stdio.h>  
#include <assert.h>
#include "Log.h"

namespace Engine {

	std::vector<SmartPtr<GameObject>> GameObject::allGameObjects;
	
	GameObject::~GameObject() {

		//GLib::Release(m_sprite);
		//free(m_sprite);
		//free(m_Name);
		//GLib::Release(m_sprite);
		//free(m_sprite);
	}
	GameObject::GameObject(const Vector3& i_position, std::string& i_name) :
		m_Position(i_position),
		m_Name(i_name)
	{

		//m_sprite = CreateSprite(i_pFilenam);
		//m_Position = i_position;
	}

	SmartPtr<GameObject> GameObject::CreateGameObject(const Vector3& i_position, std::string& i_name)
	{
		Log::I("CreateGameObject");
		return SmartPtr<GameObject>(new GameObject(i_position, i_name));
	}

	void GameObject::AddGameObject(SmartPtr<GameObject>& i_newGameObject) {
		allGameObjects.push_back(i_newGameObject);
	}


	/*GLib::Sprite* GameObject::GetSprite() {
		return m_sprite;
	}*/
}
#pragma once
#include "Math\Vector3.h"
#include "GLib.h"
#include <string>
#include <vector>
#include "Pointers.h"


namespace Engine {

	class GameObject {

	public:
		
		GameObject(const Vector3& i_position, std::string& i_name);
		~GameObject();

		static SmartPtr<GameObject> CreateGameObject(const Vector3& i_position, std::string& i_name);
		static void AddGameObject(SmartPtr<GameObject>& i_newGameObject);

		Vector3 GetPosition() { return m_Position; }
		Vector3 GetVelocity() { return m_Velocity; }
		Vector3 GetForce() { return m_Force; }
		float GetRotation() { return m_Rotation; }
		std::string GetName() { return m_Name; }
		void SetPosition(const Vector3& i_Position) { m_Position.X(i_Position.X()); m_Position.Y(i_Position.Y()); m_Position.Z(i_Position.Z()); }
		void SetVelocity(const Vector3& i_Velocity) { m_Velocity.X(i_Velocity.X()); m_Velocity.Y(i_Velocity.Y()); m_Velocity.Z(i_Velocity.Z()); }
		void SetForce(const Vector3& i_Force) { m_Force.X(i_Force.X()); m_Force.Y(i_Force.Y()); m_Force.Z(i_Force.Z()); }
		void SetRotation(const float i_Rotation) { m_Rotation = i_Rotation; }
	private:
		Vector3 m_Velocity;
		Vector3 m_Position;
		Vector3 m_Force;
		float m_Rotation = 0.0f;
		std::string m_Name;
		static std::vector<SmartPtr<GameObject>> allGameObjects;

	};
}
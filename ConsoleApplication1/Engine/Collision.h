#pragma once
#include <array>
#include "Math/Vector3.h"
#include "Math/Matrix.h"
#include "GameObject.h"
#include "nlohmann/json.hpp"
#include "Utilities.h"


namespace Engine {

	typedef std::function<void(WeakPtr<GameObject>&)> CollisionCallback_t;

	struct AABB {

		Vector3 m_Center;
		Vector3 m_Extents;
	};

	struct Collideable
	{
		WeakPtr<GameObject> m_GameObject;
		AABB m_BoundingBox;
		CollisionCallback_t		m_CollisionCallback;

		Collideable(WeakPtr<GameObject> ptr, AABB aabb): m_GameObject(ptr), m_BoundingBox(aabb){
			
		}
		
		void SetCallback(CollisionCallback_t i_callback) {
			m_CollisionCallback = i_callback;
		}

		bool operator==(const Collideable& i_Other) {
			return this->m_GameObject == i_Other.m_GameObject;
		}
	}; 

	class CollisionSystem {
	public:
		CollisionSystem();
		~CollisionSystem();
		static void AddCollideable(WeakPtr<GameObject>& WeakPtr, nlohmann::json i_JSONData);
		static void RemoveCollideable(Collideable& i_Collideable);
		static void Update(float i_dt);
		static Collideable* GetCollideable(WeakPtr<GameObject>& ptr);
	private:
		static std::vector<Collideable*> AllCollideable;
	};
}
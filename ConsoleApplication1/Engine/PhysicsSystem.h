#pragma once

#include <vector>
#include "GameObject.h"
#include "Pointers.h"
#include "nlohmann/json.hpp"

namespace Engine {

	struct Moveable {
		WeakPtr<GameObject> pGameObject;
		float kDrag;
		float Mass;

		bool operator==(const Moveable& i_Other) {
			return this->pGameObject == i_Other.pGameObject;
		}
	};

	class PhysicsSystem {

	public:
		PhysicsSystem();
		~PhysicsSystem();
		static void AddMoveable(WeakPtr<GameObject>& WeakPtr, nlohmann::json i_JSONData);
		static void RemoveMoveable(Moveable& i_Movealble);
		static void Update();
		static void Update(float i_dt);

	private:
		static std::vector<Moveable> AllMoveables;
	};

}
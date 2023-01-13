#include "PhysicsSystem.h"

namespace Engine {

	std::vector<Moveable> PhysicsSystem::AllMoveables = std::vector<Moveable>();

	PhysicsSystem::PhysicsSystem() {
		
	}
	PhysicsSystem::~PhysicsSystem() {

	}
	void PhysicsSystem::AddMoveable(WeakPtr<GameObject>& WeakPtr, nlohmann::json i_JSONData) {

		//std::vector<Moveable> AllMoveables = std::vector<Moveable>();
		
		float KDrag = 0.5f;
		float Mass = 5.0f;

		// parse mass
		if (i_JSONData.contains("mass")) {
			nlohmann::json mass = i_JSONData["mass"];
			assert(mass.is_number_float());
			Mass = mass;
		}

		// parse drag coefficient
		if (i_JSONData.contains("kDrag")) {
			nlohmann::json kDrag = i_JSONData["kDrag"];
			assert(kDrag.is_number_float());
			KDrag = kDrag;
		}


		struct Moveable newMovealble = { WeakPtr, KDrag, Mass };
		PhysicsSystem::AllMoveables.push_back(newMovealble);
		
	}

	void PhysicsSystem::RemoveMoveable(Moveable& i_Movealble) {
		std::remove(AllMoveables.begin(), AllMoveables.end(), i_Movealble);
	}

	void PhysicsSystem::Update() {
		/*
		for (auto obj : AllMoveables) {
			obj.gameobject.positiom =
		}*/
	}

	void PhysicsSystem::Update(float i_dt) { // const Vector3& i_Forces

		for (auto moveable : AllMoveables) {

			SmartPtr<GameObject> smartptrTmp(moveable.pGameObject);
			if (smartptrTmp) {

				//GameObject* io_Object = smartptrTmp.GetPtr();
				double magnitude = sqrt(pow(smartptrTmp->GetVelocity().X(), 2) + pow(smartptrTmp->GetVelocity().Y(), 2) + pow(smartptrTmp->GetVelocity().Z(), 2));

				Vector3 drag = -moveable.kDrag * smartptrTmp->GetVelocity() * magnitude;
				//Vector3 gravity = io_Object.m_Mass * Vector3(0, -10, 0);//m (kg) * 9.8 (m/s^2)

				Vector3 sum = drag + smartptrTmp->GetForce();

				Vector3 forceSum = sum;// + gravity

				Vector3 Acceleration = forceSum / moveable.Mass;

				Vector3 preVelocity = smartptrTmp->GetVelocity();

				smartptrTmp->SetVelocity(smartptrTmp->GetVelocity() + Acceleration * i_dt);
				smartptrTmp->SetPosition(smartptrTmp->GetPosition() + (preVelocity + smartptrTmp->GetVelocity()) / 2 * i_dt);

				//moveable.pGameObject = smartptr;
			}
			else {
				RemoveMoveable(moveable);
			}
		}
	}

}
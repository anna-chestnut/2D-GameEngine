#include "Collision.h"
#include "Log.h"

namespace Engine {

	std::vector<Collideable*> CollisionSystem::AllCollideable = std::vector<Collideable*>();

	CollisionSystem::CollisionSystem() {

	}
	CollisionSystem::~CollisionSystem() {

	}

	void CollisionSystem::AddCollideable(WeakPtr<GameObject>& WeakPtr, nlohmann::json i_JSONData) {

		AABB aabb;

		// parse center
		if (i_JSONData.contains("center")) {
			nlohmann::json center = i_JSONData["center"];
			assert(center.is_array());
			assert(center.size() == 3);
			assert(center[0].is_number() && center[1].is_number() && center[2].is_number());
			aabb.m_Center = Vector3(center[0], center[1], center[2]);
		}

		// parse center
		if (i_JSONData.contains("extents")) {
			nlohmann::json extents = i_JSONData["extents"];
			assert(extents.is_array());
			assert(extents.size() == 3);
			assert(extents[0].is_number() && extents[1].is_number() && extents[2].is_number());
			aabb.m_Extents = Vector3(extents[0], extents[1], extents[2]);
		}


		Collideable* newCollideable = new Collideable(WeakPtr, aabb);
		CollisionSystem::AllCollideable.push_back(newCollideable);
	}

	void CollisionSystem::RemoveCollideable(Collideable& i_Collideable) {
		//std::remove(AllCollideable.begin(), AllCollideable.end(), i_Collideable);
	}


	bool DetectCrossTimes(float i_Center, float i_Extent, float i_Point, float i_Travel, float& o_tEnter, float& o_tExit) {

		assert(i_Extent > 0.0f);

		float i_Start = i_Center - i_Extent;
		float i_End = i_Center + i_Extent;

		if (IsZeroF(i_Travel))
		{
			if ((i_Point < i_Start) || (i_Point > i_End))
				return false;
			else
			{
				o_tEnter = 0.0f;
				o_tExit = 1.0f;
				return true;
			}
		}

		o_tEnter = (i_Start - i_Point) / i_Travel;
		o_tExit = (i_End - i_Point) / i_Travel;

		if (o_tEnter > o_tExit)
			Swap(o_tEnter, o_tExit);

		return !((o_tEnter >= 1.0f) || (o_tExit <= 0.0f));
	}

	bool CheckCollision(Collideable* A, Collideable* B, float i_dt) {

		SmartPtr<GameObject> A_smartptr(A->m_GameObject);
		SmartPtr<GameObject> B_smartptr(B->m_GameObject);

		float t_Enter = 0.0f;
		float t_Exit = 1.0f;

		float t_axisEnter = 0.0f;
		float t_axisExit = 1.0f;

		// Matrix A
		Matrix M_A_Rotation = Matrix::CreateZRotation(A_smartptr->GetRotation());
		Matrix M_A_Translation = Matrix::CreateTranslation(A_smartptr->GetPosition());
		Matrix M_AtoWorld = M_A_Translation * M_A_Rotation;
		Matrix M_WorldToA = M_AtoWorld.GetInverse();

		// Matrix B
		Matrix M_B_Rotation = Matrix::CreateZRotation(B_smartptr->GetRotation());
		Matrix M_B_Translation = Matrix::CreateTranslation(B_smartptr->GetPosition());
		Matrix M_BtoWorld = M_B_Translation * M_B_Rotation;
		Matrix M_WorldToB = M_BtoWorld.GetInverse();

		// A in B coordinate system
		// ------------------------

		Matrix M_AtoB = M_WorldToB * M_AtoWorld;

		// A Velocity
		Vector3 V_ArelativeToB = A_smartptr->GetVelocity() - B_smartptr->GetVelocity();
		Vector4 V_ArelativeInBCoord = M_WorldToB * Vector4(V_ArelativeToB.X(), V_ArelativeToB.Y(), V_ArelativeToB.Z(), 1.0);
		Vector4 D_ATravel = V_ArelativeInBCoord * i_dt;

		// x axis
		// ------
		
		// Transform A’s AABB Center into B’s coordinate system
		Vector4 ACenterInB = M_AtoB * Vector4(A->m_BoundingBox.m_Center.X(), A->m_BoundingBox.m_Center.Y(), A->m_BoundingBox.m_Center.Z(), 1.0f);

		// Transform A’s AABB Extents into B’s coordinate system
		Vector4 AExtentXInB = M_AtoB * Vector4(A->m_BoundingBox.m_Extents.X(), 0.0f, 0.0f, 0.0f);
		Vector4 AExtentYInB = M_AtoB * Vector4(0.0f, A->m_BoundingBox.m_Extents.Y(), 0.0f, 0.0f);

		// Sum the x components of the transformed Extents to find the total extents along that axis (of B)
		float AExtextProjectionOntoB_x = fabs(AExtentXInB.X()) + fabs(AExtentYInB.X());

		float BExpandedExtents_x = B->m_BoundingBox.m_Extents.X() + AExtextProjectionOntoB_x;

		t_axisEnter = 0.0f;
		t_axisExit = 1.0f;

		if (!DetectCrossTimes(B->m_BoundingBox.m_Center.X(), BExpandedExtents_x, ACenterInB.X(), D_ATravel.X(), t_axisEnter, t_axisExit))
			return false;
		
		if (t_axisEnter > t_Enter)
			t_Enter = t_axisEnter;
		if (t_axisExit < t_Exit)
			t_Exit = t_axisExit;

		// y axis
		// ------

		float AExtextProjectionOntoB_y = fabs(AExtentXInB.Y()) + fabs(AExtentYInB.Y());

		float BExpandedExtents_y = B->m_BoundingBox.m_Extents.Y() + AExtextProjectionOntoB_y;

		t_axisEnter = 0.0f;
		t_axisExit = 1.0f;

		if (!DetectCrossTimes(B->m_BoundingBox.m_Center.Y(), BExpandedExtents_y, ACenterInB.Y(), D_ATravel.Y(), t_axisEnter, t_axisExit))
			return false;

		if (t_axisEnter > t_Enter)
			t_Enter = t_axisEnter;
		if (t_axisExit < t_Exit)
			t_Exit = t_axisExit;

		
		// B in A coordinate system
		// ------------------------

		Matrix M_BtoA = M_WorldToA * M_BtoWorld;

		// B Velocity
		Vector3 V_BrelativeToA = B_smartptr->GetVelocity() - A_smartptr->GetVelocity();
		Vector4 V_BrelativeInACoord = M_WorldToA * Vector4(V_BrelativeToA.X(), V_BrelativeToA.Y(), V_BrelativeToA.Z(), 1.0);
		Vector4 D_BTravel = V_BrelativeInACoord * i_dt;

		// x axis
		// ------
		
		// Transform B’s AABB Center into A’s coordinate system
		Vector4 BCenterInA = M_BtoA * Vector4(B->m_BoundingBox.m_Center.X(), B->m_BoundingBox.m_Center.Y(), B->m_BoundingBox.m_Center.Z(), 1.0f);

		// Transform B’s AABB Extents into A’s coordinate system
		Vector4 BExtentXInA = M_BtoA * Vector4(B->m_BoundingBox.m_Extents.X(), 0.0f, 0.0f, 0.0f);
		Vector4 BExtentYInA = M_BtoA * Vector4(0.0f, B->m_BoundingBox.m_Extents.Y(), 0.0f, 0.0f);

		// Sum the x components of the transformed Extents to find the total extents along that axis (of A)
		float BExtextProjectionOntoA_x = fabs(BExtentXInA.X()) + fabs(BExtentYInA.X());

		float AExpandedExtents_x = A->m_BoundingBox.m_Extents.X() + BExtextProjectionOntoA_x;

		t_axisEnter = 0.0f;
		t_axisExit = 1.0f;

		if (!DetectCrossTimes(A->m_BoundingBox.m_Center.X(), AExpandedExtents_x, BCenterInA.X(), D_BTravel.X(), t_axisEnter, t_axisExit))
			return false;

		if (t_axisEnter > t_Enter)
			t_Enter = t_axisEnter;
		if (t_axisExit < t_Exit)
			t_Exit = t_axisExit;

		// y axis
		// ------
		
		float BExtextProjectionOntoA_y = fabs(BExtentXInA.Y()) + fabs(BExtentYInA.Y());

		float AExpandedExtents_y = A->m_BoundingBox.m_Extents.Y() + BExtextProjectionOntoA_y;

		t_axisEnter = 0.0f;
		t_axisExit = 1.0f;

		if (!DetectCrossTimes(A->m_BoundingBox.m_Center.Y(), AExpandedExtents_y, BCenterInA.Y(), D_BTravel.Y(), t_axisEnter, t_axisExit))
			return false;

		if (t_axisEnter > t_Enter)
			t_Enter = t_axisEnter;
		if (t_axisExit < t_Exit)
			t_Exit = t_axisExit;

		if (t_Enter < t_Exit)
			return true;
		else return false;
	}

	void CollisionSystem::Update(float i_dt) {
		for (int i = 0; i < AllCollideable.size(); i++) {
			auto Collider1 = AllCollideable[i];
			for (int j = i + 1; j < AllCollideable.size(); j++) {
				auto Collider2 = AllCollideable[j];
				if (CheckCollision(Collider2, Collider1, i_dt)) {
					if(Collider1->m_CollisionCallback) Collider1->m_CollisionCallback(Collider2->m_GameObject);
					if(Collider2->m_CollisionCallback) Collider2->m_CollisionCallback(Collider1->m_GameObject);

				}
			}
		}
	}

	Collideable* CollisionSystem::GetCollideable(WeakPtr<GameObject>& ptr)
	{

		for(const auto& c: AllCollideable) {
			if (c->m_GameObject == ptr) return c;
		}
		return nullptr;
	}
}
#include <iostream>
#include <Windows.h>
#include <assert.h>

#include <DirectXColors.h>

#include "Initialization.h"
#include "Math\Point2D.h"
#include "GLib.h"
#include "Character.h"
#include "Timing.h"
#include "Renderer.h"
#include "Pointers.h"
#include "JSON.h"
#include "JobSystem/JobSystem.h"
#include "Math/Matrix.h"
//#include "Eigen/Dense"
#include "Log.h"
//#include <Eigen/Geometry> 

#include <corecrt_math_defines.h>

//using namespace Eigen;

void Point2DUnitTest() {

    Point2D A(0, 1);
    Point2D B(2, 3);
    // equality    
    bool bEqual = A == B;
    assert(bEqual == false);

    bEqual = B == Point2D(2, 3);
    assert(bEqual == true);

    // Inequality    
    bool bNotEqual = A != B;
    assert(bNotEqual == true);

    bNotEqual = B != Point2D(2, 3);
    assert(bNotEqual == false);
    // Point2D + Point2D    
    Point2D C = A + B;
    assert(C == Point2D(2, 4));
    // Point2D - Point2D 
    C = B - A;
    assert(C == Point2D(2, 2));
    // Point2D * int 
    C = A * 2;
    assert(C == Point2D(0, 2));
    // Point2D / int  
    C = Point2D(6, 4) / 2;
    assert(C == Point2D(3, 2));
    // int * Point2D  
    C = 2 * B;
    assert(C == Point2D(4, 6));
    // negate  
    C = -B;
    assert(C == Point2D(-2, -3));
    // Point2D += Point2D 
    B += Point2D(2, 1);
    assert(B == Point2D(4, 4));
    // Point2D -= Point2d 
    B -= Point2D(2, 1);
    assert(B == Point2D(2, 3));
    // Point2D *= int  
    B *= 2;
    assert(B == Point2D(4, 6));
    // Point2D /= int   
    B /= 2;
    assert(B == Point2D(2, 3));
}

bool rightDown = false;
bool leftDown = false;
bool upDown = false;
bool downDown = false;
//
//void TestEigen() {
//	
//	MatrixXd m(2, 2);
//	m(0, 0) = 3;
//	m(1, 0) = 2.5;
//	m(0, 1) = -1;
//	m(1, 1) = m(1, 0) + m(0, 1);
//	for (int r = 0; r < 2; r++) {
//		for (int c = 0; c < 2; c++) {
//			double d = m(r, c);
//			std::string s = std::to_string(d);
//			Log::I(s);
//		}
//	}
//}
//
//void MatrixUnitTest() {
//
//	// Test for rotation
//	// -----------------
//	Matrix3f m;
//	m = AngleAxisf(0.25 * M_PI, Vector3f::UnitX()) * AngleAxisf(0.5 * M_PI, Vector3f::UnitY()) * AngleAxisf(0.33 * M_PI, Vector3f::UnitZ());
//
//	Engine::Matrix n = Engine::Matrix();
//	n = n.CreateXRotation(0.25 * M_PI) * n.CreateYRotation(0.5 * M_PI) * n.CreateZRotation(0.33 * M_PI);
//
//	for (int r = 0; r < 3; r++) {
//		for (int c = 0; c < 3; c++) {
//			double d = m(r, c);
//			std::string s = std::to_string(d);
//			Log::I(s);
//
//			float f = n.Row(r).At(c);
//			std::string sf = std::to_string(f);
//			Log::D(sf);
//			//assert(f == d);
//		}
//	}
//
//	// Test for three determinant
//	// --------------------------
//	Eigen::Matrix3f A;
//	A << 1, 2, 1,
//		2, 1, 0,
//		-1, 1, 2;
//
//	float A_determinant = A.determinant();
//	Log::I(std::to_string(A_determinant));
//
//	Engine::Matrix B(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
//	float B_determinant = B.threeDeterminant(1, 2, 1, 2, 1, 0, -1, 1, 2);
//	Log::D(std::to_string(B_determinant));
//
//	assert(A_determinant == B_determinant);
//
//	// Test for four determinant 
//	// -------------------------
//	float B_four_determinant = B.FindDeterminant();
//	assert(B_four_determinant == 0);
//
//	// Test for Inverse
//	// ----------------
//	Engine::Matrix C(5, 2, 1, 9, 2, 7, 5, 2, 3, 1, 2, 3, 8, 7, 4, 1);
//	C.Invert();
//	for (int r = 0; r <= 3; r++) {
//		for (int c = 0; c <= 3; c++) {
//			Log::I("Inverse");
//			float f = C.Row(r).At(c);
//			std::string sf = std::to_string(f);
//			Log::D(sf);
//		}
//	}
//
//	Log::I(" --- Inverse --- ");
//	Engine::Matrix D = C.GetInverse();
//	for (int r = 0; r <= 3; r++) {
//		for (int c = 0; c <= 3; c++) {
//			float f = D.Row(r).At(c);
//			std::string sf = std::to_string(f);
//			Log::D(sf);
//		}
//	}
//
//}
/*
int main()
{

    _CrtDumpMemoryLeaks();
}
*/
void SIMDtest() {
	Engine::Vector3 v1(1, 2, 3);
	Engine::Vector3 v2(2, 1, 3);

	float value = dot(v1, v2);
	Log::I("dot product: " + std::to_string(value));

	Engine::Vector4 v3(1, 2, 3, 1);
	Engine::Vector4 v4(2, 1, 3, -1);

	value = Engine::Vector4::dot(v3, v4);
	Log::I("vector4 dot product: " + std::to_string(value));
}

void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
{
#ifdef _DEBUG
	const size_t	lenBuffer = 65;
	char			Buffer[lenBuffer];

	//right D 68
	if (i_VKeyID == 68) {
		rightDown = bWentDown ? true : false;
	}
	//left A 65
	if (i_VKeyID == 65) {
		leftDown = bWentDown ? true : false;
	}

	//left W 87
	if (i_VKeyID == 87) {
		upDown = bWentDown ? true : false;
	}

	//left S 83
	if (i_VKeyID == 83) {
		downDown = bWentDown ? true : false;
	}

	sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
	OutputDebugStringA(Buffer);
#endif // __DEBUG
}

float GetFrameTime() {

	static Engine::Timing::tick_t lastFrameTick = 0;

	float FrameTime;

	Engine::Timing::tick_t currentFrameStartTick = Engine::Timing::GetCurrentTickCounter();

	FrameTime = (lastFrameTick == 0) ? (1.0f / 60.0f) : (Engine::Timing::GetTimeDiff_ms(currentFrameStartTick) / 1000.0f);

	lastFrameTick = currentFrameStartTick;

	return IsDebuggerPresent() ? (1.0f / 60.0f) : FrameTime;


}


//int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
int APIENTRY wWinMain(_In_ HINSTANCE i_hInstance,
	_In_opt_ HINSTANCE i_hPrevInstance,
	_In_ LPWSTR    i_lpCmdLine,
	_In_ int       i_nCmdShow)
{
	//MatrixUnitTest();

	//SIMDtest();

    // IMPORTANT: first we need to initialize GLib
    bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 800, true);

	Engine::Initialize();
	Engine::Timing::Init();

	if (bSuccess)
	{
		// IMPORTANT (if we want keypress info from GLib): Set a callback for notification of key presses
		GLib::SetKeyStateChangeCallback(TestKeyCallback);

		Engine::JobSystem::Init();
		Engine::JobSystem::JobStatus JobStatus;

		SmartPtr<GameObject> player;
		SmartPtr<GameObject> monster;
		SmartPtr<GameObject> bullet;

		Engine::JobSystem::RunJob(
			Engine::JobSystem::GetDefaultQueueName(),
			[&player, &monster, &bullet]()
			{
				bullet = JSON::CreateGameObjectFromJSONFile("ActorsJSON/Bullet.json");
				GameObject::AddGameObject(bullet);

				player = JSON::CreateGameObjectFromJSONFile("ActorsJSON/Human.json");
				GameObject::AddGameObject(player);

				monster = JSON::CreateGameObjectFromJSONFile("ActorsJSON/Monster.json");
				GameObject::AddGameObject(monster);
			},
			&JobStatus
				);

		JobStatus.WaitForZeroJobsLeft();
		Engine::JobSystem::RequestShutdown();
		bool bQuit = false;

		bullet->SetForce(Engine::Vector3(0, 1.4f, 0));
		monster->SetForce(Engine::Vector3(0.5f, 0, 0));

		WeakPtr<GameObject> p(player);
		WeakPtr<GameObject> m(monster);
		WeakPtr<GameObject> b(bullet);

		auto collideable = Engine::CollisionSystem::GetCollideable(p);
		collideable->SetCallback([&b](WeakPtr<GameObject> otherObj) -> void {
			if (otherObj == b) Log::I("player collide with bullet");
			});

		unsigned int hitCount = 5;

		collideable = Engine::CollisionSystem::GetCollideable(m);
		collideable->SetCallback([&hitCount, &bQuit, &monster, &player, &bullet](WeakPtr<GameObject> otherObj) -> void {

			if(otherObj.AcquireOwnership()->GetName() == "Bullet")
				Log::I("Monster collide with bullet");
			otherObj.AcquireOwnership()->SetPosition(Engine::Vector3(0, 500, 0));
			if (--hitCount==0) {
				SmartPtr<GameObject> win = JSON::CreateGameObjectFromJSONFile("ActorsJSON/Win.json");
				GameObject::AddGameObject(win);
				monster->SetPosition(Engine::Vector3(0, 1000, 0));
				bullet->SetPosition(Engine::Vector3(0, -1000, 0));
				player->SetPosition(Engine::Vector3(0, -1000, 0));
			}
			});

		collideable = Engine::CollisionSystem::GetCollideable(b);
		collideable->SetCallback([](WeakPtr<GameObject> otherObj) -> void {
			//Log::I("Collided");
			});

		//monster->SetRotation(3.14f/3); 
		//player->SetRotation(3.14f / 3);

		float totalTime = 0.0f;
		float preTime = 0.0f;
		float fireTime = 1.0f;

		float playerSpeed = 1.1f;

		do
		{
			// IMPORTANT: We need to let GLib do it's thing. 
			GLib::Service(bQuit);

			float dt = GetFrameTime();
			Engine::Update(dt);
			
			if (bullet->GetPosition().Y() > 400) {
				Engine::Vector3 v(0, 164, 0);
				v = v + player->GetPosition();
				bullet->SetPosition(v);
			}

			if (monster->GetPosition().X() > 400) {
				monster->SetForce(Engine::Vector3(-0.5f, 0, 0));
			}

			if (monster->GetPosition().X() < -400) {
				monster->SetForce(Engine::Vector3(0.5f, 0, 0));
			}

			if (rightDown) {
				player->SetForce(Engine::Vector3(playerSpeed, 0, 0));
			}
			else if (leftDown) {
				player->SetForce(Engine::Vector3(-playerSpeed, 0, 0));
			}
			else if (upDown) {
				player->SetForce(Engine::Vector3(0, playerSpeed, 0));
			}
			else if (downDown) {
				player->SetForce(Engine::Vector3(0, -playerSpeed, 0));
			}
			else {
				player->SetForce(Engine::Vector3(0, 0, 0));
			}

		} while (bQuit == false);
		
		// IMPORTANT:  Tell GLib to shutdown, releasing resources.
		GLib::Shutdown();
	}

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG

}


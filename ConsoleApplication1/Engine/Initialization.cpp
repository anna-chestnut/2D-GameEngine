#include <stdio.h>
#include "Initialization.h"
#include "PhysicsSystem.h"
#include "Collision.h"
#include "Renderer.h"


namespace Engine {

	void Initialize() {
		printf("Engine is initialized.");
	}
	void Update(float dt) {
		CollisionSystem::Update(dt);
		PhysicsSystem::Update(dt);
		Renderer::Update(dt);
	}
}
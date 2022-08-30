#include "Physics.h"

RedMagic::Physics::Physics()
{
	velocityIterations = 6;
	positionIterations = 2;
	timeStep = 1.0f / 60.0f;
}


RedMagic::Physics::~Physics()
{
}

void RedMagic::Physics::Update(float dt, vector<GameObject*> *gameObjects) {
	//simulação
	runBox2D();

	//atualização
	if (gameObjects != NULL) {
		for (auto i = gameObjects->begin(); i != gameObjects->end(); i++) {
			RigidBody2D *comp = (*i)->GetComponent<RigidBody2D>();
			if (comp != NULL) {
				comp->Update(dt);
			}
		}
	}
}
void RedMagic::Physics::Initialize(void) {

}

void RedMagic::Physics::runBox2D() {
	SceneManager::GetInstance()->GetCurrentScene()->GetWorld()->Step(timeStep, velocityIterations, positionIterations);
	SceneManager::GetInstance()->GetCurrentScene()->GetWorld()->ClearForces();
}
#include "Scene.h"

RedMagic::Scene::Scene()
{
	gameObjects_ = new vector<GameObject*>;

	// Define the gravity vector.
	b2Vec2 gravity(0.0f, -9.8f);

	// Inicializa a biblioteca Box2D
	world = new b2World(gravity);
}


RedMagic::Scene::~Scene()
{
	for (auto it = gameObjects_->begin(); it != gameObjects_->end(); it++) {
		delete (*it);
	}
}

void RedMagic::Scene::AddGameObject(GameObject* object) {
	gameObjects_->push_back(object);
}
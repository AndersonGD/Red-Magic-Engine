#ifndef REDMAGIC_SCENE_H
#define REDMAGIC_SCENE_H

#include "GameObject.h"

namespace RedMagic {
	class Scene
	{
	private:
		vector<GameObject*> *gameObjects_;

		b2World* world;
	public:
		Scene();
		~Scene();

		vector<GameObject*>* GetObjectsWithTag(string tag) {
			vector<GameObject*> *objs;
			objs = new vector<GameObject*>;

			for (auto it = gameObjects_->begin(); it != gameObjects_->end(); it++) {
				if ((*it)->GetTag() == tag) {
					objs->push_back((*it));
				}
			}
			if (objs != NULL) {
				return objs;
			}

		}

		GameObject* FindObjectWithTag(string tag) {
			for (auto it = gameObjects_->begin(); it != gameObjects_->end(); it++) {
				if ((*it)->GetTag() == tag) {
					return (*it);
				}
			}
		}
		GameObject* FindObjectWithName(string name) {}

		void AddGameObject(GameObject* object);
		vector<GameObject*>* GetGameObjects() {
			if (gameObjects_ != NULL) {
				return gameObjects_;
			}
		}

		void setWorld(b2World* w) { world = w; }
		b2World* GetWorld() { return world; }
	};
}
#endif

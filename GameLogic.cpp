#include "GameLogic.h"


namespace RedMagic {
	GameLogic::GameLogic()
	{
	}


	GameLogic::~GameLogic()
	{
	}

	void GameLogic::Update(float dt, vector<GameObject*> *gameObjects) {
		for (auto i = gameObjects->begin(); i != gameObjects->end(); i++) {
			for (auto it = (*i)->GetScripts()->begin(); it != (*i)->GetScripts()->end(); ++it){
				Script* script = it->second;
				if (script != NULL) {
					script->Update(dt);
				}
			}			
		}
	}
	void GameLogic::Initialize(void) {

	}
}
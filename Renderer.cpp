#include "Renderer.h"

namespace RedMagic {

	RedMagic::Renderer::Renderer()
	{
	}

	RedMagic::Renderer::Renderer(SDL_Window* window) {
		_window = window;
	}


	RedMagic::Renderer::~Renderer()
	{
	}

	void RedMagic::Renderer::Update(float dt, vector<GameObject*> *gameObjects) {
		if (gameObjects != NULL) {
			glClearDepth(1.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			for (auto i = gameObjects->begin(); i != gameObjects->end(); i++) {
				Sprite *comp = (*i)->GetComponent<Sprite>();
				if (comp != NULL) {
					comp->Update(dt);
				}
			}
			SDL_GL_SwapWindow(_window);
			glFinish();
		}
	}

	void RedMagic::Renderer::Initialize(void) {

	}
}
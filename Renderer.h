#ifndef REDMAGIC_RENDERER_H
#define REDMAGIC_RENDERER_H

#include "System.h"
#include "Sprite.h"

namespace RedMagic {

	class Renderer : public System
	{
	private:
		SDL_Window* _window;
	public:
		Renderer();
		Renderer(SDL_Window* window);
		~Renderer();

		void Update(float dt, vector<GameObject*> *gameObjects);
		void Initialize(void);
	};
}
#endif

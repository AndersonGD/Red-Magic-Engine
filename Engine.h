#ifndef REDMAGIC_ENGINE_H
#define REDMAGIC_ENGINE_H

#include <Windows.h>
#include "SceneManager.h"
#include <GL/glew.h>
#include "GameObject.h"
#include "System.h"
#include "Physics.h"
#include "Renderer.h"
#include "Input.h"
#include "GameLogic.h"
#include "FpsLimiter.h"

enum GAMESTATE {
	PLAYING,
	EXIT
};

namespace RedMagic {

	class Engine
	{
	private:
		SDL_Window* _window;
		GAMESTATE _gameState;
		FpsLimiter* fpsLimiter_;
		vector<System*> *systems_;

		void Update(float dt);

		float _fps;
		float _time;

	public:
		Engine();
		~Engine();

		void initSystem(const char* name, int width, int height);
		void Run(float fps);
		void AddSystem(System* sys);

		void ReceiveMessage(int mes) {
			if (mes == 0) {
				_gameState = EXIT;
			}
		}
	};
}
#endif

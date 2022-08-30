#include "Input.h"

RedMagic::Input::Input()
	{
	}


	RedMagic::Input::~Input()
	{
	}

	void RedMagic::Input::Update(float dt, vector<GameObject*> *gameObjects_) {
		//todo loop faz isso, for bacana utilizado pra diminuir o tamanho da linha e ficar mais bonito
		//copia a keymap pro keymap anterior pra veririficar se foi pressionado só uma vez

		SDL_Event _event;

		InputManager::getInstance()->update();
		
		while (SDL_PollEvent(&_event)) {
		switch (_event.type) {
		case SDL_QUIT:
		//_gameState = EXIT;
			exit(0);
		break;
		case SDL_KEYDOWN:	//tecla foi pressionada bool true
			InputManager::getInstance()->pressKey(_event.key.keysym.sym);
		break;
		case SDL_KEYUP:	//tecla foi solta bool false
			InputManager::getInstance()->releaseKey(_event.key.keysym.sym);
		break;
		case SDL_MOUSEBUTTONDOWN:
			InputManager::getInstance()->pressKey(_event.button.button);
		break;
		case SDL_MOUSEBUTTONUP:
			InputManager::getInstance()->releaseKey(_event.button.button);
		break;
		case SDL_MOUSEMOTION:
			InputManager::getInstance()->setMousePosition(_event.motion.x, _event.motion.y);
		break;
		}

		}
	}

	void RedMagic::Input::Initialize(void) {

	}

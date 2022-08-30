#include "Engine.h"

/*	Red Magic Game Engine Version 2.0
	OpenGL, SDL2 and Box2D
	Created By: Anderson Leonardo de Oliveira
	All Rights Reserved
	Copyright(C) 2016, Red Magic Entertainment
	gdcontatoanderson@gmail.com
*/

namespace RedMagic {

	RedMagic::Engine::Engine()
	{
		_gameState = PLAYING;
		systems_ = NULL;
		_time = 0.0f;
		fpsLimiter_ = new FpsLimiter;
	}


	RedMagic::Engine::~Engine()
	{
	}

	void RedMagic::Engine::initSystem(const char* name, int width, int height) {

		systems_ = new vector<System*>;

		//Inicializa SDL e OpenGL
		if (SDL_Init(SDL_INIT_EVERYTHING < 0)) {
			cout << "SDL ERROR, could not initialize!";
		}

		int flags = IMG_INIT_JPG | IMG_INIT_PNG;
		int initted = IMG_Init(flags);
		if ((initted&flags) != flags) {
			cout<<("IMG_Init: Failed to init required jpg and png support!\n");
			cout<<("IMG_Init: %s\n", IMG_GetError());
			// handle error
		}

		_window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

		SDL_GLContext _glContext = SDL_GL_CreateContext(_window);

		if (_glContext == NULL) {
			cout << "ERROR GL CONTEXT, could not create it";
		}

		GLenum err = glewInit();
		if (err != GLEW_OK)
		{
			/* Problem: glewInit failed, something is seriously wrong. */
			fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		}
		fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


		glClearColor(0.0f, 0.0f, 0.0f, 1.0);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0, width, 0.0, height, -1.0, 1.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		Physics* phys;
		Renderer* render;
		Input* input;
		GameLogic * logic = new GameLogic;
		phys = new Physics;
		render = new Renderer(_window);
		input = new Input;

		systems_->push_back(input);
		systems_->push_back(logic);
		systems_->push_back(phys);
		systems_->push_back(render);
		

		for (auto i = systems_->begin(); i != systems_->end(); i++) {
			(*i)->Initialize();
		}

		Resources::getInstance()->Initialize();
		SceneManager::GetInstance()->Initialize();

		GLenum erro;
		while ((erro = glGetError()) != GL_NO_ERROR) {
			cerr << "OpenGL error: " << erro << endl;
		}

	}

	void RedMagic::Engine::Run(float fps) {
		fpsLimiter_->setMaxFPS(fps);

		while (_gameState != EXIT) {
			fpsLimiter_->begin();

			Update(fps);

			_time += 0.1;
			_fps = fpsLimiter_->end();
			//print only once every 10 frames
			static int frameCounter = 0;
			frameCounter++;
			if (frameCounter == 10000) {
				cout << _fps << endl;
				frameCounter = 0;
			}
		}
	}

	void RedMagic::Engine::Update(float dt) {
		for (auto i = systems_->begin(); i != systems_->end(); i++) {
			(*i)->Update(dt, SceneManager::GetInstance()->GetCurrentScene()->GetGameObjects());
		}
	}

	void RedMagic::Engine::AddSystem(System* sys) {
		if (sys != NULL) {
			systems_->push_back(sys);
		}
	}
}
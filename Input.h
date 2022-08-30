#ifndef REDMAGIC_INPUT_H
#define REDMAGIC_INPUT_H

#include "System.h"
#include "InputManager.h"

namespace RedMagic {

	class Input : public System
	{
	public:
		Input();
		~Input();

		void Update(float dt, vector<GameObject*> *gameObjects_);
		void Initialize(void);
	};
}
#endif

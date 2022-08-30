#ifndef REDMAGIC_SYSTEM_H
#define REDMAGIC_SYSTEM_H

#include <list>
#include "Resources.h"
#include "GameObject.h"

namespace RedMagic {

	class System
	{
	public:

		virtual void Update(float dt, vector<GameObject*> *gameObjects_) = 0;

		virtual void Initialize(void) = 0;

		//virtual void SendCode(int msg) = 0;

		virtual ~System() {}
	};
}
#endif

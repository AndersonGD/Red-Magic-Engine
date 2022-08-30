#ifndef REDMAGIC_GAMELOGIC_H
#define REDMAGIC_GAMELOGIC_H
#include "System.h"
namespace RedMagic {
	class GameLogic :
		public System
	{
	public:
		GameLogic();
		~GameLogic();

		void Update(float dt, vector<GameObject*> *gameObjects);
		void Initialize(void);
	};
}
#endif

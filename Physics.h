#ifndef REDMAGIC_PHYSICS_H
#define REDMAGIC_PHYSICS_H
#include "System.h"
#include "RigidBody2D.h"
#include "SceneManager.h"
namespace RedMagic {
	class Physics : public System
	{
	private:
		// Define os parâmetro para a simulação
		// Quanto maior, mais preciso, porém, mais lento
		float32 timeStep;
		int32 velocityIterations;
		int32 positionIterations;

		void runBox2D();
	public:
		Physics();
		~Physics();

		void Update(float dt, vector<GameObject*> *gameObjects);
		void Initialize(void);
	};
}
#endif

#ifndef REDMAGIC_SPRITE_H
#define REDMAGIC_SPRITE_H

#include "Resources.h"
#include "Transform.h"
#include "RigidBody2D.h"
#include <GL/glew.h>
#include "GameObject.h"

namespace RedMagic {

	class Sprite : public Part
	{
	private:
		Transform* transform_;
		RigidBody2D* rigidBody_;
		int count;
		int animation;
		int quadro;
		int frames;						//numero de frames maximo
		int animations;					//numero de animacoes maximo
		int width_total;				//largura total do spritesheet
		int height_total;				//altura total do spritesheet
		int width_frame;				//largura de cada frame
		int height_frame;				//altura de cada frame
		bool animating;
		float speed_animation;
		unsigned int idt;						//id texture
	public:
		Sprite();
		Sprite(int w, int h, int f, int a);
		~Sprite();


		void SetTransform(Transform* t) { transform_ = t; }
		void SetRigidBody2D(RigidBody2D* rb) { rigidBody_ = rb; }


		void Initialize(){}
	//	void Initialize(int w, int h, int f, int a);
		virtual void Cleanup();
		virtual void Update(double dt);

		void SetAnimation(int i) { animation = i; }
		void SetIDT(unsigned int i) { idt = i; }
		void SetSpriteSheet(string name);

		int getFramesMax() { return frames; }
		int getAnimacoesMax() { return animations; }

		int getWidthFrame() { return width_frame; }
		int getHeightFrame() { return height_frame; }
		int getQuadro() { return quadro; }
		unsigned int* getIDT() { return &idt; }
	};

}
#endif

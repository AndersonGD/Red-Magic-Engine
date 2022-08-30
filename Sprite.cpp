#include "Sprite.h"
#include <Windows.h>
#include <iostream>
#include <time.h>
using namespace std;

RedMagic::Sprite::Sprite()
{
	transform_ = NULL;
	frames = 0;
	animations = 0;
	speed_animation = 5;
	animating = false;
	quadro = 0;
	count = 0;
	idt = 0;
	animation = 0;
}

RedMagic::Sprite::Sprite(int w, int h, int f, int a)
{
	frames = f;
	animations = a;
	width_total = w;
	height_total = h;

	speed_animation = 5;
	animating = false;
	quadro = 0;
	idt = 0;

	width_frame = w / f;
	height_frame = h / a;

	transform_ = NULL;
	rigidBody_ = NULL;

	animation = 0;
}


RedMagic::Sprite::~Sprite()
{
}

void RedMagic::Sprite::Update(double dt){
	//personagem->setFrameAtual((personagem->getFrameAtual() + 1) % personagem->getSprite().getFramesMax());
	//quadro = quadro + 1 % frames;

	if (GetGameObject()->isActive()) {

		if (rigidBody_ != NULL) {

			b2Fixture* fix = rigidBody_->GetBody()->GetFixtureList();

			const b2Transform& xf = fix->GetBody()->GetTransform();

			b2PolygonShape* poly = (b2PolygonShape*)fix->GetShape();
			int32 vertexCount = poly->m_count;
			b2Assert(vertexCount <= b2_maxPolygonVertices);
			b2Vec2 vertices[b2_maxPolygonVertices];

			for (int32 i = 0; i < vertexCount; ++i)
			{
				vertices[i] = b2Mul(xf, poly->m_vertices[i]);
			}

			glBindTexture(GL_TEXTURE_2D, idt);

			glBegin(GL_POLYGON);

			glTexCoord2f((float)(quadro / frames), 1.0);
			glVertex2f(vertices[0].x, vertices[0].y);

			glTexCoord2f((float)(quadro / frames) + (float)(1 / frames), 1.0);
			glVertex2f(vertices[1].x, vertices[1].y);

			glTexCoord2f((float)(quadro / frames) + (float)(1 / frames), 0.0);
			glVertex2f(vertices[2].x, vertices[2].y);

			glTexCoord2f((float)(quadro / frames), 0.0);
			glVertex2f(vertices[3].x, vertices[3].y);

		}
		else {
			//desenho de sprite padrão quadratrica
			glBindTexture(GL_TEXTURE_2D, idt);

			glBegin(GL_POLYGON);
			glTexCoord2f((float)(quadro / frames), 0.0);
			glVertex2f(transform_->position_.x - (width_frame / 2), transform_->position_.y + (height_frame / 2));

			glTexCoord2f((float)(quadro / frames) + (float)(1 / frames), 0.0);
			glVertex2f(transform_->position_.x + (width_frame / 2), transform_->position_.y + (height_frame / 2));

			glTexCoord2f((float)(quadro / frames) + (float)(1 / frames), 1.0);
			glVertex2f(transform_->position_.x + (width_frame / 2), transform_->position_.y - (height_frame / 2));

			glTexCoord2f((float)(quadro / frames), 1.0);
			glVertex2f(transform_->position_.x - (width_frame / 2), transform_->position_.y - (height_frame / 2));
		}
		glEnd();
	}
	//contador = 0;
	//contador++;
}

/*void RedMagic::Sprite::Initialize(int w, int h, int f, int a) {
	frames = f;
	animations = a;
	width_total = w;
	height_total = h;

	speed_animation = 5;
	animating = false;
	quadro = 0;
	idt = 0;

	width_frame = w / f;
	height_frame = h / a;

	animation = 0;
}*/
void RedMagic::Sprite::Cleanup() {
	//???
}

void RedMagic::Sprite::SetSpriteSheet(string name) {
	idt = Resources::getInstance()->GetSpriteSheet(name);
}
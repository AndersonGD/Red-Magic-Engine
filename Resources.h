#ifndef REDMAGIC_RESOURCES_H
#define REDMAGIC_RESOURCES_H

#define SDL_MAIN_HANDLED
#include <SDL\SDL.h>
#include <SDL\SDL_image.h>
#include <Box2D\Box2D.h>
#include <glm/glm.hpp>
#include <map>
#include <GL\glew.h>
#include <gl\GLU.h>
#include <GL/GL.h>
using namespace std;
#define TEXTURE_TAM 50
/*#include "Image.h"
#include "ImageMap.h"
#include "Tileset.h"*/

namespace RedMagic {
	class Resources
	{
	private:
		int pos;
		unsigned int textures[50];
		map<string, unsigned int> *sprites_;

		static Resources *instance_;

	public:
		static Resources* getInstance();

		void Initialize();

		b2Vec2 convertGlm2ToB2Vec2(glm::vec2 vec);
		float degreesToRadians(float angle);
		b2Vec2 calcComponentsOfVector(float mag, float angle);

		void LoadSpriteSheet(const char* spriteSheetName, const char* path);
		unsigned int GetSpriteSheet(string name);

		/*void loadImage(const char* name, const char* path, int num_animations, int num_frames);
		Image getImage(string name);
		int getNumImages(){ return _numImages; }
		void clear();
		void generateTextures(int qnt, Image** imgs, Tileset* tileset);
		void generateTextures(Image* img, GLuint *id);
		void generateTextures(SDL_Surface* msg, GLuint* id);
		void deleteTexture();*/

	};

	class QueryCallback : public b2QueryCallback
	{
	public:
		QueryCallback(const b2Vec2& point)
		{
			m_point = point;
			m_fixture = NULL;
		}

		bool ReportFixture(b2Fixture* fixture)
		{
			b2Body* body = fixture->GetBody();
			//if (body->GetType() == b2_dynamicBody)
			//{
				bool inside = fixture->TestPoint(m_point);
				if (inside)
				{
					m_fixture = fixture;

					// We are done, terminate the query.
					return false;
				}
		//	}

			// Continue the query.
			return true;
		}

		b2Vec2 m_point;
		b2Fixture* m_fixture;
	};
}
#endif

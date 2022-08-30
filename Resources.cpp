#include "Resources.h"
#include <iostream>
/*#include <fstream>
#include <string>
#include <iostream>
#include <SDL_opengl.h>

using namespace std;
*/

namespace RedMagic {
	RedMagic::Resources* RedMagic::Resources::instance_ = 0;

	void  Resources::Initialize() {
		glGenTextures(50, textures);
		pos = 0;
		sprites_ = new map<string, unsigned int>;
		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR) {
			cout << "OpenGL error: " << err << endl;
		}
	}

	void Resources::LoadSpriteSheet(const char* spriteSheetName, const char* path) {
		SDL_Surface* image;
		image = IMG_Load(path);

		//cria textura
		glBindTexture(GL_TEXTURE_2D, textures[pos]);
		int Mode = GL_RGB;

		if (image->format->BytesPerPixel == 4) {
			Mode = GL_RGBA;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, Mode, image->w, image->h, 0, Mode, GL_UNSIGNED_BYTE, image->pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//gluBuild2DMipmaps(GL_TEXTURE_2D, GL_BGRA, image->w, image->h, GL_BGRA_EXT, GL_UNSIGNED_BYTE, image->pixels);

		unsigned int idt = 0;
		idt = textures[pos];
		sprites_->insert(make_pair(spriteSheetName, idt));

		SDL_FreeSurface(image);

		pos++;
	}

	unsigned int Resources::GetSpriteSheet(string name) {
		//acha a img com tal nome
		auto temp = sprites_->find(name);
		//se n tem a img do nome retorna um crashzão bem bonito
		if (temp == sprites_->end()) {
			return NULL;
		}

		//se sim retorna img
		return temp->second;
	}

	/*
	void Resources::loadImage(const char* name, const char* path, int num_animations, int num_frames){
		int w = 0;
		int h = 0;
		ifstream arq(path);
		if (!path){
			cout << "Erro: " << path << " " << name << endl;
		}
		char temp[1024];
		arq >> temp;
		arq >> temp;

		w = atoi(temp);

		arq >> h;
		Image img(name, w, h, num_animations, num_frames);
		int n;
		arq >> n;

		int a, r, g, b;
		for (int i = 0; i <h; i++){
			for (int j = 0; j < w; j++){
				arq >> a >> r >> g >> b;
				img.setPixelFree(a, r, g, b, j, h - i - 1);
			}
		}
		_imageMap.addImage(name, img);	//add img in the map
		arq.close();
		_numImages++;
	}

	Image Resources::getImage(string name){
		return _imageMap.getImage(name);
	}
	*/
	RedMagic::Resources* RedMagic::Resources::getInstance() {
		if (instance_ == 0) {
			instance_ = new Resources;
		}
		return instance_;
	}

	b2Vec2 RedMagic::Resources::convertGlm2ToB2Vec2(glm::vec2 vec) {
		b2Vec2 p;
		p.x = vec.x;
		p.y = vec.y;
		return p;
	}

	float RedMagic::Resources::degreesToRadians(float angle) {
		return angle * 180 / b2_pi;
	}

	b2Vec2 RedMagic::Resources::calcComponentsOfVector(float mag, float angle) {
		float v = mag;
		float angulorad = degreesToRadians(angle);
		float vx = v*cos(angulorad);
		float vy = v*sin(angulorad);
		b2Vec2 vec(vx, vy);
		return vec;
	}

	/*
	void Resources::generateTextures(int qnt, Image** imgs, Tileset* tileset){
		for (int i = 0; i < qnt; i++){
			tileset->setTileID(textures[pos], i);
			glBindTexture(GL_TEXTURE_2D, tileset->getTileByID(i).getID());
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgs[i]->getWidth(), imgs[i]->getHeight(), 0, GL_BGRA, GL_UNSIGNED_BYTE, imgs[i]->getPixels());
			//gluBuild2DMipmaps(GL_TEXTURE_2D, GL_BGRA, imgs[i]->getWidth(), imgs[i]->getHeight(), GL_BGRA_EXT, GL_UNSIGNED_BYTE, imgs[i]->getPixels());
			pos++;
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void  Resources::generateTextures(Image* img, GLuint *id){
		*id = textures[pos];
		glBindTexture(GL_TEXTURE_2D, *id);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->getWidth(), img->getHeight(), 0, GL_BGRA, GL_UNSIGNED_BYTE, img->getPixels());
		//gluBuild2DMipmaps(GL_TEXTURE_2D, GL_BGRA, img->getWidth(), img->getHeight(), GL_BGRA_EXT, GL_UNSIGNED_BYTE, img->getPixels());
		glBindTexture(GL_TEXTURE_2D, 0);
		pos++;
	}

	void Resources::generateTextures(SDL_Surface* msg, GLuint* id){
		*id = textures[pos];
		glBindTexture(GL_TEXTURE_2D, *id);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, msg->w, msg->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, msg->pixels);
		//gluBuild2DMipmaps(GL_TEXTURE_2D, GL_BGRA, img->getWidth(), img->getHeight(), GL_BGRA_EXT, GL_UNSIGNED_BYTE, img->getPixels());
		glBindTexture(GL_TEXTURE_2D, 0);
		pos++;
	}

	void Resources::deleteTexture(){
		glDeleteTextures(1, &textures[pos--]);
		//pos--;
	}*/

}
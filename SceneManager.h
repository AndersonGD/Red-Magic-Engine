#ifndef REDMAGIC_SCENEMANAGER_H
#define REDMAGIC_SCENEMANAGER_H

#include "Scene.h"

namespace RedMagic {
	class SceneManager
	{
	private:
		static SceneManager* instance_;
		~SceneManager();

		Scene *current_ = NULL;
		map <string, Scene*>* scenes_;

	public:
		static SceneManager* GetInstance();

		void Initialize();

		void AddScene(string name, Scene *s);
		void SetCurrentScene(string name);

		void DeleteScene(string name);

		Scene* SceneManager::GetCurrentScene() {
			if (current_ != NULL) {
				return current_;
			}
		}
	};
}
#endif
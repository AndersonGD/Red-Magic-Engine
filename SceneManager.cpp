#include "SceneManager.h"


RedMagic::SceneManager* RedMagic::SceneManager::instance_ = 0;

RedMagic::SceneManager::~SceneManager()
{
}

void RedMagic::SceneManager::Initialize() {
	scenes_ = new map <string, Scene*>;
}

RedMagic::SceneManager* RedMagic::SceneManager::GetInstance() {
	if (instance_ == 0) {
		instance_ = new SceneManager;
	}
	return instance_;
}

void RedMagic::SceneManager::AddScene(string name, Scene *s) {
	scenes_->insert(map<string, Scene*>::value_type(name, s));
}

void RedMagic::SceneManager::SetCurrentScene(string name) {
	auto temp = scenes_->find(name);

	if (temp != scenes_->end()) {	//if scene name is correct then set it to the current scene
		current_ = temp->second;
	}
}

void RedMagic::SceneManager::DeleteScene(string name) {
	auto temp = scenes_->find(name);

	if (temp != scenes_->end()) {	//if scene name is correct then set it to the current scene
		delete temp->second;
		scenes_->erase(temp);
	}
}
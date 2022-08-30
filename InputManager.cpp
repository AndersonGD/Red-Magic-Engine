#include "InputManager.h"

InputManager* InputManager::_instance = 0;

InputManager::InputManager(){
	 
}
InputManager::~InputManager()
{
}

void InputManager::update(){
	//todo loop faz isso, for bacana utilizado pra diminuir o tamanho da linha e ficar mais bonito
	//copia a keymap pro keymap anterior pra veririficar se foi pressionado só uma vez
	for (auto& i : _keyMap){
		_previousKeyMap[i.first] = i.second;
	}
}

void InputManager::pressKey(unsigned int key){
	_keyMap[key] = true;
}

void InputManager::releaseKey(unsigned int key){
	_keyMap[key] = false;
}

bool InputManager::isKeyDown(unsigned int key){
	auto i = _keyMap.find(key);

	if (i != _keyMap.end()){
		return i->second;
	}
	else{
		return false;
	}
}

InputManager* InputManager::getInstance(){
	if (_instance == 0){
		_instance = new InputManager;
	}
	return _instance;
}

bool InputManager::isKeyPressed(unsigned int key){
	//se a key foi pressionada mas não foi pressionada no ultimo frame,
	//então só faz tal função uma única vez
	if (isKeyDown(key) == true && wasKeyDown(key) == false){
		return true;
	}
	return false;
}

bool InputManager::wasKeyDown(unsigned int key){
	auto i = _previousKeyMap.find(key);

	if (i != _previousKeyMap.end()){
		return i->second;
	}
	else{
		return false;
	}
}

void InputManager::setMousePosition(float x, float y){
	_mouseX = x;
	_mouseY = y;
}
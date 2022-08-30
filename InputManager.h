#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <unordered_map>
using namespace std;

class InputManager
{
private:
	float _mouseY = 0;
	float _mouseX = 0;
	static InputManager* _instance;
	unordered_map<unsigned int, bool> _keyMap;
	unordered_map<unsigned int, bool> _previousKeyMap;

	bool wasKeyDown(unsigned int key);
	InputManager();
public:
	~InputManager();
	static InputManager* getInstance();

	//KEYBOARD
	void pressKey(unsigned int key);
	void releaseKey(unsigned int key);
	//segurando tecla
	bool isKeyDown(unsigned int key);
	//apenas pressionada
	bool isKeyPressed(unsigned int key);

	void update();
	//MOUSE
	void setMousePosition(float x, float y);
	float getMouseX(){ return _mouseX; }
	float getMouseY(){ return _mouseY; }


	unordered_map<unsigned int, bool> GetKeyMap() { return _keyMap; }
	unordered_map<unsigned int, bool> GetPreviousKeyMap() { return _previousKeyMap; }
};
#endif

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

class InputManager {

private:
	bool* joysticks_array;

public:
	InputManager(int);
	~InputManager();
};

#endif
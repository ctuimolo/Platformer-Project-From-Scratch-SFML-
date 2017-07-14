#include "InputManager.h"

InputManager::InputManager(int num_joysticks) {
	joysticks_array = new bool[num_joysticks];
}

InputManager::~InputManager() {
	delete[] joysticks_array;
}
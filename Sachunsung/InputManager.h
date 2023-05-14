#pragma once

#include <conio.h>
#include "Constants.h"

class InputManager {
public:
	static InputManager& getInstance();
	KeyCode inputKey();

private:
	InputManager() {}
	~InputManager() {}
	
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;
};
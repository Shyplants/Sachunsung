#include "InputManager.h"

InputManager& InputManager::getInstance() {
	static InputManager instance;
	return instance;
}

KeyCode InputManager::inputKey()
{
	int key = _getch();
	if (key == KEY_ARROW_VALUE)
	{
		key = _getch();
		if (key == KEY_UP_VALUE) return KeyCode::KEY_UP;
		if (key == KEY_DOWN_VALUE) return KeyCode::KEY_DOWN;
		if (key == KEY_LEFT_VALUE) return KeyCode::KEY_LEFT;
		if (key == KEY_RIGHT_VALUE) return KeyCode::KEY_RIGHT;
	}
	if (key == KEY_SPACE_VALUE) return KeyCode::KEY_SPACE;
	if (key == KEY_ENTER_VALUE) return KeyCode::KEY_ENTER;

	return KeyCode::KEY_DEFAULT;
}
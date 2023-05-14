#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <Windows.h>
#include "Constants.h"

class GameMenu {
public:
	GameMenu();
	~GameMenu();

	void init();
	void run();
	void update();
	void render();

	void showInfo();
	void showTitle(std::string& s, int yOffset, int spaceSize, char mark);
	void showBackGround();
private:
	bool isRunning;
	bool titleAlphaOutput[ALPHA_SIZE][BUFFER_SIZE];
	char command[BUFFER_SIZE];
	std::string titleString;
	int yCursorOffset, xCursorOffset, dyCursor, menuCode;
};
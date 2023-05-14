#include "GameMenu.h"
#include "Util.h"
#include "Game.h"
#include "InputManager.h"

GameMenu::GameMenu() {
	isRunning = false;
}

GameMenu::~GameMenu() {

}

void GameMenu::init() {
	isRunning = true;
	titleString = "SACHUNSUNG";
	yCursorOffset = CONSOLE_HEIGHT / 2;
	xCursorOffset = CONSOLE_WIDTH / 2 - MENU_WIDTH / 2;
	dyCursor = 0;

	sprintf(command, "mode con lines=%d cols=%d", CONSOLE_HEIGHT, CONSOLE_WIDTH);
	system(command);

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = false;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);

	Util& util = Util::getInstance();
	util.split(titleString, titleAlphaOutput);

	showBackGround();
}

void GameMenu::run() {
	init();

	while (isRunning) {
		render();
		update();
	}

	if (menuCode == 2) return;
	Game game;
	game.run();
}

void GameMenu::render()
{
	Util& util = Util::getInstance();
	util.drawCursor(xCursorOffset, yCursorOffset + dyCursor);
}

void GameMenu::update()
{
	while (true)
	{
		InputManager& inputManager = InputManager::getInstance();
		Util& util = Util::getInstance();
		switch (inputManager.inputKey())
		{
		case KeyCode::KEY_UP:
			util.clearCursor(xCursorOffset, yCursorOffset + dyCursor);
			dyCursor = max(0, dyCursor - 1);
			return;
		case KeyCode::KEY_DOWN:
			util.clearCursor(xCursorOffset, yCursorOffset + dyCursor);
			dyCursor = min(MENU_CNT - 1, dyCursor + 1);
			return;

		case KeyCode::KEY_SPACE:
		case KeyCode::KEY_ENTER:
			menuCode = dyCursor;
			switch (menuCode)
			{
			case 0:
			case 2:
				isRunning = false;
				return;
			case 1:
				showInfo();
				return;
			default:
				break;
			}

		default:
			break;
		}
	}
}

void GameMenu::showInfo()
{
	Util& util = Util::getInstance();
	util.clear();

	const int INFO_CNT = 4;
	std::string infoString[INFO_CNT] = { "게임제목 : 사천성", "개발자 : Shyplants", "", "스페이스바를 누르면 메인화면으로 이동합니다." };
	for (int i = 0; i < INFO_CNT; ++i) {
		util.goToXY(CONSOLE_WIDTH / 2 - INFO_WIDTH / 2, CONSOLE_HEIGHT / 2 + i);

		int centerOffset = (INFO_WIDTH - infoString[i].length()) / 2;
		for (int iter = 0; iter < centerOffset; ++iter)
			std::cout << ' ';
		std::cout << infoString[i] << '\n';
	}

	while (true)
	{
		InputManager& inputManager = InputManager::getInstance();
		if (inputManager.inputKey() == KeyCode::KEY_SPACE) break;
	}

	// return GameMenu
	showBackGround();
}

void GameMenu::showTitle(std::string& s, int yOffset, int spaceSize, char mark)
{
	for (int iter = 0; iter < yOffset; ++iter) std::cout << '\n';

	int len = s.length();
	int centerOffset = (CONSOLE_WIDTH - (ALPHA_SIZE * len + (len - 1) * spaceSize)) / 2;
	for (int y = 0; y < ALPHA_SIZE; ++y) {
		for (int iter = 0; iter < centerOffset; ++iter) {
			std::cout << ' ';
		}
		for (int idx = 0; idx < len; ++idx) {
			for (int x = 0; x < ALPHA_SIZE; ++x) {
				int xOffset = idx * ALPHA_SIZE + x;      // xOffset -> [ALPHA_SIZE*idx ... ALPHA_SIZE*idx + ALPHA_SIZE)

				std::cout << (titleAlphaOutput[y][xOffset] ? mark : ' ');
			}

			for (int iter = 0; iter < spaceSize; ++iter) {
				std::cout << ' ';
			}
		}
		std::cout << '\n';
	}
}

void GameMenu::showBackGround()
{
	Util& util = Util::getInstance();
	util.clear();
	showTitle(titleString, 3, 3, '@');

	std::string menuTitle[MENU_CNT] = { "게임시작", "게임정보", "종료" };
	for (int i = 0; i < MENU_CNT; ++i) {
		util.goToXY(CONSOLE_WIDTH / 2 - MENU_WIDTH / 2, CONSOLE_HEIGHT / 2 + i);

		int centerOffset = (MENU_WIDTH - menuTitle[i].length()) / 2;
		for (int iter = 0; iter < centerOffset; ++iter)
			std::cout << ' ';
		std::cout << menuTitle[i] << '\n';
	}

	util.drawCursor(xCursorOffset, yCursorOffset + dyCursor);
}
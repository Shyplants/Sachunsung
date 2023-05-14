#include "util.h"
#include <iostream>
#include <Windows.h>


Util& Util::getInstance() {
	static Util instance;
	return instance;
}

void Util::clear()
{
	system("cls");
}

void Util::goToXY(short x, short y)
{
	COORD pos{ x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Util::drawCursor(short x, short y)
{
	goToXY(x, y);
	std::cout << '>';
}

void Util::clearCursor(short x, short y)
{
	goToXY(x, y);
	std::cout << ' ';
}

int Util::getCursorPosX()
{
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
	return consoleInfo.dwCursorPosition.X;
}

int Util::getCursorPosY()
{
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
	return consoleInfo.dwCursorPosition.Y;
}

void Util::split(std::string& s, bool output[][BUFFER_SIZE])
{
	int len = s.length();
	for (int y = 0; y < ALPHA_SIZE; ++y) {
		for (int idx = 0; idx < len; ++idx) {
			int alphaOffset = s[idx] - 'A';              // [A...Z] -> [0...25]
			for (int x = 0; x < ALPHA_SIZE; ++x) {
				int xOffset = idx * ALPHA_SIZE + x;      // xOffset -> [ALPHA_SIZE*idx ... ALPHA_SIZE*idx + ALPHA_SIZE)

				output[y][xOffset] = alphaBoard[alphaOffset][y][x];
			}
		}
	}
}

int Util::getMax(int a, int b)
{
	return a > b ? a : b;
}

int Util::getMin(int a, int b)
{
	return a < b ? a : b;
}

int Util::pos2Id(int y, int x)
{
	return y * BOARD_WIDTH + x;
}

int Util::getDist(int y1, int x1, int y2, int x2)
{
	return abs(y1 - y2) + abs(x1 - x2);
}

void Util::setBackgroundColor(Color color)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(consoleHandle, &consoleInfo);
	WORD attributes = (consoleInfo.wAttributes & 0xFF0F) | (color << 4);
	SetConsoleTextAttribute(consoleHandle, attributes);
}

void Util::setFontColor(Color color)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(consoleHandle, &consoleInfo);
	WORD attributes = (consoleInfo.wAttributes & 0xFFF0) | color;
	SetConsoleTextAttribute(consoleHandle, attributes);
}

void Util::resetColors()
{
	setBackgroundColor(Color::Black);
	setFontColor(Color::White);
}


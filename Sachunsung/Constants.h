#pragma once

// console value
const int CONSOLE_WIDTH = 100;
const int CONSOLE_HEIGHT = 20;
const int MENU_WIDTH = 20;
const int INFO_WIDTH = 60;
const int BUFFER_SIZE = 1 << 10;

// key value
const int KEY_ARROW_VALUE = 224;
const int KEY_UP_VALUE = 72;
const int KEY_DOWN_VALUE = 80;
const int KEY_LEFT_VALUE = 75;
const int KEY_RIGHT_VALUE = 77;
const int KEY_SPACE_VALUE = 32;
const int KEY_ENTER_VALUE = 13;

// title value
const int ALPHA_CNT = 26;
const int ALPHA_SIZE = 5;

// menu value
const int MENU_CNT = 3;

// game value
const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 8;
const int GAME_BOARD_WIDTH = 8;
const int GAME_BOARD_HEIGHT = 6;
const int CARD_TYPE_CNT = 4;
const int TURN_COST = 500;
const int INF = 0x3f3f3f3f;

enum class KeyCode {
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_SPACE,
	KEY_ENTER,
	KEY_DEFAULT
};

enum Color {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DrakGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15,
};

enum class MatchingResult {
	Initial,
	Success,
	Failure
};
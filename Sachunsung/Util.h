#pragma once
#include <string>
#include "Constants.h"

class Util {
public:
	static Util& getInstance();

	void clear();
	void goToXY(short x, short y);
	void drawCursor(short x, short y);
	void clearCursor(short x, short y);
	int getCursorPosY();
	int getCursorPosX();
	void split(std::string& s, bool output[][BUFFER_SIZE]);
	
	int getMax(int a, int b);
	int getMin(int a, int b);

	int pos2Id(int y, int x);
	int getDist(int y1, int x1, int y2, int x2);

	void setBackgroundColor(Color color);
	void setFontColor(Color color);
	void resetColors();


private:
	Util() {}
	~Util() {}

	Util(const Util&) = delete;
	Util& operator=(const Util&) = delete;

	const bool alphaBoard[ALPHA_CNT][ALPHA_SIZE][ALPHA_SIZE] = {
		// A
		{
			{false, false, true, false, false},
			{false, true, false, true, false},
			{true, true, true, true, true},
			{true, false, false, false, true},
			{true, false, false, false, true}
		},
		// B
		{
			{true, true, true, true, false},
			{true, false, false, false, true},
			{true, true, true, true, false},
			{true, false, false, false, true},
			{true, true, true, true, false}
		},
		// C
		{
			{false, true, true, true, true},
			{true, false, false, false, false},
			{true, false, false, false, false},
			{true, false, false, false, false},
			{false, true, true, true, true}
		},
		// D
		{
			{true, true, true, true, false},
			{true, false, false, false, true},
			{true, false, false, false, true},
			{true, false, false, false, true},
			{true, true, true, true, false}
		},
		// E
		{
			{true, true, true, true, true},
			{true, false, false, false, false},
			{true, true, true, true, false},
			{true, false, false, false, false},
			{true, true, true, true, true}
		},
		// F
		{
			{true, true, true, true, true},
			{true, false, false, false, false},
			{true, true, true, true, false},
			{true, false, false, false, false},
			{true, false, false, false, false}
		},
		// G
		{
			{false, true, true, true, false},
			{true, false, false, false, false},
			{true, false, true, true, true},
			{true, false, false, true, false},
			{false, true, true, true, false}
		},
		// H
		{
			{true, false, false, false, true},
			{true, false, false, false, true},
			{true, true, true, true, true},
			{true, false, false, false, true},
			{true, false, false, false, true}
		},
		// I
		{
			{true, true, true, true, true},
			{false, false, true, false, false},
			{false, false, true, false, false},
			{false, false, true, false, false},
			{true, true, true, true, true}
		},
		// J
		{
			{true, true, true, true, true},
			{false, false, true, false, false},
			{false, false, true, false, false},
			{true, false, true, false, false},
			{false, true, false, false, false}
		},
		// K
		{
			{true, false, false, false, true},
			{true, false, false, true, false},
			{true, true, true, false, false},
			{true, false, false, true, false},
			{true, false, false, false, true}
		},
		// L
		{
			{true, false, false, false, false},
			{true, false, false, false, false},
			{true, false, false, false, false},
			{true, false, false, false, false},
			{true, true, true, true, true}
		},
		// M
		{
			{true, false, false, false, true},
			{true, true, false, true, true},
			{true, false, true, false, true},
			{true, false, true, false, true},
			{true, false, false, false, true}
		},
		// N
		{
			{true, false, false, false, true},
			{true, true, false, false, true},
			{true, false, true, false, true},
			{true, false, false, true, true},
			{true, false, false, false, true}
		},
		// O
		{
			{false, true, true, true, false},
			{true, false, false, false, true},
			{true, false, false, false, true},
			{true, false, false, false, true},
			{false, true, true, true, false}
		},
		// P
		{
			{true, true, true, true, false},
			{true, false, false, false, true},
			{true, true, true, true, false},
			{true, false, false, false, false},
			{true, false, false, false, false}
		},
		// Q
		{
			{false, true, true, false, false},
			{true, false, false, true, false},
			{true, false, true, true, false},
			{true, false, false, true, false},
			{false, true, true, false, true}
		},
		// R
		{
			{true, true, true, true, false},
			{true, false, false, false, true},
			{true, true, true, true, false},
			{true, false, false, true, false},
			{true, false, false, false, true}
		},
		// S
		{
			{false, true, true, true, false},
			{true, false, false, false, false},
			{false, true, true, true, false},
			{false, false, false, false, true},
			{false, true, true, true, false}
		},
		// T
		{
			{true, true, true, true, true},
			{false, false, true, false, false},
			{false, false, true, false, false},
			{false, false, true, false, false},
			{false, false, true, false, false}
		},
		// U
		{
			{true, false, false, false, true},
			{true, false, false, false, true},
			{true, false, false, false, true},
			{true, false, false, false, true},
			{false, true, true, true, false}
		},
		// V
		{
			{true, false, false, false, true},
			{true, false, false, false, true},
			{true, false, false, false, true},
			{false, true, false, true, false},
			{false, false, true, false, false}
		},
		// W
		{
			{true, false, true, false, true},
			{true, false, true, false, true},
			{true, false, true, false, true},
			{false, true, false, true, false},
			{false, true, false, true, false}
		},
		// X
		{
			{true, false, false, false, true},
			{false, true, false, true, false},
			{false, false, true, false, false},
			{false, true, false, true, false},
			{true, false, false, false, true}
		},
		// Y
		{
			{true, false, false, false, true},
			{false, true, false, true, false},
			{false, false, true, false, false},
			{false, false, true, false, false},
			{false, false, true, false, false}
		},
		// Z
		{
			{true, true, true, true, true},
			{false, false, false, true, false},
			{false, false, true, false, false},
			{false, true, false, false, false},
			{true, true, true, true, true}
		}
	};
};


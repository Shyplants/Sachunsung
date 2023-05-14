#pragma once
#include <iostream>
#include <list>
#include "Util.h"

class Pos {
public:
	Pos() {};
	Pos(int _y, int _x) : y(_y), x(_x) {}

	int y, x;
};

class Node {
public:
	int id;
	int f, g, h;
	int turnCount;
	int parentId, pparentId;

	Node() { 
		f = g = h = turnCount = 0; 
		id = parentId = pparentId = -1;
	};
	Node(int _id, int _f, int _g, int _h, int _turnCount, int _parentId, int _pparentId) {
		id = _id;
		f = _f;
		g = _g;
		h = _h;
		turnCount = _turnCount;
		parentId = _parentId;
		pparentId = _pparentId;
	}

	void init() {
		f = g = h = turnCount = 0;
		id = parentId = -1;
	}
	int getY() { return id / BOARD_WIDTH; }
	int getX() { return id % BOARD_WIDTH; }
};

struct CompareNodes {
	bool operator()(const Node* node1, const Node* node2) const {
		return node1->f < node2->f;
	}
};


class Game{
public:
	Game();
	~Game();

	void init();
	void run();
	void update();
	void render();

	void showInfo();

	Pos selectedCardPos[2];
	std::list<Node> openList, closeList;
private:
	bool isRunning;
	int gameBoardY, gameBoardX;
	int yBoardOffset, xBoardOffset;
	int yMargin, xMargin;
	int gameBoard[GAME_BOARD_HEIGHT][GAME_BOARD_WIDTH];
	bool isMatchedGameBoard[GAME_BOARD_HEIGHT][GAME_BOARD_WIDTH];
	bool isMatchedRoute[BOARD_HEIGHT][BOARD_WIDTH];
	bool isLineRoute[BOARD_HEIGHT][BOARD_WIDTH];
	char cardMark[CARD_TYPE_CNT][3];
	int cardIdx;
	int dy[4], dx[4];
	int existCardCount;
	bool isClear;

	void paintBox(int consoleY, int consoleX, int gameBoadY, int gameBoardX, Color color);
	void clearBox(int consoleY, int consoleX, int gameBoadY, int gameBoardX);
	bool isOutBoard(int y, int x);
	bool isOutGameBoard(int y, int x);
	void selectCard(int y, int x);
	void clearSelectedCard();
	void clearLineRoute();
	MatchingResult matchingResult;
	bool isMatch();
	bool isTurn(int prev, int cur, int nxt);

	void insertNode(std::list<Node>& list, Node& node);
	bool isExistNodeById(std::list<Node>& list, int targetId);
	int getValueById(std::list<Node>& list, int targetId);
	int getParentIdById(std::list<Node>& list, int targetId, int targetParentId);
	int getPparentIdById(std::list<Node>& list, int targetId);
	void updateNodeById(std::list<Node>& list, int targetId, Node& node);

	void findRoute(int srcId, int destId);
};
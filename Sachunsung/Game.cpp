#include "Game.h"
#include "InputManager.h"
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>

Game::Game() {
	isRunning = false;
	
}

Game::~Game() {
	
}

void Game::init() {
	isRunning = true;
	yBoardOffset = CONSOLE_HEIGHT/4;
	xBoardOffset = CONSOLE_WIDTH / 2 - BOARD_WIDTH;
	gameBoardY = gameBoardX = 0;
	yMargin = xMargin = 1;

	strcpy(cardMark[0], "▤");
	strcpy(cardMark[1], "▥");
	strcpy(cardMark[2], "▨");
	strcpy(cardMark[3], "▧");

	int cardCnt[CARD_TYPE_CNT] = { 0 }, generatedCnt = 0;
	for (int i = 0; i < CARD_TYPE_CNT; ++i) {
		cardCnt[i] = GAME_BOARD_HEIGHT * GAME_BOARD_WIDTH / CARD_TYPE_CNT;
	}

	srand(time(NULL));
	for (int y = 0; y < GAME_BOARD_HEIGHT; ++y) for (int x = 0; x < GAME_BOARD_WIDTH; ++x) {
		isMatchedGameBoard[y][x] = false;

		while (true) {
			int r = rand() % CARD_TYPE_CNT;

			if (cardCnt[r]) {
				cardCnt[r]--;
				gameBoard[y][x] = r;
				break;
			}
		}
	}

	for (int i = 0; i < 2; ++i)
		selectedCardPos[i] = Pos(-1, -1);
	cardIdx = 0;
	matchingResult = MatchingResult::Initial;

	// 방향
	dy[0] = -1, dx[0] = 0;  // 상
	dy[1] = 0, dx[1] = 1;   // 우
	dy[2] = 1, dx[2] = 0;   // 하
	dy[3] = 0, dx[3] = -1;  // 좌

	openList.clear();
	closeList.clear();
	existCardCount = GAME_BOARD_HEIGHT * GAME_BOARD_WIDTH;
	isClear = false;
}

void Game::run() {
	init();
	while (isRunning) {
		render();
		update();
	}

	if (isClear)
	{
		Util& util = Util::getInstance();
		util.clear();

		std::string resultString[2] = { "CLEAR!!" , "3초후에 종료됩니다.."};
		for (int i = 0; i < 2; ++i) {
			util.goToXY(CONSOLE_WIDTH / 2 - resultString[i].length() / 2, CONSOLE_HEIGHT / 2 + i*5);
			std::cout << resultString[i];
		}

		Sleep(3000);
	}
}

void Game::render() {
	Util& util = Util::getInstance();
	util.clear();

	for (int i = 0; i < BOARD_HEIGHT; ++i) {
		util.goToXY(xBoardOffset, yBoardOffset+i);
		for (int j = 0; j < BOARD_WIDTH; ++j) {
			if (isLineRoute[i][j]) {
				std::cout << "■";
				continue;
			}

			if (isOutGameBoard(i, j)) {
				std::cout << "□";
				continue;
			}

			if (isMatchedGameBoard[i-yMargin][j-xMargin]) {
				paintBox(util.getCursorPosY(), util.getCursorPosX(), i-yMargin, j-xMargin, Color::Black);
				util.resetColors();
			}
			
			else if (selectedCardPos[0].y == i - yMargin && selectedCardPos[0].x == j - xMargin) {
				paintBox(util.getCursorPosY(), util.getCursorPosX(), i-yMargin, j-xMargin, Color::Red);
				util.resetColors();
			}

			else if (selectedCardPos[1].y == i - yMargin && selectedCardPos[1].x == j - xMargin) {
				paintBox(util.getCursorPosY(), util.getCursorPosX(), i-yMargin, j-xMargin, Color::Red);
				util.resetColors();
			}

			else  std::cout << cardMark[gameBoard[i - yMargin][j - xMargin]];
		}
	}

	if(isMatchedGameBoard[gameBoardY][gameBoardX]) util.setBackgroundColor(Color::Green);
	paintBox(yBoardOffset + yMargin + gameBoardY, xBoardOffset + (xMargin + gameBoardX) * 2, gameBoardY, gameBoardX, Color::Green);
	
	showInfo();
}

void Game::update() {

	Util& util = Util::getInstance();
	InputManager& inputManager = InputManager::getInstance();

	// 게임 클리어
	if (existCardCount == 0)
	{
		isClear = true;
		isRunning = false;
	}

	// 두 카드 선택완료
	if (cardIdx == 2 && matchingResult == MatchingResult::Initial) {                                      
		int cardType[2];
		for (int i = 0; i < 2; ++i)
			cardType[i] = gameBoard[selectedCardPos[i].y][selectedCardPos[i].x];


		// 선택된 두 카드의 모양이 다름 -> 매칭 실패
		if (cardType[0] != cardType[1]) {
			matchingResult = MatchingResult::Failure;

			return;
		}

		// 선택된 두 카드의 모양이 같음 -> 경로 탐색
		else {
			if (isMatch())
			{
				matchingResult = MatchingResult::Success;

				isMatchedGameBoard[selectedCardPos[0].y][selectedCardPos[0].x] = true;
				isMatchedGameBoard[selectedCardPos[1].y][selectedCardPos[1].x] = true;

				existCardCount -= 2;
			}
			else
			{
				matchingResult = MatchingResult::Failure;
			}

			return;
		}
	}

	while (true)
	{	
		bool bKeyPressed = false;
		bool bArrowKeyPressed = false;
		switch (inputManager.inputKey())
		{
		case KeyCode::KEY_UP:
			bKeyPressed = bArrowKeyPressed = true;
			gameBoardY = util.getMax(0, gameBoardY - 1);
			break;
		case KeyCode::KEY_DOWN:
			bKeyPressed = bArrowKeyPressed = true;
			gameBoardY = util.getMin(GAME_BOARD_HEIGHT-1, gameBoardY + 1);
			break;
		case KeyCode::KEY_LEFT:
			bKeyPressed = bArrowKeyPressed = true;
			gameBoardX = util.getMax(0, gameBoardX - 1);
			break;
		case KeyCode::KEY_RIGHT:
			bKeyPressed = bArrowKeyPressed = true;
			gameBoardX = util.getMin(GAME_BOARD_WIDTH - 1, gameBoardX + 1);
			break;

		case KeyCode::KEY_SPACE:
			bKeyPressed = true;
			selectCard(gameBoardY, gameBoardX);
			break;
		case KeyCode::KEY_ENTER:
			bKeyPressed = true;
			break;

		default:
			bKeyPressed = true;
			break;
		}

		if (bKeyPressed)
		{
			if (matchingResult != MatchingResult::Initial) {
				if (matchingResult == MatchingResult::Success)
					clearLineRoute();
				
				matchingResult = MatchingResult::Initial;
				clearSelectedCard();
			}
			break;
		}

		if (bArrowKeyPressed) {
			clearBox(yBoardOffset + yMargin + gameBoardY, xBoardOffset + (xMargin + gameBoardX) * 2, gameBoardY, gameBoardX);
			break;
		}
	}
}
bool Game::isTurn(int prev, int cur, int nxt) 
{
	int prevY = prev / BOARD_WIDTH, prevX = prev % BOARD_WIDTH;
	int curY = cur / BOARD_WIDTH, curX = cur % BOARD_WIDTH;
	int nxtY = nxt / BOARD_WIDTH, nxtX = nxt % BOARD_WIDTH;

	if ((prevY == curY && curY == nxtY) || (prevX == curX && curX == nxtX))
		return false;

	return true;
}

void Game::insertNode(std::list<Node>& list, Node& node)
{
	for (auto iter = list.begin(); iter != list.end(); ++iter)
	{
		if (iter->f > node.f) {
			list.insert(iter, node);
			return;
		}
	}

	list.push_back(node);
}

bool Game::isExistNodeById(std::list<Node>& list, int targetId)
{
	for (auto& node : list) {
		if (node.id == targetId) return true;
	}

	return false;
}

int Game::getParentIdById(std::list<Node>& list, int targetId, int targetParentId)
{
	for (auto& node : list) {
		if (node.id == targetId && (node.pparentId == targetParentId || targetParentId == -1)) return node.parentId;
	}

	return -1;
}

int Game::getPparentIdById(std::list<Node>& list, int targetId)
{
	for (auto& node : list) {
		if (node.id == targetId) return node.pparentId;
	}

	return -1;
}

int Game::getValueById(std::list<Node>& list, int targetId)
{
	for (auto& node : list) {
		if (node.id == targetId) return node.f;
	}

	return -1;
}

void Game::updateNodeById(std::list<Node>& list, int targetId, Node& node)
{
	for (auto iter = list.begin(); iter != list.end(); ++iter)
	{
		if (iter->id == node.id) {
			*iter = node;
			break;
		}
	}
}

void Game::findRoute(int srcId, int destId)
{
	Util& util = Util::getInstance();

	Node curNode = closeList.back();
	isLineRoute[curNode.getY()][curNode.getX()] = true;

	for (auto iter = closeList.crbegin(); iter != closeList.crend(); ++iter)
	{
		if ((iter->id == curNode.parentId) && (iter->parentId == curNode.pparentId))
		{
			curNode = *iter;
			isLineRoute[curNode.getY()][curNode.getX()] = true;
		}
	}
}

bool Game::isMatch()
{
	Util& util = Util::getInstance();

	// Gameboarad offset -> Board offset
	Pos srcPos = Pos(selectedCardPos[0].y + yMargin, selectedCardPos[0].x + xMargin);
	Pos destPos = Pos(selectedCardPos[1].y + yMargin, selectedCardPos[1].x + xMargin);

	// init
	openList.clear();
	closeList.clear();


	Node curNode, nxtNode;
	curNode.init();
	nxtNode.init();

	curNode.id = util.pos2Id(srcPos.y, srcPos.x);
	curNode.h = util.getDist(srcPos.y, srcPos.x, destPos.y, destPos.x);
	curNode.f = curNode.g + curNode.h;
	
	insertNode(closeList, curNode);
	
	for (int dir = 0; dir < 4; ++dir) {
		int ny = curNode.getY() + dy[dir];
		int nx = curNode.getX() + dx[dir];

		if (isOutBoard(ny, nx)) continue;
		if (isOutGameBoard(ny, nx) || (ny == destPos.y && nx == destPos.x) || isMatchedGameBoard[ny - yMargin][nx - xMargin])
		{
			nxtNode.id = util.pos2Id(ny, nx);
			nxtNode.parentId = util.pos2Id(srcPos.y, srcPos.x);
			nxtNode.g = util.getDist(srcPos.y, srcPos.x, ny, nx);
			nxtNode.h = util.getDist(ny, nx, destPos.y, destPos.x);
			nxtNode.f = nxtNode.g + nxtNode.h;

			insertNode(openList, nxtNode);
		}
	}

	while (!openList.empty())
	{
		Node curNode = *openList.begin(); openList.erase(openList.begin());

		// 3번 이상 꺽은 경우 무시
		if (curNode.f >= TURN_COST * 3) continue;

		int y = curNode.getY();
		int x = curNode.getX();

		insertNode(closeList, curNode);

		// srcPos -> destPos 매칭 성공
		if (y == destPos.y && x == destPos.x) {
			findRoute(srcPos.y * BOARD_WIDTH + srcPos.x, destPos.y * BOARD_WIDTH + destPos.x);
			return true;
		}

		for (int dir = 0; dir < 4; ++dir) {
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			if (isOutBoard(ny, nx) || isExistNodeById(closeList, util.pos2Id(ny,nx))) continue;
			if (isOutGameBoard(ny, nx) || (ny == destPos.y && nx == destPos.x) || isMatchedGameBoard[ny - yMargin][nx - xMargin])
			{
				nxtNode.id = util.pos2Id(ny, nx);
				nxtNode.parentId = util.pos2Id(y, x);
				nxtNode.pparentId = curNode.parentId;

				nxtNode.turnCount = curNode.turnCount + isTurn(curNode.parentId, curNode.id, nxtNode.id);
				nxtNode.g = util.getDist(srcPos.y, srcPos.x, ny, nx) + TURN_COST*nxtNode.turnCount;
				nxtNode.h = util.getDist(ny, nx, destPos.y, destPos.x);
				nxtNode.f = nxtNode.g + nxtNode.h;


				if (!isExistNodeById(openList, util.pos2Id(ny, nx)))
				{
					insertNode(openList, nxtNode);
				}
				else
				{
					if (getValueById(openList, util.pos2Id(ny, nx)) >= nxtNode.f)
					{
						updateNodeById(openList, util.pos2Id(ny, nx), nxtNode);
					}
				}
				
			}
		}
	}
	
	return false;
}

void Game::showInfo()
{
	Util& util = Util::getInstance();
	const int xOffset = CONSOLE_WIDTH / 3 * 2;
	const int yOffset = yBoardOffset;


	util.goToXY(xOffset, yOffset);
	std::cout << "현재위치(y, x): " << '(' << gameBoardY << ", " << gameBoardX << ')';

	for (int card = 0; card < 2; ++card) {
		util.goToXY(xOffset, yOffset + 2 + card*2);
		std::cout << "선택" << card + 1 << "위치(y, x): ";
		if (selectedCardPos[card].y == -1) std::cout << "X";
		else std::cout << '(' << selectedCardPos[card].y << ", " << selectedCardPos[card].x << ')';
	}

	util.goToXY(xOffset, yOffset + 6);
	std::cout << "게임상태: ";
	if (matchingResult == MatchingResult::Failure) {
		std::cout << "매칭 실패";
	}
	if (matchingResult == MatchingResult::Success) {
		std::cout << "매칭 성공";
	}
}

void Game::paintBox(int consoleY, int consoleX, int gameBoadY, int gameBoardX, Color color)
{
	Util& util = Util::getInstance();
	util.setFontColor(color);
	util.goToXY(consoleX, consoleY);
	std::cout << cardMark[gameBoard[gameBoadY][gameBoardX]];
	util.resetColors();
}

void Game::clearBox(int consoleY, int consoleX, int gameBoadY, int gameBoardX)
{
	Util& util = Util::getInstance();
	util.goToXY(consoleX, consoleY);
	std::cout << cardMark[gameBoard[gameBoadY][gameBoardX]];
}

bool Game::isOutBoard(int y, int x)
{
	return	y < 0 || y >= BOARD_HEIGHT || x < 0 || x >= BOARD_WIDTH;
}

bool Game::isOutGameBoard(int y, int x)
{
	return	y < yMargin || y >= BOARD_HEIGHT - yMargin || x < xMargin || x >= BOARD_WIDTH - xMargin;
}

void Game::selectCard(int y, int x)
{
	selectedCardPos[cardIdx] = Pos(y, x);
	cardIdx++;
}

void Game::clearSelectedCard()
{
	for (int i = 0; i < 2; ++i) selectedCardPos[i].y = -1;
	cardIdx = 0;
}

void Game::clearLineRoute()
{
	memset(isLineRoute, 0, sizeof(isLineRoute));
}
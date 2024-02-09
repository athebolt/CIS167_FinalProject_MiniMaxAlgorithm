#pragma once
#include "Board.h"
class GameDriver
{
private:
	Board game;
public:
	void gameStart();
	void playerTurn();
	void aiTurn();
	int checkWin(Board);

	void setBoard(Board);
};


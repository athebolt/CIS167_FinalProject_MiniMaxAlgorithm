#pragma once
#include "Cell.h"
#include "Board.h"
class AI
{
private:

public:
	AI();

	Cell miniMaxStart(Board);
	int miniMaxAlg(Board, int, bool);
	int whoWon(Board);
};


#pragma once
#include "Cell.h"
class Board
{
private:
	Cell curCell;
	const static int rows = 3;
	const static int cols = 3;
	Cell board[rows][cols];
public:
	Board();
	void dispBoard();
	void initBoard();

	Cell getCell() const;
	Cell getCell(int, int) const;
	int getRows() const;
	int getCols() const;

	void setCell(Cell);
	void setCell(int, int, Cell);
};


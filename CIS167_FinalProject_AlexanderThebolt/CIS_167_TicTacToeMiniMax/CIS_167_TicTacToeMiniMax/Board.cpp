#include "Board.h"
#include "iostream"

using namespace std;

Board::Board()
{

}
void Board::dispBoard()
{
	cout << "     A   B   C" << endl << endl;
	cout << "1    " << board[0][0].getCellVal() << " | " << board[0][1].getCellVal() << " | " << board[0][2].getCellVal() << endl;
	cout << "    ---+---+---" << endl;
	cout << "2    " << board[1][0].getCellVal() << " | " << board[1][1].getCellVal() << " | " << board[1][2].getCellVal() << endl;
	cout << "    ---+---+---" << endl;
	cout << "3    " << board[2][0].getCellVal() << " | " << board[2][1].getCellVal() << " | " << board[2][2].getCellVal() << endl << endl;
}
void Board::initBoard()
{
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			Cell cell(r, c);
			setCell(r, c, cell);
		}
	}
}

Cell Board::getCell() const
{
	return curCell;
}
Cell Board::getCell(int r, int c) const
{
	return board[r][c];
}
int Board::getRows() const
{
	return rows;
}
int Board::getCols() const
{
	return cols;
}

void Board::setCell(Cell c)
{
	curCell = c;
}
void Board::setCell(int r, int c, Cell cell)
{
	board[r][c] = cell;
}
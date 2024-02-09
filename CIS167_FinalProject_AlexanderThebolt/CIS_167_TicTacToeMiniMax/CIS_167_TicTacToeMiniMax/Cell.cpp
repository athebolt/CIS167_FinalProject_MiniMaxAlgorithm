#include "Cell.h"

Cell::Cell()
{

}
Cell::Cell(int r, int c)
{
	row = r;
	col = c;
	val = ' ';
}

int Cell::getRow() const
{
	return row;
}
int Cell::getCol() const
{
	return col;
}
char Cell::getCellVal() const
{
	return val;
}

void Cell::setRow(int r)
{
	row = r;
}
void Cell::setCol(int c)
{
	col = c;
}
void Cell::setCellVal(char v)
{
	val = v;
}

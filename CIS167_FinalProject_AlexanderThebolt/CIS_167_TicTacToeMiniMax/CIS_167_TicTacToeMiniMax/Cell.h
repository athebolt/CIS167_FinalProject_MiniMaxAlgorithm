#pragma once
class Cell
{
private:
	int row;
	int col;
	char val;
public:
	Cell();
	Cell(int, int);

	int getRow() const;
	int getCol() const;
	char getCellVal() const;

	void setRow(int);
	void setCol(int);
	void setCellVal(char);
};


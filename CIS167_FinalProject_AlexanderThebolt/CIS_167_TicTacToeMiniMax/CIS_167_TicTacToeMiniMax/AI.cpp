#include "AI.h"
#include "Cell.h"
#include "Board.h"
#include "iostream"

using namespace std;

AI::AI()
{

}

Cell AI::miniMaxStart(Board b)
{
	int bestScore = -999;
	int score;
	Cell bestMove;

	bestMove.setCellVal('O');

	//board copy
	Board copy;

	//copying each cell from the game board to the copy board
	for (int r = 0; r < b.getRows(); r++)
	{
		for (int c = 0; c < b.getCols(); c++)
		{
			copy.setCell(r, c, b.getCell(r, c));
		}
	}

	//cycles through each cell on the board
	for (int r = 0; r < b.getRows(); r++)
	{
		for (int c = 0; c < b.getCols(); c++)
		{
			//if the spot is open, run the algorithm
			if (b.getCell(r, c).getCellVal() == ' ')
			{
				//creates a cell
				Cell cell(r, c);

				//puts the cell on the board
				cell.setCellVal('O');

				copy.setCell(r, c, cell);

				//scores the move using the minimax algorithm
				score = miniMaxAlg(copy, 0, false);

				//cout << score << endl;

				//if the move is better than the current best possible move
				//then store that move
				if (score > bestScore)
				{
					bestScore = score;

					bestMove.setRow(r);
					bestMove.setCol(c);
				}

				//erases the cell from the board
				cell.setCellVal(' ');

				copy.setCell(r, c, cell);
			}
		}
	}
	
	//returns the best move as a cell to be placed on the board

	if (bestScore == 0)
	{
		cout << "AI's Prediction: We tie." << endl;
	}
	else
	{
		cout << "AI's Prediction: You lose." << endl;
	}

	return bestMove;
}

int AI::miniMaxAlg(Board copy, int dep, bool isMax)
{
	int bestScore;

	//ai win
	if (whoWon(copy) == 1)
	{
		return 1;
	}
	//player win
	else if (whoWon(copy) == -1)
	{
		return -1;
	}
	//tie
	else if (whoWon(copy) == 0)
	{
		return 0;
	}

	//cycles through each possible board state
	//if isMax, then it's the AI's turn
	//else, it's the player's turn
	if (isMax)
	{
		bestScore = -999;

		//cycle through each cell on the board
		for (int r = 0; r < copy.getRows(); r++)
		{
			for (int c = 0; c < copy.getCols(); c++)
			{
				//if a spot on the board is open
				if (copy.getCell(r, c).getCellVal() == ' ')
				{
					//creates a cell
					Cell cell(r, c);

					cell.setCellVal('O');

					//puts the cell on the board
					copy.setCell(r, c, cell);

					//scores the placement of the cell
					int score = miniMaxAlg(copy, dep + 1, false);

					//the cell position with the highest score is the best score
					//this is because we are maximizing for the ai turn
					if (score > bestScore)
						bestScore = score;

					//erases the cell from the board
					cell.setCellVal(' ');

					copy.setCell(r, c, cell);
				}
			}
		}

		//return best cell position
		return bestScore;
	}
	else
	{
		bestScore = 999;

		//cycles through each cell on the board
		for (int r = 0; r < copy.getRows(); r++)
		{
			for (int c = 0; c < copy.getCols(); c++)
			{
				//if the spot is open
				if (copy.getCell(r, c).getCellVal() == ' ')
				{
					//creates a cell
					Cell cell(r, c);

					cell.setCellVal('X');

					//places cell on the board
					copy.setCell(r, c, cell);

					//scores the placement of the cell on the board
					int score = miniMaxAlg(copy, dep + 1, true);

					//the lowest score is the best because we are minimizing for player turn
					if (score < bestScore)
						bestScore = score;

					//erases the cell from the board
					cell.setCellVal(' ');

					copy.setCell(r, c, cell);
				}
			}
		}

		//return the best score (lowest possible)
		return bestScore;
	}
}

//i have this minimized because it's a lot of code
//this is all the possible win scenarios
int AI::whoWon(Board b)
{
	int win = 0;

	//vert player win
	for (int c = 0; c < b.getCols(); c++)
	{
		win = 0;

		for (int r = 0; r < b.getRows(); r++)
		{
			if (b.getCell(r, c).getCellVal() == 'X')
			{
				win++;
			}
		}

		if (win == b.getRows())
		{
			//cout << "vert player win on col " << c << endl;
			return -1;
		}
	}

	//horiz player win
	for (int r = 0; r < b.getRows(); r++)
	{
		win = 0;

		for (int c = 0; c < b.getCols(); c++)
		{
			if (b.getCell(r, c).getCellVal() == 'X')
			{
				win++;
			}
		}

		if (win == b.getCols())
		{
			//cout << "horiz player win on row " << r << endl;
			return -1;
		}
	}

	//vert AI win
	for (int c = 0; c < b.getCols(); c++)
	{
		win = 0;

		for (int r = 0; r < b.getRows(); r++)
		{
			if (b.getCell(r, c).getCellVal() == 'O')
			{
				win++;
			}
		}

		if (win == b.getRows())
		{
			//cout << "vert AI win on col " << c << endl;
			return 1;
		}
	}

	//horiz AI win
	for (int r = 0; r < b.getRows(); r++)
	{
		win = 0;

		for (int c = 0; c < b.getCols(); c++)
		{
			if (b.getCell(r, c).getCellVal() == 'O')
			{
				win++;
			}
		}

		if (win == b.getCols())
		{
			//cout << "horiz AI win on row " << r << endl;
			return 1;
		}
	}

	//upper-left to lower-right diagonal player win
	win = 0;

	for (int c = 0; c < b.getCols(); c++)
	{
		if (b.getCell(c, c).getCellVal() == 'X')
		{
			win++;
		}
	}

	if (win == b.getCols())
	{
		//cout << "diag player win ul to lr " << endl;
		return -1;
	}

	//lower-left to upper-right diagonal player win
	win = 0;

	for (int c = 0; c < b.getCols(); c++)
	{
		if (b.getCell(c, b.getRows() - (c + 1)).getCellVal() == 'X')
		{
			win++;
		}
	}

	if (win == b.getCols())
	{
		//cout << "diag player win ll to ur " << endl;
		return -1;
	}

	//upper-left to lower-right diagonal AI win
	win = 0;

	for (int c = 0; c < b.getCols(); c++)
	{
		if (b.getCell(c, c).getCellVal() == 'O')
		{
			win++;
		}
	}

	if (win == b.getCols())
	{
		//cout << "diag AI win ul to lr " << endl;
		return 1;
	}

	//lower-left to upper-right diagonal AI win
	win = 0;

	for (int c = 0; c < b.getCols(); c++)
	{
		if (b.getCell(c, b.getRows() - (c + 1)).getCellVal() == 'O')
		{
			win++;
		}
	}

	if (win == b.getCols())
	{
		//cout << "diag AI win ll to ur " << endl;
		return 1;
	}

	//checks for a tie
	int openCells = 0;

	for (int c = 0; c < b.getCols(); c++)
	{
		for (int r = 0; r < b.getRows(); r++)
		{
			if (b.getCell(r, c).getCellVal() == ' ')
			{
				openCells++;
			}
		}
	}

	if (openCells == 0)
	{
		//cout << "tie" << endl;
		return 0;
	}
}
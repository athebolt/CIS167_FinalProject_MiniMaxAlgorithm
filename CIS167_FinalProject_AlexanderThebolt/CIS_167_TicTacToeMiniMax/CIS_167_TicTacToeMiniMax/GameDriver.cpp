#include "GameDriver.h"
#include "AI.h"
#include "iostream"

using namespace std;

void GameDriver::gameStart()
{
	Board board;
	char selection = 0;

	setBoard(board);

	system("cls");

	//creates and displays the board
	game.initBoard();
	game.dispBoard();

	//menu display
	while (selection != '1' && selection != '2')
	{
		cout << "Choose who goes first" << endl;
		cout << "=====================" << endl;
		cout << "1. You" << endl;
		cout << "2. AI" << endl;
		cout << "=====================" << endl << endl;
		cout << "Make your selection: ";
		cin >> selection;

		system("cls");

		game.dispBoard();
	}

	//if the user decided that the player goes first
	//then go to player turn. else, go to ai turn
	if (selection == '1')
	{
		playerTurn();
	}
	else
	{
		aiTurn();
	}
}

void GameDriver::playerTurn()
{
	//i have the user input as a char because it's easier for me to error check
	int row = 0;
	char rowInput = NULL;
	int col = 0;
	char colInput = NULL;

	do
	{
		//column input
		while (colInput < 'A' || colInput > 'C')
		{
			cout << "Choose a column (A, B or C): ";
			cin >> colInput;

			colInput = toupper(colInput);
		}

		//row input
		while (rowInput < '1' || rowInput > '3')
		{
			cout << "Choose a row (1, 2 or 3): ";
			cin >> rowInput;
		}

		//convert from char to int
		if (rowInput == '1')
		{
			row = 0;
		}
		else if (rowInput == '2')
		{
			row = 1;
		}
		else if (rowInput == '3')
		{
			row = 2;
		}

		//convert from char to int
		if (colInput == 'A')
		{
			col = 0;
		}
		else if (colInput == 'B')
		{
			col = 1;
		}
		else if (colInput == 'C')
		{
			col = 2;
		}

		//open space check
		if (game.getCell(row, col).getCellVal() != ' ')
		{
			cout << "ERROR: This spot is already taken! Try again." << endl;

			rowInput = NULL;
			colInput = NULL;
		}

		//until the space chosen is empty, continue this loop
	} while (game.getCell(row, col).getCellVal() != ' ');

	//create the cell to be put on the board
	Cell cell(row, col);

	cell.setCellVal('X');

	//places cell on the board
	game.setCell(row, col, cell);

	//clear screen and display board
	system("cls");
	game.dispBoard();

	//game over check, if not over, it is the ai's turn
	if (checkWin(game) == -1)
	{
		cout << "You win!" << endl;

		char rerun;

		cout << "Play again? (y/n): ";
		cin >> rerun;

		if (rerun == 'y')
		{
			gameStart();
		}
	}
	else if (checkWin(game) == 0)
	{
		cout << "It's a tie!" << endl;

		char rerun;

		cout << "Play again? (y/n): ";
		cin >> rerun;

		if (rerun == 'y')
		{
			gameStart();
		}
	}
	else
	{
		aiTurn();
	}
}

void GameDriver::aiTurn()
{
	AI ai;

	system("cls");

	//starts the algorithm and it returns the best move
	game.setCell(ai.miniMaxStart(game));

	//placing the best move on the board
	game.setCell(game.getCell().getRow(), game.getCell().getCol(), game.getCell());

	game.dispBoard();

	//game over check, if it is not game over then it is the player's turn
	if (checkWin(game) == 1)
	{
		cout << "You lose!" << endl;

		char rerun;

		cout << "Play again? (y/n): ";
		cin >> rerun;

		if (rerun == 'y')
		{
			gameStart();
		}
	}
	else if (checkWin(game) == 0)
	{
		cout << "It's a tie!" << endl;

		char rerun;

		cout << "Play again? (y/n): ";
		cin >> rerun;

		if (rerun == 'y')
		{
			gameStart();
		}
	}
	else
	{
		playerTurn();
	}
}

//checks each possible win scenario (minimized because it's a lot of code)
int GameDriver::checkWin(Board b)
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
		return 0;
	}
}

void GameDriver::setBoard(Board b)
{
	game = b;
}
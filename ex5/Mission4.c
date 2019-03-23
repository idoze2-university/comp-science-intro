/******************************************
*Student name: Ido Zeira
*Student ID: 322607177
*Submit Info: Zeiraid
*Exercise name: ex5
******************************************/
#include "Mission4.h"
/************************************************************************
* function name: Mission4   											*
* The Input: None								 						*
* The output: None														*
* The Function operation: Runs Mission 4 of Ex5						 	*
*************************************************************************/
void Mission4()
{
	int n, m;
	long c;
	char board[MAX_SIZE][MAX_SIZE];

	printf("Please enter the number of rows (n):\n");
	scanf("%d", &n);
	if (n<MIN_SIZE || n>MAX_SIZE)
		return;
	printf("Please enter the number of columns (m):\n");
	scanf("%d", &m);
	if (m<MIN_SIZE || m>MAX_SIZE)
		return;
	printf("Please enter the number of iterations (c):\n");
	scanf("%ld", &c);
	if (c<MIN_ITERATIONS || c>MAX_ITERATIONS)
		return;
	printf("Please enter the board:\n");
	loadBoard(board, n, m);		// Reading the Board
	RunGame(n, m, c, board);
}
/************************************************************************
* function name: RunGame	   											*
* The Input: int n- Number Of board Rows,int m- Number of board columns *
*				long c- Number of iterations to run the game through,   *
*				char board[][]- The board on which the game runs		*
* The output: None														*
* The Function operation: Runs c iterations of 'game of life' on board  *
*						And prints the result board						*
*************************************************************************/
void RunGame(int n, int m, long c, char board[][MAX_SIZE])
{
	int iteration;
	for (iteration = 0; iteration < c; iteration++)
	{
		//If the board hasn't changed, don't bother keeping the algorighm running.
		if (!getNextGen(n, m, board))
		{
			break;
		}
	}
	printf("The board after %d iterations is:\n", iteration);
	printBoard(n, m, board);
}
/************************************************************************
* function name: loadBoard												*
* The Input: char mat[][]-the matrix to be loaded, rows and cols count	*
*							of the matrix.								*
* The output: None														*
* The Function operation: Reads user input and inserts it to mat.		*
*************************************************************************/
void loadBoard(char mat[][MAX_SIZE], int rows, int cols)
{
	int row;
	for (row = 0; row < rows; row++)
	{
		char input[MAX_SIZE];
		scanf("%s", input);
		int col;
		for (col = 0; col <= cols; col++)
		{
			mat[row][col] = input[col];
		}
	}
}
/************************************************************************
* function name: getNextGen												*
* The Input: int rows- The number of board's rows, int cols- The number *
*						of board's columns, char board[][]- The board.  *
* The output: int- indicates wether or not the board changed.			*
* The Function operation: Applies the game of life algorithm and stores *
*						The resulted board in board.					*
*************************************************************************/
int getNextGen(int rows, int cols, char board[][MAX_SIZE])
{
	char nextGen[MAX_SIZE][MAX_SIZE];
	int row;
	for (row = 0; row < rows; row++)
	{
		int col;
		for (col = 0; col < cols; col++)
		{
			//Calculate the state of current cell in the next generation.
			int living = countLivingNeighbours(rows, cols, row, col, board);
			if (living == 3 || (living == 2 && isAlive(rows, cols, row, col, board)))
			{
				nextGen[row][col] = ALIVE_CHAR;
			}
			else
				nextGen[row][col] = DEAD_CHAR;
		}
		nextGen[row][col] = '\0';
	}

	//inidicates if board was changed
	int boardChanged = 0;
	for (row = 0; row < rows; row++)
	{
		int col;
		for (col = 0; col <= cols; col++)
		{
			//if Noticed a differance between board and nextGen, Save so to boardChanged and update board.
			if (board[row][col] != nextGen[row][col])
			{
				boardChanged = 1;
				(board)[row][col] = nextGen[row][col];
			}
		}
	}
	return boardChanged;
}
/************************************************************************
* function name: countLivingNeighbours									*
* The Input: int rows- The number of board's rows, int cols- The number *
*						of board's columns, char board[][]- The board.  *
*						(row,col) is the point to be tested.			*
* The output: None														*
* The Function operation: counts the amount of living neighbours around	*
*							(row,col) and returns it.					*
*************************************************************************/
int countLivingNeighbours(int rows, int cols, int row, int col, char board[][MAX_SIZE])
{
	int livingNeighbours = 0;
	int r;
	for (r = row - 1; r < row + 2; r++)
	{
		int c;
		for (c = col - 1; c < col + 2; c++)
		{
			//Don't count yourself as a neighbour
			if (r != row || c != col)
				//Count neighbours
				livingNeighbours += isAlive(rows, cols, r, c, board);
		}
	}
	return livingNeighbours;
}
/************************************************************************
* function name: isAlive	   											*
* The Input: board[rows][cols]- the board to test on, (row,col) is the	*
*								point which should be tested.			*
* The output: int - 1: Alive, 0: Dead									*
* The Function operation:	returns the state of cell in (row,col).		*
*************************************************************************/
int isAlive(int rows, int cols, int row, int col, char board[][MAX_SIZE])
{
	int fixed_row = row;
	int fixed_col = col;
	if (row > rows - 1)
		//Wrap the matrix borders.
		fixed_row = 0;
	else if (row < 0)
		//Wrap the matrix borders.
		fixed_row = rows - 1;
	if (col > cols - 1)
		//Wrap the matrix borders.
		fixed_col = 0;
	else if (col < 0)
		//Wrap the matrix borders.
		fixed_col = cols - 1;
	return board[fixed_row][fixed_col] == ALIVE_CHAR;
}
/************************************************************************
* function name: printBoard   											*
* The Input: board[rows][cols] to print.								*
* The output: None														*
* The Function operation: prints a visual representation of board.		*
*************************************************************************/
void printBoard(int rows, int cols, const char board[][MAX_SIZE])
{
	int row;
	for (row = 0; row < rows; row++)
	{
		printf("%s\n", board[row]);
	}
}
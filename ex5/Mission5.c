/******************************************
*Student name: Ido Zeira
*Student ID: 322607177
*Submit Info: Zeiraid
*Exercise name: ex5
******************************************/

#include "Mission5.h"

/************************************************************************
* function name: Mission5   											*
* The Input: None								 						*
* The output: None														*
* The Function operation: Runs Mission 5 of Ex5						 	*
*************************************************************************/
void Mission5()
{
	int n;
	char board[MAX_SIZE][MAX_SIZE];

	int startX, startY, goalX, goalY, result;

	printf("Please enter the number of rows and columns (n):\n");
	scanf("%d", &n);
	if (n < MIN_SIZE || n > MAX_SIZE)
		return;
	printf("Please enter the X of the starting position:\n");
	scanf("%d", &startX);
	if (startX < 0 || startX > n)
		return;
	printf("Please enter the Y of the starting position:\n");
	scanf("%d", &startY);
	if (startY < 0 || startY > n)
		return;
	printf("Please enter the X of the goal position:\n");
	scanf("%d", &goalX);
	if (goalX < 0 || goalX > n)
		return;
	printf("Please enter the Y of the goal position:\n");
	scanf("%d", &goalY);
	if (goalY < 0 || goalY> n)
		return;
	printf("Please enter the grid:\n");
	loadCastleBoard(board, n, n);		// Reading the Board

	result = getMinLength(board, startX, startY, goalX, goalY, n);	// Getting the Minimum Value
	if (result != -1)
	{
		printf("The minimum number of steps is %d\n", result);
	}
	else
	{
		printf("No path was found from (%d,%d) to (%d,%d)\n", startX, startY, goalX, goalY);
	}
}

/************************************************************************
* function name: getMinLength											*
* The Input: mat[n][n]- board to run the algorithm on. (c,r)- starting	*
*						Point, (goalR,goalC)- Endpoint.					*
* The output: The minimum amount of steps required to get from (c,r) to	*
*				(goalC,goalR). -1: impossile to reach.					*
* The Function operation: Recursively counts the minimum amoun of steps	*
*				required to get frop (c,r) to (goalC, goalR).			*
*************************************************************************/
int getMinLength(char mat[][MAX_SIZE], int r, int c, int goalR, int goalC, int n)
{
	if (r < 0 || r >= n || c < 0 || c >= n || mat[r][c] == CHAR_WALL)
		return -1;
	if (r == goalR && c == goalC)
		return 0;
	//Mark current point BLOCKED to prevent loops.
	char temp = mat[r][c];
	mat[r][c] = CHAR_WALL;
	//initialize values
	int up = -1, right = -1, down = -1, left = -1;
	//Recursively count the minimum amount of steps required from the ajacent points in each direction.
	up = getMinLength(mat, r - 1, c, goalR, goalC, n);
	right = getMinLength(mat, r, c + 1, goalR, goalC, n);
	down = getMinLength(mat, r + 1, c, goalR, goalC, n);
	left = getMinLength(mat, r, c - 1, goalR, goalC, n);
	//Unset the mark to keep the integrity of the board.
	mat[r][c] = temp;
	//In case fully blocked: mark impossible to solve.
	if (up == -1 && down == -1 && right == -1 && left == -1)
		return -1;
	//Recursively count each step.
	return min(min(up, down), min(right, left)) + 1;
}

/************************************************************************
* function name: loadBoard												*
* The Input: char mat[][]-the matrix to be loaded, rows and cols count	*
*							of the matrix.								*
* The output: None														*
* The Function operation: Reads user input and inserts it to mat.		*
*************************************************************************/
void loadCastleBoard(char mat[][MAX_SIZE], int rows, int cols)
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
* function name: min													*
* The Input: a,b - two integers to compare.								*
* The output: the smallest non -1 of {a,b}.								*
* The Function operation: Figures out which one of {a,b} is smallest	*
*							And returns it.								*
*************************************************************************/
int min(int a, int b)
{
	if (a == -1)
		return b;
	if (b == -1 || a <= b)
		return a;
	return b;
}
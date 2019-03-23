/*************************
Student name: Ido Zeira
Student ID: 322607177
Exercise name: Exercise 2
*************************/
//Definitions: Entire Program
#define MIN_OPTION 1
#define MAX_OPTION 4
//Definitions: ex1
#define MIN_N 1
#define MAX_N 1000
#define MIN_A 1
#define MAX_A 1000000000
#define MIN_B 1
#define MAX_B 1000000000
//Definitions: ex2
#define MIN_N 0
#define MAX_N 101
//Definitions: ex3
#define MIN_X 1
#define MAX_X 100
//Definitions: ex4
#define MIN_TURNS 1
#define MAX_TURNS 30
#define WIN ">"
#define LOSS "<"
#define TIE "="
#define ROCK "Rock"
#define PAPER "Paper"
#define SCISSORS "Scissors"
#define LIZARD "Lizard"
#define SPOCK "Spock"
enum Shape { Rock = 0, Paper, Scissors, Lizard, Spock };
enum Result { Win = 0, Loss, Tie };
//Inclusions: Entire Program
#include <stdio.h>
//Function Definitions: Entire Program
int power(int num, int power);

//Function Definitions: ex1 functions
int contains(int a, int b);
int countDigits(int n);

//Function Definitions: ex2 functions
int printSteps(int N);
int printStepCount(int N, int step);
int stepCount(int N, int step);
int divide(int N);
int divideHelp(int N, int div);

//Function Definitions: ex3 functions
void printXOR(unsigned long num);
int printXORHelper(unsigned long num, unsigned long curr);

//Function Definitions: ex4 functions
void printResult(enum Result res);
void printShape(enum Shape shape);
enum Shape nextBobShape(enum Result lastGameResult, enum Shape lastBobShape);
enum Shape getAbsoluteStronger(enum Shape shape);
enum Shape nextAliceShape(enum Result lastGameResult, enum Shape lastAliceShape, enum Shape lastBobShape);
int isWinning(enum Shape shapeA, enum Shape shapeB);
enum Result evaluate(enum Shape shapeA, enum Shape shapeB);

/************************************************************************
* function name: main.
*
* The Input: none (void).
*
* The output: Integer.
*
* The Function operation: Allows the user to browse between 4 exercises given on Ex4.
*
*************************************************************************/
int main(void)
{
	int option = 1;
	char dummy;
	while ((option >= MIN_OPTION) && (option <= MAX_OPTION))
	{
		printf("Please enter the mission number:\n");
		scanf("%d%c", &option, &dummy);
		switch (option)
		{
		case 1:
		{
			int numOfPairs, matchingPairs = 0;
			printf("Please enter the number of pairs:\n");
			scanf("%d", &numOfPairs);
			int i;
			for (i = 0; i < numOfPairs; i++)
			{
				int a, b;
				printf("Please enter the larger number of pair %d (a):\n", i + 1);
				scanf("%d", &a);
				printf("Please enter the smaller number of pair %d (b):\n", i + 1);
				scanf("%d", &b);
				if (contains(a, b))
					matchingPairs++;
			}
			printf("The number of pairs satisfying the condition is: %d\n", matchingPairs);
		}
		break;
		case 2:
		{
			int N;
			printf("Please enter the number:\n");
			scanf("%d", &N);
			printSteps(N);
		}
		break;
		case 3:
		{
			unsigned long x;
			printf("Please enter the number:\n");
			scanf("%lu", &x);
			printXOR(x);
		}
		break;
		case 4:
		{
			enum Shape alicesShape, bobsShape;
			int rounds, aliceWins = 0, bobWins = 0, ties = 0;
			printf("Please enter the shape Alice chose:\n");
			scanf("%d", &alicesShape);
			printf("Please enter the shape Bob chose:\n");
			scanf("%d", &bobsShape);
			printf("Please enter the number of rounds:\n");
			scanf("%d", &rounds);
			int i;
			for (i = 0; i < rounds; i++)
			{
				enum Result res = evaluate(alicesShape, bobsShape);
				switch (res)
				{
				case Win:
					aliceWins++;
					break;
				case Loss:
					bobWins++;
					break;
				case Tie:
					ties++;
					break;
				default:
					break;
				}
				printShape(alicesShape);
				printf(" ");
				printResult(res);
				printf(" ");
				printShape(bobsShape);
				printf("\n");
				alicesShape = nextAliceShape(res, alicesShape, bobsShape);
				bobsShape = nextBobShape(res, bobsShape);
			}
			if (aliceWins > bobWins)
				printf("Alice wins, by winning %d game(s) and tying %d game(s)\n", aliceWins, ties);
			else if (aliceWins < bobWins)
				printf("Bob wins, by winning %d game(s) and tying %d game(s)\n", bobWins, ties);
			else
				printf("Alice and Bob tie, each winning %d game(s) and tying %d game(s)\n", aliceWins, ties);
		}
		break;
		default:
			break;
		}
	}
	return 0;
}
/************************************************************************
* function name: power.
*
* The Input: int num,int pow.
*
* The output: Integer.
*
* The Function operation: Returns the pow-th power of num (num ^ pow).
*
*************************************************************************/
int power(int num, int power)
{
	if (power == 0)
		return 1;
	int result = 1;
	int i;
	for (i = 0; i < power; i++)
	{
		result *= num;
	}
	return result;
}
//ex1
/************************************************************************
* function name: contains.
*
* The Input: int a, int b.
*
* The output: Integer.
*
* The Function operation: recursively returns wether or not b is a contained in a
* (like substring). (1- true, 0- false).
*
*************************************************************************/
int contains(int a, int b)
{
	if ((a < b) || (a == 0))
		return 0;
	int countDigitsB = countDigits(b);
	if (a%power(10, countDigitsB) == b)
		return 1;
	return contains(a / 10, b);
}

/************************************************************************
* function name: countDigits.
*
* The Input: int n.
*
* The output: Integer.
*
* The Function operation: recursively counts the amount of digits n has.
*
*************************************************************************/
int countDigits(int n)
{
	if (n == 0)
		return 0;
	else
		return countDigits(n / 10) + 1;
}
//ex2
/************************************************************************
* function name: printSteps.
*
* The Input: int N.
*
* The output: Integer.
*
* The Function operation: prints the shortest path of N to Zero and 
* returns it's iteration count.
*
*************************************************************************/
int printSteps(int N)
{
	printf("The sequence of numbers produced by the actions is:\n");
	int minSteps = printStepCount(N, 0);
	printf("The minimum number of moves is %d\n", minSteps);
}

/************************************************************************
* function name: printStepCount.
*
* The Input: int N, int step.
*
* The output: Integer.
*
* The Function operation: recursively prints each iteration from N to 0
* and returns the amount of iterations (step).
*
*************************************************************************/
int printStepCount(int N, int step)
{
	if (N == 0)
		return step;
	int div = divide(N);
	if (div == N)
	{
		printf("%d\n", N - 1);
		return printStepCount(N - 1, step + 1);
	}
	//find the shortest path, recursively
	if (stepCount(N - 1, 0) >= stepCount(div, 0))
	{
		printf("%d\n", div);
		return printStepCount(div, step + 1);
	}
	printf("%d\n", N - 1);
	return printStepCount(N - 1, step + 1);
}

/************************************************************************
* function name: StepCount.
*
* The Input: int N, int step.
*
* The output: Integer.
*
* The Function operation: recursively finds the shortest path for each iteration from N to 0
* and returns the amount of iterations (step).
*
*************************************************************************/
int stepCount(int N, int step)
{
	if (N == 0)
		return step;
	int div = divide(N);
	if (div == N)
		return stepCount(N - 1, step + 1);
	//find the shortest path, recursively
	if (stepCount(N - 1, 0) >= stepCount(div, 0))
		return stepCount(div, step + 1);
	return stepCount(N - 1, step + 1);
}
/************************************************************************
* function name: divide.
*
* The Input: int n.
*
* The output: Integer.
*
* The Function operation: finds the number which is the none-one largest divisor 
* of n, and returns it.
*
*************************************************************************/
int divide(int N)
{
	return divideHelp(N, 2);
}
/************************************************************************
* function name: divideHelp.
*
* The Input: int n, int div.
*
* The output: Integer.
*
* The Function operation: recursively finds the number which is the none-one smallest divisor
* of n (div), and returns N/div (to get the biggest divisor).
*
*************************************************************************/
int divideHelp(int N, int div)
{
	//the number is a prime number
	if ((N == div)||(N<=3))
		return N;
	if (N%div == 0)
	{
		return N / div;
	}
	return divideHelp(N, div + 1);
}
//ex3
/************************************************************************
* function name: printXOR.
*
* The Input: unsigned long num.
*
* The output: none (void).
*
* The Function operation: prints all numbers that satisfy ex3 conditions and their count.
*
*************************************************************************/
void printXOR(unsigned long num)
{
	printf("The numbers are:\n");
	int count = printXORHelper(num, 1);
	printf("A total of %d numbers\n", count);
}

/************************************************************************
* function name: printXORHelper.
*
* The Input: unsigned long num, unsigned long curr.
*
* The output: Integer.
*
* The Function operation: counts all numbers that satisfy ex3 conditions and returns their count.
*
*************************************************************************/
int printXORHelper(unsigned long num, unsigned long curr)
{
	//curr = current number
	if (num == curr)
		return 0;
	if ((curr ^ num) > num)
	{
		printf("%lu\n", curr);
		return printXORHelper(num, curr + 1) + 1;
	}
	return printXORHelper(num, curr + 1);
}
//ex4
/************************************************************************
* function name: printResult.
*
* The Input: (enum Result) res.
*
* The output: none (void).
*
* The Function operation: prints a literal representation of res.
*
*************************************************************************/
void printResult(enum Result res)
{
	switch (res)
	{
	case Win:
		printf(WIN);
		break;
	case Loss:
		printf(LOSS);
		break;
	case Tie:
		printf(TIE);
		break;
	default:
		break;
	}
}
/************************************************************************
* function name: printShape.
*
* The Input: (enum Shape) shape.
*
* The output: none (void).
*
* The Function operation: prints a literal representation of shape.
*
*************************************************************************/
void printShape(enum Shape shape)
{
	switch (shape)
	{
	case Rock:
		printf(ROCK);
		break;
	case Paper:
		printf(PAPER);
		break;
	case Scissors:
		printf(SCISSORS);
		break;
	case Lizard:
		printf(LIZARD);
		break;
	case Spock:
		printf(SPOCK);
		break;
	default:
		break;
	}
}
/************************************************************************
* function name: nextAliceShape.
*
* The Input: (enum Result) lastGameResult, (enum Shape) lastAliceShape, 
* (enum Shape) lastBobShape.
*
* The output: enum Shape.
*
* The Function operation: Returns the next shape Alice should play according to her strategy.
*
*************************************************************************/
enum Shape nextAliceShape(enum Result lastGameResult, enum Shape lastAliceShape, enum Shape lastBobShape)
{
	switch (lastGameResult)
	{
	case Win:
		return lastAliceShape;
		break;
	case Loss:
		return getAbsoluteStronger(lastBobShape);
		break;
	case Tie:
		return getAbsoluteStronger(lastAliceShape);
		break;
	default:
		break;
	}
}
/************************************************************************
* function name: nextBobShape.
*
* The Input: (enum Result) lastGameResult, (enum Shape) lastBobShape,
*
* The output: enum Shape.
*
* The Function operation: Returns the next shape Bob should play according to his strategy.
*
*************************************************************************/
enum Shape nextBobShape(enum Result lastGameResult, enum Shape lastBobShape)
{
	if (lastBobShape != Spock)
		return Spock;
	switch (lastGameResult)
	{
		//Bob won.
	case Loss:
		return Rock;
		break;
		//Bob lost.
	case Win:
		return Paper;
		break;
	case Tie:
		return Lizard;
		break;
	default:
		break;
	}
}
/************************************************************************
* function name: getAbsoluteStronger.
*
* The Input: (enum Shape) shape,
*
* The output: enum Shape.
*
* The Function operation: Returns a shape of the two shapes which are stronger than the 
* given shape, which is the strongest of the two (wins the other shape too).
*
*************************************************************************/
enum Shape getAbsoluteStronger(enum Shape shape)
{
	int i = 0;
	//get the first winning shape
	while (!isWinning(i, shape))
	{
		i++;
	}
	enum Shape shapeA = i++;
	//get the second winning shape
	while (!isWinning(i, shape))
	{
		i++;
	}
	enum Shape shapeB = i;
	//choose the strongest shape between shapeA and shapeB
	if (isWinning(shapeA, shapeB))
		return shapeA;
	return shapeB;
}

/************************************************************************
* function name: isWinning.
*
* The Input: (enum Shape) shapeA, (enum Shape) shapeB
*
* The output: int.
*
* The Function operation: Returns wether or not shapeA wins shapeB. (1 - true, 0 - false).
*
*************************************************************************/
int isWinning(enum Shape shapeA, enum Shape shapeB)
{
	return evaluate(shapeA, shapeB) == Win;
}
/************************************************************************
* function name: evaluate.
*
* The Input: (enum Shape) shapeA, (enum Shape) shapeB
*
* The output: int.
*
* The Function operation: Returns a Result which represents the state between shapeA and shapeB.
* (Win - shapeA wins shapeB, Loss - shapeB wins shapeA, tie - shapeA ties shapeB).
*
*************************************************************************/
enum Result evaluate(enum Shape shapeA, enum Shape shapeB)
{
	if (shapeA == shapeB)
		return Tie;
	switch (shapeA)
	{
	case Rock:
		if ((shapeB == Paper) || (shapeB == Spock))
			return Loss;
		return Win;
		break;
	case Paper:
		if ((shapeB == Lizard) || (shapeB == Scissors))
			return Loss;
		return Win;
		break;
	case Scissors:
		if ((shapeB == Rock) || (shapeB == Spock))
			return Loss;
		return Win;
		break;
	case Lizard:
		if ((shapeB == Scissors) || (shapeB == Rock))
			return Loss;
		return Win;
		break;
	case Spock:
		if ((shapeB == Lizard) || (shapeB == Paper))
			return Loss;
		return Win;
		break;
	default:
		break;
	}
}

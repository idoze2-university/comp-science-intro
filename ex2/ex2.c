/*************************
Student name: Ido Zeira
Student ID: 322607177
Exercise name: Exercise 2
*************************/
#define _CRT_SECURE_NO_WARNINGS
#define HOT "This year the weather was hot\n"
#define NORMAL "This year the weather was normal\n"
#define COLD "This year the weather was cold\n"
#include <stdio.h>
enum weather { hot, normal, cold };


/************************************************************************
* function name: main.
*
* The Input: none (void).
*
* The output: Integer.
*
* The Function operation: Allows the user to browse between 3 exercises given on Ex2.
*
*************************************************************************/
int main(void)
{
	int option;
	char dummy;
	printf("Please choose an option:\n");
	scanf("%d%c", &option, &dummy);
	switch (option)
	{
	case 1:
#pragma region Task 1
	{
		char char1, char2, char3, char4;
		//initialize flags, indicating wether or not any bracket pair follows the rules.
		int flagRound = 0, flagSquare = 0;
		printf("Please enter four chars:\n");
		scanf("%c %c %c %c", &char1, &char2, &char3, &char4);
		switch (char1)
		{
		case '[':
			//This is expected to be balanced by flagSquare--, indicating brackets were closed.
			flagSquare++;
			break;
		case '(':
			//This is expected to be balanced by flagRound-, indicating brackets were closed.
			flagRound++;
			break;
		case ')':
		case ']':
			printf("Bad structure\n");
			return 0;
			break;
		case 'a':
			break;
		default:
			//any other character input is invalid
			printf("Invalid input\n");
			return 0;
			break;
		}
		switch (char2)
		{
		case '(':
			//This is expected to be balanced by flagRound-, indicating brackets were closed.
			//Checks for invalidity by watching for double Round-Bracket openings.
			if (flagRound++)
			{
				printf("Bad structure\n");
				return 0;
			}
			if (flagSquare)
				//Second condition for Square brackets, is wether or not it contains a valid Round-brackets pair.
				//This should also be balanced by flagSquare--.
				flagSquare++;
			break;
		case ')':
			//If there is no Round-brackets to be balanced, Throw Structure Invalidity.
			if (!(flagRound--))
			{
				printf("Bad structure\n");
				return 0;
			}
			break;
		case ']':
		case '[':
			printf("Bad structure\n");
			return 0;
			break;
		case 'a':
			break;
		default:
			printf("Invalid input\n");
			return 0;
			break;
		}
		switch (char3)
		{
		case '[':
			//Square Brackets, If they appear, Should only appear On num1(opening) and num4(closing).
			if (flagSquare++)
			{
				printf("Bad structure\n");
				return 0;
			}
			break;
		case '(':
			//Checks for invalidity by watching for double Round-Bracket openings.
			if (flagRound++)
			{
				printf("Bad structure\n");
				return 0;
			}
			break;
		case ')':
			if (!(flagRound--))
			{
				printf("Bad structure\n");
				return 0;
			}
			break;
		case ']':
			if (!(flagSquare--))
			{
				printf("Bad structure\n");
				return 0;
			}
			break;
		case 'a':
			break;
		default:
			printf("Invalid input\n");
			return 0;
			break;
		}
		switch (char4)
		{
		case '[':
		case '(':
			printf("Bad structure\n");
			return 0;
			break;
		case ')':
			flagRound--;
			break;
		case ']':
			flagSquare -= 2;
			break;
		case 'a':
			break;
		default:
			printf("Invalid input\n");
			return 0;
			break;
		}
		if (!(flagRound) && !(flagSquare))
		{
			//Check Bracket Flags for compliance with the rules.
			printf("Ok\n");
		}
		else
			printf("Bad structure\n");
		return 0;
	}
#pragma endregion  
	break;
	case 2:
#pragma region Task 2
	{
		int num1, num2;
		char operation;
		double result = 0.0,dummy;
		printf("Please enter first number: \n");
		scanf("%d", &num1);
		printf("Please enter second number: \n");
		scanf("%d", &num2);
		printf("Please enter operator: \n");
		scanf("%c %c",&dummy, &operation);
		//Determine Operation and calculate result
		switch (operation)
		{
		case '+':
			result = (1.0)*(num1 + num2);
			break;
		case '-':
			result = (1.0)*(num1 - num2);
			break;
		case '*':
			result = (1.0)*(num1 * num2);
			break;
		case '/':
			//Avoid division by 0.
			if (num2)
				result = ((1.0*num1) / (1.0*num2));
			else
			{
				printf("Invalid input\n");
				return 0;
			}
			break;
		case '%':
			//Avoid calculation of a 0 - Modulus.
			if (num2)
				result = 1.0*(num1 % num2);
			else
			{
				printf("Invalid input\n");
				return 0;
			}
			break;
		default:
			printf("Invalid input\n");
			return 0;
			break;
		}
		//print the result
		printf("The result is: %7.2f\n", result);
		return 0;
	}
#pragma endregion
	break;
	case 3:
#pragma region Task 3
	{
		int num1, num2, num3, num4;
		printf("Please enter the average temperature per season:\n");
		scanf("%d %d %d %d", &num1, &num2, &num3, &num4);
		//Make sure temperature is reasonable.
		if (num1 < 9 || num1>37 || num2 < 9 || num2>37 || num3 < 9 || num3>37 || num4 < 9 || num4>37)
		{
			printf("Invalid input\n");
			return 0;
		}
		//Calculate average temperature towards the year.
		double average = ((num1 + num2 + num3 + num4) / 4.0);
		enum weather currentWeather;
		//Determine which type of weather was this year.
		if (average > 30.0)
			currentWeather = hot;
		else if (average > 20.0)
			currentWeather = normal;
		else
			currentWeather = cold;
		switch (currentWeather)
		{
		case hot:
			printf(HOT);
			break;
		case normal:
			printf(NORMAL);
			break;
		case cold:
			printf(COLD);
			break;
		default:
			break;
		}
		printf("Estimated average: %.2f\n", average);
		return 0;
	}
#pragma endregion
	break;
	default:
		break;
	}
	return 0;
}


/*************************
Student name: Ido Zeira
Student ID: 322607177
Exercise name: Exercise 2
*************************/
//Entire program
#define _CRT_SECURE_NO_WARNINGS
#define MAX_OPTION 4
#define MIN_OPTION 1
//Exercise 1
#define MAX_BASE 10
#define MIN_BASE 2
//Exercise 2
#define MAX_TIME 10000000
#define MIN_TIME 1
//Exercise 3
#define MAX_RANGE 10000
#define MIN_RANGE 0
#include <stdio.h>

/************************************************************************
* function name: main.
*
* The Input: none (void).
*
* The output: Integer.
*
* The Function operation: Allows the user to browse between 4 exercises given on Ex3.
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
			int b, num1, num2;
			printf("Please enter the base of the problem:\n");
			scanf("%d", &b);
			if (MIN_BASE <= b && b <= MAX_BASE)
			{
				printf("Please enter the first number in base %d:\n", b);
				scanf("%d", &num1);
				printf("Please enter the second number in base %d:\n", b);
				scanf("%d", &num2);
			}
			else
			{
				printf("ERROR - The base %d is not between 2 and 10\n", b);
				break;
			}
			//decimal result
			int dec_result = 0;
			int c_num1 = num1, c_num2 = num2;
			//Convert numbers and add them to result, divide num1, num2 by 10 each loop to get the next digit.
			int i;
			for (i = 0; (c_num1 > 0) || (c_num2 > 0); i++, c_num1 /= 10, c_num2 /= 10)
			{
				//Get the digit in position i from both numbers
				int digit1 = c_num1 % 10, digit2 = c_num2 % 10;
				//Preform conversion to decimal on both digits (digit = digit * b ^ i) 
				int j;
				for (j = 0; j < i; j++)
				{
					digit1 *= b;
					digit2 *= b;
				}
				//Add Converted digits to result.
				dec_result += digit1 + digit2;
			}
			//Converted result
			int con_result = 0;
			int k;
			//We'll convert the digit in position k to base b and add it to con_result.
			for (k = 0; dec_result > 0; k++, dec_result /= b)
			{
				int digit = dec_result % b;
				int j;
				for (j = 0; j < k; j++)
				{
					digit *= 10;
				}
				con_result += digit;
			}
			printf("The result of %d + %d in base %d is %d\n", num1, num2, b, con_result);
		}
		break;
		case 2:
		{
			int t;
			printf("Please enter the time:\n");
			scanf("%d", &t);
			if (t >= MIN_TIME && t <= MAX_TIME)
			{
				int value = 3, current_time = 1, counter = 3;
				//count time value until current_time = t;
				while (current_time < t)
				{
					//when value on current time gets to 1, Initiate a new rotation
					if (value == 1)
					{
						counter *= 2;
						value = counter;
					}
					else
					{
						value--;
					}
					//Progress the time
					current_time++;
				}
				printf("The time in the timer after %d seconds is %d \n", t, value);
			}
			else
			{
				printf("ERROR - The time %d is invalid\n", t);
				break;
			}
		}
		break;
		case 3:
		{
			int p, q;
			printf("Please enter the lower limit of the range (p):\n");
			scanf("%d", &p);
			printf("Please enter the upper limit of the range (q):\n");
			scanf("%d", &q);
			if (p > MIN_RANGE &&p < q && q <= MAX_RANGE)
			{
				int found_number = 0;
				int num;
				for (num = p; num < q; num++)
				{
					int d;
					int exponent = 10;
					//calculate d - num of digits
					for (d = 1; (num / exponent) > 0; d++)
					{
						exponent *= 10;
					}
					//now: exponent = 10^d
					int l = (num*num) / exponent, r = (num*num) % exponent;
					if (l + r == num)
					{
						if (!found_number)
						{
							found_number = 1;
							printf("The numbers between %d and %d are:\n", p, q);
						}
						printf("%d\n", num);
					}
				}
				if (!found_number)
					printf("NO NUMBERS BETWEEN %d AND %d\n", p, q);
			}
			else
			{
				printf("ERROR - The range %d to %d isn't valid\n", p, q);
			}
		}
		break;
		case 4:
		{
			int num, richard = 1;
			printf("Please enter the initial value for the game:\n");
			scanf("%d", &num);
			printf("Louise: %d\n", num);
			while (num > 1)
			{
				int closest_power = 0x1;
				while (closest_power <= num>>1)
				{
					closest_power = closest_power << 1;
				}
				if (closest_power == num)
				{
					num = num >> 1;
				}
				else
				{
					num = num ^ closest_power;
				}
				if (richard)
				{
					printf("Richard: %d\n", num);
					richard = 0;
				}
				else
				{
					printf("Louise: %d\n", num);
					richard = 1;
				}
			}
			if (richard)
				printf("The winner is: Richard\n");
			else
				printf("The winner is: Louise\n");

		}
		break;
		default:
			break;
		}
	}
	return 0;
}
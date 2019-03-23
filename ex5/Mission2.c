/******************************************
*Student name: Ido Zeira
*Student ID: 322607177
*Submit Info: Zeiraid
*Exercise name: ex5
******************************************/

#include "Mission2.h"

/************************************************************************
 Fill comment
*************************************************************************/
int SweetCookies(int cookies[], int n, int K)
{
	int operation;
	for (operation = 0; !isSweetEnough(cookies, operation, n, K); operation++)
	{
		int i, leastSweet1, leastSweet2;
		for (i = operation; i < n; i++)
		{
			if (cookies[operation] >= cookies[i])
			{
				leastSweet1 = cookies[i];
				cookies[i] = cookies[operation];
				cookies[operation] = leastSweet1;
			}
		}
		//store the second least sweet cookie to leastSweet2.
		int j;
		for (j = operation + 1; j < n; j++)
		{
			if (cookies[operation + 1] >= cookies[j])
			{
				leastSweet2 = cookies[j];
				cookies[j] = cookies[operation + 1];
				cookies[operation + 1] = leastSweet2;
			}
		}
		//empty the current unempty index
		cookies[operation] = -1;
		//Calculate the sweetness and insert into the next unempty index.
		cookies[operation + 1] = leastSweet1 + 2 * leastSweet2;
	}
	return operation;
}

int isSweetEnough(int cookies[], int firstUnemptyIndex, int n, int K)
{
	if (firstUnemptyIndex == n - 1)
		if (cookies[firstUnemptyIndex] < K)
			return -1;
		else
			return 1;
	int i;
	for (i = firstUnemptyIndex; i < n; i++)
	{
		if (cookies[i] < K)
			return 0;
	}
	return 1;
}

/************************************************************************

*************************************************************************/
void Mission2()
{
	int n, sweet;
	int cookies[MAX_COOKIES];
	int i;
	int result;
	printf("Please enter the amount of cookies:\n");
	scanf("%d", &n);
	if (n< MIN_COOKIES || n>MAX_COOKIES)
		return;
	printf("Please enter the minimum required sweetness:\n");
	scanf("%d", &sweet);
	if (sweet < MIN_SWEETNESS || sweet > MAX_SWEETNESS)
		return;
	for (i = 0; i < n; i++)
	{
		printf("Please enter cookie number %d:\n", i + 1);
		scanf("%d", &cookies[i]);
		if (cookies[i]<MIN_COOKIES || cookies[i]>MAX_COOKIES)
			return;

	}
	result = SweetCookies(cookies, n, sweet);
	printf("The number of operations that are needed is %d\n", result);
}
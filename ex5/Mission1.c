/******************************************
*Student name: Ido Zeira
*Student ID: 322607177
*Submit Info: Zeiraid
*Exercise name: ex5
******************************************/

#include "Mission1.h"

/************************************************************************
* function name: Mission1	  											*
* The Input: None								 						*
* The output: None														*
* The Function operation: Runs Mission 1 of Ex5						 	*
*************************************************************************/
void Mission1()
{
	int n, i, count = 0;
	char source[MAX_LENGTH], target[MAX_LENGTH];

	printf("Please enter the amount of pairs:\n");
	// Input the n
	scanf("%d", &n);
	if (n<MIN_RANGE || n> MAX_RANGE)
		return;

	for (i = 0; i < n; i++)
	{
		printf("Please enter the first string of pair %d:\n", i + 1);
		scanf("%s", target);
		if (!isValidCharArray(target))
			return;
		printf("Please enter the second string pair %d:\n", i + 1);
		scanf("%s", source);
		if (!isValidCharArray(source))
			return;
		count += isSemiSimilar(target, source);
	}
	printf("The amount of Semi-Similar strings is %d\n", count);
}

/************************************************************************
* function name: isSemiSimilar 											*
* The Input: target - The target string containing a-z letters 			*
* 			 source - The source string containing a-z letters			*
* The output: The function returns 1 or 0
*
* The Function operation: The function checks if target is 				*
*						   semi-similar to source 						*
*************************************************************************/
int isSemiSimilar(char target[], char source[])
{
	int arr[26] = { 0 };
	int i, strLength = 0;
	for (i = 0; source[i] != '\0'; i++)
	{
		arr[(int)source[i] - (int)'a']++;
		strLength++;
	}
	for (i = 0; target[i] != '\0'; i++)
	{
		arr[(int)target[i] - (int)'a']--;
		strLength--;
	}
	//If target and source aren't of same length, return 0.
	if (strLength != 0)
		return 0;
	for (i = 0; i < 26; i++)
	{
		if (arr[i] != 0)
			return 0;
	}
	return 1;
}

/************************************************************************
* function name: isValidCharArray 										*
* The Input: arr - an array containing letters							*
* The output: The function returns 1 or 0								*
* The Function operation: The function checks if arr consists of		*
*						   letters ranging from 'a' to 'z' 				*
*************************************************************************/
int isValidCharArray(char arr[])
{
	int i;
	for (i = 0; arr[i] != '\0'; i++)
	{
		if (arr[i] < 'a' || arr[i] > 'z')
			return 0;
	}
	return 1;
}

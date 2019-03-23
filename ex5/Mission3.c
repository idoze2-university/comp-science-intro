/******************************************
*Student name: Ido Zeira
*Student ID: 322607177
*Submit Info: Zeiraid
*Exercise name: ex5
******************************************/

#include "Mission3.h"

/************************************************************************
* function name: CanAnagram 											*
* The Input: str - string containing a-z letters 						*
* The output: None														*
* The Function operation: The function prints if str can be changed to 	*
							be a polindrom								*
*************************************************************************/
void CanAnagram(char str[])
{
	int arr[26] = { 0 };
	int i;
	for (i = 0; str[i] != '\0'; i++)
	{
		arr[(int)str[i] - (int)'a']++;
	}
	char midChar;
	int foundMidChar = 0, annagramLCount = 0, annagramRCount = 0;
	char anagramL[MAX_LENGTH], anagramR[MAX_LENGTH];
	for (i = 0; i < 26; i++)
	{
		//Handle an odd amount of characters
		if (arr[i] % 2 != 0)
		{

			if (foundMidChar)
			{
				//in case a mid character was found again,
				//theres no possible palindrome.
				printf("The string %s does not have a palindrome\n", str);
				return;
			}
			else//should only happen once.
			{
				//Save the character which is found an odd amount of times,
				//remove it from the counting array.
				midChar = 'a' + i;
				arr[i]--;
				foundMidChar = 1;
			}
		}
		//Insert current char half of the times it showes into The Left Side.
		int k;
		for (k = 0; k < arr[i] / 2; k++)
		{
			anagramL[annagramLCount + k] = 'a' + i;
		}
		annagramLCount += arr[i] / 2;
	}

	//End The Left Side Of The Annagram.
	anagramL[annagramLCount] = '\0';
	for (i = 25; i >= 0; i--)
	{
		//Insert current char half of the times it showes into the Right Side.
		int k;
		for (k = 0; k < arr[i] / 2; k++)
		{
			anagramR[annagramRCount + k] = 'a' + i;
		}
		annagramRCount += arr[i] / 2;
	}

	//End The Right Side Of The Annagram.
	anagramR[annagramRCount] = '\0';
	//Print the Three components of the annagram: anagramL, midChar, anagramR.
	printf("The string %s has the palindrome %s", str, anagramL);
	if (foundMidChar)
		printf("%c", midChar);
	printf("%s\n", anagramR);
}

/************************************************************************
* function name: Mission3
* The Input: Nonde
* The output: None
* The Function operation: The function reads an str, and
						  prints if str can be changed to be a polindrome,
						  If so, also prints the Palindrome.
*************************************************************************/
void Mission3()
{
	char str[MAX_LENGTH];
	printf("Please enter the string:\n");
	scanf("%s", str);		// input the str
	if (!isValidCharArray(str))
		return;
	CanAnagram(str);
}
/******************************************
*Student name: Ido Zeira
*Student ID: 322607177
*Submit Info: Zeiraid
*Exercise name: ex5
******************************************/ 
#define MAX_COOKIES 1000
#define MIN_COOKIES 1
#define MAX_SWEETNESS 10000
#define MIN_SWEETNESS 0
#define MAX_COOKIE_NUMBER 100000
#define MIN_COOKIE_NUMBER 0
#include <stdio.h>

#ifndef _MISSION2_H_
#define _MISSION2_H_
void Mission2();
int SweetCookies(int cookies[], int n, int K);
int isSweetEnough(int coockies[], int firstUnemptyIndex, int n, int K);
#endif
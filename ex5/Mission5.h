/******************************************
*Student name: Ido Zeira
*Student ID: 322607177
*Submit Info: Zeiraid
*Exercise name: ex5
******************************************/ 
#define MAX_SIZE 25
#define MIN_SIZE 1
#define CHAR_WALL 'X'
#define CHAR_PATH '-'
#include <stdio.h>

#ifndef _MISSION5_H_
#define _MISSION5_H_
void Mission5();
void loadCastleBoard(char mat[][MAX_SIZE], int rows, int cols);
int getMinLength(char mat[][MAX_SIZE], int r, int c, int goalR, int goalC, int n);
int min(int a, int b);
#endif
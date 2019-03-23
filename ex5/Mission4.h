/******************************************
*Student name: Ido Zeira
*Student ID: 322607177
*Submit Info: Zeiraid
*Exercise name: ex5
******************************************/

#define MAX_SIZE 25
#define MIN_SIZE 3
#define MAX_ITERATIONS 100000
#define MIN_ITERATIONS 1
#define ALIVE_CHAR '*'
#define DEAD_CHAR '-'

#include <stdio.h>
#include <string.h>

#ifndef _MISSION4_H_
#define _MISSION4_H_
void Mission4();
void RunGame(int n, int m, long c, char board[][MAX_SIZE]);
void loadBoard(char mat[][MAX_SIZE], int rows, int cols);
int getNextGen(int rows, int cols, char board[][MAX_SIZE]);
int countLivingNeighbours(int rows, int cols, int row, int col, char board[][MAX_SIZE]);
int isAlive(int rows, int cols, int row, int col, char board[][MAX_SIZE]);
void printBoard(int rows, int cols, const char board[][MAX_SIZE]);
#endif
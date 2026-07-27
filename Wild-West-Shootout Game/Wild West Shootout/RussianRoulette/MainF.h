#define _CRT_SECURE_NO_WARNINGS
#define clrscr printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n")
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int update;
int num_live, items[2][3];     //   varible to check if game ended
int HasEnded;
int MainF_generate(int** arr);
void MainF_Tutorials();
void MainF_Credits();
void MainF_StartScreeen();

int drawGame();
void items_itemMain(int* chamber, int* ptr, int turn, int* health, int* IsCuffed, int* dmg);
void items_getlist(int player);
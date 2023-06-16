#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

#define NONE -1
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define PAUSE 112
#define ESC 27

#define MAP_X 3
#define MAP_Y 2
#define MAP_WIDTH 30
#define MAP_HEIGHT 20


int x[100], y[100]; //x,y ÁÂÇ¥°ªÀ» ÀúÀå ÃÑ 100°³ 
int star_x, star_y;
int length;
int score;
int best_score;
int dir;
int key;
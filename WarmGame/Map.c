#include "Map.h"
#include "GlobalSettings.h"






void gotoxy(int x, int y, char* s)
{ // 좌표값에 바로 문자열을 입력할 수 있도록 printf함수 삽입  
    COORD pos = { 2 * x,y }; //가로의 크기가 짧아서 x에 2배
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    printf("%s", s); //받은 문자열 출력
}








void DrawMap(void) //맵 테두리 생성
{ 
    int i;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    for (i = 0; i < MAP_WIDTH; i++) 
    {
        gotoxy(MAP_X + i, MAP_Y, "■");//맨 윗줄 생성
    }
    for (i = MAP_Y + 1; i < MAP_Y + MAP_HEIGHT - 1; i++) //i가 Y 맨 아랫줄 -1칸까지 반복 
    {
        gotoxy(MAP_X, i, "■");
        gotoxy(MAP_X + MAP_WIDTH - 1, i, "■");
    }
    for (i = 0; i < MAP_WIDTH; i++) //맨 아랫줄 생성
    {
        gotoxy(MAP_X + i, MAP_Y + MAP_HEIGHT - 1, "■");
    }
}
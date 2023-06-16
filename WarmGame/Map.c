#include "Map.h"
#include "GlobalSettings.h"






void gotoxy(int x, int y, char* s)
{ // ��ǥ���� �ٷ� ���ڿ��� �Է��� �� �ֵ��� printf�Լ� ����  
    COORD pos = { 2 * x,y }; //������ ũ�Ⱑ ª�Ƽ� x�� 2��
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    printf("%s", s); //���� ���ڿ� ���
}








void DrawMap(void) //�� �׵θ� ����
{ 
    int i;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    for (i = 0; i < MAP_WIDTH; i++) 
    {
        gotoxy(MAP_X + i, MAP_Y, "��");//�� ���� ����
    }
    for (i = MAP_Y + 1; i < MAP_Y + MAP_HEIGHT - 1; i++) //i�� Y �� �Ʒ��� -1ĭ���� �ݺ� 
    {
        gotoxy(MAP_X, i, "��");
        gotoxy(MAP_X + MAP_WIDTH - 1, i, "��");
    }
    for (i = 0; i < MAP_WIDTH; i++) //�� �Ʒ��� ����
    {
        gotoxy(MAP_X + i, MAP_Y + MAP_HEIGHT - 1, "��");
    }
}
#include "Map.h"
#include "Object.h"
#include "GlobalSettings.h"

void GenerateStar(void)
{
    int i;

    int StarCrushOn = 0;//star�� �� ������ǥ�� ���� ��� true 
    int r = 0; //�߰� ���� ���� ���� 

    while (1)
    {
        StarCrushOn = 0;
        srand((unsigned)time(NULL) + r); //srand�� �õ尪�� �ٸ��� ����
        star_x = (rand() % (MAP_WIDTH - 2)) + 1;    //������ ��ǥ���� ���� 
        star_y = (rand() % (MAP_HEIGHT - 2)) + 1;

        for (i = 0; i < length; i++) { //star�� �� ����� ��ġ���� üũ  
            if (star_x == x[i] && star_y == y[i]) {
                StarCrushOn = 1; //��ġ�� star_crush_on �� true 
                r++; //���� ����
                break;
            }
        }

        if (StarCrushOn == 1) continue; //����� star ������ ��� while�� ó������ 
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
        gotoxy(MAP_X + star_x, MAP_Y + star_y, "��"); //�Ȱ����� ��� ��ǥ���� star����

        break;
    }
}

void MoveSnake(void)
{
    int i;

    gotoxy(MAP_X + x[length - 1], MAP_Y + y[length - 1], "  "); //���� �������� ���� 
    for (i = length - 1; i > 0; i--) { //���� ��ǥ�� ��ĭ�� �Űܼ� �� ������ 
        x[i] = x[i - 1];
        y[i] = y[i - 1];
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    gotoxy(MAP_X + x[0], MAP_Y + y[0], "��"); //�Ӹ��� �������� ���� 
    if (dir == LEFT) --x[0]; //�𷺼ǰ��� ���� ���ο� �Ӹ���ǥ(x[0],y[0])���� ���� 
    if (dir == RIGHT) ++x[0];
    if (dir == UP) --y[0];
    if (dir == DOWN) ++y[0];
    gotoxy(MAP_X + x[0], MAP_Y + y[0], "��"); //���ο� �Ӹ���ǥ���� �Ӹ��� ����
}

#include "Map.h"
#include "Object.h"
#include "GlobalSettings.h"

void GenerateStar(void)
{
    int i;

    int StarCrushOn = 0;//star가 뱀 몸통좌표에 생길 경우 true 
    int r = 0; //추가 난수 생성 변수 

    while (1)
    {
        StarCrushOn = 0;
        srand((unsigned)time(NULL) + r); //srand의 시드값을 다르게 지정
        star_x = (rand() % (MAP_WIDTH - 2)) + 1;    //난수를 좌표값에 넣음 
        star_y = (rand() % (MAP_HEIGHT - 2)) + 1;

        for (i = 0; i < length; i++) { //star가 뱀 몸통과 겹치는지 체크  
            if (star_x == x[i] && star_y == y[i]) {
                StarCrushOn = 1; //겹치면 star_crush_on 를 true 
                r++; //난수 변경
                break;
            }
        }

        if (StarCrushOn == 1) continue; //몸통과 star 겹쳤을 경우 while문 처음으로 
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
        gotoxy(MAP_X + star_x, MAP_Y + star_y, "★"); //안겹쳤을 경우 좌표값에 star생성

        break;
    }
}

void MoveSnake(void)
{
    int i;

    gotoxy(MAP_X + x[length - 1], MAP_Y + y[length - 1], "  "); //몸통 마지막을 삭제 
    for (i = length - 1; i > 0; i--) { //몸통 좌표를 한칸씩 옮겨서 맨 앞으로 
        x[i] = x[i - 1];
        y[i] = y[i - 1];
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    gotoxy(MAP_X + x[0], MAP_Y + y[0], "○"); //머리를 몸통으로 변경 
    if (dir == LEFT) --x[0]; //디렉션값에 따라 새로운 머리좌표(x[0],y[0])값을 변경 
    if (dir == RIGHT) ++x[0];
    if (dir == UP) --y[0];
    if (dir == DOWN) ++y[0];
    gotoxy(MAP_X + x[0], MAP_Y + y[0], "●"); //새로운 머리좌표값에 머리를 생성
}

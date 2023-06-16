#include "Map.h"
#include "Object.h"
#include "System.h"
#include "GlobalSettings.h"

void StartTitleScene(void) {
    int i, j;

    while (_kbhit()) _getch(); 

    DrawMap();    //맵 테두리를 그림 
    for (i = MAP_Y + 1; i < MAP_Y + MAP_HEIGHT - 1; i++)
    { // 맵 테두리 안쪽을 빈칸으로 채움 
        for (j = MAP_X + 1; j < MAP_X + MAP_WIDTH - 1; j++)
        {
            gotoxy(j, i, "  ");
        }
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 5, "+--------------------------+");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 6, "|        S N A K E         |");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 7, "+--------------------------+");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 11, "   ◇ ←,→,↑,↓ : Move    ");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 12, "   ◇ P : Pause             ");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 13, "   ◇ ESC : Quit            ");

    UpdateTitleScene();
}

void UpdateTitleScene()
{
    while (1)
    {
        if (_kbhit() != 0)
        {
            GetUserInput();

            // ESC키면 종료. ESC가 아닌 키가 눌렸으면 게임 시작. 
            if (key == ESC)
            {
                exit(0);
            }
            else
            {
                break;
            }
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 9, "   PRESS ANY KEY TO START   ");
        Sleep(400);
        gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 9, "                            ");
        Sleep(400);
    }

    StartGameScene(); // 게임 시작  
}

void StartGameScene(void)
{
    while (_kbhit()) _getch(); //버퍼에 있는 키값을 버림 

    system("cls"); // 스크린 초기화
    DrawMap(); //맵 재생성


    dir = LEFT; // 방향 초기화     
    length = 5; //뱀 길이 초기화 
    score = 0; //점수 초기화 

    int i;

    //뱀 몸통값 입력
    for (i = 0; i < length; i++)
    {
        x[i] = MAP_WIDTH / 2 + i;
        y[i] = MAP_HEIGHT / 2;
        gotoxy(MAP_X + x[i], MAP_Y + y[i], "○");
    }
    gotoxy(MAP_X + x[0], MAP_Y + y[0], "●"); //뱀 머리 그림 
    GenerateStar(); // star 생성  

    UpdateGameScene(); // 게임 플레이 씬 업데이트
}

void UpdateGameScene(void)
{
    int i;
    while (TRUE)
    {
        GetUserInput();

        if (key == PAUSE) 
        {
            Pause();
        }

        if (x[0] == star_x && y[0] == star_y) //star와 충돌했을 경우
        {  
            score += 1; //점수 증가 
            GenerateStar(); //새로운 star 추가 
            length++; //길이증가 
            x[length - 1] = x[length - 2]; //새로만든 몸통에 값 입력 
            y[length - 1] = y[length - 2];
        }

        if (x[0] == 0 || x[0] == MAP_WIDTH - 1 || y[0] == 0 || y[0] == MAP_HEIGHT - 1) //벽과 충돌했을 경우 
        { 
            GameOverScene();
            return; 
        }

        for (i = 1; i < length; i++) //자기몸과 충돌했는지 검사
        {  
            if (x[0] == x[i] && y[0] == y[i]) {
                GameOverScene();
                return;
            }
        }

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        gotoxy(MAP_X, MAP_Y + MAP_HEIGHT, " YOUR SCORE: ");  
        printf("%3d, BEST SCORE: %3d", score, best_score);

        MoveSnake();

        Sleep(100); 
    }
}

void GameOverScene(void)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 6, MAP_Y + 5, "+----------------------+");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 6, MAP_Y + 6, "|      GAME OVER       |");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 6, MAP_Y + 7, "+----------------------+");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 6, MAP_Y + 8, " YOUR SCORE : ");
    printf("%d", score); 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 12, " Press any keys to restart. ");

    if (score > best_score) //최고 점수 갱신시 출력
    {
        best_score = score;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
        gotoxy(MAP_X + (MAP_WIDTH / 2) - 1, MAP_Y + 10, " NEW ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
        gotoxy(MAP_X + (MAP_WIDTH / 2) - 3, MAP_Y + 11, "  HIGH SCORE ");
    }
    Sleep(500);

    while (_kbhit()) _getch(); 

    key = _getch(); 

    StartTitleScene();
}

 
void Pause(void)
{
    while (_kbhit())
    {
        _getch();
    }
    while (TRUE)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        gotoxy(MAP_X + (MAP_WIDTH / 2) - 9, MAP_Y + MAP_HEIGHT + 2, "< PAUSE : PRESS ANY KEY TO RESUME > ");
        Sleep(400);
        gotoxy(MAP_X + (MAP_WIDTH / 2) - 9, MAP_Y + MAP_HEIGHT + 2, "                                    ");
        Sleep(400);
        if (_kbhit())
        {
            _getch();
            break;
        }
    }

}

void GetUserInput()
{
    int curKey = NONE;
    int curDir = dir;
    if (_kbhit()) do { curKey = _getch(); } while (curKey == 224); //방향키 초기값 제거후 다시 키값 입력 받기

    switch (curKey)
    {
    case LEFT:
    case RIGHT:
    case UP:
    case DOWN:
        if ((curDir == LEFT && curKey != RIGHT) || (curDir == RIGHT && curKey != LEFT) ||
            (curDir == UP && curKey != DOWN) || (curDir == DOWN && curKey != UP)) //180도 돌아가지 않을때만 받은 값을 디렉션에 저장
        {
            dir = curKey;
        }
        break;
    case PAUSE:
        break;

    case ESC:
        break;
    }
    key = curKey;

    // 한번 입력된 후 버퍼 비우기
    while (_kbhit()) { _getch(); }
}

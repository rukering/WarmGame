#include "Map.h"
#include "Object.h"
#include "System.h"
#include "GlobalSettings.h"

void StartTitleScene(void) {
    int i, j;

    while (_kbhit()) _getch(); 

    DrawMap();    //�� �׵θ��� �׸� 
    for (i = MAP_Y + 1; i < MAP_Y + MAP_HEIGHT - 1; i++)
    { // �� �׵θ� ������ ��ĭ���� ä�� 
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
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 11, "   �� ��,��,��,�� : Move    ");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 12, "   �� P : Pause             ");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 13, "   �� ESC : Quit            ");

    UpdateTitleScene();
}

void UpdateTitleScene()
{
    while (1)
    {
        if (_kbhit() != 0)
        {
            GetUserInput();

            // ESCŰ�� ����. ESC�� �ƴ� Ű�� �������� ���� ����. 
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

    StartGameScene(); // ���� ����  
}

void StartGameScene(void)
{
    while (_kbhit()) _getch(); //���ۿ� �ִ� Ű���� ���� 

    system("cls"); // ��ũ�� �ʱ�ȭ
    DrawMap(); //�� �����


    dir = LEFT; // ���� �ʱ�ȭ     
    length = 5; //�� ���� �ʱ�ȭ 
    score = 0; //���� �ʱ�ȭ 

    int i;

    //�� ���밪 �Է�
    for (i = 0; i < length; i++)
    {
        x[i] = MAP_WIDTH / 2 + i;
        y[i] = MAP_HEIGHT / 2;
        gotoxy(MAP_X + x[i], MAP_Y + y[i], "��");
    }
    gotoxy(MAP_X + x[0], MAP_Y + y[0], "��"); //�� �Ӹ� �׸� 
    GenerateStar(); // star ����  

    UpdateGameScene(); // ���� �÷��� �� ������Ʈ
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

        if (x[0] == star_x && y[0] == star_y) //star�� �浹���� ���
        {  
            score += 1; //���� ���� 
            GenerateStar(); //���ο� star �߰� 
            length++; //�������� 
            x[length - 1] = x[length - 2]; //���θ��� ���뿡 �� �Է� 
            y[length - 1] = y[length - 2];
        }

        if (x[0] == 0 || x[0] == MAP_WIDTH - 1 || y[0] == 0 || y[0] == MAP_HEIGHT - 1) //���� �浹���� ��� 
        { 
            GameOverScene();
            return; 
        }

        for (i = 1; i < length; i++) //�ڱ���� �浹�ߴ��� �˻�
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

    if (score > best_score) //�ְ� ���� ���Ž� ���
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
    if (_kbhit()) do { curKey = _getch(); } while (curKey == 224); //����Ű �ʱⰪ ������ �ٽ� Ű�� �Է� �ޱ�

    switch (curKey)
    {
    case LEFT:
    case RIGHT:
    case UP:
    case DOWN:
        if ((curDir == LEFT && curKey != RIGHT) || (curDir == RIGHT && curKey != LEFT) ||
            (curDir == UP && curKey != DOWN) || (curDir == DOWN && curKey != UP)) //180�� ���ư��� �������� ���� ���� �𷺼ǿ� ����
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

    // �ѹ� �Էµ� �� ���� ����
    while (_kbhit()) { _getch(); }
}

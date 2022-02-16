#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<time.h>

#include"Snake.h"
#include"Food.h"

int score = 0;
Snake snake;
Food food;

void UpdateScore()
{
	gotoxy(106, 10);
	printf("%d", ++score);
	gotoxy(107, 11);
	printf("%zu", snake.bodies->length);
}

int touchFood(Node* node)
{
	if (node->body.x == food.x && node->body.y == food.y)
	{
		Food_Generate(&food);
		Food_Print(&food);
		Snake_AddBody(&snake);
		UpdateScore();
		return 1;
	}
	return 0;
}

int touchWall()
{
	return (snake.bodies->head->body.x == 98 || snake.bodies->head->body.x == 0 || snake.bodies->head->body.y == 0 || snake.bodies->head->body.y == 29);
}

int touchBody(Node* node)
{
	return (node->body.x == snake.bodies->head->body.x && node->body.y == snake.bodies->head->body.y);
}

int isGameRunning()
{
	return !(touchWall() || List_ForEach(snake.bodies, touchBody, 1, snake.bodies->length - 1ULL));
}

int main()
{
	srand((unsigned int)time(NULL));

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(hOut, &CursorInfo);
	CursorInfo.bVisible = 0;
	SetConsoleCursorInfo(hOut, &CursorInfo);

	snake = Snake_Construct();

	printf("***************************************************************************************************\n");
	for (int i = 0; i < 28; i++)
	{
		printf("*");
		for (int i2 = 0; i2 < 97; i2++)
		{
			printf(" ");
		}
		printf("*\n");
	}
	printf("***************************************************************************************************");

	gotoxy(100, 10);
	printf("score:%d", score);
	gotoxy(100, 11);
	printf("length:%zu", snake.bodies->length);

	Food_Generate(&food);
	Food_Print(&food);

	while (isGameRunning())
	{
		if (_kbhit())
		{
			switch (_getch())
			{
			case 'w':
				Snake_ChangeDir(&snake, Up);
				break;
			case 'a':
				Snake_ChangeDir(&snake, Left);
				break;
			case 's':
				Snake_ChangeDir(&snake, Down);
				break;
			case 'd':
				Snake_ChangeDir(&snake, Right);
				break;
			case 'j':
				Snake_AddBody(&snake);
				UpdateScore();
			}
		}
		Snake_Move(&snake);
		Snake_PrintBody(&snake);
		List_ForEach(snake.bodies, touchFood, 0, snake.bodies->length);
		Sleep(50);
	}

	gotoxy(43, 14);
	printf("Game Over");
	Snake_Free(&snake);

	_getch();
	return 0;
}
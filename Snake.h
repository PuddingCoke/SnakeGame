#pragma once

#ifndef _SNAKE_H_
#define _SNAKE_H_

#include"List.h"

typedef struct Snake
{
	List* bodies;
} Snake;

Snake Snake_Construct()
{
	Snake snake;
	snake.bodies = List_Construct();
	List_AddNode(snake.bodies, 30, 15, Up);
	List_AddNode(snake.bodies, 30, 16, Up);
	List_AddNode(snake.bodies, 30, 17, Up);
	return snake;
}

void Snake_Free(Snake* snake)
{
	List_Free(snake->bodies);
}

int moveStepOne(Node* node)
{
	switch (node->body.dir)
	{
	case Up:
		--(node->body.y);
		break;
	case Down:
		++(node->body.y);
		break;
	case Left:
		--(node->body.x);
		break;
	case Right:
		++(node->body.x);
	}
	return 0;
}

int moveStepTwo(Node* node)
{
	node->body.dir = node->prev->body.dir;
	return 0;
}

void Snake_Move(Snake* snake)
{
	gotoxy(snake->bodies->cur->body.x, snake->bodies->cur->body.y);
	printf(" ");
	List_ForEach(snake->bodies, moveStepOne, 0, snake->bodies->length);
	List_ForEachR(snake->bodies, moveStepTwo, 0, snake->bodies->length - 1ULL);
}

void Snake_PrintBody(Snake* snake)
{
	gotoxy(snake->bodies->head->body.x, snake->bodies->head->body.y);
	printf("*");
}

void Snake_AddBody(Snake* snake)
{
	switch (snake->bodies->cur->body.dir)
	{
	case Up:
		List_AddNode(snake->bodies, snake->bodies->cur->body.x, snake->bodies->cur->body.y + 1, Up);
		break;
	case Down:
		List_AddNode(snake->bodies, snake->bodies->cur->body.x, snake->bodies->cur->body.y - 1, Down);
		break;
	case Left:
		List_AddNode(snake->bodies, snake->bodies->cur->body.x + 1, snake->bodies->cur->body.y, Left);
		break;
	case Right:
		List_AddNode(snake->bodies, snake->bodies->cur->body.x - 1, snake->bodies->cur->body.y, Right);
	}
}

void Snake_ChangeDir(Snake* snake, Dir dir)
{
	if (dir != Dir_Reverse(snake->bodies->head->body.dir))
	{
		snake->bodies->head->body.dir = dir;
	}
}

#endif // !_SNAKE_H_



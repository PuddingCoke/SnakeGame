#pragma once

#ifndef _BODY_H_
#define _BODY_H_

#include<stdio.h>
#include<windows.h>

HANDLE hOut;

void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(hOut, pos);
}

typedef enum Dir
{
	Up, Down, Left, Right
} Dir;

Dir Dir_Reverse(Dir dir)
{
	switch (dir)
	{
	case Up:
		return Down;
	case Down:
		return Up;
	case Left:
		return Right;
	case Right:
		return Left;
	default:
		return Up;
	}
}

typedef struct Body
{
	int x;
	int y;
	Dir dir;
} Body;

Body Body_Construct(int x, int y, Dir dir)
{
	Body body;
	body.x = x;
	body.y = y;
	body.dir = dir;
	return body;
}

void Body_Print(Body* body)
{
	if (body)
	{
		printf("[Body]\nx:%d\ny:%d\n", body->x, body->y);
		printf("dir:");
		switch (body->dir)
		{
		case Up:
			printf("Up");
			break;
		case Down:
			printf("Down");
			break;
		case Left:
			printf("Left");
			break;
		case Right:
			printf("Right");
			break;
		}
		printf("\n/[Body]\n");
	}
}

#endif // !_BODY_H_
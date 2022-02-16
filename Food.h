#pragma once

#ifndef _FOOD_H_
#define _FOOD_H_

#include<stdlib.h>
#include<time.h>

#include"Body.h"

typedef struct Food
{
	int x;
	int y;
} Food;

void Food_Generate(Food* food)
{
	food->x = rand() % 70 + 15;
	food->y = rand() % 10 + 15;
}

void Food_Print(Food* food)
{
	gotoxy(food->x, food->y);
	printf("*");
}

#endif // !_FOOD_H_

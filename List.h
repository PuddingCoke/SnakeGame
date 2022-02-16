#pragma once

#ifndef _LIST_H_
#define _LIST_H_

#include"Body.h"

typedef struct Node Node;

struct Node
{
	Body body;
	Node* prev;
	Node* next;
};

typedef struct List
{
	size_t length;
	Node* head;
	Node* cur;
} List;

List* List_Construct()
{
	List* list = (List*)malloc(sizeof(List));
	if (list)
	{
		list->length = 0;
		list->cur = NULL;
		list->head = NULL;
		return list;
	}
	return NULL;
}

void List_Free(List* list)
{
	Node* temp;
	for (int i = 0; i < list->length; i++)
	{
		temp = list->head;
		list->head = list->head->next;
		free(temp);
	}
	free(list);
}

void List_AddNode(List* list, int x, int y, Dir dir)
{
	if (list->head == NULL)
	{
		list->head = (Node*)malloc(sizeof(Node));
		if (list->head)
		{
			list->head->body.x = x;
			list->head->body.y = y;
			list->head->body.dir = dir;
			list->head->prev = NULL;
			list->head->next = NULL;
			list->cur = list->head;
		}
	}
	else
	{
		list->cur->next = (Node*)malloc(sizeof(Node));
		if (list->cur->next)
		{
			list->cur->next->prev = list->cur;
			list->cur = list->cur->next;
			list->cur->body.x = x;
			list->cur->body.y = y;
			list->cur->body.dir = dir;
			list->cur->next = NULL;
		}
	}
	list->length++;
}

int List_ForEach(List* list, int (*function)(Node* node), int offset, int count)
{
	Node* temp = list->head;

	for (int i = 0; i < offset; i++)
	{
		temp = temp->next;
	}

	for (int i = 0; i < count; i++)
	{
		if (function(temp))
		{
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}

int List_ForEachR(List* list, int (*function)(Node*), int offset, int count)
{
	Node* temp = list->cur;

	for (int i = 0; i < offset; i++)
	{
		temp = temp->prev;
	}

	for (int i = 0; i < count; i++)
	{
		if (function(temp))
		{
			return 1;
		}
		temp = temp->prev;
	}
	return 0;
}







#endif // !_LIST_H_

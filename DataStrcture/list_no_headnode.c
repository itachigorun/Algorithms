#include<stdio.h>
#include<stdlib.h>

typedef struct list {
	int a;
	char b;
	struct list *next;
	struct list *prev;
}listnode;

void listInit(listnode **Head, listnode **Tail)
{
	*Head = NULL;
	*Tail = NULL;
}

bool listTailInsert(listnode **Head, listnode **Tail, int a, char b)
{
	listnode *temp = (listnode *)malloc(sizeof(listnode));
	if (!temp)
	{
		printf("malloc failed\n");
		return false;
	}
	temp->a = a;
	temp->b = b;
	temp->next = NULL;
	temp->prev = (*Tail);
	if (*Tail)
	{
		(*Tail)->next = temp;
	}
	else
	{
		(*Head) = temp;
	}
	
	(*Tail) = temp;

	return true;
}

bool listHeadInsert(listnode **Head, listnode **Tail, int a, char b)
{
	listnode *temp = (listnode *)malloc(sizeof(listnode));
	if (!temp)
	{
		printf("malloc failed\n");
		return false;
	}
	temp->a = a;
	temp->b = b;
	temp->prev = NULL;
	temp->next = (*Head);
	if (*Head)
	{
		(*Head)->prev = temp;
	}
	else
	{
		(*Tail) = temp;
	}
	(*Head) = temp;
	return true;
}

void listPrint(listnode *Head)
{
	listnode *node = Head;
	while (node)
	{
		printf("a:[%d] b:[%c] \n", node->a, node->b);
		node = node->next;
	}
}

void listDelete(listnode **Head, listnode **Tail, listnode *temp)
{
	if (*Head == *Tail)
	{
		free(temp);
		(*Head) = NULL;
		(*Tail) = NULL;
	}
	else if (temp->next == NULL)
	{
		temp->prev->next = NULL;
		(*Tail) = temp->prev;
		free(temp);
	}
	else if (temp->prev == NULL)
	{
		temp->next->prev = NULL;
		(*Head) = temp->next;
		free(temp);
	}
	else
	{
		listnode * node = temp;
		temp->next->prev = temp->prev;
		temp->prev->next = temp->next;
		free(node);
	}
}

void listDestroy(listnode **Head, listnode **Tail)
{
	while (*Head)
	{
		listDelete(Head,Tail,*Head);
	}
}

int main()
{
	struct list * Head;
	struct list * Tail;

	listInit(&Head, &Tail);
	listHeadInsert(&Head, &Tail, 2, 'a');
	listTailInsert(&Head, &Tail, 3, 'b');
	listPrint(Head);
	listDestroy(&Head, &Tail);

	return 0;
}
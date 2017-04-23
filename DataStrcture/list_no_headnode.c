// itachigorun 
// 2017-04-04


#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct node{
    int key;
    struct node *prev;
    struct node *next;
}Node;


void InitList(Node **L)
{
    *L = NULL;      
}    

void InsertHeadList(Node **L, int input_num)
{
    Node *p = malloc(sizeof(Node));
    if(!p)
    {
        printf("Memory error\n");
        return ;
    }
    p->key = input_num;
    p->next = *L;
    if(*L)
        *L->next->prev = p;
    
    *L = p;
    p->prev = NULL;
}

void InsertTailList(Node *L, int input_num)
{
    Node *tail;
    Node *p = malloc(sizeof(Node));
    if(!p)
    {
        printf("Memory error\n");
        return ;
    }
    p->key = input_num;
    p->next = NULL;
    tail = L;
    while(tail->next != NULL)
        tail = tail->next;
    
    p->prev = tail;
    tail->next = p;
}

Node *ListSearch(Node *L, int input_num)
{
    Node *p = L;
    while(p!= NULL && p->key!=input_num)
        p = p->next;
    
    return p;
}

void DeleteList(Node *L, int input_num)
{
    Node *p = NULL;
    if(L == NULL)
    {
        printf("The list is empty\n");
	    return ;
    }

    p = ListSearch(L, input_num);
    if(p->prev!=NULL)
        p->prev->next = p->next;
    else
        L = p->next;
    if(p->next!=NULL)
        p->next->prev = p->prev;
    
    free(p);
}

void PrintList(Node *L)
{
    while(L!=NULL)
    {
        printf("%d ", L->key);
        L = L->next;
    }
    printf("\n");
}

void ClearList(Node *L)
{
  Node *p = NULL;
  if(L == NULL)
  return ;
  p = L;
  while(L->next!=NULL)
  {
     L = L->next;
     free(p);
     p = L->next;
  }
  free(p);
}

int main()
{
    Node *L = NULL;
    int select_num;
    int input_num;
    bool select_flag = true;
    
    while(select_flag)
    {
        printf("Please input the select 1)insert node  2)delete node 3)show list 4)exit\n");
        scanf("%d", &select_num);
        if(select_num == 1 || select_num ==2)
        {
	    printf("Please input the number: ");
	    scanf("%d", &input_num);
	}

	printf("dd");
        switch(select_num)
        {
            case 1:
            InitListHead(&L);
	        InsertHeadList(&L, input_num);
	        break;
            case 2:
    	        DeleteList(L, input_num);
    	        break;
    	    case 3:
    	        PrintList(L);
    	        break;
	    case 4:
	        select_flag = false;
	        ClearList(L);
	    default:
	        printf("Please input again\n");
        }
    }

    return 0;
}
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

typedef struct head1{
    Node *head;
}Head;

void ListInsert(Head *L, int input_num)
{
    Node *p = malloc(sizeof(Node));
    p->key = input_num;
    p->next = L->head;
    if(L->head!=NULL)
        L->head->prev = p;
    
    L->head = p;
    p->prev = NULL;
}

Node *ListSearch(Head *L, int input_num)
{
    Node *p = L->head;
    while(p!= NULL && p->key!=input_num)
        p = p->next;
    
    return p;
}

void ListDelete(Head *L, int input_num)
{
    Node *p = NULL;
    if(L->head == NULL)
    {
        printf("The list is empty\n");
	return ;
    }

    p = ListSearch(L, input_num);
    if(p->prev!=NULL)
        p->prev->next = p->next;
    else
        L->head = p->next;
    if(p->next!=NULL)
        p->next->prev = p->prev;
    
    free(p);
}

void ListShow(Head *L)
{
    Node *p = L->head;
    while(p!=NULL)
    {
        printf("%d ", p->key);
        p = p->next;
    }
    printf("\n");
}

void ListDestroy(Head *L)
{
  Node *p = NULL;
  if(L->head == NULL)
  return ;
  p = L->head;
  while(L->head->next!=NULL)
  {
     L->head = L->head->next;
     free(p);
     p = L->head->next;
  }
  free(p);
}

int main()
{
    Head *L = NULL;
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
	        ListInsert(L, input_num);
	        break;
            case 2:
    	        ListDelete(L, input_num);
    	        break;
    	    case 3:
    	        ListShow(L);
    	        break;
	    case 4:
	        select_flag = false;
	        ListDestroy(L);
	    default:
	        printf("Please input again\n");
        }
    }

    return 0;
}

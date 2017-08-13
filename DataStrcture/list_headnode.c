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


void InitListHead(Node **pnode)
{
    *pnode = (Node *)malloc(sizeof(Node));
    if(*pnode == NULL)
        printf("The head of list init error\n");
    else
    {
       (*pnode)->next = NULL;
       (*pnode)->prev = NULL;
    }
}

void InsertHeadList(Node *L, int input_num)
{
    Node *p = malloc(sizeof(Node));
    p->key = input_num;
    p->next = L->next;
    if(L->next)
        L->next->prev = p;

    p->prev = L;
    L->next = p;
}


Node *SearchList(Node *L, int input_num)
{
    Node *p = L->next;
    while(p!= NULL && p->key!=input_num)
        p = p->next;
    
    return p;
}

void DeleteOneList(Node *L, int input_num)
{
    Node *p = NULL;
    if(L->next == NULL)
    {
        printf("The list is empty\n");
	    return ;
    }

    p = SearchList(L, input_num);
    if(!p)
    {
        printf("The number is not found\n");
        return ;
    }
    
    p->prev->next = p->next;
    p->next->prev = p->prev;
    
    free(p);
}

void PrintList(Node *L)
{
    Node *p = L->next;
    while(p!=NULL)
    {
        printf("%d ", p->key);
        p = p->next;
    }
    printf("\n");
}

void ClearList(Node *L)
{
  Node *p = L;
  while(p)
  {
     L = L->next;
     free(p);
     p = L;
  }
}

int main()
{
    Node *L = NULL;
    int select_num;
    int input_num;
    bool select_flag = true;
    
    InitListHead(&L);
    while(select_flag)
    {
        printf("Please input the select 1)insert node  2)delete node 3)show list 4)exit ");
        scanf("%d", &select_num);
        if(select_num == 1 || select_num ==2)
        {
     	    printf("Please input the number: ");
	        scanf("%d", &input_num);
	    }

        switch(select_num)
        {
            case 1:
	            InsertHeadList(L, input_num);
	            break;
            case 2:
    	        DeleteOneList(L, input_num);
    	        break;
    	    case 3:
    	        PrintList(L);
    	        break;
	        case 4:
	            select_flag = false;
	            ClearList(L);
                break;
	        default:
	            printf("Please input again\n");
        }
    }

    return 0;
}

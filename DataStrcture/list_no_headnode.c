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
        (*L)->prev = p;
    
    *L = p;
    p->prev = NULL;
}

/* 无头结点链表尾巴插入节点,用二级指针操作第一个节点插入，若是带头节点链表则插入不用二级指针
list* concat(list* l, list* r)
{
    list** indir = &l;
    while(*indir) {
        indir = &((*indir)->next);
    }
    *indir = r;
    return l;
}
*/


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
    if(!p)
    {
        printf("The number is not found\n");
        return ;
    }
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
    Node *p = L;
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

    InitList(&L);
    while(select_flag)
    {
        printf("Please input the select 1)insert node  2)delete node 3)show list 4)exit: ");
        scanf("%d", &select_num);
        if(select_num == 1 || select_num ==2)
        {
	        printf("Please input the number: ");
	        scanf("%d", &input_num);
    	}

        switch(select_num)
        {
            case 1:
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
                break;
	        default:
	            printf("Please input again\n");
        }
    }

    return 0;
}

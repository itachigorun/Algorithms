#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100
#define ELEMTYPE int

typedef struct{
    ELEMTYPE data[MAXSIZE];
    int length;
}SeqList;

void InitSeqList(SeqList *L)
{
    L->length = 0;
    printf("Init List success\n");
}

void CreateSeqList(SeqList *L)
{
    ELEMTYPE x;
    x = -1;
    scanf("%d", &x);
    while(x != 0&&L->length<=MAXSIZE)
    {
        L->data[L->length] = x;
        L->length++;
        scanf("%d", &x);
    }
    printf("Create List success\n");
}

void InsertSeqList(SeqList *L, int i, ELEMTYPE x)
{
    if(L->length == MAXSIZE)
        printf("The list is full\n");
    else if(i<1 || i>L->length+1)
    {
        printf("The insert position is error\n");
        return ;
    }
    
    int j;
    for(j = L->length; j >= i; j--)
    {
        L->data[j] = L->data[j-1];
    }
    L->data[i-1] = x;
    L->length++;
}

ELEMTYPE GetElemSeqList(SeqList *L, int i)
{
    if(i < 1 || i > L->length)
    {
        printf("Search position is error\n");
        return 0;
    }
    else
        return L->data[i-1];
}

int LocateElemSeqList(SeqList *L, ELEMTYPE x)
{
    int i = 0;
    while(i <= L->length && L->data[i] != x)
        i++;

    if(i <= L->length)
        return i+1;
    else
        return 0;
}

void DeleteSeqList(SeqList *L, int i)
{
    if(i < 1 || i > L->length)
        printf("Delete position is error\n");
    int j;
    if(i == L->length)
    {
        L->length--;
	    return ;
    }

    for(j = i-1; j < L->length-1; j++)
        L->data[j] = L->data[j+1];

    L->length--;
  
}

void PrintSeqList(SeqList L)
{
    int i = 0;
    while(L.length>0)
    {
        printf("%d ", L.data[i]);
        i++;
        L.length--;
    }
    printf("\n");
}


int main()
{
    SeqList L;
    int i;
    ELEMTYPE x;
    InitSeqList(&L);
    CreateSeqList(&L);
    PrintSeqList(L);

    printf("Please input the position you want to insert: ");
    scanf("%d",&i);
    printf("Please input the number: ");
    scanf("%d",&x);
    InsertSeqList(&L,i,x);
    PrintSeqList(L);

    printf("Please input the positon you want to search: ");
    scanf("%d", &i);
    x = GetElemSeqList(&L,i);
    printf("The number is %d\n",x);

    printf("Please input the number you want to search: ");
    scanf("%d", &x);
    i = LocateElemSeqList(&L, x);
    printf("The position is: %d\n", i);

    printf("Please input the position of number you want to delete: ");
    scanf("%d", &i);
    DeleteSeqList(&L, i);
    PrintSeqList(L);

    return 0;
}

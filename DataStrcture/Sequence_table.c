#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100
#define ELEMTYPE int

typedef struct{
    ELEMTYPE data[MAXSIZE];
    int length;
}SeqList;

SeqList InitSeqList()
{
    SeqList L;
    L.length = 0;
    return L;
}

SeqList CreateSeqList(SeqList L)
{
    ELEMTYPE x;
    while(scanf("%d", &x) != EOF)
    {
        L.data[L.length] = x;
        L.length++;
    }
    return L;
}

SeqList InsertSeqList(SeqList L, int i, ELEMTYPE x)
{
    if(L.length == MAXSIZE)
        printf("The list is full\n");
    else if(i<1 || i>L.length)
        printf("The insert position is error\n");

    int j;
    for(j = L.length-1; j >= i-1; j--)
    {
        L.data[j+1] = L.data[j];
    }
    L.data[i-1] = x;
    L.length++;
    return L;
}

ELEMTYPE GetElemSeqList(SeqList L, int i)
{
    if(i < 1 || i > L.length)
    {
        printf("Search position is error\n");
        return 0;
    }
    else
        return L.data[i-1];
}

int LocateElemSeqList(SeqList L, ELEMTYPE x)
{
    int i = 0;
    while(i <= L.length && L.data[i] != x)
    {
        i++;
    }

    if(i <= L.length)
        return i+1;
    else
        return 0;
}

SeqList DeleteSeqList(SeqList L, int i)
{
    if(i < 1 || i > L.length)
        printf("Delete position is error\n");
    int j;
    if(i == L.length)
    {
        L.length--;
        return L;
    }
    for(j = i-1; j < L.length-1; j++)
        L.data[j] = L.data[j+1];

    L.length--;
    return L;
}


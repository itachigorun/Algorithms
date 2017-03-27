// Author: itachigorun 
// Date:   2017-03-17

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int g_length;

bool IsEmpty(int stackTop)
{
    return stackTop == 0 ? true : false;
}

bool IsFull(int stackTop)
{
    return stackTop == g_length ? true : false;
}

void push(int *stackTmp, int num, int *stackTop)
{
    if(IsFull(*stackTop))
    {
	printf("The stack is full\n");
        return ;	
    }
    stackTmp[*stackTop] = num;
    (*stackTop)++;
}

void pop(int *stackTop)
{
    if(IsEmpty(*stackTop))
    {
        printf("The stack is empty\n");
	return ;
    }
    (*stackTop)--;
    printf("pop a number\n");
}

void ShowStack(int *stackTmp, int stackTop)
{
    if(IsEmpty(stackTop))
    {
        printf("The stack is empty\n");
	return ;
    }
    for(int i=0; i < stackTop; i++)
        printf("%d ",stackTmp[i]);
    printf("\n");
}

int main()
{
    int *stackTmp;
    int selectNum;
    int inputNum;
    int stackTop = 0;
    bool loopFlag = true;
    printf("Please input the g_length of stack:");
    scanf("%d", &g_length);
    if(g_length == 0)
        return 0;
    stackTmp = (int *)malloc(4*g_length);
    while(loopFlag)
    {
        printf("Please select: push the number : 1 pop the number : 2 exit : 3 show stack : 4\n");
        scanf("%d",&selectNum);
	if(selectNum == 1)
	    scanf("%d",&inputNum);
	switch(selectNum)
	{
            case 1:
	        push(stackTmp, inputNum, &stackTop);
		break;
	    case 2:
	        pop(&stackTop);
		break;
	    case 3:
	        loopFlag = false;
		break;
	    case 4:
	        ShowStack(stackTmp, stackTop);
		break;
	    default:
	        printf("Sorry, it's the incorrect number\n");
	}
    }	
    free(stackTmp);
}

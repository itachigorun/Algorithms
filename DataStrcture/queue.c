// itachigorun 
// 2017-04-03
// queue_head is pointer the first element of array, queue_tail is pointer the next position of element

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int g_queue_length;

bool IsEmpty(int *queue_head, int *queue_tail)
{
    return *queue_head == *queue_tail ? true : false;
}

bool IsFull(int *queue_head, int *queue_tail)
{
    return *queue_head == (*queue_tail +1) % g_queue_length ? true : false;
}

void EnQueue(int *queue_pointer, int input_num, int *queue_head, int *queue_tail)
{   
    if(IsFull(queue_head, queue_tail))
    {
        printf("Tht queue is full\n");
	return ;
    }
    queue_pointer[*queue_tail] = input_num;
    *queue_tail = (*queue_tail + 1) % g_queue_length;
}

void DeQueue(int *queue_pointer, int *queue_head, int *queue_tail)
{
   if(IsEmpty(queue_head, queue_tail))
   {
       printf("The queue is empty\n");
       return ;
   }

   *queue_head = (*queue_head + 1) % g_queue_length;
}

void ShowQueue(int *queue_pointer, int queue_head, int queue_tail)
{
     if(IsEmpty(&queue_head, &queue_tail))
     {
     printf("The queue is empty\n");
     return ;
     }

     while(queue_tail != ((queue_head + 1) % g_queue_length))
     {
        printf("%d ", queue_pointer[queue_head]);
        queue_head = (queue_head + 1) % g_queue_length;
     }
     printf("%d\n", queue_pointer[queue_head]);
}

int main()
{
int *queue_pointer = NULL;
bool bool_flag = true;
int select_num;
int input_num;
int queue_tail = 0;
int queue_head = 0;

printf("Please input the number of queue:");
scanf("%d", &g_queue_length);
if(g_queue_length == 0)
    return 0;
g_queue_length++;
queue_pointer = malloc(4*g_queue_length+1);

while(bool_flag)
{
    printf("Please select the operating: 1)input the queue 2)delete the queue 3)show the queue 4) exit\n");
    scanf("%d", &select_num);
    if(select_num == 1){
    printf("please input the input_num :");
    scanf("%d", &input_num);
    }
    switch(select_num)
    {
        case 1:
	      EnQueue(queue_pointer, input_num, &queue_head, &queue_tail);
	      break;
	case 2:
	      DeQueue(queue_pointer, &queue_head, &queue_tail);
	      break;
	case 3:
	      ShowQueue(queue_pointer, queue_head, queue_tail);
	      break;
	case 4:
	      bool_flag = false;
	      break;
	default:
	      printf(" Please select again\n");
    }
}
free(queue_pointer);
return 0;
}

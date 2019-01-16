#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "head.h"

void FCFS(Queue *pqueue, PCB pcbs[], int size)
{
    int pcbnumber = size;
	int time = 0;
	//
	//  |_______|_______|_______|_______|_______|_______|_______|_______|___
	//	0       1       2       3       4       5       6       7       8 

	while (1) {
		//等待进程
        for (int i = 0; i < size; i++) {
            if (pcbs[i].ArrivalTime == time) {
                QueuePush(pqueue, pcbs[i]);
			    printf("PCB %c ARRIVAL TIME IS %d\n", pcbs[i].name, time);
                pcbnumber--;
            }
        }
        if (QueueEmpty(pqueue) && pcbnumber == 0) {
			printf("进程执行完毕！\n");
			break;
		}
        //
        //显示时间
//		printf("time is %d \n", time);

		//执行进程
        if (!QueueEmpty(pqueue) && QueueTop(pqueue)->data.ResidualTime == 0) {
            printf("PCB %c FINISH TIME IS %d\n", QueueTop(pqueue)->data.name, time);
            QueuePop(pqueue);
        }

        if (!QueueEmpty(pqueue)) {
            QueueTop(pqueue)->data.ResidualTime--;
        }

		time++;
       // sleep(1);
	}
}

void RR(Queue *pqueue, PCB pcbs[], int size)
{ 
	//这里是时间片的大小
	int q = 0;
    printf("please input q:");
    scanf("%d", &q);
	//这个表示本次时间片q剩下多少
	int lessq = 0;
    int pcbnumber = size;
	//表示本进程还需要的服务时间
	int time = 0;
	//
	//  |_______|_______|_______|_______|_______|_______|_______|_______|___
	//	0       1       2       3       4       5       6       7       8 

	while (1) {
		//等待进程
        for (int i = 0; i < size; i++) {
            if (pcbs[i].ArrivalTime == time) {
                QueuePush(pqueue, pcbs[i]);
                //       printf("QueueTop(pqueue)->next == %p\n", QueueTop(pqueue)->next);
                printf("PCB %c ARRIVAL TIME IS %d\n", pcbs[i].name, time);
                pcbnumber--;
                //	    printf("pcbnumber == %d\n", pcbnumber);
            }
        }
        if (QueueEmpty(pqueue) && pcbnumber == 0) {
			printf("进程执行完毕！\n");
			break;
		}
//		printf("time is %d \n", time);
        //
        //
		//执行进程
        if (lessq == 0) {
            if (!QueueEmpty(pqueue) && QueueTop(pqueue)->data.ResidualTime == 0) {
                printf("PCB %c FINISH TIME IS %d\n", QueueTop(pqueue)->data.name, time);
                QueuePop(pqueue);
            }
            else {
                if (!QueueEmpty(pqueue) && 
                    (QueueTop(pqueue)->data.ServiceTime != 
                    QueueTop(pqueue)->data.ResidualTime)) {
                    pqueue->rear->next = pqueue->front;
                    pqueue->rear = pqueue->rear->next;
                    pqueue->front = pqueue->front->next;
                    pqueue->rear->next = NULL;
                }
            }
            lessq = q;
		}else {
            if (!QueueEmpty(pqueue) && QueueTop(pqueue)->data.ResidualTime == 0) {
                printf("PCB %c FINISH TIME IS %d\n", QueueTop(pqueue)->data.name, time);
                QueuePop(pqueue);
                lessq = q;
            }
        }
        if (!QueueEmpty(pqueue)) {
            QueueTop(pqueue)->data.ResidualTime--;
        }
        lessq--;
		time++;
        //sleep(1);
	}
}


void SPF(linkList *plinklist, PCB pcbs[], int size)
{

	int pcbid = 0;
    int pcbnumber = size;
	int time = 0;
    Node *curnode = NULL;
    Node *minnode = NULL;
    //
	//  |_______|_______|_______|_______|_______|_______|_______|_______|___
    //	0       1       2       3       4       5       6       7       8 
    while (1) {
        //等待进程
        for (int i = 0; i < size; i++) {
            if (pcbs[i].ArrivalTime == time) {
                linkListPushBack(plinklist, pcbs[i]);
                //       printf("QueueTop(pqueue)->next == %p\n", QueueTop(pqueue)->next);
                printf("PCB %c ARRIVAL TIME IS %d\n", pcbs[i].name, time);
                pcbnumber--;
                //	    printf("pcbnumber == %d\n", pcbnumber);
            }
        }

        if (linkListEmpty(plinklist) && pcbnumber == 0) {
			printf("进程执行完毕！\n");
			break;
		}
	//	printf("time is %d \n", time);
        //
		//执行进程
        //
        if (minnode != NULL && (minnode->data).ResidualTime == 0) {
            printf("PCB %c FINISH TIME IS %d\n", (minnode->data).name, time);
            linkListErase(plinklist, minnode);
            minnode = NULL;
        }
        
        if (!linkListEmpty(plinklist) && minnode == NULL) {
            minnode = NULL;
            curnode = plinklist->head;
            while(curnode != NULL) {
                if (minnode == NULL || curnode->data.ServiceTime < minnode->data.ServiceTime) {
                    minnode = curnode;
                }
                curnode = curnode->next;
            }
        }        


        if (minnode != NULL) {
            --(minnode->data).ResidualTime;
        }
        
		time++;
       // sleep(1);
    }
}


void PSA(linkList *plinklist, PCB pcbs[], int size)
{

	int pcbid = 0;
    int pcbnumber = size;
	int time = 0;
    Node *curnode = NULL;
    Node *minnode = NULL;
    //
	//  |_______|_______|_______|_______|_______|_______|_______|_______|___
    //	0       1       2       3       4       5       6       7       8 
    while (1) {
        //等待进程
        for (int i = 0; i < size; i++) {
            if (pcbs[i].ArrivalTime == time) {
                linkListPushBack(plinklist, pcbs[i]);
                //       printf("QueueTop(pqueue)->next == %p\n", QueueTop(pqueue)->next);
                printf("PCB %c ARRIVAL TIME IS %d\n", pcbs[i].name, time);
                pcbnumber--;
                //	    printf("pcbnumber == %d\n", pcbnumber);
            }
        }

        if (linkListEmpty(plinklist) && pcbnumber == 0) {
			printf("进程执行完毕！\n");
			break;
		}
//		printf("time is %d \n", time);
        //
		//执行进程
        //
        if (minnode != NULL && (minnode->data).ResidualTime == 0) {
            printf("PCB %c FINISH TIME IS %d\n", (minnode->data).name, time);
            linkListErase(plinklist, minnode);
            minnode = NULL;
        }
        
        if (!linkListEmpty(plinklist) && minnode == NULL) {
            minnode = NULL;
            curnode = plinklist->head;
            while(curnode != NULL) {
                if (minnode == NULL || curnode->data.Priority < minnode->data.Priority) {
                    minnode = curnode;
                }
                curnode = curnode->next;
            }
        }        


        if (minnode != NULL) {
            --(minnode->data).ResidualTime;
        }
        
		time++;
       // sleep(1);
    }
}


void DPSA(linkList *plinklist, PCB pcbs[], int size)
{

	int pcbid = 0;
    int pcbnumber = size;
	int time = 0;
    Node *curnode = NULL;
    Node *minnode = NULL;
    //
	//  |_______|_______|_______|_______|_______|_______|_______|_______|___
    //	0       1       2       3       4       5       6       7       8 
    while (1) {
        //等待进程
        for (int i = 0; i < size; i++) {
            if (pcbs[i].ArrivalTime == time) {
                linkListPushBack(plinklist, pcbs[i]);
                //       printf("QueueTop(pqueue)->next == %p\n", QueueTop(pqueue)->next);
                printf("PCB %c ARRIVAL TIME IS %d\n", pcbs[i].name, time);
                pcbnumber--;
                //	    printf("pcbnumber == %d\n", pcbnumber);
            }
        }

        if (linkListEmpty(plinklist) && pcbnumber == 0) {
			printf("进程执行完毕！\n");
			break;
		}
//		printf("\n\ntime is %d \n", time);
        //
		//执行进程
        //
        if (minnode != NULL && (minnode->data).ResidualTime == 0) {
            printf("PCB %c FINISH TIME IS %d\n", (minnode->data).name, time);
            linkListErase(plinklist, minnode);
            minnode = NULL;
        }
        
        if (!linkListEmpty(plinklist)) {
            minnode = NULL;
            curnode = plinklist->head;
            while(curnode != NULL) {
                if (minnode == NULL || curnode->data.Priority < minnode->data.Priority) {
                    minnode = curnode;
                }
                curnode = curnode->next;
            }
        }        


        if (minnode != NULL) {
            --(minnode->data).ResidualTime;
            ++(minnode->data.Priority);
            printf("PCB %c IS DO\n", (minnode->data).name);
        }
        curnode = plinklist->head;
        while(curnode != NULL) {
            if (curnode == minnode) {
                printf("%c priority ==  %d   ", curnode->data.name , curnode->data.Priority);
                curnode = curnode->next;
                continue;
            }
            (curnode->data.Priority) = (curnode->data.Priority - 1) > 0 ? (curnode->data.Priority) - 1 : 0;
            printf("%c priority ==  %d   ", curnode->data.name , curnode->data.Priority);
            curnode = curnode->next;
        }
        printf("\n");
		time++;
       // sleep(1);
    }
}


int main()
{
    int processnumber = 0;
	Queue queue;
    linkList linklist;
 // char name;
 // int ArrivalTime;        //到达时间
 // int ServiceTime;        //服务时间
 // int StartTime;          //开始时间
 // int FinishTime;         //完成时间
 // int ResidualTime;       //剩余服务时间
 // double WholeTime;          //周转时间
 // double weightWholeTime;    //带权周转时间
 // int Priority;           //优先级
   // PCB pcbs[] = {p1};
    printf("please input process number: ");
    scanf("%d", &processnumber);
    PCB *pcbs = (PCB *) malloc (sizeof(PCB) * processnumber);
    memset(pcbs, 0, sizeof(PCB) * processnumber);
    for (int i = 0; i < processnumber; i++) {
        printf("process->name: ");
        //这里有坑 ：
        //  可以用 scanf(" %c")    //   %c 前面加一个空格
        //  或者在上一行加一个getchar()
        //  getchar();
        scanf(" %c",&(pcbs[i].name));
        printf("process->ArricalTime: ");
        scanf("%d",&(pcbs[i].ArrivalTime));
        printf("process->ServiceTime: ");
        scanf("%d",&(pcbs[i].ServiceTime));
        pcbs[i].ResidualTime = pcbs[i].ServiceTime;
        printf("process->Priority: ");
        scanf("%d",&(pcbs[i].Priority));
    }
	int input = 0;
	QueueInit(&queue);
    linkListInitialize(&linklist);
	printf("1. FCFS   2.RR   3.SPF   4.PSA   5.DPSA\n");
	printf("Please input number: ");
	scanf("%d", &input);
	switch (input)
	{
	case 1:
		FCFS(&queue, pcbs, processnumber);
		break;
	case 2:
		RR(&queue, pcbs, processnumber);
		break;
	case 3:
        SPF(&linklist, pcbs, processnumber);
		break;
	case 4:
        PSA(&linklist, pcbs, processnumber);
		break;
	case 5:
        DPSA(&linklist, pcbs, processnumber);
		break;
	default:
		break;
	}
    linkListDestroy(&linklist);
	QueueDestroy(&queue);
	return 0;
}

#pragma once

typedef struct PCB {
	char name;                 //进程名
	int ArrivalTime;           //到达时间
	int ServiceTime;           //服务时间
	int StartTime;             //开始时间
	int FinishTime;            //完成时间
    int ResidualTime;          //剩余服务时间
	double WholeTime;          //周转时间
	double weightWholeTime;    //带权周转时间
    int Priority;              //优先级
}PCB;
typedef PCB DataType;
typedef struct Node {
	DataType data;
	struct Node *next;
}Node;
typedef struct Queue {
	Node *front;
	Node *rear;
	size_t size;			//队列中有几个元素
}Queue;


typedef struct linkList {
    Node *head;
    Node *tail;
    size_t size;
}linkList;

void QueueInit(Queue *pqueue) {			//初始化
	assert(pqueue != NULL);
	pqueue->front = NULL;
	pqueue->rear = NULL;
	pqueue->size = 0;
}

void QueueDestroy(Queue *pqueue)
{
	Node *cur = NULL;
	Node *del = NULL;
	assert(pqueue != NULL);
	if (pqueue->front == NULL) {
		return;
	}
	cur = pqueue->front;
	while (cur != NULL) {
		del = cur;
		cur = cur->next;
		free(del);
		del = NULL;
	}
}

Node *CreatNode(DataType data)
{
	Node *ret = (Node *)malloc(sizeof(Node));
	if (ret == NULL) {
		exit(0);
	}
	ret->data = data;
	ret->next = NULL;
	return ret;
}

void QueuePush(Queue *pqueue, DataType data)
{
	assert(pqueue != NULL);
	Node *temp = CreatNode(data);
	if (pqueue->front == NULL) {
		pqueue->front = temp;
		pqueue->rear = temp;
		//pqueue->rear = pqueue->front = temp;
		++pqueue->size;
	}
	else {
		pqueue->rear->next = temp;
		pqueue->rear = pqueue->rear->next;
		//pqueue->rear = temp;
		++pqueue->size;
	}
}

void QueuePop(Queue *pqueue)
{
	assert(pqueue != NULL);
	Node *del = NULL;
	assert(pqueue != NULL);
	if (pqueue->front == NULL) {
		return;
	}
	del = pqueue->front;
	pqueue->front = pqueue->front->next;
	free(del);
	del = NULL;
	++pqueue->size;
    
}

Node *QueueTop(Queue *pqueue)
{
	return pqueue->front;
}


bool QueueEmpty(const Queue *pqueue)
{
	return pqueue->front == NULL;
}

size_t QueueSize(const Queue *pqueue)
{
    return pqueue->size;
}




void linkListInitialize(linkList *plinklist)
{
    assert(plinklist != NULL);
    plinklist->head = NULL;
    plinklist->tail = NULL;
    plinklist->size = 0;    

}

void linkListDestroy(linkList *plinklist)
{
	Node *cur = NULL;
	Node *del = NULL;
	assert(plinklist != NULL);
	if (plinklist->head == NULL) {
		return;
	}
	cur = plinklist->head;
	while (cur != NULL) {
		del = cur;
		cur = cur->next;
		free(del);
		del = NULL;
	}
}

void linkListPushBack(linkList *plinklist, DataType data)
{
	assert(plinklist != NULL);
	Node *temp = CreatNode(data);
	if (plinklist->head == NULL) {
		plinklist->head = temp;
		plinklist->tail = temp;
		//pqueue->rear = pqueue->front = temp;
		++plinklist->size;
	}
	else {
		plinklist->tail->next = temp;
		plinklist->tail = plinklist->tail->next;
		//pqueue->rear = temp;
		++plinklist->size;
	}
}

void linkListErase(linkList *plinklist, Node *pnode)
{
	Node *cur = NULL;
	assert(plinklist != NULL);
	cur = plinklist->head;
	if ((plinklist->head) == NULL) {
		return;
	}
    if ((plinklist->head) == pnode) {
        plinklist->head = pnode->next;
        free(pnode);
        pnode = NULL;
        --(plinklist->size);
        return;
    }
    while(cur != NULL) {
        if (cur->next == pnode) {
            cur->next = pnode->next;
            free(pnode);
            pnode = NULL;
            --(plinklist->size);
            break;
        }
        cur = cur->next;
    } 
}

bool linkListEmpty(const linkList *plinkList)
{
	return plinkList->head == NULL;
}

size_t linkListSize(const linkList *plinklist)
{
    return plinklist->size;
}

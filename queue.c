/*
an implementation of sqqueue in chapter 3
presented by xdxu@ustc.edu.cn
*/

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// create a queue
SqQueue* createQueue(int capacity) {
	SqQueue *Q;
	Q = (SqQueue *)malloc(sizeof(SqQueue));
	Q->base = (int *)malloc(sizeof(int)*capacity);
	Q->capacity = capacity;
	Q->front = 0;
	Q->rear = 0;
	return Q;
}

// check if the queue is empty
int  isEmptyQueue(SqQueue *Q) {
	if (Q->rear == Q->front) return 1;
	return 0;
}

// tranverse the queue
void showQueue(SqQueue *Q) {
	int i;
	if (Q==NULL || Q->front==Q->rear) {
		printf("the queue does not exist or is empty.\n");
		return;
	}
	i = Q->front;
	printf("the queue contains: ");
	while (i != Q->rear) {
		printf("%d ", Q->base[i]);
		i = (i+1)%Q->capacity;
	}
	printf("\n");
}

// push an element into the queue
int EnQueue(SqQueue *Q, int data) {
	if (Q==NULL) return -1;
	if ((Q->rear+1)%Q->capacity == Q->front) return -1;
	Q->base[Q->rear] = data;
	Q->rear = (Q->rear+1)%Q->capacity;
	return 0;
}

// pop an element out of the queue
int DeQueue(SqQueue *Q, int *data) {
	if (Q==NULL) return -1;
	if (Q->rear == Q->front) return -1;
	*data = Q->base[Q->front];
	Q->front = (Q->front+1)%Q->capacity;
	return 0;
}

// destroy an existing queue
void destroyQueue(SqQueue **Q) {
	if (*Q==NULL) return;
	free((*Q)->base);
	free(*Q);
	*Q = NULL;
}



/*
an implementation of sqqueue in chapter 3
presented by xdxu@ustc.edu.cn
*/

#ifndef _QUEUE_H_
#define _QUEUE_H_

typedef struct Queue {
	int *base;
	int front;
	int rear;
	int capacity;
}SqQueue;

// create a queue
SqQueue* createQueue(int capacity);

// check if the queue is empty
int  isEmptyQueue(SqQueue *Q);

// tranverse the queue
void showQueue(SqQueue *Q);

// push an element into the queue
int EnQueue(SqQueue *Q, int data);

// pop an element out of the queue
int DeQueue(SqQueue *Q, int *data);

// destroy an existing queue
void destroyQueue(SqQueue **Q);

#endif
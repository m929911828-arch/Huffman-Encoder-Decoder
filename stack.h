/*
an implementation of sqstack in chapter 3
presented by xdxu@ustc.edu.cn
*/

#ifndef _STACK_H_
#define _STACK_H_

typedef struct Stack {
	int *base;
	int top;
	int capacity;
}SqStack;

// create an empty stack
SqStack* createStack(int capacity);

// check if the stack is empty
int isEmptyStack(SqStack *S);

// check if the stack is full
int isFullStack(SqStack *S);

// tranverse a stack
void showStack(SqStack *S);

// get the element at the top of the stack
int getTop(SqStack *S, int *data);

// push an element into the stack
int push(SqStack *S, int data);

// pop an element out of the stack
int pop(SqStack *S, int *data);

// destroy an existing stack
void destroyStack(SqStack **S);

int StackLength(SqStack *S);

#endif
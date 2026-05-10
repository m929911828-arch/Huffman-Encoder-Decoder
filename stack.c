/*
an implementation of sqstack in chapter 3
presented by xdxu@ustc.edu.cn
*/

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

// create an empty stack
SqStack* createStack(int capacity) {
	SqStack *S;
	S = (SqStack *)malloc(sizeof(SqStack));
	S->base = (int *)malloc(sizeof(int)*capacity);
	S->top = -1;//empty stack
	S->capacity = capacity;
	return S;
}

// check if the stack is empty
int isEmptyStack(SqStack *S) {
	if (S==NULL || S->top!=-1) return 0;
	return 1;
}

// check if the stack is full
int isFullStack(SqStack *S) {
	if (S==NULL || S->top!=S->capacity-1) return 0;
	return 1;
}

// tranverse a stack
void showStack(SqStack *S) {
	int i;
	if (S==NULL || S->top==-1) {
		printf("stack does not exist or is empty.\n");
		return;
	}
	for (i=0; i<=S->top; i++) {
		printf("%d ", S->base[i]);
	}
	printf("\n");
}

// get the element at the top of the stack
int getTop(SqStack *S, int *data) {
	if (S==NULL || S->top==-1) return -1;
	*data = S->base[S->top];
	return 0;
}

// push an element into the stack
int push(SqStack *S, int data) {
	if (S==NULL || S->top==S->capacity-1) return -1;
	S->base[++S->top] = data;
	return 0;
}

// pop an element out of the stack
int pop(SqStack *S, int *data) {
	if (S==NULL || S->top==-1) return -1;
	*data = S->base[S->top--];
	return 0;
}

// destroy an existing stack
void destroyStack(SqStack **S) {
	if (*S==NULL) return;
	free((*S)->base);
	free(*S);
	*S = NULL;
}

int StackLength(SqStack *S) {
	if (S==NULL) return -1;
	return S->top+1;
}
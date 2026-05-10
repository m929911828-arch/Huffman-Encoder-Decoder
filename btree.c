/*
an implementation of binary tree in chapter 6
presented by xdxu@ustc.edu.cn
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "btree.h"
#include "stack.h"
#include "queue.h"


// create a binary tree via preorder sequence
BTree createTree(int *arr, int arrSize, int *n /*Treenode parent */) {
	struct TreeNode *p;//1st parent is NULL

	if (*n==arrSize) return NULL;
	if (arr[*n] == OUTLIER) {
		*n += 1;
		return NULL;
	}

	p = malloc(sizeof(struct TreeNode));
	p->data = arr[*n];
	//p->parent = parent;
	*n += 1;
	p->left = createTree(arr, arrSize, n/*,p*/);
	p->right = createTree(arr, arrSize, n/*,p*/);
	return p;
}

/*how to create a tread tree?
In struct: add "int ltag,rtag;"
In createTree: add two lines:"p->ltag = 0; p->rtag = 0;"before line p->left...
In main function: add one line:"InOrderTreading(root)"after line createTree.
*/

// create a binary tree via postorder sequence
BTree createTreeByPostSeq(int *arr, int arrSize, int *n) {
	TreeNode *p;
	SqStack *S;
	int i = 0, data;	
	S = createStack(arrSize);
	while (i<arrSize) {
		if (arr[i] == OUTLIER) push(S, (int)NULL);
		else {
			p = (TreeNode *)malloc(sizeof(TreeNode));
			p->data = arr[i];
			pop(S, &data);
			p->right = (TreeNode *)data;
			pop(S, &data);
			p->left = (TreeNode *)data;
			push(S, (int)p);
		}
		i++;
	}
	pop(S, &data);
	p = (TreeNode *)data;
	destroyStack(&S);
	return p;
}

// create a binary tree using two sequences(pre- & in-)
BTree create(int *pre, int *ind, int low1, int high1, int low2, int high2) {
	TreeNode *p;
	int m;
	if (low1 > high1) return NULL;
	p = (TreeNode *)malloc(sizeof(TreeNode));
	p->data = pre[low1];
	m = low2;
	while (pre[low1] != ind[m]) m++;
	p->left = create(pre, ind, low1+1, low1+m-low2, low2, m-1);
	p->right = create(pre, ind, low1+m-low2+1, high1, m+1, high2);
	return p;
}

// a preorder traverse of the binary tree
void preorder(BTree bt) {
	if (bt==NULL) return;
	printf("%d ", bt->data);
	preorder(bt->left);
	preorder(bt->right);
}

// an inorder traverse of the binary tree
void inorder(BTree bt) {
	if (bt==NULL) return;
	inorder(bt->left);
	printf("%d ", bt->data);
	inorder(bt->right);
}

// a postorder traverse of the binary tree
void postorder(BTree bt) {
	if (bt==NULL) return;
	postorder(bt->left);
	postorder(bt->right);
	printf("%d ", bt->data);
}

// a layerorder traverse of the binary tree
void layerorder(BTree bt) {
	SqQueue *Q;
	int p;
	TreeNode *q;
	if (bt==NULL) return;  
	Q = createQueue(100);
	EnQueue(Q, (int)bt);
	while (!isEmptyQueue(Q)) {
		DeQueue(Q, &p);
		q = (TreeNode *)p;
		printf("%d ", q->data);
		if (q->left != NULL) EnQueue(Q, (int)(q->left));
		if (q->right != NULL) EnQueue(Q, (int)(q->right));
	}
	destroyQueue(&Q);
}

// count the depth of a tree
int getTreeDepth(BTree root) {
    int left, right;
    if (root == NULL) return 0;
    left = getTreeDepth(root->left);
    right = getTreeDepth(root->right);
    if (left > right) return left+1;
    else return right+1; 
}

// count the number of tree nodes
int getNumTreeNodes(BTree root) {
    int nl=0,nr=0; //left, right;
    if (root == NULL) return 0;
	nl = getNumTreeNodes(root->left);
	nr = getNumTreeNodes(root->right);
    return nl + nr + 1;
}
 
// count the number of leaf nodes
int getTreeLeaves(BTree bt) {
	int nl, nr;
	if (bt==NULL) return 0;
	if (bt->left==NULL && bt->right==NULL) return 1;
	nl = getTreeLeaves(bt->left);
	nr = getTreeLeaves(bt->right);
	return nl+nr;
}

// find if there exists a node with given element
TreeNode* searchTreeNode(BTree bt, int data) {
	TreeNode *p;
	if (bt==NULL) return NULL;
	if (bt->data==data) return bt;
	p = searchTreeNode(bt->left, data);
	if (p!=NULL) return p;
	return searchTreeNode(bt->right, data);
}

// get the parent of a tree node
TreeNode* getParent(BTree bt, TreeNode *x) {
	TreeNode *p;
	if (bt==NULL) return NULL;
	if (bt->left==x || bt->right==x) return bt;
	p = getParent(bt->left, x);
	if (p!=NULL) return p;
	return getParent(bt->right, x);
}

// destroy an existing tree
void destroyTree(BTree *bt) {
	if (*bt==NULL) return;
	destroyTree(&(*bt)->left);
	destroyTree(&(*bt)->right);
	free(*bt);
	*bt = NULL;
}

// copy a tree
void copyBTree(BTree S, BTree *T) {
	TreeNode *left, *right;
	if (S==NULL) *T = NULL;
	else {
		copyBTree(S->left, &left);
		copyBTree(S->right, &right);
		*T = (TreeNode *)malloc(sizeof(TreeNode));
		(*T)->data = S->data;
		(*T)->left = left;
		(*T)->right = right;
	}
}

// print the route between a root and a leaf
void printRoute(BTree bt, SqStack *s) {
	int data;
	if (bt==NULL) return;
	push(s, bt->data);
	if (bt->left==NULL && bt->right==NULL) showStack(s);
	else {
		printRoute(bt->left, s);
		printRoute(bt->right, s);
	}
	pop(s, &data);
}

// build an expression tree
BTree buildExpreTree(char *postfix) {
	SqStack *S;
	TreeNode *node;
	int T1, T2;
	int i;
	S = createStack(100);
	for (i=0; postfix[i]!='\0'; i++) {
		if (postfix[i]>='a' && postfix[i]<='z') {
			node = (TreeNode *)malloc(sizeof(TreeNode));
			node->data = (int)postfix[i];
			node->left = NULL;
			node->right = NULL;
			push(S, (int)node);
		} else {
			node = (TreeNode *)malloc(sizeof(TreeNode));
			node->data = (int)postfix[i];
			pop(S, &T1);
			pop(S, &T2);
			node->left = (TreeNode *)T2;
			node->right = (TreeNode *)T1;
			push(S, (int)node);
		}
	}
	pop(S, &T1);
	destroyStack(&S);
	return (TreeNode *)T1;
}

// print all nodes in the tree from a horizonal view
void showHorizonView(BTree bt) {
	static int level = -1;
	int i;
	if (bt == NULL) return;
	level++;
	showHorizonView(bt->right);
	for (i=0; i<level; i++) printf("\t");
	printf("%2d\n", bt->data);
	showHorizonView(bt->left);
	level--;
}

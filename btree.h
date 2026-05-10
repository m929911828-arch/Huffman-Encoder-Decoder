/*
an implementation of binary tree in chapter 6
presented by xdxu@ustc.edu.cn
*/

#ifndef _BTREE_H_
#define _BTREE_H_

#include "stack.h"
#define OUTLIER 2147483647

 typedef struct TreeNode {
     int data;
     struct TreeNode *left;
     struct TreeNode *right;
}TreeNode, *BTree;

// create a binary tree
BTree createTree(int *arr, int arrSize, int *n);

// create a binary tree via postorder sequence
BTree createTreeByPostSeq(int *arr, int arrSize, int *n);

// create a binary tree using two sequences
BTree create(int *pre, int *ind, int low1, int high1, int low2, int high2);

// a preorder traverse of the binary tree
void preorder(BTree bt);

// a inorder traverse of the binary tree
void inorder(BTree bt);

// a postorder traverse of the binary tree
void postorder(BTree bt);

// a layerorder traverse of the binary tree
void layerorder(BTree bt);

// count the depth of a tree
int getTreeDepth(BTree root);

// count the number of tree nodes
int getNumTreeNodes(BTree root);

// count the number of leaf nodes
int getTreeLeaves(BTree bt);

// find if there exists a node with given element
TreeNode* searchTreeNode(BTree bt, int data);

// get the parent of a tree node
TreeNode* getParent(BTree bt, TreeNode *x);

// destroy an existing tree
void destroyTree(BTree *bt);

// copy a tree
void copyBTree(BTree S, BTree *T);

// print the route between a root and a leaf
void printRoute(BTree bt, SqStack *s);

// build an expression tree
BTree buildExpreTree(char *postfix);

// print all nodes in the tree from a horizonal view
void showHorizonView(BTree bt);


#endif
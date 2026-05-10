
#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include "stack.h"

typedef struct {
    char ch;
    char* code;
} HuffmanCodeEntry;

typedef HuffmanCodeEntry* HuffmanCode;

typedef struct
{
    char ch;
    unsigned int weight;
    int parent, lchild, rchild;
} HTNode;

typedef struct
{
    HTNode *Htree;
    int root;
} HuffmanTree;


void CreateHuffman(HuffmanTree *T, int *w, int n, char* chars);

void select(HTNode *HT, int end, int *s);

void HuffmanCoding(HuffmanTree HT,HuffmanCode *HC,int n);

void Coding(HuffmanTree T, int i, SqStack *S, HuffmanCodeEntry *HC);

void PrintHuffmanTree(HuffmanTree HT, const char *filename);

void Decoding(HuffmanTree T, char *bits, HuffmanCodeEntry *HC, char *ch);

void Encoding(HuffmanTree HT, HuffmanCode *HC, int n, char *result);

#endif
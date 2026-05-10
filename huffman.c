#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"
#include "stack.h"
#include "huffman.h"

void select(HTNode *HT, int end, int *s)
{
    if (!HT || end < 0 || !s)
        return;
    int j, count = -1;
    unsigned int mini = 0;
    for (j = 0; j <= end; j++)
    {
        if (HT[j].parent != -1)
            continue;
        if (count == -1 || HT[j].weight < mini)
        {
            mini = HT[j].weight;
            count = j;
        }
    }
    *s = count;
}
void CreateHuffman(HuffmanTree *T, int *w, int n, char *chars) // w为权值，n为叶子数
{
    int m = n * 2 - 1;
    int i, s1, s2;
    T->Htree = malloc(m * sizeof(HTNode));
    HTNode *HT = T->Htree;
    for (i = 0; i < n; i++)
    {
        HT[i].ch = chars[i];
        HT[i].weight = w[i];
        HT[i].parent = -1;
        HT[i].lchild = -1;
        HT[i].rchild = -1;
    } // 初始化
    for (i = n; i < m; i++)
    {
        HT[i].ch = '#';
        HT[i].weight = -1;
        HT[i].parent = -1;
        HT[i].lchild = -1;
        HT[i].rchild = -1;
    } // 初始化
    for (i = n; i < m; i++)
    {
        select(HT, i - 1, &s1); // 在T.HTree[0..i-1]中
        // 选parent=-1的最小权值根
        HT[s1].parent = i;
        select(HT, i - 1, &s2);
        HT[s2].parent = i;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
    }
    T->root = m - 1;
} // CreateHuffman

void HuffmanCoding(HuffmanTree HT, HuffmanCode *HC, int n)
{
    // 先序遍历huffman树, 将每个字符的huffman编码存入HC
    // n是huffman树的叶子结点数
    *HC = (HuffmanCodeEntry *)malloc(n * sizeof(HuffmanCodeEntry));
    SqStack *S = createStack(30);
    // 初始化一个空栈S， S中保留遍历时收集的0码和1码

    Coding(HT, HT.root, S, *HC);
}

void Coding(HuffmanTree T, int i, SqStack *S, HuffmanCodeEntry *HC)
{ // 先序遍历huffman树，获取每个字符的huffman编码
    char ch;
    if (T.Htree[i].lchild == -1 && T.Htree[i].rchild == -1)
    {
        // i是树叶
        push(S, '\0'); // 字符串结束标志‘\0’进栈
        HC[i].ch = T.Htree[i].ch;
        HC[i].code = malloc(StackLength(S) * sizeof(char));
        for (int m = 0; m < StackLength(S); m++)
        {
            HC[i].code[m] = S->base[m];
        }
        pop(S, &ch); // 出栈   1111111
    }
    else
    {
        push(S, '0');                        // 向左转前‘0’进栈
        Coding(T, T.Htree[i].lchild, S, HC); // 遍历左子树
        pop(S, &ch);
        push(S, '1');                        // 向右转前‘1’进栈
        Coding(T, T.Htree[i].rchild, S, HC); // 遍历右子树    
        pop(S, &ch);                   
    }
   // pop(S, &ch); // 一棵子树遍历结束，出栈  -- removed
} // Coding

static void PrintHuffmanNode(const HuffmanTree HT, int idx, int depth, FILE *f)
{
    if (idx == -1)
        return;

    PrintHuffmanNode(HT, HT.Htree[idx].rchild, depth + 1, f);

    for (int k = 0; k < depth; k++)
        fprintf(f, "    ");

    if (HT.Htree[idx].lchild == -1 && HT.Htree[idx].rchild == -1)
        fprintf(f, "%c(%u)\n", HT.Htree[idx].ch, HT.Htree[idx].weight);
    else
        fprintf(f, "#(%u)\n", HT.Htree[idx].weight);

    PrintHuffmanNode(HT, HT.Htree[idx].lchild, depth + 1, f);
}

void PrintHuffmanTree(HuffmanTree HT, const char *filename)
{
    FILE *f = fopen(filename, "w");
    if (f == NULL)
    {
        printf("open file error, quit!\n");
        return;
    }

    PrintHuffmanNode(HT, HT.root, 0, f);
    fclose(f);

    f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("open file error, quit!\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), f) != NULL)
    {
        printf("%s", line);
    }

    fclose(f);
}

void Decoding(HuffmanTree T, char *bits, HuffmanCodeEntry *HC, char *ch)
{
    // Huffman解码， bits是比特流串， chars存放字符集字符
    char *p = bits;
    int i = T.root;
    int idx = 0;

    while (*p != '\0')
    {
        if (*p == '0')
            i = T.Htree[i].lchild; // 逢0左拐
        else
            i = T.Htree[i].rchild; // 逢1右拐

        if (T.Htree[i].lchild == -1 && T.Htree[i].rchild == -1)
        {
            ch[idx++] = T.Htree[i].ch;
            printf("%c", T.Htree[i].ch);
            i = T.root; // 回到树根
        }
        p++;
    }
    ch[idx] = '\0';
printf("\n");
    if (i != T.root)
        printf("Error\n");
} // Decoding

void Encoding(HuffmanTree HT, HuffmanCode *HC, int n, char *result)
{
    FILE *fp = fopen("ToBeTran.txt", "r");
    char str[100] = {0}, temp[100] = {0};

    if (fp == NULL)
    {
        printf("open file error, quit!\n");
        return;
    }
    fgets(temp, 100, fp);
    int len = strlen(temp);
    for (int m = 0; m < len; m++)
    {
        if (isalpha(temp[m]))
        {
            str[strlen(str)] = temp[m];
        }
    }
    str[strlen(str)] = '\0';
    // isalpha  put in str
    printf("Text to be encoded: %s %s %d \n", temp, str, len); // THIS PROGRAM IS MY FAVORITE
    HuffmanCoding(HT, HC, n);
    for (int m = 0; m < n; m++)
    {
        printf("char: %c, code: %s\n", (*HC)[m].ch, (*HC)[m].code);
    }

    result[0] = '\0';
    int i, j;
    for (i = 0; str[i] != '\0'; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (str[i] == (*HC)[j].ch)
            {
                strcat(result, (*HC)[j].code);
                break;
            }
        }
    }
    printf("Encoded text: %s\n", result);
    fclose(fp);
}

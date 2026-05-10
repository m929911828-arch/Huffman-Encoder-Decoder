#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "btree.h"
#include "stack.h"
#include "huffman.h"

void Encoding(HuffmanTree HT, HuffmanCode *HC, int n)
{
    FILE *fp = fopen("D:\\ToBeTran.txt", "r");
    char str[100] = {0},temp[100] = {0};
    char result[300] = {0};
    if (fp == NULL)
    {
        printf("open file error, quit!\n");
        return;
    }
    fgets(temp, 100, fp);
    int len = strlen(temp);
    for(int m = 0;m < len;m++){ 
        if(isalpha(temp[m]))
        {
            str[strlen(str)] = temp[m];
        }
    }
    str[len] = '\0';
    //isalpha  put in str
    printf("Text to be encoded: %s %s %d \n", temp,str,len);//THIS PROGRAM IS MY FAVORITE
    HuffmanCoding(HT, HC, n);
    for(int m = 0;m < n;m++){
        printf("char: %c, code: %s\n", (*HC)[m].ch, (*HC)[m].code);
    }
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

int main(void)
{
    HuffmanTree *HT = NULL;
    HT = malloc(sizeof(HuffmanTree));
    HT->Htree = NULL;
    HuffmanCode HC = NULL;
    printf("-----Huffman Coding & Decoding Tool-----\n");
    printf("------------1.Initialize(I)-------------\n");
    printf("------------2.Encode(E)-----------------\n");
    printf("------------3.Decode(D)-----------------\n");
    printf("------------4.Print code(P)-------------\n");
    printf("------------5.Print Huffman Tree(T)-----\n");
    printf("------------6.Quit(q)-------------------\n");
    printf("Please enter a command:\n");
    char cmd;
    while(1) {
        scanf("%c", &cmd);
        switch (cmd)
        {
        case 'I':
            for (j = 0; j < i * 2 - 1; j++)
            {
                fprintf(fout, "%c,%u,%d,%d,%d\n",
                        HT->Htree[j].ch,
                        HT->Htree[j].weight,
                        HT->Htree[j].parent,
                        HT->Htree[j].lchild,
                        HT->Htree[j].rchild);
            }

            fclose(fout);
            printf("success!");
            break;
        case 'E':
            Encoding(*HT, &HC, i);
            break;
        case 'D':
            break;
        case 'P':
            if (HC == NULL)
            {
                printf("Please encode first!\n");
                break;
            }
            for (j = 0; j < i; j++)
            {
                printf("char: %c, code: %s\n", HC[j].ch, HC[j].code);
            }
            break;
        case 'T':
            break;
        case 'q':
        case 'Q':
            goto end;
        default:
            break;
        }
    }
    end:

    return 0;
}
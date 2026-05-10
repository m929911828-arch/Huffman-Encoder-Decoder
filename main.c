#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "btree.h"
#include "stack.h"
#include "huffman.h"


int main(void)
{
    HuffmanTree *HT = NULL;
    char chars[30] = {0};
    int w[30] = {0};
    HT = malloc(sizeof(HuffmanTree));
    HT->Htree = NULL;
    HuffmanCode HC = NULL;
    FILE *fp = fopen("D:\\CharSet.txt", "r");
    if (fp == NULL)
    {
        printf("open file error, quit!\n");
        return -1;
    }
    fscanf(fp, "%*[^\n]\n"); // 跳过整行

    int i = 0;
    while (fscanf(fp, " %c %d", &chars[i], &w[i]) == 2)
    {
        i++;
    }
    CreateHuffman(HT, w, i, chars);
    printf("test i = %d\n", i);
    fclose(fp);
    printf("-----Huffman Coding & Decoding Tool-----\n");
    printf("------------1.Initialize(I)-------------\n");
    printf("------------2.Encode(E)-----------------\n");
    printf("------------3.Decode(D)-----------------\n");
    printf("------------4.Print code(P)-------------\n");
    printf("------------5.Print Huffman Tree(T)-----\n");
    printf("------------6.Quit(q)-------------------\n");
    printf("Please enter a command:\n");
    char cmd;
    char result[300] = {0};
  
    while (1)
    {
        scanf(" %c", &cmd);
        switch (cmd)
        {
        case 'I':
        {
         
            FILE *fout = fopen("hfmtree.txt", "w");
            if (fout == NULL)
            {
                printf("open file error, quit!\n");
                return -1;
            }
            for (int j = 0; j < i * 2 - 1; j++)
            {
                fprintf(fout, "%c,%u,%d,%d,%d\n",
                        HT->Htree[j].ch,
                        HT->Htree[j].weight,
                        HT->Htree[j].parent,
                        HT->Htree[j].lchild,
                        HT->Htree[j].rchild);
            }

            fclose(fout);
            printf("Initialize success!");
            break;
        }
        case 'E':
        {
   
            result[0] = '\0';
            Encoding(*HT, &HC, i, result);
         
            FILE *fcode = fopen("CodeFile.txt", "w");
            if (fcode == NULL)
            {
                printf("open file error, quit!\n");
                return -1;
            }

            fprintf(fcode, "%s", result);
     
            fclose(fcode);
            printf("Encoding success!");
            break;
        }
        case 'D':
        {
              char decode[30] = {0};
            // 读文件CodeFile，把里面的编码字符串传给Decoding函数，解码后输出到屏幕上
            FILE *fcodein = fopen("CodeFile.txt", "r");
            if (fcodein == NULL)
            {
                printf("open file error, quit!\n");
                return -1;
            }
            char codestr[300] = {0};
            fgets(codestr, 300, fcodein);
            fclose(fcodein);
            Decoding(*HT, codestr, HC, decode);
            // printf("Decoded text: %s\n", decode);
            FILE *fdecode = fopen("TextFile.txt", "w");
            if (fdecode == NULL)
            {
                printf("open file error, quit!\n");
                return -1;
            }
            fprintf(fdecode, "%s", decode);
            fclose(fdecode);
            printf("Decoding success!");
            break;
        }
        case 'P':
        {
            FILE *fcodeprint = fopen("CodeFile.txt", "r");
            FILE *fdecodeprint = fopen("CodePrint.txt", "r");
            if (fdecodeprint == NULL)
            {
                printf("open file error, quit!\n");
                return -1;
            }
            if (fcodeprint == NULL)
            {
                printf("open file error, quit!\n");
                return -1;
            }
            char codeStr[300] = {0};
            fgets(codeStr, 300, fcodeprint);
            fclose(fcodeprint);
            char decodeStr[300] = {0};
            fprintf(fdecodeprint, "%s", codeStr);
            fclose(fdecodeprint);
            printf("Print code success!");
            break;
        }
        case 'T':
        {
            PrintHuffmanTree(*HT, "TreePrint.txt");
            break;
        }
        case 'q':
            return 0;
            break;
        default:
            printf("Invalid command. Please try again.\n");
            break;
        }
    }

    return 0;
}
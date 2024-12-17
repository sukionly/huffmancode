#ifndef _ENCODE_H
#define _ENCODE_H
#include"counter.h"
#include"queue.h"
#include <stdio.h>

void sort(WeightType *count, CharType *order);
void createHT(HTNode *HT, WeightType *count, CharType *order, int NLeaf);
void getHCode(HTNode *HT, CharType HCode[256][33], int NLeaf);
void encodeFile(FILE *fp, FILE *out, CharType HCode[256][33]);

void sort(  WeightType *count, // char count
            CharType *order // order[i] = i
            ){
    int i, j;
    for (i = 0; i < NChar; i++)
        order[i] = i;
    for (i = 0; i < NChar - 1; i++)
        for (j = i + 1; j < NChar; j++)
            if(count[i] > count[j]){
                WeightType temp = count[i];
                count[i] = count[j];
                count[j] = temp;
                CharType temp2 = order[i];
                order[i] = order[j];
                order[j] = temp2;
            }
}

void createHT(  HTNode *HT, // Huffman Tree
                WeightType *count, // char count
                CharType *order, // order[i] = i
                int NLeaf // number of leaf nodes
                ){
    // initialize the HT
    int i;
    for(i = 0; i < NLeaf * 2 - 1; i++){
        // TODO: fill the ch and weight of the HTNode
        HT[i].ch = '\0';
        HT[i].weight = 0;
        HT[i].idx = i;
        HT[i].parent = -1;
        HT[i].LChild = -1;
        HT[i].RChild = -1;
    }
    // create the HT, use two queues
    Queue Q1, Q2;
    HTNode min1, min2;
    int idx = NLeaf;
    int index = 0;
    InitQueue(&Q1);
    InitQueue(&Q2);
    // TODO: implement the createHT function
    for(i = 0; i < NChar; i++){
        if(count[i] > 0){    
        HT[index].ch = order[i];
        HT[index].weight = count[i];
        InQueue(&Q1, HT[index]);
        index++;
        }
    }
    while(Q1.length > 0 || Q2.length > 1)  
    {
        if(Q1.length && Q2.length){ 
            if(Q1.elem[Q1.front].weight < Q2.elem[Q1.front].weight){
                outQueue(&Q1,&min1);
            }else{
                outQueue(&Q2,&min1);
            }
            if(Q1.elem[Q1.front].weight < Q2.elem[Q1.front].weight){
                outQueue(&Q1,&min2);
            }else{
                outQueue(&Q2,&min2);
            }
        }else if(!Q1.length){
            outQueue(&Q2,&min1);
        }else if(!Q2.length){
            outQueue(&Q1,&min1);
        }
        if(Q1.length && Q2.length){ 
            if(Q1.elem[Q1.front].weight < Q2.elem[Q1.front].weight){
                outQueue(&Q1,&min1);
            }else{
                outQueue(&Q2,&min1);
            }
            if(Q1.elem[Q1.front].weight < Q2.elem[Q1.front].weight){
                outQueue(&Q1,&min2);
            }else{
                outQueue(&Q2,&min2);
            }
        }else if(!Q1.length){
            outQueue(&Q2,&min1);
        }else if(!Q2.length){
            outQueue(&Q1,&min1);
        }    
        HT[idx].weight = min1.weight + min2.weight;
        HT[idx].idx = idx;
        HT[idx].LChild = min1.idx;
        HT[idx].RChild = min2.idx;
        HT[min1.idx].parent = idx;
        HT[min2.idx].parent = idx;
        InQueue(&Q2, HT[idx]);
        idx++;
    }
    
}

void getHCode(HTNode *HT, CharType HCode[256][33], int NLeaf){//左0右1
    int i, j;
    //TODO: get the Huffman code for each character
    for(i = 0; i < NChar; i++){
        j = 1;
        if(HT[i].ch != '\0'){
            int index = i;
            while(HT[index].parent != -1){
                index = HT[index].parent;
                if(HT[index].LChild == HT[i].idx){
                    HCode[HT[i].ch][j] = 0;
                }else{
                    HCode[HT[i].ch][j] = 1;
                }
                j++;
            }
            HCode[HT[i].ch][0] = j;
        }
        int k,tmp;
        for(k = 1;k < j/2+1;k++){
            tmp = HCode[HT[i].ch][k];
            HCode[HT[i].ch][k] = HCode[HT[i].ch][j-k];
            HCode[HT[i].ch][j-k] = tmp;
        }
    }
}

void encodeFile(FILE *fp, 
                FILE *out, 
                CharType HCode[256][33] // [1]存储编码长度, [2] 存储编码
                ){
    if(!fp || !out)
        return;
    CharType buffer = '\0', ch = '\0';
    int count = 0, i;
    //TODO: encode the file
    while((ch = fgetc(fp)) != EOF){
        buffer = ch;
        count = 0;
        for(i = 1;i < HCode[ch][0];i++)
            fputc(HCode[ch][i] + '0', out);
    }
    fputc(EOF, out);
}
#endif
#ifndef _DECODE_H
#define _DECODE_H
#include "init.h"
#include <stdio.h>

void decodeFile(FILE *fp, FILE *out, HTNode *HT, int NLeaf);

void decodeFile(FILE *in, 
                FILE *out, 
                HTNode *HT, // Huffman Tree 
                int NLeaf 
                ){
    // TODO: decode the file
    CharType ch;
    HTNode Current = HT[NLeaf*2-2];
    while((ch = fgetc(in))!= EOF){
        if(ch == '0'){
            Current = HT[Current.LChild];
        }
        else{
            Current = HT[Current.RChild];
        }
        if(Current.ch!= -1){
            fputc(Current.ch, out);
            Current = HT[NLeaf*2-2];
        }
    }
}
#endif
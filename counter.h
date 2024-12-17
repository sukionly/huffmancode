#ifndef _COUNTER_H
#define _COUNTER_H
#include "init.h"
#include <stdio.h>

void parseFile(FILE *fp, WeightType *count, WeightType *FileLength);//parse the file and count the frequency of each character

void parseFile( FILE *fp, // input file 
                WeightType *count, // count the frequency of each character
                WeightType *FileLength // count the length of the file
                ){
    CharType ch;
    //TODO: parse the file and count the frequency of each character
    while((ch = fgetc(fp))!= EOF){
        count[ch]++;
        (*FileLength)++;
    }
}
#endif
#include<stdlib.h>
#include<stdio.h>
#include "word.h"
int main(int argc, char *argv[]){
    char* fileName, line[64];
    FILE *file;
    int num=0;
    fileName=argv[1];
    file=fopen(fileName, "r");
    while(fgets(line, 64, file)!=NULL){
        num+=countWordsInLine(line);
    }
    printf("%d\n", num);
    fclose(file);
}
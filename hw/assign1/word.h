#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

char ** getWordsInLine(char *str){
    int num=0, index=0;
    bool space=false;
    char **words=malloc(sizeof(char*)*1);
    words[0]=malloc(sizeof(char)*1);
    words[0][0]='\0';
    while(str[index]!=EOF&&str[index]!='\0'){
        
        if(str[index]==' '||str[index]=='\t'||str[index]=='\n'){
            space=true;
        }else{
            if(space){
                space=false;
                num++;
            }
        }
        index++;
    }
    return num;
}

int countWordsInLine(char *str){
    int num=0, index=0;
    bool space=false;

    while(str[index]!=EOF&&str[index]!='\0'){
        if(str[index]==' '||str[index]=='\t'||str[index]=='\n'){
            space=true;
        }else{
            if(space){
                space=false;
                num++;
            }
        }
        index++;
    }
    return num;
}
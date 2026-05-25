#include <stdio.h>
#include <string.h>
#include "lexical.h"



int main(int argc,char *argv[])
{
    if(argc != 2)
    {
        printf("ERROR : Invalid input\n Input should be ./a.out <file.c>\n");
        return 0;
    }
    if(strstr(argv[1],".c") == NULL || *(strchr(argv[1],'.') + 2)!='\0')
    {
        printf("ERROR : Input file extension should be .c\n");
        return 0;
    }
    FILE * fp = fopen(argv[1],"r");
    if(fp == NULL)
    {
        printf("ERROR : %s is not exist\n",argv[1]);
        return 0;
    }

    printf("Leximes          Tokens\n");
    lexical_analyse(fp);

    fclose(fp);

}
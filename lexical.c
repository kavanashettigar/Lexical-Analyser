#include "lexical.h"

char operators[] = {'+','-','*','/','=','%','<','>','~','!','&','^','|',','};
char symbols[] = {'(',')','{','}','[',']',':',';'};
char *keywords[] = {"int","char","float","double","signed","unsigned",
    "static","extern","const","volatile","auto","register","void","struct",
    "enum","union","short","long","typedef","if","else","switch","for","while","do",
    "case","sizeof","goto","continue","break","return","default"};
    
void lexical_analyse(FILE *fp)
{
    char buffer[100];
    int ch;
    int i=0;
    while((ch = fgetc(fp))!= EOF)
    {
        if(ch == '#')
        {
            i = 0;
            buffer[i++] = ch;
            while(((ch = fgetc(fp))!= EOF) && ch !='\n' && ch != '\r')
            {
                buffer[i++] = ch;
            }
            
            buffer[i] = '\0';
            printf("%s -> preproccesor directive\n",buffer);
            
        }
        else if(isalpha(ch) || ch == '_')
        {
             i = 0;
            buffer[i++] = ch;
            while(((ch = fgetc(fp))!= EOF) && (isalnum(ch) || ch == '_'))
            {
                buffer[i++] = ch;
            }
            buffer[i] = '\0';
            key_identifier_handler(buffer);
            if(ch != EOF)
            {
                fseek(fp,-1,SEEK_CUR);
            }
           

        }
        else if(isdigit(ch))
        {
            i = 0;
            buffer[i++] = ch;
            while(((ch = fgetc(fp))!= EOF) && isdigit(ch) )
            {
                buffer[i++] = ch;
            }
            buffer[i] = '\0';
            printf("%s -> numeric constant\n",buffer);
            if(ch != EOF)
            {
                fseek(fp,-1,SEEK_CUR);
            }
            
        }
        else if(ch == '/')
        {
            if((ch = fgetc(fp)) == '/')
            {
                while( (ch = fgetc(fp))!= EOF && (ch != '\n'));  
            }
            else if(ch == '*')
            {
                char prev = 0;
                while( (ch = fgetc(fp))!= EOF)
                {
                    if(prev == '*' && ch == '/')
                    break;

                    prev = ch;

                }
            }
            else
            {
                fseek(fp,-1,SEEK_CUR);
                printf("/ -> operator\n");
            }

            
        }

        else if(isoperators(ch))
        {
            i = 0;
            buffer[i++] = ch;
            if((ch = fgetc(fp))!= EOF && isoperators(ch)) 
            {
                buffer[i++] = ch;
            }
            else 
            {
                fseek(fp,-1,SEEK_CUR);
            }
            buffer[i] = '\0';
            printf("%s -> operator\n",buffer);
            
        }
        else if(issymbols(ch))
        {
            if(ch == '(')
            printf("%c -> open bracket\n",ch);

            else if(ch == ')')
            printf("%c -> close bracket\n",ch);

            else if(ch == '{')
            printf("%c -> open curly bracket\n",ch);

            else if(ch == '}')
            printf("%c -> close curly bracket\n",ch);

            else if(ch == '[')
            printf("%c -> open square bracket\n",ch);

            else if(ch == ']')
            printf("%c -> close square bracket\n",ch);

            else if(ch == ':')
            printf("%c -> colon symbol\n",ch);

            else if(ch == ';')
            printf("%c -> end of statementt\n",ch);

        }
        else if(ch == '"')
        {
            i = 0;
            buffer[i++] = ch; 
            while(((ch = fgetc(fp))!= EOF) && ch != '"')
            {
                buffer[i++] = ch;
            }
            buffer[i++] = '"';
            buffer[i] = '\0';
            printf("%s -> string literals\n",buffer);
            if(ch != EOF && ch !='"' )
            {
                fseek(fp,-1,SEEK_CUR);
            }
            
        }
        else if(ch == '\'')
        {
            i = 0;
            buffer[i++] = ch; 
            while(((ch = fgetc(fp))!= EOF) && ch != '\'')
            {
                buffer[i++] = ch;
            }
            buffer[i++] = '\'';
            buffer[i] = '\0';
            printf("%s -> character literal\n",buffer);
            if(ch != EOF && ch !='\'' )
            {
                fseek(fp,-1,SEEK_CUR);
            }
            
        }


    }

}

void key_identifier_handler(char *buffer)
{
    int flag = 0;
    for(int i=0;i<32;i++)
    {
        if(strcmp(keywords[i],buffer) == 0)
        {
            flag = 1;
            break;
        }
    }
    if(flag == 1)
    {
        printf("%s -> keyword\n",buffer);
    }
    else
    printf("%s -> identifier\n",buffer);
    
}
int isoperators(char ch)
{
    for(int i=0;i<14;i++)
    {
        if(operators[i] == ch)
        {
            return 1;
        }
    }
    return 0;
}

int issymbols(char ch)
{
    for(int i=0;i<8;i++)
    {
        if(symbols[i] == ch)
        {
            return 1;
        }
    }
    return 0;
}
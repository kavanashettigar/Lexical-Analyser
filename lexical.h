#include <stdio.h>
#include <string.h>
#include <ctype.h>

void lexical_analyse(FILE *fp);
void key_identifier_handler(char *buffer);
int isoperators(char ch);
int issymbols(char ch);
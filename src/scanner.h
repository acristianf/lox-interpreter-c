#ifndef SCANNER_H
#define SCANNER_H

#include <string.h>
#include <malloc.h>

typedef struct Scanner Scanner;
typedef struct Token Token;

void initScanner(char *source);
// Return number of tokens scanned
void scanTokens(Token **tokens);

struct Scanner {
    char * start;
    char *current;
    unsigned int line;
    unsigned int sourceLength;
    unsigned int nTokens;
};

#endif

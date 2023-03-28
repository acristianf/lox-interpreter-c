#ifndef SCANNER_H
#define SCANNER_H

#include <string.h>
#include <malloc.h>
#include <string.h>

typedef struct Scanner Scanner;
typedef struct Token Token;

Scanner *createScanner(const char *source);
void destroyScanner(Scanner *scanner);
void scanTokens(Scanner *scanner, Token **tokens);

struct Scanner {
  char *start;
  char *current;
  unsigned int line;
  unsigned int sourceLength;
  unsigned int nTokens;
    char *source;
};

#endif

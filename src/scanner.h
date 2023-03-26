#include <string.h>
#include <malloc.h>

typedef struct Scanner Scanner;
typedef struct Token Token;

Scanner *createScanner(const char *source);
void destroyScanner(Scanner *scanner);
void scanTokens(Scanner *scanner, Token **tokens);

struct Scanner {
    char *source;
};

#include "scanner.h"

Scanner *createScanner(const char* source) {
    Scanner *scanner = (Scanner *)malloc(sizeof(Scanner)); 
    size_t l = strlen(source);
    scanner->source = (char *)malloc(sizeof(char)*l);
    for(int i = 0; i < l; i++) {scanner->source[i] = source[i];}
    return scanner;
};

void destroyScanner(Scanner *scanner) {
    if (scanner->source) {
	free(scanner->source);
    }
    free(scanner);
}

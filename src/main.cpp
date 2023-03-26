#include <stdio.h>
#include <stdlib.h>

#include "lox.cpp"

int main(int argc, char **argv) {

    if (argc > 2) {
	printf("Usage: clox [script]");
	// Using sysexits standard codes
	exit(64);
    } else if(argc == 2) {
	runFile(argv[1]);
    } else {
	runPrompt();
    }

    return 0;
}

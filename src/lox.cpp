#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <malloc.h>

#include "scanner.cpp"

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

static void run(const char *source) {
    Scanner *scanner = createScanner(source);
    // TODO: Implement tokens
    Token *tokens[512];
    scanTokens(scanner, tokens);
    destroyScanner(scanner);
}

void runFile(const char *filePath) {

    // READ FILE CONTENTS INTO fileBuffer
    FILE *fp;
    fopen_s(&fp, filePath, "rb");
    if(fp == NULL) {
	perror("Error opening file.");
	exit(74);
    }

    fseek(fp, 0, SEEK_END);
    size_t fileSize = ftell(fp);
    rewind(fp);

    char *sourceBuffer = (char *)malloc(sizeof(char)*(fileSize+1));
    if (sourceBuffer == NULL) {
	perror("Error allocating memory for file buffer.");
	exit(74);
    }
    fread_s(sourceBuffer, fileSize, sizeof(char), fileSize/sizeof(char), fp);
    sourceBuffer[fileSize] = '\0';
    fclose(fp);

    run(sourceBuffer);

    free(sourceBuffer);

}

// TODO: Implement this to read one line at a time
// and then execute it.
void runPrompt() {
    printf("Type script name: ");
    char buf[64];
    scanf_s("%63s", buf, (uint32_t)ARRAY_SIZE(buf));
    runFile(buf);
}

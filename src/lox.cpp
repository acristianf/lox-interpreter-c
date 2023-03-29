#include <malloc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "scanner.cpp"

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

static void run(char *source) {
  initKeywords();
  initScanner(source);
  Token tokens[512] = {};
  scanTokens(tokens);
}

void runFile(const char *filePath) {

  // READ FILE CONTENTS INTO fileBuffer
  FILE *fp;
  fopen_s(&fp, filePath, "rb");
  if (fp == NULL) {
    perror("Error opening file.");
    exit(74);
  }

  fseek(fp, 0, SEEK_END);
  size_t fileSize = ftell(fp);
  rewind(fp);

  char *sourceBuffer = (char *)malloc(sizeof(char) * (fileSize + 1));
  if (sourceBuffer == NULL) {
    perror("Error allocating memory for file buffer.");
    exit(74);
  }
  fread_s(sourceBuffer, fileSize, sizeof(char), fileSize / sizeof(char), fp);
  sourceBuffer[fileSize] = '\0';
  fclose(fp);

  run(sourceBuffer);

  free(sourceBuffer);

  // Check for errors
  if (GlobalHadError)
    exit(65);
}

// TODO: Implement this to read one line at a time
// and then execute it.
void runPrompt() {
  puts(" --- Interactive prompt --- ");
  char line[256];
  while (true) {
    printf(">> ");
    fgets(line, 256, stdin);
    run(line);
    GlobalHadError = false;
  }
}

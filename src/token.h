#ifndef TOKEN_H
#define TOKEN_H

#include "token_type.h"

typedef struct Token Token;

Token createToken(TokenType tpye);

// NOTE: REFERENCE FOR IMPLEMENTATION IN C
// https://github.com/zlliang/clox/blob/main/src/scanner.c
struct Token {
  TokenType type;
  char *start;
  unsigned int length;
  unsigned int line;
};

#endif

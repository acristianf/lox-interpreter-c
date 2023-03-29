#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

#define KEYWORD_TABLE_SIZE 97

#include <string.h>

enum TokenType {
  // Single-character tokens
  LEFT_PAREN,
  RIGHT_PAREN,
  LEFT_BRACE,
  RIGHT_BRACE,
  COMMA,
  DOT,
  MINUS,
  PLUS,
  SEMICOLON,
  SLASH,
  STAR,

  // One or two character tokens
  EXCL,
  EXCL_EQUAL,
  EQUAL,
  EQUAL_EQUAL,
  GREATER,
  GREATER_EQUAL,
  LESS,
  LESS_EQUAL,

  // Literals
  IDENTIFIER,
  STRING,
  NUMBER,

  // KEYWORDS
  AND,
  CLASS,
  ELSE,
  FALSE,
  TRUE,
  FUN,
  FOR,
  IF,
  NIL,
  OR,
  PRINT,
  RETURN,
  SUPER,
  THIS,
  VAR,
  WHILE,

  // ERRORS
  ERROR_TOKEN,

  // EOF
  EOF_
};

// KEYWORDS HASH TABLE, USES LINEAR PROBING

struct KeywordNode {
  const char *keyword;
  TokenType type;
};

static struct KeywordNode KEYWORDTABLE[KEYWORD_TABLE_SIZE];

inline static int hash(const char *key) {
  int v = 0;
  while (*key) {
    v += *key;
    key++;
  }
  return v % KEYWORD_TABLE_SIZE;
}

inline static void set(const char *key, TokenType type) {
  int h = hash(key);
  while (strcmp(KEYWORDTABLE[h].keyword, "") != NULL) {
    h++;
    if (h >= KEYWORD_TABLE_SIZE) {
      h = 0;
    }
  }
  KEYWORDTABLE[h] = {key, type};
}

static void initKeywords() {
  KeywordNode nullNode;
  nullNode.keyword = "";
  nullNode.type = LEFT_PAREN;
  for (int i = 0; i < KEYWORD_TABLE_SIZE; i++) {
    KEYWORDTABLE[i] = nullNode;
  }
  set("and", AND);
  set("class", CLASS);
  set("else", ELSE);
  set("false", FALSE);
  set("for", FOR);
  set("fun", FUN);
  set("if", IF);
  set("nil", NIL);
  set("or", OR);
  set("print", PRINT);
  set("return", RETURN);
  set("super", SUPER);
  set("this", THIS);
  set("true", TRUE);
  set("var", VAR);
  set("while", WHILE);
};

inline TokenType getKeywordType(const char *key) {
  int h = hash(key);
  while (strcmp(KEYWORDTABLE[h].keyword, key) != NULL) {
    h++;
  }
  return KEYWORDTABLE[h].type;
}

#endif

#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "scanner.h"
#include "token.h"

Scanner scanner;

static Token createToken(TokenType type) {
  Token token;

  token.start = scanner.start;
  token.type = type;
  token.length = (unsigned int)(scanner.current - scanner.start);
  token.line = scanner.line;

  return token;
};

void initScanner(char *source) {
  scanner.current = source;
  scanner.start = source;
  scanner.line = 1;
};

static char advance() {
  char c = *scanner.current;
  scanner.current++;
  return c;
}

static bool isDigit(char c) { return (c >= '0' && c <= '9'); }

static Token makeToken(TokenType tokenType) {

  Token token = createToken(tokenType);
  return token;
}

static void addToken(Token token, Token tokens[]) {
  tokens[scanner.nTokens] = token;
  scanner.nTokens++;
}

static bool isAtEnd() { return *scanner.current == '\0'; }

static char peek() {
  if (isAtEnd())
    return '\0';
  return *scanner.current;
}

static char peekNext() {
  if (isAtEnd())
    return '\0';
  return scanner.current[1];
}

static bool match(char expected) {
  if (isAtEnd())
    return false;
  if (*scanner.current != expected)
    return false;
  scanner.current++;
  return true;
}

static void string() {
  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n')
      scanner.line++;
    advance();
  }

  if (isAtEnd()) {
    error(scanner.line, "Unterminated string.");
    return;
  }

  advance();
}

static bool isWhiteSpace(char c) {
  switch (c) {
  case ' ':
  case '\r':
  case '\t':
    return true;
  case '\n': {
    scanner.line++;
    return true;
  }
  case '/':
    if (peekNext() == '/') {
      // A comment goes until the end of the line
      while (peek() != '\n' && !isAtEnd()) {
        advance();
      }
      return true;
    }
  default:
    return false;
  }
}

//static bool isValidBlockComment() {
//  // Test for comment block
//  for (;;) {
//    if (isAtEnd()) {
//      error(scanner.line, "Block comment unterminated.");
//      return false;
//    }
//    if (peek() == '*') {
//      advance();
//      if (match('/'))
//        return true;
//    } else if (peek() == '\n') {
//      scanner.line++;
//    }
//    advance();
//  }
//}

static bool isAlpha(char c) {
  return (c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c == '_');
}

static bool isAlphaNumeric(char c) { return (isAlpha(c) || isDigit(c)); }

static void identifier() {
  while (isAlphaNumeric(peek()))
    advance();
}

static TokenType identifierType() {
  char text[32];
  strncpy_s(text, scanner.start, scanner.current - scanner.start);
  TokenType type = getKeywordType(text);
  text[scanner.current - scanner.start] = '\0';
  if (type == NULL)
    type = IDENTIFIER;
  return type;
}

static void number() {
  while (isDigit(peek()))
    advance();

  if (peek() == '.' && isDigit(peekNext())) {
    advance();

    while (isDigit(peek())) {
      advance();
    }
  }
}

static void skipWhitespace() {
  char c = peek();
  while (isWhiteSpace(c)) {
    advance();
    c = peek();
  }
}

static Token scanToken() {
  skipWhitespace();
  scanner.start = scanner.current;

  if (isAtEnd()) {
    return makeToken(EOF_);
  }

  // TODO: IMPLEMENT BLOCK COMMENTS
  // If we encounter a block comment check if it's valid
  // if (peek() == '/' && peekNext() == '*' && !isValidBlockComment())
  //   return makeToken(ERROR_TOKEN);

  char c = advance();

  if (isDigit(c)) {
    number();
    return makeToken(NUMBER);
  } else if (isAlpha(c)) {
    identifier();
    TokenType type = identifierType();
    return makeToken(type);
  }

  switch (c) {
  case '(':
    return makeToken(LEFT_PAREN);
  case ')':
    return makeToken(RIGHT_PAREN);
  case '{':
    return makeToken(LEFT_BRACE);
  case '}':
    return makeToken(RIGHT_BRACE);
  case ',':
    return makeToken(COMMA);
  case '.':
    return makeToken(DOT);
  case ';':
    return makeToken(SEMICOLON);
  case '-':
    return makeToken(MINUS);
  case '+':
    return makeToken(PLUS);
  case '*':
    return makeToken(STAR);
  case '!':
    return makeToken(match('=') ? EXCL_EQUAL : EXCL);
  case '=':
    return makeToken(match('=') ? EQUAL_EQUAL : EQUAL);
  case '<':
    return makeToken(match('=') ? LESS_EQUAL : LESS);
  case '>':
    return makeToken(match('=') ? GREATER_EQUAL : GREATER);
  case '/':
    return makeToken(SLASH);
  case '"':
    string();
    return makeToken(STRING);
  default:
    error(scanner.line, "Unexpected character.");
    return makeToken(ERROR_TOKEN);
  }
}

void scanTokens(Token tokens[]) {
  scanner.nTokens = 0;

  Token token = {};
  while (token.type != EOF_) {
    token = scanToken();
    addToken(token, tokens);
  }
}

#include <stdlib.h>
#include <string.h>

#include "scanner.h"
#include "token.h"
#include "error.h"

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

static bool isDigit(char c) {
    return (c>= '0' && c <= '9');
}

static void addToken(TokenType tokenType, Token tokens[]) {

    Token token = createToken(tokenType);
    tokens[scanner.nTokens] = token;
    scanner.nTokens++;
}

static bool isAtEnd() {
    return *scanner.current == '\0';
}

static char peek() {
    if(isAtEnd()) return '\0';
    return *scanner.current++;
}

static char peekNext() {
    if (isAtEnd()) return '\0';
    return scanner.current[1];
}

static bool match(char expected) {
    if (isAtEnd()) return false;
    if(*scanner.current != expected) return false;
    scanner.current++;
    return true;
}

static void string() {
    while (peek() != '"' && !isAtEnd()) {
	if(peek() == '\n') scanner.line++;
	advance();
    }

    if (isAtEnd()) {
	error(scanner.line, "Unterminated string.");
	return;
    }

    advance();
}

static void number() {
    while (isDigit(peek())) advance();

    if (peek() == '.' && isDigit(peekNext())) {
	advance();

	while (isDigit(peek())) {
	    advance();
	}
    }
}

static void scanToken(Token tokens[]) {

    char c = advance();
    switch(c) {
    case '(':
	addToken(LEFT_PAREN, tokens);
	break;
    case ')':
	addToken(RIGHT_PAREN, tokens);
	break;
    case '{':
	addToken(LEFT_BRACE, tokens);
	break;
    case '}':
	addToken(RIGHT_BRACE, tokens);
	break;
    case ',':
	addToken(COMMA, tokens);
	break;
    case '.':
	addToken(DOT, tokens);
	break;
    case ';':
	addToken(SEMICOLON, tokens);
	break;
    case '-':
	addToken(MINUS, tokens);
	break;
    case '+':
	addToken(PLUS, tokens);
	break;
    case '*':
	addToken(STAR, tokens);
	break;
    case '!':
	addToken(match('=') ? EXCL_EQUAL : EXCL, tokens);
	break;
    case '=':
	addToken(match('=') ? EQUAL_EQUAL : EQUAL, tokens);
	break;	
    case '<':
	addToken(match('=') ? LESS_EQUAL : LESS, tokens);
	break;	
    case '>':
	addToken(match('=') ? GREATER_EQUAL : GREATER, tokens);
	break;	
    case '/':
	if(match('/')) {
	    // A comment goes until the end of the line
	    while (peek() != '\n' && !isAtEnd()) {
		advance();
	    }
	} else {
	    addToken(SLASH, tokens);
	}
	break;
    case ' ':
    case '\r':
    case '\t':
	break;
    case '\n':
	scanner.line++;
	break;
    case '"':
	string();
	addToken(STRING, tokens);
	break;
    default:
	if (isDigit(c)) {
	    number();
	    addToken(NUMBER, tokens);
	} else {
          error(scanner.line, "Unexpected character.");
        }
        break;
    }
    
}

void scanTokens(Token tokens[]) {

    scanner.nTokens = 0;

    while (!isAtEnd()) {
	scanner.start = scanner.current;
	scanToken(tokens);
    }

    Token eof = createToken(EOF_);

    tokens[scanner.nTokens] = eof; 
    scanner.nTokens++;
}

#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

enum TokenType {
    // Single-character tokens
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

    // One or two character tokens
    EXCL, EXCL_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    // Literals
    IDENTIFIER, STRING, NUMBER,

    // KEYWORDS
    AND, CLASS, ELSE, FALSE, TRUE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, VAR, WHILE,

    // EOF
    EOF_
};

#endif
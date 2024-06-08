/*
 * Copyright (C) Andrew Houghton, 2024
 */

#ifndef __LEXER__H__
#define __LEXER__H__

#include "inputbuf.h"

typedef enum { END_OF_FILE = 0, INT, REAL,
    BOO, TR, FA, IF, WHILE, SWITCH, CASE,
    PUBLIC, PRIVATE, NUM, REALNUM, NOT, PLUS,
    MINUS, MULT, DIV, GTEQ, GREATER, LTEQ,
    NOTEQUAL, LESS, LPAREN, RPAREN, EQUAL,
    COLON, COMMA, SEMICOLON, LBRACE,
    RBRACE, ID, ERROR
} TokenType;

class Token {
public:
    std::string lexeme;
    TokenType token_type;
    int line_no;

    void Print();
};

class LexicalAnalyzer {
public:
    Token GetToken();
    TokenType UngetToken(Token);
    LexicalAnalyzer();

private:
    std::vector<Token> tokens;
    int line_no;
    Token tmp;
    InputBuffer input;

    bool SkipSpace();
    bool SkipComments();
    bool IsKeyword(std::string);
    TokenType FindKeywordIndex(std::string);
    Token ScanIdOrKeyword();
    Token ScanNumber();
};

#endif  //__LEXER__H__

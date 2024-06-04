/*
 * Copyright (C) Andrew Houghton, 2024
 */

#ifndef __LEXER__H__
#define __LEXER__H__

#include "inputbuf.h"

using namespace std;

typedef enum { END_OF_FILE = 0,
    PUBLIC, PRIVATE, EQUAL, COLON,
    COMMA, SEMICOLON, LBRACE, RBRACE,
    ID, ERROR
} TokenType;

class Token {
    public:
        string lexeme;
        TokenType token_type;
        int line_no;
};

class LexicalAnalyzer {
    public:
        vector<Token> tokens;

        void Tokenize();
        void SaveToken(Token tok);
        LexicalAnalyzer();

    private:
        int line_no;
        Token tmp;
        InputBuffer input;

        void SkipSpace();
        void SkipComment();
        bool IsKeyword(string);
        TokenType FindKeywordIndex(string);
        Token ScanIdOrKeyword();
};

#endif  //__LEXER__H__

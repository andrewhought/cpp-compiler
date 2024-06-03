/*
 * Copyright (C) Andrew Houghton, 2024
 */

#ifndef __LEXER__H__
#define __LEXER__H__

#include "inputbuf.h"

typedef enum { END_OF_FILE = 0,
    PUBLIC, PRIVATE, EQUAL, COLON,
    COMMA, SEMICOLON, LBRACE, RBRACE,
    ID, ERROR
} TokenType;

class Token {
    public:
        std::string lexeme;
        TokenType token_type;
        int line_no;
};

class LexicalAnalyzer {
    public:
        std::vector<Token> tokens;

        void GetTokens();
        void SaveToken(Token tok);
        LexicalAnalyzer();

    private:
        int line_no;
        Token tmp;
        InputBuffer input;

        void SkipSpace();
        void SkipComment();
        bool IsKeyword(std::string);
        TokenType FindKeywordIndex(std::string);
        Token ScanIdOrKeyword();
};

#endif  //__LEXER__H__

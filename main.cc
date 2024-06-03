/*
 * Copyright (C) Andrew Houghton, 2024
 */

#include "parser.h"

int main()
{
    LexicalAnalyzer lexer;
    lexer.Tokenize();

    std::reverse(lexer.tokens.begin(), lexer.tokens.end());

    Parser parser(lexer.tokens);

    for (Token token : parser.tokens) {
        if (token.token_type == ERROR) {
            parser.SyntaxError();
        }
    }

    parser.ParseProgram();
}
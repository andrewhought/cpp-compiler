/*
 * Copyright (C) Andrew Houghton, 2024
 */

#include "parser.h"

int main()
{
    LexicalAnalyzer lexer;
    lexer.GetTokens();

    Parser parser(lexer.tokens);
    parser.GetProgram();
}
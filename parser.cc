/*
 * Copyright (C) Andrew Houghton, 2024
 */

#include "parser.h"

using namespace std;

Parser::Parser(std::vector<Token> tokens)
{
    this->tokens = tokens;
}

void Parser::SyntaxError()
{
    cout << "Syntax Error\n";
    exit(1);
}

void Parser::ParseGlobalVars()
{

}

void Parser::ParseVarList()
{

}

void Parser::ParseScope()
{

}

void Parser::ParsePublicVars()
{

}

void Parser::ParsePrivateVars()
{

}

void Parser::ParseStmtList()
{

}

void Parser::ParseStmt()
{

}

void Parser::GetProgram()
{

}

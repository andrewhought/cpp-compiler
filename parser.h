/*
 * Copyright (C) Andrew Houghton, 2024
 */

#ifndef __PARSER__H__
#define __PARSER__H__

#include "lexer.h"

/*
 * GRAMMAR
 * program        ->    global_vars scope
 * global_vars    ->    var_list SEMICOLON | ε
 * var_list       ->    ID | ID COMMA var_list
 * scope          ->    ID LBRACE public_vars private_vars stmt_list RBRACE
 * public_vars    ->    PUBLIC COLON var_list SEMICOLON | ε
 * private_vars   ->    PRIVATE COLON var_list SEMICOLON | ε
 * stmt_list      ->    stmt | stmt_list
 * stmt           ->    ID EQUAL ID SEMICOLON | scope
 */

class Parser {
    public:
        std::vector<Token> tokens;

        void GetProgram();
        Parser(std::vector<Token>);

    private:
        void SyntaxError();
        void ParseGlobalVars();
        void ParseVarList();
        void ParseScope();
        void ParsePublicVars();
        void ParsePrivateVars();
        void ParseStmtList();
        void ParseStmt();
};

#endif  //__PARSER__H__

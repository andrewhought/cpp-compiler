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

class Scope {
    public:
        std::string scope;
        std::vector<std::string> scopes;
        std::vector<Token> global_vars;
        std::vector<Token> public_vars;
        std::vector<Token> private_vars;
        std::unordered_map<std::string, std::vector<Token>> public_scopes;
        std::unordered_map<std::string, std::vector<Token>> private_scopes;
        std::vector<std::pair<Token, Token>> assignments;
        Token left;
        Token right;

        void PrintAssignments();
        void AssignScope(Token &tok);

    private:
        bool CheckGlobal(Token&);
        bool CheckPublic(Token&);
        bool CheckPrivate(Token&);
};

class Parser {
    public:
        std::vector<Token> tokens;

        void SyntaxError();
        void ParseProgram();
        Parser(std::vector<Token>);

    private:
        Token tmp;
        Scope vis;

        void ParseGlobalVars();
        std::vector<Token> ParseVarList();
        void ParseScope();
        void ParsePublicVars();
        void ParsePrivateVars();
        void ParseStmtList();
        void ParseStmt();
        void UngetToken(Token);
        void GetToken(Token&);
};

#endif  //__PARSER__H__

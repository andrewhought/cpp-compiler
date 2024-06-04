/*
 * Copyright (C) Andrew Houghton, 2024
 */

#include "parser.h"

using namespace std;

void Scope::PrintAssignments()
{
    if (!assignments.empty()) {
        for (std::pair<Token, Token> assignment : assignments) {
            cout << assignment.first.lexeme << " = " << assignment.second.lexeme << endl;
        }
    }
}

bool Scope::CheckGlobal(Token& tok)
{
    for (Token var : global_vars) {
        if (tok.lexeme == var.lexeme) {
            tok.lexeme = "::" + tok.lexeme;
            return true;
        }
    }
    return false;
}

bool Scope::CheckPublic(Token& tok)
{
    for (int i = (int) this->scopes.size() - 1; i >= 0; i--) {
        for (Token var : public_scopes[scopes[i]]) {
            if (tok.lexeme == var.lexeme) {
                tok.lexeme = scopes[i] + "." + tok.lexeme;
                return true;
            }
        }
    }
    return false;
}

bool Scope::CheckPrivate(Token& tok)
{
    for (Token var : this->private_scopes[scope]) {
        if (tok.lexeme == var.lexeme) {
            tok.lexeme = scope + "." + tok.lexeme;
            return true;
        }
    }
    return false;
}

void Scope::AssignScope(Token& tok)
{
    if (CheckPrivate(tok)) {
        return;
    }

    if (CheckPublic(tok)) {
        return;
    }

    if (CheckGlobal(tok)) {
        return;
    }

    tok.lexeme = "?." + tok.lexeme;
}

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
    vis.global_vars = ParseVarList();
}

std::vector<Token> Parser::ParseVarList()
{
    std::vector<Token> vars;

    GetToken(tmp);
    if (tmp.token_type != ID) {
        SyntaxError();
    }

    vars.push_back(tmp);
    GetToken(tmp);
    while (tmp.token_type != SEMICOLON) {
        if (tmp.token_type == LBRACE) {
            vis.scope = vars.back().lexeme;
            vis.scopes.push_back(vis.scope);
            UngetToken(tmp);
            ParseScope();
            GetToken(tmp);
            if (tmp.token_type == END_OF_FILE) {
                UngetToken(tmp);
                return vars;
            }
        } else if (tmp.token_type == COMMA) {
            GetToken(tmp);
            if (tmp.token_type == ID) {
                vars.push_back(tmp);
            } else {
                SyntaxError();
            }
            GetToken(tmp);
        } else {
            SyntaxError();
        }
    }
    return vars;
}

void Parser::ParseScope()
{
    GetToken(tmp);
    if (tmp.token_type != LBRACE) {
        SyntaxError();
    }

    GetToken(tmp);
    if (tmp.token_type == PUBLIC) {
        ParsePublicVars();
    } else {
        UngetToken(tmp);
    }

    GetToken(tmp);
    if (tmp.token_type == PRIVATE) {
        ParsePrivateVars();
    } else {
        UngetToken(tmp);
    }

    ParseStmtList();

    GetToken(tmp);
    if (tmp.token_type != RBRACE) {
        SyntaxError();
    }

    vis.scopes.pop_back();
    if (!vis.scopes.empty()) {
        vis.scope = vis.scopes.back();
    }
}

void Parser::ParsePublicVars()
{
    GetToken(tmp);

    if (tmp.token_type != COLON) {
        SyntaxError();
    }

    vis.public_vars = ParseVarList();
    vis.public_scopes[vis.scope] = vis.public_vars;
}

void Parser::ParsePrivateVars()
{
    GetToken(tmp);

    if (tmp.token_type != COLON) {
        SyntaxError();
    }

    vis.private_vars = ParseVarList();
    vis.private_scopes[vis.scope] = vis.private_vars;
}

void Parser::ParseStmtList()
{
    GetToken(tmp);

    if (tmp.token_type != ID) {
        SyntaxError();
    } else {
        while (tmp.token_type == ID) {
            UngetToken(tmp);
            ParseStmt();
            GetToken(tmp);
        }
        UngetToken(tmp);
    }
}

void Parser::ParseStmt()
{
    GetToken(tmp);
    vis.left = tmp;

    GetToken(tmp);
    if (tmp.token_type == LBRACE) {
        vis.scope = vis.left.lexeme;
        vis.scopes.push_back(vis.scope);
        UngetToken(tmp);
        ParseScope();
    } else if (tmp.token_type == EQUAL) {
        vis.AssignScope(vis.left);

        GetToken(tmp);
        if (tmp.token_type != ID) {
            SyntaxError();
        }

        vis.right = tmp;
        vis.AssignScope(vis.right);

        GetToken(tmp);
        if (tmp.token_type != SEMICOLON) {
            SyntaxError();
        }

        vis.assignments.push_back(make_pair(vis.left, vis.right));
    } else {
        SyntaxError();
    }
}

void Parser::UngetToken(Token tok)
{
    tokens.push_back(tok);
}

void Parser::GetToken(Token& tok)
{
    if (!tokens.empty()) {
        tok = tokens.back();
        tokens.pop_back();
    }
}

void Parser::ParseProgram()
{
    ParseGlobalVars();

    GetToken(tmp);
    if (tmp.token_type != END_OF_FILE) {
        vis.scope = tmp.lexeme;
        vis.scopes.push_back(vis.scope);
        ParseScope();
    }

    vis.PrintAssignments();
}

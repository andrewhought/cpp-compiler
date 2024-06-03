/*
 * Copyright (C) Andrew Houghton, 2024
 */

#include "lexer.h"

using namespace std;

#define KEYWORDS_COUNT 2
string keyword[] = { "public", "private" };

LexicalAnalyzer::LexicalAnalyzer()
{
    this->line_no = 1;
    tmp.lexeme = "";
    tmp.line_no = 1;
    tmp.token_type = ERROR;
}

void LexicalAnalyzer::SkipSpace()
{
    char c;

    input.GetChar(c);
    line_no += (c == '\n');

    while (!input.EndOfInput() && isspace(c)) {
        input.GetChar(c);
        line_no += (c == '\n');
    }

    if (!input.EndOfInput()) {
        input.UngetChar(c);
    } else {
        tmp.token_type = END_OF_FILE;
        SaveToken(tmp);
    }
}

void LexicalAnalyzer::SkipComment()
{
    char c;

    input.GetChar(c);
    line_no += (c == '\n');

    while (!input.EndOfInput() && c != '\n') {
        input.GetChar(c);
        line_no += (c == '\n');
    }
}

bool LexicalAnalyzer::IsKeyword(string s)
{
    for (int i = 0; i < KEYWORDS_COUNT; i++) {
        if (s == keyword[i]) {
            return true;
        }
    }
    return false;
}

TokenType LexicalAnalyzer::FindKeywordIndex(string s)
{
    for (int i = 0; i < KEYWORDS_COUNT; i++) {
        if (s == keyword[i]) {
            return (TokenType) (i + 1);
        }
    }
    return ERROR;
}

Token LexicalAnalyzer::ScanIdOrKeyword()
{
    char c;
    input.GetChar(c);

    if (isalpha(c)) {
        tmp.lexeme = "";
        while (!input.EndOfInput() && isalnum(c)) {
            tmp.lexeme += c;
            input.GetChar(c);
        }
        if (!input.EndOfInput()) {
            input.UngetChar(c);
        }
        tmp.line_no = line_no;
        if (IsKeyword(tmp.lexeme))
            tmp.token_type = FindKeywordIndex(tmp.lexeme);
        else
            tmp.token_type = ID;
    } else {
        if (!input.EndOfInput()) {
            input.UngetChar(c);
        }
        tmp.lexeme = "";
        tmp.token_type = ERROR;
    }
    return tmp;
}

void LexicalAnalyzer::SaveToken(Token tok)
{
    tokens.push_back(tok);
}

void LexicalAnalyzer::GetTokens()
{
    char c;

    while (!input.EndOfInput())
    {
        SkipSpace();

        if (tmp.token_type == END_OF_FILE) {
            return;
        }

        tmp.lexeme = "";
        tmp.line_no = line_no;

        input.GetChar(c);

        switch (c) {
            case '/':
                input.GetChar(c);
                if (c == '/') {
                    SkipComment();
                    break;
                } else {
                    tmp.token_type = ERROR;
                    SaveToken(tmp);
                    break;
                }
            case '=':
                tmp.token_type = EQUAL;
                SaveToken(tmp);
                break;
            case ':':
                tmp.token_type = COLON;
                SaveToken(tmp);
                break;
            case ',':
                tmp.token_type = COMMA;
                SaveToken(tmp);
                break;
            case ';':
                tmp.token_type = SEMICOLON;
                SaveToken(tmp);
                break;
            case '{':
                tmp.token_type = LBRACE;
                SaveToken(tmp);
                break;
            case '}':
                tmp.token_type = RBRACE;
                SaveToken(tmp);
                break;
            default:
                if (isalpha(c)) {
                    input.UngetChar(c);
                    SaveToken(ScanIdOrKeyword());
                } else if (input.EndOfInput()) {
                    tmp.token_type = END_OF_FILE;
                    SaveToken(tmp);
                }
                else {
                    tmp.token_type = ERROR;
                    SaveToken(tmp);
                }
        }
    }
}

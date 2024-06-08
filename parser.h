/*
 * Copyright (C) Andrew Houghton, 2024
 */

#ifndef __PARSER__H__
#define __PARSER__H__

#include "lexer.h"

/*
 * GRAMMAR
 * program          ->      global_vars body
 * global_vars      ->      var_decl_list | ε
 * var_decl_list    ->      var_decl | var_decl var_decl_list
 * var_decl         ->      var_list COLON type_name SEMICOLON
 * var_list         ->      ID | ID COMMA var_list
 * type_name        ->      INT | REAL | BOOL
 * body             ->      LBRACE stmt_list RBRACE
 * stmt_list        ->      stmt | stmt stmt_list
 * stmt             ->      assignment_stmt | if_stmt | while_stmt | switch_stmt
 * assignment_stmt  ->      ID EQUAL expression SEMICOLON
 * expression       ->      primary | binary_operator expression expression | unary_operator expression
 * unary_operator   ->      NOT
 * binary_operator  ->      PLUS | MINUS | MULT | DIV | GREATER | LESS | GTEQ | LTEQ | EQUAL | NOTEQUAL
 * primary          ->      ID | NUM | REALNUM | TRUE | FALSE
 * if_stmt          ->      IF LPAREN expression RPAREN body
 * while_stmt       ->      WHILE LPAREN expression RPAREN body
 * switch_stmt      ->      SWITCH LPAREN expression RPAREN LBRACE case_list RBRACE
 * case_list        ->      case | case case_list
 * case             ->      CASE NUM COLON body
 */

class Parser {
public:
    LexicalAnalyzer lexer;
    Token token;
    TokenType tempTokenType;

    int parse_program();

private:
    int parse_varlist();
    int parse_unaryOperator();
    int parse_binaryOperator();
    int parse_primary();
    int parse_expression();
    int parse_assstmt();
    int parse_case();
    int parse_caselist();
    int parse_switchstmt();
    int parse_whilestmt();
    int parse_ifstmt();
    int parse_stmt();
    int parse_stmtlist();
    int parse_body();
    int parse_typename();
    int parse_vardecl();
    int parse_vardecllist();
    int parse_globalVars();
};

#endif  //__PARSER__H__

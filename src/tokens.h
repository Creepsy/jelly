#pragma once

#include <string>
#include <map>

namespace jelly_tokens {

    enum token_type {
        ADD,
        SUB,
        MUL,
        DIV,
        INCR,
        DECR,
        POW,
        MOD,
        ADD_ASSIGN,
        SUB_ASSIGN,
        MUL_ASSIGN,
        DIV_ASSIGN,
        POW_ASSIGN,
        MOD_ASSIGN,
        GREATER,
        SMALLER,
        NOT,
        GREATER_EQ,
        SMALLER_EQ,
        NOT_EQ,
        EQUALS,
        ASSIGN,
        OR,
        AND,
        INT,
        FLOAT,
        TRUE,
        FALSE,
        IDENTIFIER,
        COMMA,
        LINE_END,
        BRACKET_OPEN,
        BRACKET_CLOSE,
        CUR_BRACKET_OPEN,
        CUR_BRACKET_CLOSE,
        SQ_BRACKET_OPEN,
        SQ_BRACKET_CLOSE,
        INT_IDENT,
        FLOAT_IDENT,
        ARRAY_IDENT,
        STRING_IDENT,
        BOOL_IDENT,
        FUNC,
        IF,
        ELSE,
        FOR,
        WHILE,
        BREAK,
        RETURN,
        IMPORT,
        STRING,
        END_OF_FILE,
        NONE
    };

    struct token {
        token_type typ;
        std::string identifier;

        size_t line_begin;
        size_t chr_begin;

        size_t line_end;
        size_t chr_end;   
    };
}
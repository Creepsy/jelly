#pragma once

#include <istream>
#include <vector>
#include <string>

namespace jelly {
    const std::vector<std::string> tokenToString = {
        "STRING",
        "FLOAT",
        "INT",
        "MULTIPLY",
        "DIVIDE",
        "ADD",
        "SUBSTRACT",
        "MODULO",
        "DOT",
        "OPENING BRACKET",
        "CLOSING BRACKET",
        "OPENING BRACE",
        "CLOSING BRACE",
        "OPENING SQUARE BRACKET",
        "CLOSING SQUARE BRACKET",
        "OR",
        "AND",
        "SEPARATOR",
        "ASSIGN",
        "NOT",
        "GREATER",
        "SMALLER",
        "EQUALS",
        "NOT_EQUALS",
        "GREATER_EQUALS",
        "SMALLER_EQUALS",
        "IDENTIFIER",
        "UNDEFINED",
        "IF",
        "ELSE",
        "FOR",
        "WHILE",
        "FUNCTION",
        "TYPE_INT",
        "TYPE_FLOAT",
        "TYPE_BOOL",
        "TYPE_STRING",
        "TYPE_STRUCT",
        "TYPE_ARRAY",
        "STRUCT",
        "VOID",
        "TRUE",
        "FALSE",
        "IMPORT",
        "RETURN",
        "BREAK",
        "INCREASE",
        "DECREASE",
        "END OF LINE",
        "END OF FILE"
    };

    enum tokenType {
        STRING,
        FLOAT,
        INT,
        MULTIPLY,
        DIVIDE,
        ADD,
        SUBSTRACT,
        MODULO,
        DOT,
        O_BRACKET,
        C_BRACKET,
        O_BRACE,
        C_BRACE,
        O_S_BRACKET,
        C_S_BRACKET,
        OR,
        AND,
        SEPARATOR,
        ASSIGN,
        NOT,
        GREATER,
        SMALLER,
        EQUALS,
        NOT_EQUALS,
        GREATER_EQUALS,
        SMALLER_EQUALS,
        IDENTIFIER,
        UNDEFINED,
        IF,
        ELSE,
        FOR,
        WHILE,
        FUNCTION,
        TYPE_INT,
        TYPE_FLOAT,
        TYPE_BOOL,
        TYPE_STRING,
        TYPE_STRUCT,
        TYPE_ARRAY,
        STRUCT,
        VOID,
        TRUE,
        FALSE,
        IMPORT,
        RETURN,
        BREAK,
        INCREASE,
        DECREASE,
        EOL,
        END
    };

    struct token {
        tokenType typ;
        std::string identifier;
        size_t line;
        size_t begin;
        size_t end;

        std::string get_position();
    };

    class jelly_lexer {
    private:
        std::istream& input;

        size_t line;
        size_t character;

        token next_number(const char curr);
        token next_string();
        tokenType check_keywords(const std::string& ident);
    public:
        jelly_lexer(std::istream& input);
        token next_token();
        ~jelly_lexer();
    };
}
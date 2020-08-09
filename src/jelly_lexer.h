#pragma once

#include <istream>
#include <vector>
#include <string>

namespace jelly {
    const std::vector<std::string> tokenToString = {
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
        "QUOTE",
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
        QUOTE,
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
    };

    class jelly_lexer {
    private:
        std::istream& input;

        size_t line;
        size_t character;

        token next_number(const char curr);
        tokenType check_keywords(const std::string& ident);
    public:
        jelly_lexer(std::istream& input);
        token next_token();
        ~jelly_lexer();
    };
}
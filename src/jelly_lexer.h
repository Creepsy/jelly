#pragma once

#include <fstream>

#include "tokens.h"

class jelly_lexer {
    private:
        std::ifstream& inp;

        size_t line;
        size_t chr;

        char next_chr();
        void prev_chr();

        void clear_wspace(char next);
        jelly_tokens::token get_operator(char next);
        jelly_tokens::token get_number(char next);
        void throw_error(std::string err);
        std::string get_identifier(char next);
        jelly_tokens::token_type get_keyword(std::string ident);
        void consume_comment();
        jelly_tokens::token get_string();
    public:
        jelly_lexer(std::ifstream& inp);
        jelly_tokens::token next_token();
        ~jelly_lexer();
};
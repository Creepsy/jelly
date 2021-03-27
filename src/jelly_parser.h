#pragma once

#include <vector>

#include "jelly_lexer.h"
#include "branch.h"

class jelly_parser {
private:
    jelly_lexer& lexer;
    jelly_tokens::token curr;

    void consume();

    bool accept(jelly_tokens::token_type type);
    bool accept(const std::vector<jelly_tokens::token_type>& types);

    void expect(jelly_tokens::token_type type);
    void expect(const std::vector<jelly_tokens::token_type>& types);

    void throw_error(const std::string& err);
public:
    jelly_parser(jelly_lexer& lexer);
    branch* parse();
    ~jelly_parser();
};
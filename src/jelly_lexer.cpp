#include "jelly_lexer.h"

#include <iostream>

jelly::jelly_lexer::jelly_lexer(std::istream& input) : input(input), line(0), character(0) {
}

jelly::token jelly::jelly_lexer::next_token() {
    char next = this -> input.get();
    this -> character++;
    if(!this -> input.fail()) {
        if(std::isspace(next)) {
            while(std::isspace(next)) {
                if(next == '\n') {
                    this -> character = 0;
                    this -> line++;
                }
                next = this -> input.get();
                this -> character++;
            }
        }

        if(std::isdigit(next)) return this -> next_number(next);

        if(next == '*') {
            return token{tokenType::MULTIPLY, "*", this -> line, this -> character - 1, this -> character};
        } else if(next == '/') {
            return token{tokenType::DIVIDE, "/", this -> line, this -> character - 1, this -> character};
        } else if(next == '+') {
            return token{tokenType::ADD, "+", this -> line, this -> character - 1, this -> character};
        } else if(next == '-') {
            return token{tokenType::SUBSTRACT, "-", this -> line, this -> character - 1, this -> character};
        } else if(next == '%') {
            return token{tokenType::MODULO, "%", this -> line, this -> character - 1, this -> character};
        }
    }

    return token{tokenType::END, "END", this -> line, this -> character - 1, this -> character};
}

jelly::token jelly::jelly_lexer::next_number(const char curr) {
    size_t line = this -> line;
    size_t start = this -> character - 1;
    std::string number;
    number.push_back(curr);

    char next = this -> input.get();
    this -> character++;

    bool is_float = false;

    while(!this -> input.fail() && (std::isdigit(next) || next == '.')) {
        if(is_float && next == '.') throw std::runtime_error("Number parse error at Ln " + std::to_string(line) + ", Col " + std::to_string(this -> character));
        if(next == '.') is_float = true;
        number.push_back(next);

        next = this -> input.get();
        this -> character++;
    }

    this -> input.seekg(-1, std::ios::cur);
    this -> character--;

    return token{tokenType::NUMBER, number, line, start, this -> character};
}

jelly::jelly_lexer::~jelly_lexer() {
}
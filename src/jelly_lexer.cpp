#include "jelly_lexer.h"

#include <iostream>

jelly::jelly_lexer::jelly_lexer(std::istream& input) : input(input), line(0), character(0) {
}

jelly::token jelly::jelly_lexer::next_token() {
    char next = this -> input.get();
    if(!this -> input.fail()) {
        std::cout << "not end" << std::endl;
    }

    return token{tokenType::END, "END", this -> line, this -> character, this -> character};
}

jelly::jelly_lexer::~jelly_lexer() {
}
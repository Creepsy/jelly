#include "jelly_parser.h"

#include <iostream>

jelly::jelly_parser::jelly_parser(jelly_lexer& lexer) : lexer(lexer) {
}

jelly::jelly_parser::~jelly_parser() {
}

void jelly::jelly_parser::consume() {
    this -> next = this -> lexer.next_token();
}

bool jelly::jelly_parser::accept(tokenType type) {
    return this -> next.typ == type;
}

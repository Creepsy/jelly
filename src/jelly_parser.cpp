#include "jelly_parser.h"

jelly_parser::jelly_parser(jelly_lexer& lexer)
 : lexer(lexer) {
}



jelly_parser::~jelly_parser() {
}

//private

void jelly_parser::consume() {

}

bool jelly_parser::accept(jelly_tokens::token_type type) {
    return true;
}

bool jelly_parser::accept(const std::vector<jelly_tokens::token_type>& types) {
    return true;
}

void jelly_parser::expect(jelly_tokens::token_type type) {

}

void jelly_parser::expect(const std::vector<jelly_tokens::token_type>& types) {

}
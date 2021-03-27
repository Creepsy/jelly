#include "jelly_parser.h"

jelly_parser::jelly_parser(jelly_lexer& lexer)
 : lexer(lexer) {
}

branch* jelly_parser::parse() {
    return nullptr;
}

jelly_parser::~jelly_parser() {
}

//private

void jelly_parser::consume() {
    this->curr = this->lexer.next_token();
}

bool jelly_parser::accept(jelly_tokens::token_type type) {
    return this->curr.typ == type;
}

bool jelly_parser::accept(const std::vector<jelly_tokens::token_type>& types) {
    for(jelly_tokens::token_type type : types) {
        if(this->curr.typ == type) {
            return true;
        }
    }
    return false;
}

void jelly_parser::expect(jelly_tokens::token_type type) {
    if(!this->accept(type)) this->throw_error("Unexpected token!");
}

void jelly_parser::expect(const std::vector<jelly_tokens::token_type>& types) {
    if(!this->accept(types)) this->throw_error("Unexpected token!");
}

void jelly_parser::throw_error(const std::string& err) {
    throw std::runtime_error("[Ln " + std::to_string(this->curr.seq.begin.line) + ", Col " + std::to_string(this->curr.seq.begin.chr) + "]: " + err);
}
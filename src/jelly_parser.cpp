#include "jelly_parser.h"

#include <iostream>

jelly::jelly_parser::jelly_parser(jelly_lexer& lexer) : lexer(lexer) {
}

jelly::jelly_parser::~jelly_parser() {
}

void jelly::jelly_parser::consume() {
    this -> next = this -> lexer.next_token();
}

jelly::branch* jelly::jelly_parser::parse() {
    consume();
    return this->parseSum();
}

jelly::branch* jelly::jelly_parser::parseSum() {
    branch* left = this->parseMultiplication();
    while(true){
        if(this->accept({tokenType::ADD, tokenType::SUBSTRACT})) {
            tokenType op = this->next.typ;
            this->consume();
            branch* right = this->parseMultiplication();
            left = new binary_expression{left, right, op};
        } else {
            break;
        }
    }

    return left;
}

jelly::branch* jelly::jelly_parser::parseMultiplication() {
    branch* left = this->parseValue();
    while(true){
        if(this->accept({tokenType::MULTIPLY, tokenType::DIVIDE})) {
            tokenType op = this->next.typ;
            this->consume();
            branch* right = this->parseValue();
            left = new binary_expression{left, right, op};
        } else {
            break;
        }
    }

    return left;
}

jelly::branch* jelly::jelly_parser::parseValue() {
    if(this->accept({tokenType::INT, tokenType::FLOAT})) {
        const_expression* value = new const_expression{this->next.typ, this->next.identifier};
        this->consume();
        return value;
    } else {
        throw std::runtime_error(this->next.get_position() + " Expected an value!");
    }
}

bool jelly::jelly_parser::accept(tokenType type) {
    return this -> next.typ == type;
}

bool jelly::jelly_parser::accept(const std::vector<tokenType>& type) {
    for(const tokenType& t : type) {
        if(this -> next.typ == t) {
            return true;
        }
    }
    return false;
}

void jelly::jelly_parser::expect(tokenType type) {
    if(this -> next.typ != type) throw std::runtime_error(this->next.get_position() + " Expected \'" + tokenToString[type] + "\', found \'" + tokenToString[this -> next.typ] + "\'!");
}

void jelly::jelly_parser::expect(const std::vector<tokenType>& type) {
    for(const tokenType& t : type) {
        if(this -> next.typ == t) {
            return;
        }
    }
    std::string possibilities;
    for(int i = 0; i < type.size(); i++) {
        if(i == 0) {
            possibilities.push_back('[');
        }
        if(i != 0) possibilities += ", ";
        possibilities += tokenToString[type[i]];

        if(i == type.size() - 1) {
            possibilities.push_back(']');
        }
    }

    throw std::runtime_error(this->next.get_position() + " Expected one of the following: " + possibilities + "\', found \'" + tokenToString[this -> next.typ] + "\'!");
}
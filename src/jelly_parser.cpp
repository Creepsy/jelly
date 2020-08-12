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
    return this->parse_equation();
}

jelly::branch* jelly::jelly_parser::parse_sum() {
    branch* left = this->parse_multiplication();
    while(true){
        if(this->accept({tokenType::ADD, tokenType::SUBSTRACT})) {
            tokenType op = this->next.typ;
            this->consume();
            branch* right = this->parse_multiplication();
            left = new binary_expression{left, right, op};
        } else {
            break;
        }
    }

    return left;
}

jelly::branch* jelly::jelly_parser::parse_multiplication() {
    branch* left = this->parse_unary();
    while(true){
        if(this->accept({tokenType::MULTIPLY, tokenType::DIVIDE})) {
            tokenType op = this->next.typ;
            this->consume();
            branch* right = this->parse_unary();
            left = new binary_expression{left, right, op};
        } else {
            break;
        }
    }

    return left;
}

jelly::branch* jelly::jelly_parser::parse_value() {
    if(this->accept({tokenType::INT, tokenType::FLOAT, tokenType::STRING, tokenType::TRUE, tokenType::FALSE})) {
        const_expression* value = new const_expression{this->next.typ, this->next.identifier};
        this->consume();
        return value;
    } else if(this->accept(tokenType::IDENTIFIER)) {
        variable_expression* value = new variable_expression{this->next.identifier};
        this->consume();
        return value;
    } else {
        throw std::runtime_error(this->next.get_position() + " Expected a value!");
    }
}

jelly::branch* jelly::jelly_parser::parse_parenthesis() {
    if(this->accept(tokenType::O_BRACKET)) {
        this->consume();
        branch* content = this->parse_equation();
        this->expect(tokenType::C_BRACKET);
        this->consume();
        return content;
    }
    return this->parse_value();
}

jelly::branch* jelly::jelly_parser::parse_comparison() {
    branch* left = this->parse_sum();
    while(true){
        if(this->accept({tokenType::GREATER, tokenType::SMALLER, tokenType::GREATER_EQUALS, tokenType::SMALLER_EQUALS})) {
            tokenType op = this->next.typ;
            this->consume();
            branch* right = this->parse_sum();
            left = new binary_expression{left, right, op};
        } else {
            break;
        }
    }

    return left;
}

jelly::branch* jelly::jelly_parser::parse_equation() {
    branch* left = this->parse_comparison();
    while(true){
        if(this->accept({tokenType::EQUALS, tokenType::NOT_EQUALS})) {
            tokenType op = this->next.typ;
            this->consume();
            branch* right = this->parse_comparison();
            left = new binary_expression{left, right, op};
        } else {
            break;
        }
    }

    return left;
}

jelly::branch* jelly::jelly_parser::parse_unary(){
    if(this->accept({tokenType::ADD, tokenType::SUBSTRACT, tokenType::NOT})) {
        tokenType t = this->next.typ;
        this->consume();
        return new unary_expression{t, this->parse_unary()};
    }

    return this->parse_parenthesis();
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
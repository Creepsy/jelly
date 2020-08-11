#include "jelly_ast.h"

jelly::branch::branch() {
}

jelly::branch::~branch() {
}

jelly::binary_expression::binary_expression(branch* left, branch* right, tokenType op) : left(left), right(right), op(op) {
}

jelly::binary_expression::~binary_expression() {
    delete this->left;
    delete this->right;
}

std::string jelly::binary_expression::to_string() {
    return "(" + this->left->to_string() + ") " + tokenToString[this -> op] + " (" + this->right->to_string() + ")";
}

jelly::const_expression::const_expression(tokenType typ, std::string value) : typ(typ), value(value) {

}
jelly::const_expression::~const_expression() {

}

std::string jelly::const_expression::to_string() {
    return tokenToString[this->typ] + " : " + this->value;
}

jelly::unary_expression::unary_expression(tokenType sign, branch* value) : sign(sign), value(value) {

}
jelly::unary_expression::~unary_expression() {
    delete this->value;
}

std::string jelly::unary_expression::to_string() {
    return tokenToString[this->sign] + " : [" + this->value->to_string() + "]";
}
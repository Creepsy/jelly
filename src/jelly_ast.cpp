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

jelly::variable_expression::variable_expression(std::string identifier) : identifier(identifier) {

}

std::string jelly::variable_expression::to_string() {
    return "Variable: " + this -> identifier;
}

jelly::variable_expression::~variable_expression() {

}

jelly::assign_statement::assign_statement(std::string identifier, branch* value) : identifier(identifier), value(value) {

}

std::string jelly::assign_statement::to_string() {
    return "Assign " + this->value->to_string() + " to " + this->identifier;
}

jelly::assign_statement::~assign_statement() {
    delete this->value;
}

jelly::define_statement::define_statement(std::string identifier, tokenType typ) : identifier(identifier), typ(typ) {

}

std::string jelly::define_statement::to_string() {
    return "Define " + this->identifier + ", " + tokenToString[this->typ];
}

jelly::define_statement::~define_statement() {

}

jelly::initialize_statement::initialize_statement(std::string identifier, tokenType typ, branch* value) : identifier(identifier), typ(typ), value(value) {

}

std::string jelly::initialize_statement::to_string() {
    return "Initialize " + this->identifier + ", " + tokenToString[this->typ] + " with " + this->value->to_string();
}

jelly::initialize_statement::~initialize_statement() {
    delete this->value;
}

jelly::struct_define_statement::struct_define_statement(std::string identifier, std::string struct_type) : identifier(identifier), struct_type(struct_type) {

}

std::string jelly::struct_define_statement::to_string() {
    return "Define struct " + this->identifier + ", " + this->struct_type;
}

jelly::struct_define_statement::~struct_define_statement() {

}

jelly::struct_initialize_statement::struct_initialize_statement(std::string identifier, std::string struct_type, branch* value) : identifier(identifier), struct_type(struct_type), value(value) {

}

std::string jelly::struct_initialize_statement::to_string() {
    return "Initialize struct " + this->identifier + ", " + this->struct_type + " with " + this->value->to_string();
}

jelly::struct_initialize_statement::~struct_initialize_statement() {
    delete this->value;
}

jelly::struct_instance_expression::struct_instance_expression(std::string struct_type, branch* initializer_list) : struct_type(struct_type), initializer_list(initializer_list) {

}

std::string jelly::struct_instance_expression::to_string() {
    return "Struct instance of " + this->struct_type + ", Args: " + this->initializer_list->to_string();
}

jelly::struct_instance_expression::~struct_instance_expression() {
    delete this->initializer_list;
}

jelly::list_expression::list_expression(std::vector<branch*> elements, size_t length) : elements(elements), length(length) {

}

std::string jelly::list_expression::to_string() {
    std::string list = "Size: " + std::to_string(this->length) + ", {";
    for(int i = 0; i < this->elements.size(); i++) {
        if(i != 0) list += ", ";
        list += this->elements.at(i)->to_string();
    }

    return list + "}";
}

jelly::list_expression::~list_expression() {
    for(branch* b : this->elements) delete b;
}
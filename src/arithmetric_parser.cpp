#include "arithmetric_parser.h"

using namespace arithmetrics;

binary_operation::binary_operation(sequence seq, branch* left, branch* right, binary_operators op)
 : branch{ seq }, left(left), right(right), op(op) {

}

std::string binary_operation::to_string() {
    return "{left: " + this->left->to_string() + ", right: " + this->right->to_string() + ", operator: " + std::to_string(this->op) + "}";
}

binary_operation::~binary_operation() {
    delete this->left;
    delete this->right;
}
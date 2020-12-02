#include "arithmetric_parser.h"

using namespace arithmetrics;

binary_operation::binary_operation()
 : branch{ position{ 0, 0, 0, 0 } } {
}

std::string binary_operation::to_string() {
    return "";
}

binary_operation::~binary_operation() {
    delete this->left;
    delete this->right;
}
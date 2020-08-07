#include <iostream>
#include <fstream>

#include "src/jelly_lexer.h"

int main() {
    std::ifstream test{};
    test.open("test_file.jelly");

    if(!test.is_open()) return -1;

    jelly::jelly_lexer lexer{test};

    jelly::token t;

    do {
        t = lexer.next_token();
        std::cout << jelly::tokenToString.at(t.typ)<<
         ", Line: " << t.line <<
         ", From: " << t.begin << 
         ", To: " << t.end <<
         ", Identifier: " << t.identifier << std::endl;
    } while(t.typ != jelly::tokenType::END);

    return 0;
}
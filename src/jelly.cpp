#include <iostream>

#include "jelly_lexer.h"

int main() {

    std::ifstream file;
    file.open("example.jelly");
    if(!file.is_open()) return -1;

    jelly_lexer lexer{ file };

    jelly_tokens::token t;
    do {
        t = lexer.next_token();
        std::cout << t.typ << ", " << t.identifier << ", From: (" << t.line_begin << ", " << t.chr_begin << "), To: (" << t.line_end << ", " << t.chr_end << ")" << std::endl;
    } while(t.typ != jelly_tokens::token_type::END_OF_FILE);

    file.close();

    return 0;
}
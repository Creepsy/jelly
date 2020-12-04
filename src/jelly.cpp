#include <iostream>

#include "jelly_parser.h"

int main() {

    std::ifstream file;
    file.open("example.jelly");
    if(!file.is_open()) return -1;

    jelly_lexer lexer{ file };

    jelly_tokens::token t;
    do {
        t = lexer.next_token();
        std::cout << t.typ << ", " << t.identifier << ", From: (" << t.seq.begin.line << ", " << t.seq.begin.chr << "), To: (" << t.seq.end.line << ", " << t.seq.end.chr << ")" << std::endl;
    } while(t.typ != jelly_tokens::token_type::END_OF_FILE);

    file.close();

    return 0;
}
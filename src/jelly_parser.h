#pragma once

#include <vector>

#include "jelly_lexer.h"
#include "jelly_ast.h"

namespace jelly {
    class jelly_parser {
        private:
            jelly_lexer& lexer;
            token next;

            void consume();
            bool accept(tokenType type);
            bool accept(const std::vector<tokenType>& type);
            void expect(tokenType type);
            void expect(const std::vector<tokenType>& type);
            branch* parseSum();
            branch* parseMultiplication();
            branch* parseValue();
        public:
            jelly_parser(jelly_lexer& lexer);
            branch* parse();
            ~jelly_parser();
    };
} 
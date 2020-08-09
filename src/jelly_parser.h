#pragma once

#include "jelly_lexer.h"

namespace jelly {
    class jelly_parser {
        private:
            jelly_lexer& lexer;
            token next;

            void consume();
            bool accept(tokenType type);
        public:
            jelly_parser(jelly_lexer& lexer);
            ~jelly_parser();
    };
} 
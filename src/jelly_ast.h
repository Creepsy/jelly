#pragma once

#include <string>

#include "jelly_lexer.h"

namespace jelly {

    
    class branch {
        public:
            branch();
            virtual std::string to_string() = 0;
            virtual ~branch();
    };

    class binary_expression : public branch {
        public:
            branch* left;
            branch* right;
            tokenType op;

            binary_expression(branch* left, branch* right, tokenType op);
            std::string to_string() override;
            ~binary_expression();
    };

    class const_expression : public branch {
        public:
            tokenType typ;
            std::string value;

            const_expression(tokenType typ, std::string value);
            std::string to_string() override;
            ~const_expression();
    };
}
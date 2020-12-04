#pragma once

#include "branch.h"

namespace arithmetrics {

    enum binary_operators {
        ADD,
        SUBSTRACT,
        MULTIPLY,
        DIVIDE
    };

    class binary_operation : public branch {
        private:
            branch* left;
            branch* right;

            binary_operators op;
        public:
            binary_operation(sequence seq, branch* left, branch* right, binary_operators op);
            std::string to_string() override;
            ~binary_operation();
    };
}
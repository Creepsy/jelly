#pragma once

#include "branch.h"

namespace arithmetrics {
    class binary_operation : public branch {
        private:
            branch* left;
            branch* right;
        public:
            binary_operation();
            std::string to_string() override;
            ~binary_operation();
    };
}
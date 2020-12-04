#pragma once

#include <string>

#include "positional_types.h"

class branch {
    private:
        sequence seq;
    public:
        branch(sequence seq);
        sequence get_sequence();
        virtual std::string to_string() = 0;
        virtual ~branch();
};
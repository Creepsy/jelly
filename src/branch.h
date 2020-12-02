#pragma once

#include <string>

struct position {
    size_t line_begin;
    size_t chr_begin;

    size_t line_end;
    size_t chr_end;
};

class branch {
    private:
        position pos;
    public:
        branch(position pos);
        virtual std::string to_string() = 0;
        virtual ~branch();
};
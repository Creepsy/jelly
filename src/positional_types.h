#pragma once

#include <stddef.h>

struct position {
    size_t line;
    size_t chr;
};

struct sequence {
    position begin;

    position end;
};
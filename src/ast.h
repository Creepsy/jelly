#pragma once

#include <string>

class ast
{
private:
public:
    ast();
    virtual std::string to_string() = 0;
    virtual ~ast() = 0;
};
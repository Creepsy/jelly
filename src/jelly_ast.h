#pragma once

#include <string>
#include <vector>

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

    class unary_expression : public branch {
        public:
            tokenType sign;
            branch* value;

            unary_expression(tokenType sign, branch* value);
            std::string to_string() override;
            ~unary_expression();
    };

    class variable_expression : public branch {
        public:
            std::string identifier;

            variable_expression(std::string identifier);
            std::string to_string() override;
            ~variable_expression();
    };

    class assign_statement : public branch {
        public:
            std::string identifier;
            branch* value;

            assign_statement(std::string identifier, branch* value);
            std::string to_string() override;
            ~assign_statement();
    };

    class define_statement : public branch {
        public:
            std::string identifier;
            tokenType typ;

            define_statement(std::string identifier, tokenType typ);
            std::string to_string() override;
            ~define_statement();
    };

    class initialize_statement : public branch {
        public:
            std::string identifier;
            tokenType typ;
            branch* value;

            initialize_statement(std::string identifier, tokenType typ, branch* value);
            std::string to_string() override;
            ~initialize_statement();
    };

    class struct_define_statement : public branch {
        public:
            std::string identifier;
            std::string struct_type;

            struct_define_statement(std::string identifier, std::string struct_type);
            std::string to_string() override;
            ~struct_define_statement();
    };

    class struct_initialize_statement : public branch {
        public:
            std::string identifier;
            std::string struct_type;
            branch* value;

            struct_initialize_statement(std::string identifier, std::string struct_type, branch* value);
            std::string to_string() override;
            ~struct_initialize_statement();
    };

    class struct_instance_expression : public branch {
        public:
            std::string struct_type;
            branch* initializer_list;

            struct_instance_expression(std::string struct_type, branch* initializer_list);
            std::string to_string() override;
            ~struct_instance_expression();
    };

    class list_expression : public branch {
        public:
            std::vector<branch*> elements;
            size_t length;

            list_expression(std::vector<branch*> elements, size_t length);
            std::string to_string() override;
            ~list_expression();
    };
}
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
            branch* parse_sum();
            branch* parse_multiplication();
            branch* parse_value();
            branch* parse_parenthesis();
            branch* parse_comparison();
            branch* parse_equation();
            branch* parse_unary();
            branch* parse_statement();
            branch* parse_assign_statement();
            branch* parse_define_statement();
            branch* parse_struct_define_statement(std::string type_string);
            branch* parse_list();
            branch* parse_struct_instance();
            branch* parse_array(std::string type_string);
        public:
            jelly_parser(jelly_lexer& lexer);
            branch* parse();
            ~jelly_parser();
    };
} 
#include "jelly_lexer.h"

#include <iostream>

jelly::jelly_lexer::jelly_lexer(std::istream& input) : input(input), line(0), character(0) {
}

jelly::token jelly::jelly_lexer::next_token() {
    char next = this -> input.get();
    this -> character++;
    if(!this -> input.fail()) {
        if(std::isspace(next)) {
            while(std::isspace(next)) {
                if(next == '\n') {
                    this -> character = 0;
                    this -> line++;
                }
                next = this -> input.get();
                this -> character++;
            }
        }

        if(next == '#') {
            next = this -> input.get();
            bool multiline = (next == '#');
            if(multiline) {
                bool start_end = false;
                while(!this -> input.fail()) {
                    next = this -> input.get();
                    this -> character++;

                    if(next == '\n') {
                        this -> character = 0;
                        this -> line++;
                    }

                    if(next == '#'){
                        if(start_end) {
                            break;
                        } else {
                            start_end = true;
                        }
                    } else {
                        if(start_end) start_end = false;
                    }
                }
                if(this -> input.fail()) throw std::runtime_error("Expected comment end \'##\', found EOF");
                return this -> next_token();
            } else {
                while(next != '\n' && !this -> input.fail()) {
                    next = this -> input.get();
                    this -> character++;
                }
                if(!this -> input.fail()) {
                    this -> character = 0;
                    this -> line++;
                } else {
                    return token{tokenType::END, "END", this -> line, this -> character - 1, this -> character};
                }
                return this -> next_token();
            }
        }

        if(std::isdigit(next) || next == '.') return this -> next_number(next);

        if(next == '*') {
            return token{tokenType::MULTIPLY, "*", this -> line, this -> character - 1, this -> character};
        } else if(next == '/') {
            return token{tokenType::DIVIDE, "/", this -> line, this -> character - 1, this -> character};
        } else if(next == '+') {
            next = this -> input.get();
            this -> character++;
            if(next == '+') {
                return token{tokenType::INCREASE, "++", this -> line, this -> character - 2, this -> character};
            } else {
                this -> input.seekg(-1, std::ios::cur);
                this -> character--;
                return token{tokenType::ADD, "+", this -> line, this -> character - 1, this -> character};
            }
        } else if(next == '-') {
            next = this -> input.get();
            this -> character++;
            if(next == '-') {
                return token{tokenType::DECREASE, "--", this -> line, this -> character - 2, this -> character};
            } else {
                this -> input.seekg(-1, std::ios::cur);
                this -> character--;
                return token{tokenType::SUBSTRACT, "-", this -> line, this -> character - 1, this -> character};
            }
        } else if(next == '%') {
            return token{tokenType::MODULO, "%", this -> line, this -> character - 1, this -> character};
        } else if(next == ';') {
            return token{tokenType::EOL, ";", this -> line, this -> character - 1, this -> character};
        } else if(next == '(') {
            return token{tokenType::O_BRACKET, "(", this -> line, this -> character - 1, this -> character};
        } else if(next == ')') {
            return token{tokenType::C_BRACKET, ")", this -> line, this -> character - 1, this -> character};
        } else if(next == '{') {
            return token{tokenType::O_BRACE, "{", this -> line, this -> character - 1, this -> character};
        } else if(next == '}') {
            return token{tokenType::C_BRACE, "}", this -> line, this -> character - 1, this -> character};
        } else if(next == '[') {
            return token{tokenType::O_S_BRACKET, "[", this -> line, this -> character - 1, this -> character};
        } else if(next == ']') {
            return token{tokenType::C_S_BRACKET, "]", this -> line, this -> character - 1, this -> character};
        } else if(next == '|') {
            return token{tokenType::OR, "|", this -> line, this -> character - 1, this -> character};
        } else if(next == '&') {
            return token{tokenType::AND, "&", this -> line, this -> character - 1, this -> character};
        } else if(next == ',') {
            return token{tokenType::SEPARATOR, ",", this -> line, this -> character - 1, this -> character};
        } else if(next == '"') {
            return token{tokenType::QUOTE, "\"", this -> line, this -> character - 1, this -> character};
        } else if(next == '=') {
            next = this -> input.get();
            this -> character++;
            if(next == '=') {
                return token{tokenType::EQUALS, "==", this -> line, this -> character - 2, this -> character};
            } else {
                this -> input.seekg(-1, std::ios::cur);
                this -> character--;
                return token{tokenType::ASSIGN, "=", this -> line, this -> character - 1, this -> character};
            }
        } else if(next == '>') {
            next = this -> input.get();
            this -> character++;
            if(next == '=') {
                return token{tokenType::GREATER_EQUALS, ">=", this -> line, this -> character - 2, this -> character};
            } else {
                this -> input.seekg(-1, std::ios::cur);
                this -> character--;
                return token{tokenType::GREATER, ">", this -> line, this -> character - 1, this -> character};
            }
            
        } else if(next == '<') {
            next = this -> input.get();
            this -> character++;
            if(next == '=') {
                return token{tokenType::SMALLER_EQUALS, "<=", this -> line, this -> character - 2, this -> character};
            } else {
                this -> input.seekg(-1, std::ios::cur);
                this -> character--;
                return token{tokenType::SMALLER, "<", this -> line, this -> character - 1, this -> character};
            }
            
        } else if(next == '!') {
            next = this -> input.get();
            this -> character++;
            if(next == '=') {
                return token{tokenType::NOT_EQUALS, "!=", this -> line, this -> character - 2, this -> character};
            } else {
                this -> input.seekg(-1, std::ios::cur);
                this -> character--;
                return token{tokenType::NOT, "!", this -> line, this -> character - 1, this -> character};
            }     
        }

        if(std::isalpha(next) || next == '_') {
            size_t start = this -> character - 1;
            std::string ident;

            while(std::isalnum(next) && !this -> input.fail() || next == '_') {
                ident.push_back(next);
                next = this -> input.get();
                this -> character++;
            }

            this -> input.seekg(-1, std::ios::cur);
            this -> character--;

            return token{this -> check_keywords(ident), ident, this -> line, start, this -> character};
        }
        return token{tokenType::UNDEFINED, std::string(1, next), this -> line, this -> character - 1, this -> character};
    }

    return token{tokenType::END, "END", this -> line, this -> character - 1, this -> character};
}

jelly::token jelly::jelly_lexer::next_number(const char curr) {
    size_t line = this -> line;
    size_t start = this -> character - 1;
    std::string number;
    number.push_back(curr);

    char next = this -> input.get();
    this -> character++;

    if(curr == '.' && !std::isdigit(next)) {
        this -> input.seekg(-1, std::ios::cur);
        this -> character--;

        return token{tokenType::DOT, number, line, start, this -> character};
    }

    bool is_float = false;

    if(curr == '.') is_float = true;

    while(!this -> input.fail() && (std::isdigit(next) || next == '.')) {
        if(is_float && next == '.') throw std::runtime_error("Number parse error at Ln " + std::to_string(line) + ", Col " + std::to_string(this -> character - 1));
        if(next == '.') is_float = true;
        number.push_back(next);

        next = this -> input.get();
        this -> character++;
    }

    this -> input.seekg(-1, std::ios::cur);
    this -> character--;

    return (is_float) ? token{tokenType::FLOAT, number, line, start, this -> character} : token{tokenType::INT, number, line, start, this -> character};
}

jelly::tokenType jelly::jelly_lexer::check_keywords(const std::string& ident) {
    if(ident == "if") {
        return tokenType::IF;
    } else if(ident == "else") {
        return tokenType::ELSE;
    } else if(ident == "for") {
        return tokenType::FOR;
    } else if(ident == "while") {
        return tokenType::WHILE;
    } else if(ident == "func") {
        return tokenType::FUNCTION;
    } else if(ident == "int") {
        return tokenType::TYPE_INT;
    } else if(ident == "float") {
        return tokenType::TYPE_FLOAT;
    } else if(ident == "bool") {
        return tokenType::TYPE_BOOL;
    } else if(ident == "string") {
        return tokenType::TYPE_STRING;
    } else if(ident == "struct") {
        return tokenType::STRUCT;
    } else if(ident == "void") {
        return tokenType::VOID;
    } else if(ident == "true") {
        return tokenType::TRUE;
    } else if(ident == "false") {
        return tokenType::FALSE;
    } else if(ident == "import") {
        return tokenType::IMPORT;
    } else if(ident == "return") {
        return tokenType::RETURN;
    } else if(ident == "break") {
        return tokenType::BREAK;
    }

    return tokenType::IDENTIFIER;
}

jelly::jelly_lexer::~jelly_lexer() {
}
#include "jelly_lexer.h"

using namespace jelly_tokens;

jelly_lexer::jelly_lexer(std::ifstream& inp) : inp(inp), chr(0), line(0) {
}

token jelly_lexer::next_token() {
    char next = this->next_chr();
    if(!this->inp.fail()) {
        if(std::isspace(next)) {
            this->clear_wspace(next);
            return this->next_token();
        }
        
        token op = this->get_operator(next);
        if(op.typ != token_type::NONE) return op;

        if(next == '.' || std::isdigit(next)) {
            return this->get_number(next);
        }

        if(std::isalpha(next) || next == '_') {
            size_t start_chr = this->chr - 1, start_line = this->line;
            std::string ident = this->get_identifier(next);
            return token{ this->get_keyword(ident), ident, start_line, start_chr, this->line, this->chr };
        }

        return token{ token_type::NONE, "NONE", this->line, this->chr - 1, this->line, this->chr };
    }

    return token{ token_type::END_OF_FILE, "EOF", this->line, this->chr - 1, this->line, this->chr };
}

jelly_lexer::~jelly_lexer() {

}

//private

char jelly_lexer::next_chr() {
    this->chr++;
    return this->inp.get();
}

void jelly_lexer::prev_chr() {
    this->inp.seekg(-1, std::ios::cur);
    this->chr--;
}

void jelly_lexer::clear_wspace(char next) {
    while(std::isspace(next) && !this->inp.fail()) {
        if(next == '\n') {
            this->chr = 0;
            this->line++;
        }
        next = this->next_chr();
    }
    this->prev_chr();
}

token jelly_lexer::get_operator(char next) {
    switch (next) {
        case '|':
            return token{ token_type::OR, "|", this->line, this->chr - 1, this->line, this->chr };
        case '&':
            return token{ token_type::AND, "&", this->line, this->chr - 1, this->line, this->chr };
        case '=':
            next = this->next_chr();
            if(next == '=') return token{ token_type::EQUALS, "==", this->line, this->chr - 2, this->line, this->chr };
            this->prev_chr();
            return token{ token_type::ASSIGN, "=", this->line, this->chr - 1, this->line, this->chr };
        case '+':
            next = this->next_chr();
            if(next == '=') return token{ token_type::ADD_ASSIGN, "+=", this->line, this->chr - 2, this->line, this->chr };
            if(next == '+') return token{ token_type::INCR, "++", this->line, this->chr - 2, this->line, this->chr };
            this->prev_chr();
            return token{ token_type::ADD, "+", this->line, this->chr - 1, this->line, this->chr };
        case '-':
            next = this->next_chr();
            if(next == '=') return token{ token_type::SUB_ASSIGN, "-=", this->line, this->chr - 2, this->line, this->chr };
            if(next == '-') return token{ token_type::DECR, "--", this->line, this->chr - 2, this->line, this->chr };
            this->prev_chr();
            return token{ token_type::SUB, "-", this->line, this->chr - 1, this->line, this->chr };
        case '*':
            next = this->next_chr();
            if(next == '=') return token{ token_type::MUL_ASSIGN, "*=", this->line, this->chr - 2, this->line, this->chr };
            this->prev_chr();
            return token{ token_type::MUL, "*", this->line, this->chr - 1, this->line, this->chr };
        case '/':
            next = this->next_chr();
            if(next == '=') return token{ token_type::DIV_ASSIGN, "/=", this->line, this->chr - 2, this->line, this->chr };
            this->prev_chr();
            return token{ token_type::DIV, "/", this->line, this->chr - 1, this->line, this->chr };
        case '^':
            next = this->next_chr();
            if(next == '=') return token{ token_type::POW_ASSIGN, "^=", this->line, this->chr - 2, this->line, this->chr };
            this->prev_chr();
            return token{ token_type::POW, "^", this->line, this->chr - 1, this->line, this->chr };
        case '%':
            next = this->next_chr();
            if(next == '=') return token{ token_type::MOD_ASSIGN, "%=", this->line, this->chr - 2, this->line, this->chr };
            this->prev_chr();
            return token{ token_type::MOD, "%", this->line, this->chr - 1, this->line, this->chr };
        case '>':
            next = this->next_chr();
            if(next == '=') return token{ token_type::GREATER_EQ, ">=", this->line, this->chr - 2, this->line, this->chr };
            this->prev_chr();
            return token{ token_type::GREATER, ">", this->line, this->chr - 1, this->line, this->chr };
        case '<':
            next = this->next_chr();
            if(next == '=') return token{ token_type::SMALLER_EQ, "<=", this->line, this->chr - 2, this->line, this->chr };
            this->prev_chr();
            return token{ token_type::SMALLER, "<", this->line, this->chr - 1, this->line, this->chr };
        case '!':
            next = this->next_chr();
            if(next == '=') return token{ token_type::NOT_EQ, "!=", this->line, this->chr - 2, this->line, this->chr };
            this->prev_chr();
            return token{ token_type::NOT, "!", this->line, this->chr - 1, this->line, this->chr };
        case ',':
            return token{ token_type::COMMA, ",", this->line, this->chr - 1, this->line, this->chr };
        case ';':
            return token{ token_type::LINE_END, ";", this->line, this->chr - 1, this->line, this->chr };
        case '(':
            return token{ token_type::BRACKET_OPEN, "(", this->line, this->chr - 1, this->line, this->chr };
        case ')':
            return token{ token_type::BRACKET_CLOSE, ")", this->line, this->chr - 1, this->line, this->chr };
        case '{':
            return token{ token_type::CUR_BRACKET_OPEN, "{", this->line, this->chr - 1, this->line, this->chr };
        case '}':
            return token{ token_type::CUR_BRACKET_CLOSE, "}", this->line, this->chr - 1, this->line, this->chr };
        case '[':
            return token{ token_type::SQ_BRACKET_OPEN, "[", this->line, this->chr - 1, this->line, this->chr };
        case ']':
            return token{ token_type::SQ_BRACKET_CLOSE, "]", this->line, this->chr - 1, this->line, this->chr };
            
        default:
            return token{ token_type::NONE, "NONE", this->line, this->chr - 1, this->line, this->chr };
    }
}

token jelly_lexer::get_number(char next) {
    size_t start_chr = this->chr - 1, start_line = this->line;

    bool is_float = false;
    std::string num;

    while (std::isdigit(next) || next == '.') {
        if(next == '.') {
            if(is_float) this->throw_error("InvalidNumberFormat - can't have more than one '.' in a number!");
            is_float = true;
        }
        num += next;
        next = this->next_chr();
    }
    this->prev_chr();

    if(is_float && num.size() == 1) this->throw_error("InvalidNumberFormat - a number can't consist out of a single '.'!");
    return token{ (is_float) ? token_type::FLOAT : token_type::INT, num, start_line, start_chr, this->line, this->chr };
}

void jelly_lexer::throw_error(std::string err) {
    throw std::runtime_error("[Ln " + std::to_string(this->line) + ", Col " + std::to_string(this->chr) + "]: " + err);
}

std::string jelly_lexer::get_identifier(char next) {
    std::string ident;

    do {
        ident += next;
        next = this->next_chr();
    } while(std::isalnum(next) || next == '_');
    this->prev_chr();

    return ident;
}

token_type jelly_lexer::get_keyword(std::string ident) {
    if(ident == "int") {
        return token_type::INT_IDENT;
    } else if(ident == "float") {
        return token_type::FLOAT_IDENT;
    } else if(ident == "array") {
        return token_type::ARRAY_IDENT;
    } else if(ident == "string") {
        return token_type::STRING_IDENT;
    } else if(ident == "bool") {
        return token_type::BOOL_IDENT;
    } else if(ident == "func") {
        return token_type::FUNC;
    } else if(ident == "if") {
        return token_type::IF;
    } else if(ident == "else") {
        return token_type::ELSE;
    } else if(ident == "for") {
        return token_type::FOR;
    } else if(ident == "break") {
        return token_type::BREAK;
    } else if(ident == "while") {
        return token_type::WHILE;
    } else if(ident == "return") {
        return token_type::RETURN;
    } else if(ident == "import") {
        return token_type::IMPORT;
    } else if(ident == "true") {
        return token_type::TRUE;
    } else if(ident == "false") {
        return token_type::FALSE;
    }

    return token_type::IDENTIFIER;
}
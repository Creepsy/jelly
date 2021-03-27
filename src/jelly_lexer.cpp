#include "jelly_lexer.h"

using namespace jelly_tokens;

jelly_lexer::jelly_lexer(std::ifstream& inp)
 : inp(inp), curr_pos{ position{ 0, 0 } } {
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

        if(next == '#') {
            this->consume_comment();
            return this->next_token();
        }

        if(next == '.' || std::isdigit(next)) {
            return this->get_number(next);
        }

        if(next == '"') {
            return this->get_string();
        }

        if(std::isalpha(next) || next == '_') {
            size_t start_chr = this->curr_pos.chr - 1, start_line = this->curr_pos.line;
            std::string ident = this->get_identifier(next);
            return token{ this->get_keyword(ident), ident, start_line, start_chr, this->curr_pos.line, this->curr_pos.chr };
        }

        return token{ token_type::NONE, "NONE", this->curr_pos.line, this->curr_pos.chr - 1, this->curr_pos.line, this->curr_pos.chr };
    }

    return token{ token_type::END_OF_FILE, "EOF", this->curr_pos.line, this->curr_pos.chr - 1, this->curr_pos.line, this->curr_pos.chr };
}

position jelly_lexer::get_current_position() {
    return this->curr_pos;
}

jelly_lexer::~jelly_lexer() {

}

//private

char jelly_lexer::next_chr() {
    this->curr_pos.chr++;
    return this->inp.get();
}

void jelly_lexer::prev_chr() {
    this->inp.seekg(-1, std::ios::cur);
    this->curr_pos.chr--;
}

void jelly_lexer::clear_wspace(char next) {
    while(std::isspace(next) && !this->inp.fail()) {
        if(next == '\n') {
            this->curr_pos.chr = 0;
            this->curr_pos.line++;
        }
        next = this->next_chr();
    }
    this->prev_chr();
}

token jelly_lexer::get_operator(char next) {
    switch (next) {
        case '|':
            return token{ token_type::OR, "|", this->curr_pos.line, this->curr_pos.chr - 1, this->curr_pos.line, this->curr_pos.chr };
        case '&':
            return token{ token_type::AND, "&", this->curr_pos.line, this->curr_pos.chr - 1, this->curr_pos.line, this->curr_pos.chr };
        case '=':
            next = this->next_chr();
            if(next == '=') return token{ token_type::EQUALS, "==", this->curr_pos.line, this->curr_pos.chr - 2, this->curr_pos.line, this->curr_pos.chr };
            this->prev_chr();
            return token{ token_type::ASSIGN, "=", this->curr_pos.line, this->curr_pos.chr - 1, this->curr_pos.line, this->curr_pos.chr };
        case '+':
            next = this->next_chr();
            if(next == '=') return token{ token_type::ADD_ASSIGN, "+=", this->curr_pos.line, this->curr_pos.chr - 2, this->curr_pos.line, this->curr_pos.chr };
            if(next == '+') return token{ token_type::INCR, "++", this->curr_pos.line, this->curr_pos.chr - 2, this->curr_pos.line, this->curr_pos.chr };
            this->prev_chr();
            return token{ token_type::ADD, "+", this->curr_pos.line, this->curr_pos.chr - 1, this->curr_pos.line, this->curr_pos.chr };
        case '-':
            next = this->next_chr();
            if(next == '=') return token{ token_type::SUB_ASSIGN, "-=", this->curr_pos.line, this->curr_pos.chr - 2, this->curr_pos.line, this->curr_pos.chr };
            if(next == '-') return token{ token_type::DECR, "--", this->curr_pos.line, this->curr_pos.chr - 2, this->curr_pos.line, this->curr_pos.chr };
            this->prev_chr();
            return token{ token_type::SUB, "-", this->curr_pos.line, this->curr_pos.chr - 1, this->curr_pos.line, this->curr_pos.chr };
        case '*':
            next = this->next_chr();
            if(next == '=') return token{ token_type::MUL_ASSIGN, "*=", this->curr_pos.line, this->curr_pos.chr - 2, this->curr_pos.line, this->curr_pos.chr };
            this->prev_chr();
            return token{ token_type::MUL, "*", this->curr_pos.line, this->curr_pos.chr - 1, this->curr_pos.line, this->curr_pos.chr };
        case '/':
            next = this->next_chr();
            if(next == '=') return token{ token_type::DIV_ASSIGN, "/=", this->curr_pos.line, this->curr_pos.chr - 2, this->curr_pos.line, this->curr_pos.chr };
            this->prev_chr();
            return token{ token_type::DIV, "/", this->curr_pos.line, this->curr_pos.chr - 1, this->curr_pos.line, this->curr_pos.chr };
        case '^':
            next = this->next_chr();
            if(next == '=') return token{ token_type::POW_ASSIGN, "^=", this->curr_pos.line, this->curr_pos.chr - 2, this->curr_pos.line, this->curr_pos.chr };
            this->prev_chr();
            return token{ token_type::POW, "^", this->curr_pos.line, this->curr_pos.chr - 1, this->curr_pos.line, this->curr_pos.chr };
        case '%':
            next = this->next_chr();
            if(next == '=') return token{ token_type::MOD_ASSIGN, "%=", this->curr_pos.line, this->curr_pos.chr - 2, this->curr_pos.line, this->curr_pos.chr };
            this->prev_chr();
            return token{ token_type::MOD, "%", this->curr_pos.line, this->curr_pos.chr - 1, this->curr_pos.line, this->curr_pos.chr };
        case '>':
            next = this->next_chr();
            if(next == '=') return token{ token_type::GREATER_EQ, ">=", this->curr_pos.line, this->curr_pos.chr - 2, this->curr_pos.line, this->curr_pos.chr };
            this->prev_chr();
            return token{ token_type::GREATER, ">", this->curr_pos.line, this->curr_pos.chr - 1, this->curr_pos.line, this->curr_pos.chr };
        case '<':
            next = this->next_chr();
            if(next == '=') return token{ token_type::SMALLER_EQ, "<=", this->curr_pos.line, this->curr_pos.chr - 2, this->curr_pos.line, this->curr_pos.chr };
            this->prev_chr();
            return token{ token_type::SMALLER, "<", this->curr_pos.line, this->curr_pos.chr - 1, this->curr_pos.line, this->curr_pos.chr };
        case '!':
            next = this->next_chr();
            if(next == '=') return token{ token_type::NOT_EQ, "!=", this->curr_pos.line, this->curr_pos.chr - 2, this->curr_pos.line, this->curr_pos.chr };
            this->prev_chr();
            return token{ token_type::NOT, "!", this->curr_pos.line, this->curr_pos.chr - 1, this->curr_pos.line, this->curr_pos.chr };
        case ',':
            return token{ token_type::COMMA, ",", this->curr_pos.line, this->curr_pos.chr - 1, this->curr_pos.line, this->curr_pos.chr };
        case ';':
            return token{ token_type::LINE_END, ";", this->curr_pos.line, this->curr_pos.chr - 1, this->curr_pos.line, this->curr_pos.chr };
        case '(':
            return token{ token_type::BRACKET_OPEN, "(", this->curr_pos.line, this->curr_pos.chr - 1, this->curr_pos.line, this->curr_pos.chr };
        case ')':
            return token{ token_type::BRACKET_CLOSE, ")", this->curr_pos.line, this->curr_pos.chr - 1, this->curr_pos.line, this->curr_pos.chr };
        case '{':
            return token{ token_type::CUR_BRACKET_OPEN, "{", this->curr_pos.line, this->curr_pos.chr - 1, this->curr_pos.line, this->curr_pos.chr };
        case '}':
            return token{ token_type::CUR_BRACKET_CLOSE, "}", this->curr_pos.line, this->curr_pos.chr - 1, this->curr_pos.line, this->curr_pos.chr };
        case '[':
            return token{ token_type::SQ_BRACKET_OPEN, "[", this->curr_pos.line, this->curr_pos.chr - 1, this->curr_pos.line, this->curr_pos.chr };
        case ']':
            return token{ token_type::SQ_BRACKET_CLOSE, "]", this->curr_pos.line, this->curr_pos.chr - 1, this->curr_pos.line, this->curr_pos.chr };
            
        default:
            return token{ token_type::NONE, "NONE", this->curr_pos.line, this->curr_pos.chr - 1, this->curr_pos.line, this->curr_pos.chr };
    }
}

token jelly_lexer::get_number(char next) {
    size_t start_chr = this->curr_pos.chr - 1, start_line = this->curr_pos.line;

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
    return token{ (is_float) ? token_type::FLOAT : token_type::INT, num, start_line, start_chr, this->curr_pos.line, this->curr_pos.chr };
}

void jelly_lexer::throw_error(const std::string& err) {
    throw std::runtime_error("[Ln " + std::to_string(this->curr_pos.line) + ", Col " + std::to_string(this->curr_pos.chr) + "]: " + err);
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

token_type jelly_lexer::get_keyword(const std::string& ident) {
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

void jelly_lexer::consume_comment() {
    char next;
    do {
        next = this->next_chr();
        if(next == '\n') {
            this->curr_pos.chr = 0;
            this->curr_pos.line++;
        }
    } while(next != '#' && !this->inp.fail());
    if(this->inp.fail()) this->throw_error("Expected comment end, but found EOF!");
}

token jelly_lexer::get_string() {
    size_t start_chr = this->curr_pos.chr - 1, start_line = this->curr_pos.line;
    std::string content;

    char next = this->next_chr();
    while(next != '"' && !this->inp.fail()) {
        if(next == '\n') {
            this->curr_pos.chr = 0;
            this->curr_pos.line++;
        }

        if(next == '\\') {
            next = this->next_chr();
            switch(next) {
                case 'n':
                    content += '\n';
                    break;
                case 't':
                    content += '\t';
                    break;
                case 'b':
                    content += '\b';
                    break;
                case 'r':
                    content += '\r';
                    break;
                case 'f':
                    content += '\f';
                    break;
                case '\"':
                    content += '\"';
                    break;
                case '\\': 
                    content += '\\';
                    break;
                default:
                    this->throw_error("Expected one of the following: { n, t, b, r, f, \", \\ }, found " + std::string(1, next));
            }
        } else {
            content += next;
        }
        
        next = this->next_chr();
    }
    if(this->inp.fail()) this->throw_error("Expected string end, found EOF");

    return token{ token_type::STRING, content, start_line, start_chr, this->curr_pos.line, this->curr_pos.chr };
}
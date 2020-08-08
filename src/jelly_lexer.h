#include <istream>
#include <vector>
#include <string>

namespace jelly {
    const std::vector<std::string> tokenToString = {
        "FLOAT",
        "INT",
        "MULTIPLY",
        "DIVIDE",
        "ADD",
        "SUBSTRACT",
        "MODULO",
        "DOT",
        "OPENING BRACKET",
        "CLOSING BRACKET",
        "OPENING BRACE",
        "CLOSING BRACE",
        "OPENING SQUARE BRACKET",
        "CLOSING SQUARE BRACKET",
        "OR",
        "AND",
        "SEPARATOR",
        "QUOTE",
        "ASSIGN",
        "END OF LINE",
        "END OF FILE"
    };

    enum tokenType {
        FLOAT,
        INT,
        MULTIPLY,
        DIVIDE,
        ADD,
        SUBSTRACT,
        MODULO,
        DOT,
        O_BRACKET,
        C_BRACKET,
        O_BRACE,
        C_BRACE,
        O_S_BRACKET,
        C_S_BRACKET,
        OR,
        AND,
        SEPARATOR,
        QUOTE,
        ASSIGN,
        EOL,
        END
    };

    struct token {
        tokenType typ;
        std::string identifier;
        size_t line;
        size_t begin;
        size_t end;
    };

    class jelly_lexer {
    private:
        std::istream& input;

        size_t line;
        size_t character;

        token next_number(const char curr);
    public:
        jelly_lexer(std::istream& input);
        token next_token();
        ~jelly_lexer();
    };
}
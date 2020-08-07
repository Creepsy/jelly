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
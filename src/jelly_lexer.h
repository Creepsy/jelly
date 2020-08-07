#include <istream>
#include <vector>
#include <string>

namespace jelly {
    const std::vector<std::string> tokenToString = {
        "NUMBER",
        "MULTIPLY",
        "DIVIDE",
        "ADD",
        "SUBSTRACT",
        "MODULO",
        "END OF FILE"
    };

    enum tokenType {
        NUMBER,
        MULTIPLY,
        DIVIDE,
        ADD,
        SUBSTRACT,
        MODULO,
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
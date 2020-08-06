#include <istream>
#include <vector>
#include <string>

namespace jelly {
    const std::vector<std::string> tokenToString = {
        "END OF FILE"
    };

    enum tokenType {
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
    public:
        jelly_lexer(std::istream& input);
        token next_token();
        ~jelly_lexer();
    };
}
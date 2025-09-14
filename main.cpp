#include <vector>
#include <string>
#include "token.h"
#include "lexer.h"
#include "parser.h"

int main(int argc, char const *argv[])
{
    std::string input = "1 - 2 * 3 + 4 / 5";

    Lexer lexer(input);
    std::vector<Token> tokens = lexer.tokenize();
    for (auto& token : tokens) {
	token.print();
    } 
    Parser parser(tokens);
    std::unique_ptr<ASTNode> ast = parser.parse_expression();
    ast->print(); 


    return 0;
}

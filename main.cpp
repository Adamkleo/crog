#include <vector>
#include "token.h"
#include "lexer.h"

int main(int argc, char const *argv[])
{
    std::string input = "f(x) = sin(2) + x^2 * 3!";

    Lexer lexer(input);
    std::string line;
    int lineNumber = 1;
    while (std::getline(input, line)) {
	if (!line.empty() && line.find_first_not_of(" \t") != std::string::npos) {
	    std::vector<Token> tokens = lexer.tokenize(line);
	}
    }
    
    
    
    return 0;
}

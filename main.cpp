#include <vector>
#include <string>
#include "token.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "exception.cpp"

int main(int argc, char* argv[]) {
    try {
        std::string input;
        if (argc > 1) {
            input = argv[1]; 
        }
        else {
            input = "f(x) = 3";
        }
        
        Lexer lexer(input);
        std::vector<Token> tokens = lexer.tokenize();
        Parser parser(tokens);
        std::unique_ptr<ASTNode> ast = parser.parse_function();
        ast->print();
        
    } catch (const SyntaxError& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (const LexicalError& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (const RuntimeError& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (const InterpreterException& e) {
        // Catches any interpreter exception not caught above
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        // Catches any other standard exception
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}

#pragma once
#include "token.hpp"
#include "ast.hpp"
#include <memory>
#include <vector>
#include <algorithm>

class Parser {

private:
    std::vector<Token>& tokens;
    size_t currentIndex;
    std::vector<TokenType> mathFunctions = {TokenType::SIN, TokenType::COS, TokenType::TAN, TokenType::LOG, TokenType::ABS};

    bool current_type_is(TokenType type);

    bool current_type_in(std::vector<TokenType> tokenTypes); 

    TokenValue get_current_value();
    
    Token& current();

    void advance();

    void eat(TokenType tokenType);     

public:
    Parser(std::vector<Token>& t) : tokens(t), currentIndex(0) {};
    
    std::unique_ptr<ASTNode> parse_function();

    std::unique_ptr<ASTNode> parse_expression();
    std::unique_ptr<ASTNode> parse_rest_expression(std::unique_ptr<ASTNode> firstTerm);

    std::unique_ptr<ASTNode> parse_term();
    std::unique_ptr<ASTNode> parse_rest_term(std::unique_ptr<ASTNode> firstFactor);

    std::unique_ptr<ASTNode> parse_unary();
    std::unique_ptr<ASTNode> parse_power();

    std::unique_ptr<ASTNode> parse_factor();


};  

#pragma once

#include "token.h"
#include "ast.h"
#include <memory>

class Parser {

private:
    std::vector<Token>& tokens;
    size_t currentIndex;

    bool current_type_is(TokenType type);

    TokenValue get_current_value();
    
    Token& current();

    void advance();

public:
    Parser(std::vector<Token>& t) : tokens(t), currentIndex(0) {};

    std::unique_ptr<ASTNode> parse_expression();
    std::unique_ptr<ASTNode> parse_rest_expression(std::unique_ptr<ASTNode> firstTerm);

    std::unique_ptr<ASTNode> parse_term();
    std::unique_ptr<ASTNode> parse_rest_term(std::unique_ptr<ASTNode> firstFactor);

    std::unique_ptr<ASTNode> parse_factor();




};  

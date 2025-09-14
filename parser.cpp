#include "parser.h"
#include "ast.h"
#include "token.h"
#include <memory>

bool Parser::current_type_is(TokenType type) {
    return tokens[currentIndex].get_type() == type;
}

TokenValue Parser::get_current_value() {
    return tokens[currentIndex].get_value();
}

Token& Parser::current() {
    return tokens[currentIndex];
}

void Parser::advance() {
    if (current().get_type() != TokenType::_EOF) {
	++currentIndex;
    }
}

std::unique_ptr<ASTNode> Parser::parse_expression() {
    // Parse the first term of the expression
    std::unique_ptr<ASTNode> firstTerm = parse_term();
    // Iteratively parse the chained terms to ensure left associativity 
    return parse_rest_expression(std::move(firstTerm));
}

std::unique_ptr<ASTNode> Parser::parse_rest_expression(std::unique_ptr<ASTNode> firstTerm) {
    while (current_type_is(TokenType::PLUS) || current_type_is(TokenType::MINUS)) {
	char op;
	if (current_type_is(TokenType::PLUS)) {
	    op = '+';
	    advance();
	} else if (current_type_is(TokenType::MINUS)) {
	    op = '-';
	    advance();
	}
	std::unique_ptr<ASTNode> chainedTerm = parse_term();
	firstTerm = std::make_unique<BinaryOpNode>(op, std::move(firstTerm), std::move(chainedTerm));
    } 
    return firstTerm;
}


std::unique_ptr<ASTNode> Parser::parse_term() {
    std::unique_ptr<ASTNode> firstFactor = parse_factor();
    return parse_rest_term(std::move(firstFactor));
}


std::unique_ptr<ASTNode> Parser::parse_rest_term(std::unique_ptr<ASTNode> firstFactor) {
    while (current_type_is(TokenType::MUL) || current_type_is(TokenType::DIV)) {
	char op;
	if (current_type_is(TokenType::MUL)) {
	    op = '*';
	    advance();
	} else if (current_type_is(TokenType::DIV)) {
	    op = '/';
	    advance();
	}
	std::unique_ptr<ASTNode> chainedFactor = parse_factor();
	firstFactor = std::make_unique<BinaryOpNode>(op, std::move(firstFactor), std::move(chainedFactor));
    }
    return firstFactor;
}


std::unique_ptr<ASTNode> Parser::parse_factor() {
    if (current_type_is(TokenType::LPAREN)) {
	advance();
	std::unique_ptr<ASTNode> exprNode = parse_expression();
	advance();
	return exprNode;

    } else {
	auto numNode = std::make_unique<NumberNode>(std::get<double>(get_current_value()));
	advance();
	return numNode;
    }
} 



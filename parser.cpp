#include "parser.hpp"
#include "exception.cpp"

bool Parser::current_type_is(TokenType type) {
    return tokens[currentIndex].get_type() == type;
}

bool Parser::current_type_in(std::vector<TokenType> tokenTypes) {
    return std::count(tokenTypes.begin(), tokenTypes.end(), tokens[currentIndex].get_type()) == 1;
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

void Parser::eat(TokenType tokenType) {
    if (current().get_type() == tokenType) {
	advance();
    } else {
	throw SyntaxError("Invalid Syntax"); 
    }
}


std::unique_ptr<ASTNode> Parser::parse_function() {
    if (current_type_is(TokenType::IDENTIFIER)) {
	std::string functionIdentifier = std::get<std::string>(get_current_value());
	eat(TokenType::IDENTIFIER);
	eat(TokenType::LPAREN);
	std::string parameter = std::get<std::string>(get_current_value());
	eat(TokenType::IDENTIFIER);
	eat(TokenType::RPAREN);
	eat(TokenType::EQUAL);
	std::unique_ptr<ASTNode> functionBody = parse_expression();
	return std::make_unique<FunctionNode>(functionIdentifier, parameter, std::move(functionBody));
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
	    eat(TokenType::PLUS);
	} else if (current_type_is(TokenType::MINUS)) {
	    op = '-';
	    eat(TokenType::MINUS);
	}
	std::unique_ptr<ASTNode> chainedTerm = parse_term();
	firstTerm = std::make_unique<BinaryOpNode>(op, std::move(firstTerm), std::move(chainedTerm));
    } 
    return firstTerm;
}



std::unique_ptr<ASTNode> Parser::parse_term() {
    std::unique_ptr<ASTNode> firstFactor = parse_unary();
    return parse_rest_term(std::move(firstFactor));
}



std::unique_ptr<ASTNode> Parser::parse_rest_term(std::unique_ptr<ASTNode> firstFactor) {
    while (current_type_is(TokenType::MUL) || current_type_is(TokenType::DIV)) {
	char op;
	if (current_type_is(TokenType::MUL)) {
	    op = '*';
	    eat(TokenType::MUL);
	} else if (current_type_is(TokenType::DIV)) {
	    op = '/';
	    eat(TokenType::DIV);
	}
	std::unique_ptr<ASTNode> chainedFactor = parse_unary();
	firstFactor = std::make_unique<BinaryOpNode>(op, std::move(firstFactor), std::move(chainedFactor));
    }
    return firstFactor;
}


std::unique_ptr<ASTNode> Parser::parse_unary() {
    if (current_type_is(TokenType::MINUS)) {
	eat(TokenType::MINUS);
	char op = '-';
        return std::make_unique<UnaryOpNode>(op, parse_power());
    }
    return parse_power();
}

std::unique_ptr<ASTNode> Parser::parse_power() {
    std::unique_ptr<ASTNode> factor = parse_factor();
    if (current_type_is(TokenType::POW)) {
        eat(TokenType::POW);
        return std::make_unique<BinaryOpNode>('^', std::move(factor), parse_power());
    }
    return factor;
}


std::unique_ptr<ASTNode> Parser::parse_factor() {
    if (current_type_is(TokenType::LPAREN)) {
	eat(TokenType::LPAREN);
	std::unique_ptr<ASTNode> exprNode = parse_expression();
	eat(TokenType::RPAREN);
	return exprNode;

    } else if (current_type_is(TokenType::NUMBER)) {
	auto numNode = std::make_unique<NumberNode>(std::get<double>(get_current_value()));
	eat(TokenType::NUMBER);
	return numNode;
    } else if (current_type_is(TokenType::IDENTIFIER)) {
	auto identifierNode = std::make_unique<IdentifierNode>(std::get<std::string>(get_current_value()));
	eat(TokenType::IDENTIFIER);
	return identifierNode;
    } else if (current_type_in(mathFunctions)) {
	// cleaner way to do this
	std::string functionName = std::get<std::string>(get_current_value());
	eat(tokens[currentIndex].get_type());
	eat(TokenType::LPAREN);
	std::unique_ptr<ASTNode> functionArg = parse_expression();
	auto inlineFunctionNode = std::make_unique<InlineFunctionNode>(functionName, std::move(functionArg));
	return inlineFunctionNode;
    }
} 












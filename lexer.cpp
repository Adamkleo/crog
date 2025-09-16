#include "lexer.hpp"
#include <vector>


void Lexer::_advance() {
    ++pos;
    if ((size_t) pos < input.length()) {
	currentChar = input[pos];
    } else {
	currentChar = '\0';
    }
}
Lexer::Lexer(std::string i) {
    if (!std::empty(i)) {
	input = i;
	currentChar = input[0];
    }
    // do something when input is empty
} 


Token Lexer::number() {
    std::string tokenValue = "";

    do {
	tokenValue += currentChar;
	_advance();
    } while (std::isdigit(currentChar));
    
    if (currentChar == '.') {
	tokenValue += currentChar;
	_advance();

	while (std::isdigit(currentChar)) {
	    tokenValue += currentChar;
	    _advance();
	}
    }
    
    return Token(TokenType::NUMBER, tokenValue, std::stod(tokenValue));

}

Token Lexer::alpha() {
    std::string tokenValue = "";

    do {
	tokenValue += currentChar;
	_advance();
    } while (std::isalpha(currentChar));

    if (symbol_map.count(tokenValue)) {
	return Token(symbol_map.at(tokenValue), tokenValue, tokenValue);
    }

    return Token(TokenType::IDENTIFIER, tokenValue, tokenValue);
}

Token Lexer::symbol() {
    std::string lexeme(1, currentChar);
    TokenType tokenType = symbol_map.at(lexeme);
    TokenValue tokenValue = currentChar;
    _advance();
    return Token(tokenType, lexeme, tokenValue);
}


Token Lexer::get_next_token() {
    while (currentChar != '\0') {
	if (std::isspace(currentChar)) _advance();
	  
	// comment found
	if (currentChar == '#') {
	    do {
		_advance();
	    } while (currentChar != '\n');
	}

	if (isSymbol(currentChar)) {
	    return symbol();
	}

	if (std::isdigit(currentChar)) {
	    return number();
	}

	if (std::isalpha(currentChar)) {
	    return alpha();
	}
	
    }
    return Token(TokenType::_EOF, "", "");
}

bool Lexer::isSymbol(char c) {
    return symbol_map.count(std::string(1, c));
}

    
std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    Token token = get_next_token();
    while (token.get_type() != TokenType::_EOF) {
        tokens.push_back(token);
	token = get_next_token();
    }
    return tokens;
}





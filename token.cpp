// token.cpp

#include "token.hpp"


std::string Token::to_string(TokenType t) {
    switch (t) {
	case TokenType::_EOF: return "_EOF";
	case TokenType::NUMBER: return "NUMBER";
	case TokenType::IDENTIFIER: return "IDENTIFIER";
	case TokenType::PLUS: return "PLUS";
	case TokenType::MINUS: return "MINUS";
	case TokenType::MUL: return "MUL";
	case TokenType::DIV: return "DIV";
	case TokenType::POW: return "POW";
	case TokenType::EQUAL: return "EQUAL";
	case TokenType::FACTORIAL: return "FACTORIAL";
	case TokenType::PRIME: return "PRIME";
	case TokenType::LPAREN: return "LPAREN";
	case TokenType::RPAREN: return "RPAREN";
	case TokenType::COMMA: return "COMMA";
	case TokenType::LBRACKET: return "LBRACKET";
	case TokenType::RBRACKET: return "RBRACKET";
	case TokenType::SIN: return "SIN";
	case TokenType::COS: return "COS";
	case TokenType::TAN: return "TAN";
	case TokenType::LOG: return "LOG";
	case TokenType::ABS: return "ABS";
    }
}

// Constructor takes a the type of the token, the string literal (no matter the type), and the value of the token in its original datatype
Token::Token(TokenType t, std::string l, TokenValue v): type(t), lexeme(l), value(v) {};

TokenType Token::get_type() {
    return type;
}

TokenValue Token::get_value() {
    return value;
}

void Token::print() {
    std::cout << "Token(" << to_string(type) << ", " << lexeme << ")" << std::endl;
}
    




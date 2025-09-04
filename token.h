#pragma once

#include <string>
#include <iostream>
#include <cctype>
#include <unordered_map>


enum class TokenType {
    _EOF,
    NUMBER,
    IDENTIFIER,
    PLUS,
    MINUS,
    MUL,
    DIV,
    POW,
    EQUAL,
    FACTORIAL,
    PRIME,
    LPAREN,
    RPAREN,
    COMMA,
    LBRACKET,
    RBRACKET,
    SIN,
    COS,
    TAN,
    LOG,
    ABS
};

const std::unordered_map<std::string, TokenType> symbol_map = {
    {"+", TokenType::PLUS},
    {"-", TokenType::MINUS},
    {"*", TokenType::MUL},
    {"/", TokenType::DIV},
    {"^", TokenType::POW},
    {"=", TokenType::EQUAL},
    {"!", TokenType::FACTORIAL},
    {"'", TokenType::PRIME},
    {"(", TokenType::LPAREN},
    {")", TokenType::RPAREN},
    {",", TokenType::COMMA},
    {"[", TokenType::LBRACKET},
    {"]", TokenType::RBRACKET},
    {"sin", TokenType::SIN},
    {"cos", TokenType::COS},
    {"tan", TokenType::TAN},
    {"log", TokenType::LOG},
    {"abs", TokenType::ABS}
};


using TokenValue = std::variant<int, float, char, std::string>;



class Token {
private:
    TokenType type;
    std::string lexeme;
    TokenValue value;

    std::string to_string(TokenType t);

public:
    Token(TokenType t, std::string l, TokenValue v);

    TokenType get_type();

    TokenValue get_value();

    void print();
    
};



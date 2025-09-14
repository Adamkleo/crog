/**
 * @file lexer.h
 * @brief Lexer class  
 * @author Adam Kaawach
 * @date 2025-09-14
 * @version 1.0
 */

#pragma once

#include <string>
#include <cctype>
#include "token.h"

class Lexer {
private:
    int pos = 0;
    std::string input;
    char currentChar;

    // Advance current character pointer by 1
    void _advance();

    // Tokenize number in the input stream (whole and decimal numbers)
    Token number();
    
    // Tokenize alpha string in the input stream
    Token alpha();
    
    // Tokenize symbol in the input stream, symbols defined in symbol table (token.h)
    Token symbol();

    // Helper to check if a character is a character is a symbol (single-char symbols only)
    bool isSymbol(char c);

    // Get next token in the input stream
    Token get_next_token();

public:
    // Constructor 
    Lexer(std::string i);

    // Tokenize entire input stream, return vector of tokens
    std::vector<Token> tokenize();
};





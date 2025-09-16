#include "ast.hpp"
#include <iostream>


void IdentifierNode::print() { 
    std::cout << id; 
}

void NumberNode::print() { 
    std::cout << value; 
}

void UnaryOpNode::print() {
    std::cout << "(" << op;
    operand->print(); 
    std::cout << ")";
}

void BinaryOpNode::print() {
    std::cout << "(";
    left->print();
    std::cout << " " << op << " ";
    right->print();
    std::cout << ")";
}

void FunctionNode::print() {
    std::cout << "function " << id << "(" << param << ") { ";
    body->print();
    std::cout << " }";
}

void InlineFunctionNode::print() {
    std::cout << name << "("; 
    arg->print();
    std::cout << ")";
}

#include "ast.h"
#include <iostream>


void NumberNode::print() {
    std::cout << "Num(" << value << ")";
}


void BinaryOpNode::print() {
    std::cout << "BinOp(" << op << ",\n\t";
    left->print();
    std::cout << "\t";
    right->print();
    std::cout << ")";
}


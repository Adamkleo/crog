#pragma once

#include <iostream>

enum class NodeType {
    NUMBER,
    BINARY_OP,
    // more later
};

class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual void print() = 0;
};

class NumberNode : public ASTNode {
private:
    double value;

public:
    NumberNode(double v) : value(v) {};

    void print();
};

class BinaryOpNode : public ASTNode {
private:
    char op;
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;

public:
    BinaryOpNode(char op, std::unique_ptr<ASTNode> l, std::unique_ptr<ASTNode> r) 
	: op(op), left(std::move(l)), right(std::move(r)) {};

    void print();
};

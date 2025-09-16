#pragma once
#include <memory>
#include <string>

enum class NodeType {
    NUMBER,
    BINARY_OP,
    // more later
};

// ASTNode class to derive other types
class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual void print() = 0;
};

class FunctionNode : public ASTNode {
private:
    std::string id;
    std::string param;
    std::unique_ptr<ASTNode> body;
public: 
    FunctionNode(std::string identifier, std::string parameter, std::unique_ptr<ASTNode> functionBody) : id(identifier), param(parameter) {
	body = std::move(functionBody);
    };

    void print();
};

class InlineFunctionNode : public ASTNode {
private:
    std::string name;
    std::unique_ptr<ASTNode> arg;
public:
    InlineFunctionNode(std::string n, std::unique_ptr<ASTNode> argument) : name(n) {
	arg = std::move(argument);
    }
    void print();
};


class UnaryOpNode : public ASTNode {
private:
    char op;  // '-' for now, maybe '+' later
    std::unique_ptr<ASTNode> operand;
public:
    UnaryOpNode(char op, std::unique_ptr<ASTNode> operand) {
	this->op = op;
	this->operand = std::move(operand);
    }
    void print();
};

// Identifier node type
class IdentifierNode : public ASTNode {
private:
    std::string id;
public:
    IdentifierNode(std::string identifier) : id(identifier) {};

    void print();
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

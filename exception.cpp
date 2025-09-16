#include <exception>
#include <string>
#include <sstream>

// Base exception for all interpreter errors
class InterpreterException : public std::runtime_error {
protected:
    size_t line_;
    size_t column_;
    std::string file_;
    
public:
    InterpreterException(const std::string& message, 
                        size_t line = 0, 
                        size_t column = 0, 
                        const std::string& file = "")
        : std::runtime_error(buildMessage(message, line, column, file)),
          line_(line), column_(column), file_(file) {}
    
    size_t line() const noexcept { return line_; }
    size_t column() const noexcept { return column_; }
    const std::string& file() const noexcept { return file_; }
    
private:
    static std::string buildMessage(const std::string& msg, 
                                   size_t line, 
                                   size_t column, 
                                   const std::string& file) {
        std::ostringstream oss;
        if (!file.empty()) oss << file << ":";
        if (line > 0) {
            oss << line;
            if (column > 0) oss << ":" << column;
            oss << ": ";
        }
        oss << msg;
        return oss.str();
    }
};

// Syntax errors (parsing phase)
class SyntaxError : public InterpreterException {
public:
    SyntaxError(const std::string& message, 
                size_t line = 0, 
                size_t column = 0, 
                const std::string& file = "")
        : InterpreterException("Syntax Error: " + message, line, column, file) {}
};

// Lexical errors (tokenization phase)
class LexicalError : public InterpreterException {
public:
    LexicalError(const std::string& message,
                 size_t line = 0,
                 size_t column = 0,
                 const std::string& file = "")
        : InterpreterException("Lexical Error: " + message, line, column, file) {}
};

// Runtime errors (execution phase)
class RuntimeError : public InterpreterException {
public:
    RuntimeError(const std::string& message,
                 size_t line = 0,
                 size_t column = 0,
                 const std::string& file = "")
        : InterpreterException("Runtime Error: " + message, line, column, file) {}
};

// Specific runtime errors
class NameError : public RuntimeError {
public:
    NameError(const std::string& name,
              size_t line = 0,
              size_t column = 0,
              const std::string& file = "")
        : RuntimeError("Undefined variable '" + name + "'", line, column, file) {}
};

class TypeError : public RuntimeError {
public:
    TypeError(const std::string& message,
              size_t line = 0,
              size_t column = 0,
              const std::string& file = "")
        : RuntimeError("Type Error: " + message, line, column, file) {}
};

class DivisionByZeroError : public RuntimeError {
public:
    DivisionByZeroError(size_t line = 0,
                        size_t column = 0,
                        const std::string& file = "")
        : RuntimeError("Division by zero", line, column, file) {}
};

class IndexError : public RuntimeError {
public:
    IndexError(const std::string& message,
               size_t line = 0,
               size_t column = 0,
               const std::string& file = "")
        : RuntimeError("Index Error: " + message, line, column, file) {}
};

// Usage example:
/*
try {
    // Lexer phase
    if (invalidToken) {
        throw LexicalError("Unexpected character '$'", 5, 12, "script.lang");
    }
    
    // Parser phase
    if (unexpectedToken) {
        throw SyntaxError("Expected ';' after statement", 10, 25, "script.lang");
    }
    
    // Runtime phase
    if (undefinedVar) {
        throw NameError("myVariable", 15, 8, "script.lang");
    }
    
    if (denominator == 0) {
        throw DivisionByZeroError(20, 15, "script.lang");
    }
    
} catch (const InterpreterException& e) {
    std::cerr << e.what() << std::endl;
    // Can also access e.line(), e.column(), e.file() for custom handling
} catch (const std::exception& e) {
    std::cerr << "Unexpected error: " << e.what() << std::endl;
}
*/

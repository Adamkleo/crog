CXX = clang++
CXXFLAGS = -Wall -Wextra -std=c++17

TARGET = main
SOURCES = main.cpp token.cpp lexer.cpp ast.cpp parser.cpp exception.cpp


$(TARGET): $(SOURCES) 
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)


clean:
	rm -f $(TARGET)

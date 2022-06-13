cmake_minimum_required(VERSION 3.18)    # CMake version check
project(lax)                            # Create project "lax"
set(CMAKE_CXX_STANDARD 14)              # Enable c++14 standard

# Add the src/ directory as a search path for include files
include_directories(src)

# Add all .cpp files in src/ directory as source file
set(SOURCE_FILES main.cpp
        src/interpreter/interpreter.cpp
        src/lexer/lexer.cpp
        src/lexer/token.cpp
        src/parser/parser.cpp src/ast/exprnode.cpp src/ast/exprnode.h src/ast/binopnode.cpp src/ast/binopnode.h src/ast/constantnode.cpp src/ast/constantnode.h src/ast/logicalnode.cpp src/ast/logicalnode.h src/ast/relationalnode.cpp src/ast/relationalnode.h src/ast/stmtnode.h src/ast/stmtexpressionnode.cpp src/ast/stmtexpressionnode.h src/ast/stmtprintnode.cpp src/ast/stmtprintnode.h src/ast/conditionalnode.cpp src/ast/conditionalnode.h src/interpreter/stmtvisitor.h src/interpreter/exprvisitor.h src/lexer/tokentype.h src/lexer/num.cpp src/lexer/num.h src/lexer/op.cpp src/lexer/op.h src/lexer/word.cpp src/lexer/word.h src/symbols/type.cpp src/symbols/type.h)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(lax ${SOURCE_FILES})

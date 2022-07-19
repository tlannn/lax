cmake_minimum_required(VERSION 3.18)    # CMake version check
project(lax)                            # Create project "lax"
set(CMAKE_CXX_STANDARD 14)              # Enable c++14 standard

# Add the src/ directory as a search path for include files
include_directories(src)

# Add all .cpp files in src/ directory as source file
set(SOURCE_FILES main.cpp
        src/lax.cpp
        src/ast/assignnode.cpp
        src/ast/binopnode.cpp
        src/ast/blocknode.cpp
        src/ast/conditionalnode.cpp
        src/ast/declnode.cpp
        src/ast/exprnode.cpp
        src/ast/id.cpp
        src/ast/literalnode.cpp
        src/ast/logicalnode.cpp
        src/ast/relationalnode.cpp
        src/ast/seqnode.cpp
        src/ast/stmtexpressionnode.cpp
        src/ast/stmtnode.cpp
        src/ast/stmtprintnode.cpp
        src/ast/unarynode.cpp
        src/common/exception.cpp
        src/interpreter/interpreter.cpp
        src/interpreter/runtimeerror.cpp
        src/lexer/lexer.cpp
        src/lexer/lexerror.cpp
        src/lexer/memento.cpp
        src/parser/parseerror.cpp
        src/parser/parser.cpp
        src/semantic/semanticanalyzer.cpp
        src/semantic/semanticerror.cpp
        src/symbols/env.cpp
        src/symbols/symbol.cpp
        src/symbols/symboltable.cpp
        src/symbols/varsymbol.cpp
        src/tokens/num.cpp
        src/tokens/object.cpp
        src/tokens/token.cpp
        src/tokens/type.cpp
        src/utils/logger.cpp
)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(lax ${SOURCE_FILES})

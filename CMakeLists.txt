cmake_minimum_required(VERSION 3.18)    # CMake version check
project(lax)                            # Create project "lax"
set(CMAKE_CXX_STANDARD 14)              # Enable c++14 standard

# Add the src/ directory as a search path for include files
include_directories(include)

# Add all .cpp files in src/ directory as source file
set(SOURCE_FILES
        src/main.cpp
        src/Lax.cpp
        src/ast/AssignNode.cpp
        src/ast/BinOpNode.cpp
        src/ast/BlockNode.cpp
        src/ast/CallNode.cpp
        src/ast/ConditionalNode.cpp
        src/ast/DeclNode.cpp
        src/ast/ExprNode.cpp
        src/ast/Id.cpp
        src/ast/FunNode.cpp
        src/ast/LiteralNode.cpp
        src/ast/LogicalNode.cpp
        src/ast/RelationalNode.cpp
        src/ast/ReturnNode.cpp
        src/ast/SeqNode.cpp
        src/ast/StmtExpressionNode.cpp
        src/ast/StmtNode.cpp
        src/ast/StmtPrintNode.cpp
        src/ast/UnaryNode.cpp
        src/common/CompileTimeException.cpp
        src/common/Exception.cpp
        src/common/ValueType.cpp
        src/interpreter/Callframe.cpp
        src/interpreter/Interpreter.cpp
        src/interpreter/Return.cpp
        src/interpreter/RuntimeError.cpp
        src/lexer/Lexer.cpp
        src/lexer/LexError.cpp
        src/lexer/Memento.cpp
        src/objects/ObjClosure.cpp
        src/objects/Object.cpp
        src/objects/ObjFunction.cpp
        src/objects/ObjString.cpp
        src/objects/Variable.cpp
        src/parser/ParseError.cpp
        src/parser/Parser.cpp
        src/semantic/SemanticAnalyzer.cpp
        src/semantic/SemanticError.cpp
        src/symbols/Env.cpp
        src/symbols/FunSymbol.cpp
        src/symbols/Symbol.cpp
        src/symbols/SymbolTable.cpp
        src/symbols/VarSymbol.cpp
        src/tokens/Token.cpp
        src/utils/Logger.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(lax ${SOURCE_FILES})

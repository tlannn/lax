cmake_minimum_required(VERSION 3.18)    # CMake version check
project(lax)                            # Create project "lax"
set(CMAKE_CXX_STANDARD 14)              # Enable c++14 standard

option(DEBUG "Enable debug mode" OFF)

# Add the src/ directory as a search path for include files
include_directories(include)

# Add all .cpp files in src/ directory as source file
set(SOURCE_FILES
        src/main.cpp
        src/Lax.cpp
        src/ast/nodes/AssignNode.cpp
        src/ast/nodes/ASTNode.cpp
        src/ast/nodes/BinOpNode.cpp
        src/ast/nodes/BlockNode.cpp
        src/ast/nodes/CallNode.cpp
        src/ast/nodes/ConditionalNode.cpp
        src/ast/nodes/DeclNode.cpp
        src/ast/nodes/ExprNode.cpp
        src/ast/nodes/IdNode.cpp
        src/ast/nodes/FunNode.cpp
        src/ast/nodes/LiteralNode.cpp
        src/ast/nodes/LogicalNode.cpp
        src/ast/nodes/RelationalNode.cpp
        src/ast/nodes/ReturnNode.cpp
        src/ast/nodes/SeqNode.cpp
        src/ast/nodes/StmtExpressionNode.cpp
        src/ast/nodes/StmtNode.cpp
        src/ast/nodes/UnaryNode.cpp
        src/ast/AST.cpp
        src/common/Chunk.cpp
        src/common/CompileTimeException.cpp
        src/common/Debug.cpp
        src/common/Exception.cpp
        src/common/Memory.cpp
        src/common/StringTable.cpp
        src/compiler/Compiler.cpp
        src/lexer/Lexer.cpp
        src/lexer/LexError.cpp
        src/lexer/Memento.cpp
        src/natives/NativeFunctions.cpp
        src/objects/ObjClosure.cpp
        src/objects/Object.cpp
        src/objects/ObjFunction.cpp
        src/objects/ObjNative.cpp
        src/objects/ObjString.cpp
        src/objects/ObjUpvalue.cpp
        src/objects/Variable.cpp
        src/parser/ParseError.cpp
        src/parser/Parser.cpp
        src/semantic/SemanticAnalyzer.cpp
        src/semantic/SemanticError.cpp
        src/symbols/BuiltInSymbol.cpp
        src/symbols/FunSymbol.cpp
        src/symbols/Scope.cpp
        src/symbols/Symbol.cpp
        src/symbols/SymbolTable.cpp
        src/symbols/VarSymbol.cpp
        src/tokens/Token.cpp
        src/utils/Logger.cpp
        src/vm/Table.cpp
        src/vm/VM.cpp
        src/values/FunctionType.cpp
        src/values/LaxType.cpp
        src/values/ObjectType.cpp
        src/values/PrimitiveType.cpp
        src/values/Value.cpp
        src/values/ValueArray.cpp
)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(lax ${SOURCE_FILES})

if (DEBUG)
    message("Debug mode activated")
    add_definitions(-DDEBUG_TRACE_EXECUTION)
    add_definitions(-DDEBUG_PRINT_CODE)
endif (DEBUG)

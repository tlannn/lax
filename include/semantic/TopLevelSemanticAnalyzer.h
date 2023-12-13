#ifndef LAX_TOPLEVELSEMANTICANALYZER_H
#define LAX_TOPLEVELSEMANTICANALYZER_H

#include <memory>

#include "SemanticAnalyzer.h"
#include "SemanticError.h"
#include "ast/ASTVisitor.h"
#include "ast/ASTFwdDecl.h"
#include "lexer/Lexer.h"
#include "objects/Object.h"
#include "symbols/FunSymbol.h"
#include "symbols/VarSymbol.h"
#include "utils/Logger.h"

// Forward declarations
class AST;

class TopLevelSemanticAnalyzer : public SemanticAnalyzer {
public:
    /**
     * Class constructor
     *
     * @param parser
     */
    explicit TopLevelSemanticAnalyzer(AST &ast);

    /**
     * Class destructor
     */
    ~TopLevelSemanticAnalyzer() = default;

    /**
     * Analyze semantically the code parsed by the parser
     */
    void analyze() override;

    /**
     * Visit an ExprNode and determine the type of the value to which it
     * has been reduced
     */
    void visit(ExprNode &node) override;

    /**
     * Visit an AssignNode and check that the new value is type-consistent, and
     * if needed, update the type of the variable symbol
     */
    void visit(AssignNode &node) override;

    /**
     * Visit a BinOpNode and determine the type of the result computed by the
     * operation represented by the node
     */
    void visit(BinOpNode &node) override;

    /**
     * Visit a LogicalNode and set the type of the expression as boolean
     */
    void visit(LogicalNode &node) override;

    /**
     * Visit a RelationalNode and set the type of the expression as boolean
     */
    void visit(RelationalNode &node) override;

    /**
     * Visit an UnaryNode and determine the type of the literal
     */
    void visit(UnaryNode &node) override;

    /**
     * Visit a CallNode and check if the function called is defined
     */
    void visit(CallNode &node) override;

    /**
     * Visit a LiteralNode and determine the type of the literal
     */
    void visit(LiteralNode &node) override;

    /**
     * Visit an IdNode and determine the type of the value associated
     */
    void visit(IdNode &node) override;

    /**
     * Visit a StmtNode and check semantics inside it
     */
    void visit(StmtNode &node) override;

    /**
     * Visit a BlockNode and check semantics in the sequence of statements
     * inside it
     */
    void visit(BlockNode &node) override;

    /**
     * Visit a SeqNode and check semantics in all statements inside it
     */
    void visit(SeqNode &node) override;

    /**
     * Visit a DeclNode and create a symbol associated to the variable created
     * to keep track of its type
     */
    void visit(DeclNode &node) override;

    /**
     * Visit a ConditionalNode and check symbols in both branches 'then'
     * and 'else'
     */
    void visit(ConditionalNode &node) override;

    /**
     * Visit a FunNode and define a function in the environment
     */
    void visit(FunNode &node) override;

    /**
     * Visit a ReturnNode and exit a function call by returning a value
     */
    void visit(ReturnNode &node) override;

    /**
     * Visit a StmtExpressionNode and check semantics in the expression
     */
    void visit(StmtExpressionNode &node) override;
};

#endif

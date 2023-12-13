#ifndef LAX_DEFINER_H
#define LAX_DEFINER_H

#include "SemanticAnalyzer.h"

// Forward declarations
class AST;
class ASTNode;

/**
 * @class Definer
 * @brief Defines identifiers at the top level of the source code.
 *
 * This class is responsible for defining identifiers at the top level of the
 * source code. This includes function declarations and variable declarations.
 *
 * This class is also responsible for binding the scope of expressions and
 * statements to a scope. This is done so that the resolver can resolve
 * identifiers in expressions and statements, with respect to the context of
 * the expression or statement.
 */
class Definer : public SemanticAnalyzer {
public:
    explicit Definer(AST& ast);

    virtual ~Definer() = default;

    void analyze() override;

private:
    /**
     * @brief Visits an expression node.
     * @param node The expression node to visit.
     *
     * This function will bind the scope of the expression to the current scope.
     */
    void visit(ExprNode& node) override;

    //void visit(AssignNode& node) override;

    //void visit(CallNode& node) override;

    //void visit(IdNode& node) override;

    /**
     * @brief Visits a statement node.
     * @param node The statement node to visit.
     *
     * This function will bind the scope of the statement to the current scope.
     *
     * The statement body is visited after the scope is bound only if the
     * statement is declared in the global scope.
     */
    void visit(StmtNode& node) override;

    void visit(BlockNode& node) override;

    //void visit(DeclNode& node) override;

    /**
     * @brief Visits a function declaration.
     * @param node The function declaration to visit.
     *
     * This function will bind the scope of the function body to the function
     * declaration. This is done so that the function body can access the
     * function parameters.
     *
     * The function body is visited after the scope is bound only if the
     * function is declared in the global scope.
     */
    void visit(FunNode& node) override;

private:
    /**
     * @brief Binds the current scope to the given node.
     * @param node The node to bind the scope to.
     */
    void bindScope(ASTNode& node);
};

#endif // LAX_DEFINER_H

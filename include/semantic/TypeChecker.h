#ifndef LAX_TYPECHECKER_H
#define LAX_TYPECHECKER_H

#include "ast/ASTVisitor.h"
#include "ast/ASTFwdDecl.h"
#include "semantic/SemanticAnalyzer.h"

// Forward declarations
class SymbolTable;

class TypeChecker : public SemanticAnalyzer {
public:
	explicit TypeChecker(AST& ast);

	virtual ~TypeChecker() = default;

    void analyze() override;

    using SemanticAnalyzer::visit;

	void visit(AssignNode& node) override;

	void visit(BinOpNode& node) override;

	void visit(CallNode& node) override;

	void visit(LiteralNode& node) override;

	void visit(IdNode& node) override;

	void visit(DeclNode& node) override;

	void visit(FunNode& node) override;

private:
    LaxType *m_result;
};

#endif //LAX_TYPECHECKER_H

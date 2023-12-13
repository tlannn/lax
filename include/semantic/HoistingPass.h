#ifndef LAX_HOISTINGPASS_H
#define LAX_HOISTINGPASS_H

#include "ast/AST.h"
#include "SemanticAnalyzer.h"

/**
 * @class HoistingPass
 * @brief Hoists variable declarations to the top of the scope.
 *
 * This class is responsible for hoisting function declarations to the top of
 * the scope. This is done so that functions can be used before they are
 * declared.
 */
class HoistingPass : public SemanticAnalyzer {
public:
    explicit HoistingPass(AST& node);

    void analyze() override;

private:
    void visit(SeqNode& node) override;

    void visit(StmtNode& node) override;

    void visit(FunNode& node) override;

    bool m_hoistStmt;
};

#endif // LAX_HOISTINGPASS_H

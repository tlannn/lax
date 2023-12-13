#include "semantic/HoistingPass.h"
#include "ast/nodes/FunNode.h"
#include "ast/nodes/SeqNode.h"
#include "objects/ObjString.h"
#include "utils/Logger.h"
#include "symbols/Scope.h"

HoistingPass::HoistingPass(AST& ast) : SemanticAnalyzer(ast),
    m_hoistStmt(false) {}

void HoistingPass::analyze() {
#ifdef DEBUG_TRACE_EXECUTION
    Logger::log("--- Hoisting pass ---");
#endif

    SemanticAnalyzer::analyze();

#ifdef DEBUG_TRACE_EXECUTION
    Logger::log("--- End of Hoisting pass ---");
#endif
}

void HoistingPass::visit(SeqNode& node) {
    if (node.getScope() && !node.getScope()->isGlobalScope())
        return;

    auto& stmts = node.getStatements();
    for (auto&& stmt = stmts.cbegin(); stmt != stmts.cend(); ++stmt) {
        visit(**stmt);
        if (m_hoistStmt) {
            auto nextIt = std::next(stmt);
            node.moveToFront(stmt);
            stmt = std::prev(nextIt);
        }
    }
}

void HoistingPass::visit(StmtNode& node) {
    m_hoistStmt = false;
    node.accept(*this);
}

void HoistingPass::visit(FunNode& node) {
    Logger::log("HoistingPass - Hoisting function " + node.getName()->toString());
    m_hoistStmt = true;
}

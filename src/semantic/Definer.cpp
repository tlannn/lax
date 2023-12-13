#include "semantic/Definer.h"
#include "ast/AST.h"
#include "ast/ASTIncludes.h"
#include "objects/ObjString.h"
#include "objects/Variable.h"
#include "symbols/SymbolTable.h"
#include "utils/Logger.h"

Definer::Definer(AST& ast) : SemanticAnalyzer(ast) {}

void Definer::analyze() {
#ifdef DEBUG_TRACE_EXECUTION
    Logger::log("--- Definer pass ---");
#endif

    SemanticAnalyzer::analyze();

#ifdef DEBUG_TRACE_EXECUTION
    Logger::log("--- End of Definer pass ---");
#endif
}

void Definer::visit(ExprNode& node) {
    bindScope(node); // Bind scope for all StmtNode and subclasses
    SemanticAnalyzer::visit(node);
}

//void Definer::visit(AssignNode& node) {
//    VarSymbol* varSymbol = m_symtable->lookupVariable(
//        m_symtable->currentScope(), node.getVariableName()
//    );
//
//    if (!varSymbol) {
//        report(
//            error(
//                node.getToken(),
//                "Cannot assign value to unknown variable '" + node.getVariableName()->toString() + "'",
//                "UndefinedSymbol"
//            )
//        );
//        return;
//    }
//
//    node.setSymbol(varSymbol);
//
//    visit(*node.getExpr());
//}

//void Definer::visit(CallNode& node) {
//    visit(*node.getCallee());
//
//    //FunSymbol* funSymbol = nullptr;
//    if (auto* callee = dynamic_cast<IdNode*>(node.getCallee())) {
//        Symbol* calleeSymbol = callee->getSymbol();
//        if (!calleeSymbol) return;
//
//        else if (!LaxType::isFunction(*calleeSymbol->getType())) {
//            report(
//                error(
//                    callee->getToken(),
//                    "Could not find function " + callee->getName()->toString(),
//                    "UndefinedSymbol"
//                )
//            );
//            return;
//        }
//
//        node.setSymbol(callee->getSymbol());
//    }
//
//    //if (!funSymbol) {
//    //    report(
//    //        error(
//    //            node.getCallee()->getToken(),
//    //            "Could not find function " + node.getCallee()->getToken()->toString(),
//    //            "UndefinedSymbol"
//    //        )
//    //    );
//    //}
//
//    for (const auto& arg : node.getArgs()) {
//        visit(*arg);
//    }
//}

//void Definer::visit(IdNode& node) {
//    Symbol* sym = m_symtable->lookup(*node.getScope(), node.getName());
//
//    if (!sym) {
//        report(
//            error(
//                node.getToken(),
//                "Could not find a symbol associated to '" + node.getName()->toString() + "'",
//                "UndefinedSymbol"
//            )
//        );
//        return;
//    }
//
//    node.setSymbol(sym);
//
//    ///*****/
//    //
//    //VarSymbol* var = m_symtable->lookupVariable(*node.getScope(), node.getName());
//    //FunSymbol* fun = m_symtable->lookupFunction(*node.getScope(), node.getName());
//    //
//    //if (!var && !fun) {
//    //    report(
//    //        error(
//    //            node.getToken(),
//    //            "'" + node.getName()->toString() + "' was not declared in this scope",
//    //            "Undefined symbol"
//    //        )
//    //    );
//    //    return;
//    //}
//    //
//    //if (var) {
//    //    node.
//    //}
//}

void Definer::visit(StmtNode& node) {
    bindScope(node); // Bind scope for all StmtNode and subclasses

    //if (node.getScope()->isGlobalScope())
        SemanticAnalyzer::visit(node);
}

void Definer::visit(BlockNode& node) {
    m_symtable->beginScope();
    bindScope(node);
    visit(*node.getSequence());
    m_symtable->endScope();
}

//void Definer::visit(DeclNode& node) {
//    bindScope(node);
//
//    //if (!node.getType() && node.getRValue()) {
//    //    auto assignee = dynamic_cast<IdNode*>(node.getRValue());
//    //    assignee.
//    //}
//
//    // Create a symbol for that variable and associate it to the node
//    auto symbol = std::make_unique<VarSymbol>(
//        node.getName(), node.getType()
//    );
//    node.setSymbol(symbol.get());
//
//    // Register the symbol in the symbol table
//    bool inserted = m_symtable->define(
//        *node.getScope(), std::move(symbol)
//    );
//
//    // An insertion failure means that this symbol already exists
//    if (!inserted) {
//        report(
//            error(
//                node.getToken(),
//                "'" + node.getName()->toString() + "' has already been declared in this scope",
//                "Error"
//            )
//        );
//    }
//
//    if (node.getRValue())
//        visit(*node.getRValue());
//}

void Definer::visit(FunNode& node) {
    // Create the scope for the body block ourselves so that we can define
    // parameters inside that scope, before resolving the body itself
    bindScope(node);
    visit(*node.getBody());

    //m_symtable->beginScope();
    //bindScope(*node.getBody());

    if (node.getScope()->isLocalScope()) return;

    std::vector<VarSymbol> params;
    for (const auto& item : node.getParams()) {
        auto symbol = std::make_unique<VarSymbol>(
            ObjString::copyString(item->getVarName()->toString()),
            item->getType()
        );
        params.push_back(*symbol);
        m_symtable->define(*node.getBody()->getScope(), std::move(symbol));
    }

    auto symbol = std::make_unique<FunSymbol>(
        node.getName(), params, node.getReturnType()
    );
    m_symtable->define(*node.getScope(), std::move(symbol));

    //SeqNode& n = *node.getBody()->getSequence();
    //SemanticAnalyzer::visit(n);
    //m_symtable->endScope(); // End the body scope
}

void Definer::bindScope(ASTNode& node) {
    node.setScope(&m_symtable->currentScope());
}

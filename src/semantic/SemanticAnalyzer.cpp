#include "semantic/SemanticAnalyzer.h"
#include "ast/AST.h"
#include "ast/ASTIncludes.h"
#include "objects/Variable.h"
#include "symbols/SymbolTable.h"

SemanticAnalyzer::SemanticAnalyzer(AST& ast) :
    m_ast(ast),
    m_errors(false),
    m_symtable(SymbolTable::instance()) {}

void SemanticAnalyzer::analyze() {
    m_ast.traverse(*this);
}

bool SemanticAnalyzer::hadErrors() const {
    return m_errors;
}

SemanticError SemanticAnalyzer::error(
    Token* token, const std::string& message, const std::string& type) {
    m_errors = true;
    return SemanticError(
        Lexer::currentFile, token->getLine(),token->getColumn(), message, type
    );
}

void SemanticAnalyzer::report(const SemanticError& err) {
    Logger::error(err.what());
}

void SemanticAnalyzer::visit(ExprNode& node) {
    node.accept(*this);
}

void SemanticAnalyzer::visit(AssignNode& node) {
    visit(*node.getExpr());
}

void SemanticAnalyzer::visit(LogicalNode& node) {
    visit(*node.getLeft());
    visit(*node.getRight());
}

void SemanticAnalyzer::visit(RelationalNode& node) {
    visit(*node.getLeft());
    visit(*node.getRight());
}

void SemanticAnalyzer::visit(BinOpNode& node) {
    visit(*node.getLeft());
    visit(*node.getRight());
}

void SemanticAnalyzer::visit(UnaryNode& node) {
    visit(*node.getExpr());
}

void SemanticAnalyzer::visit(CallNode& node) {
    visit(*node.getCallee());
    const auto& args = node.getArgs();

    for (const auto& arg : args)
        visit(*arg);
}

void SemanticAnalyzer::visit(LiteralNode& node) {}

void SemanticAnalyzer::visit(IdNode& node) {}

void SemanticAnalyzer::visit(StmtNode& node) {
    node.accept(*this);
}

void SemanticAnalyzer::visit(BlockNode& node) {
    visit(*node.getSequence());
}

void SemanticAnalyzer::visit(SeqNode& node) {
    auto& stmts = node.getStatements();

    for (const auto& stmt : stmts) {
        StmtNode &n = *stmt;
        visit(n);
    }
}

void SemanticAnalyzer::visit(DeclNode& node) {
    if (node.getRValue())
        visit(*node.getRValue());
}

void SemanticAnalyzer::visit(ConditionalNode& node) {
    visit(*node.getConditionExpression());
    visit(*node.getThenStatement());

    if (node.getElseStatement())
        visit(*node.getElseStatement());
}

void SemanticAnalyzer::visit(FunNode& node) {
    visit(*node.getBody());
}

void SemanticAnalyzer::visit(ReturnNode& node) {
    if (node.getValue())
        visit(*node.getValue());
}

void SemanticAnalyzer::visit(StmtExpressionNode& node) {
    visit(*node.getExpr());
}

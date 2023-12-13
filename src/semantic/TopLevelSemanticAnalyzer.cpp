//#include "semantic/TopLevelSemanticAnalyzer.h"
//#include "ast/AST.h"
//#include "ast/ASTIncludes.h"
//#include "objects/ObjString.h"
//#include "objects/Variable.h"
//
//TopLevelSemanticAnalyzer::TopLevelSemanticAnalyzer(AST &ast) : SemanticAnalyzer(ast) {}
//
///// Visit an expression node and determine the type of the value to which it
///// has been reduced
//void TopLevelSemanticAnalyzer::analyze() {
//    _ast.traverse(*this);
//}
//
///// Visit an AssignNode and check that the new value is type-consistent, and
///// if needed, update the type of the variable symbol
//void TopLevelSemanticAnalyzer::visit(AssignNode &node) {
//	std::string varName = node.getToken()->toString();
//	VarSymbol *var = dynamic_cast<VarSymbol *>(_env->get(varName));
//
//	if (!var) {
//		report(error(node.getToken(),
//					 "'" + varName + "' was not declared in this scope", "Undefined symbol"));
//		visit(*node.getExpr());
//		return;
//	}
//
//	ValueType varType = var->getType();
//	visit(*node.getExpr());
//
//	ValueType assignType = _resultType;
//
//	if (varType == ValueType::VAL_NULL)
//		var->setType(assignType);
//
//	else if (assignType != varType)
//		report(error(node.getExpr()->getToken(),
//					 "Cannot convert '" + ValueType::toString(assignType) + "' to '" + ValueType::toString(varType) +
//					 "'",
//					 "TypeError"));
//}
//
///// Visit a LogicalNode and set the type of the expression as boolean
//void TopLevelSemanticAnalyzer::visit(LogicalNode &node) {}
//
///// Visit a RelationalNode and set the type of the expression as boolean
//void TopLevelSemanticAnalyzer::visit(RelationalNode &node) {}
//
///// Visit a BinOpNode and determine the type of the result computed by the
///// operation represented by the node
//void TopLevelSemanticAnalyzer::visit(BinOpNode &node) {}
//
///// Visit an UnaryNode and determine the type of the literal
//void TopLevelSemanticAnalyzer::visit(UnaryNode &node) {}
//
///// Visit a LiteralNode and determine the type of the literal
//void TopLevelSemanticAnalyzer::visit(LiteralNode &node) {}
//
///// Visit an IdNode and determine the type of the value associated
//void TopLevelSemanticAnalyzer::visit(IdNode &node) {
//	std::string name = node.getName()->toString();
//	Symbol* sym = _env->get(name);
//
//	if (!sym) {
//		report(error(node.getName(),
//					 "'" + name + "' was not declared in this scope",
//					 "Undefined symbol"));
//
//		_resultType = ValueType::VAL_NULL;
//	}
//
//	else
//		_resultType = sym->getType();
//}
//
///// Visit a StmtNode and check semantics inside it
//void TopLevelSemanticAnalyzer::visit(StmtNode &node) {
//    node.accept(*this);
//}
//
///// Visit a BlockNode and check semantics in the sequence of statements
///// inside it
//void TopLevelSemanticAnalyzer::visit(BlockNode &node) {
//	visit(*node.getSequence());
//}
//
///// Visit a SeqNode and check semantics in all statements inside it
//void TopLevelSemanticAnalyzer::visit(SeqNode &node) {
//	auto& stmts = node.getStatements();
//
//	for (const auto & stmt : stmts)
//		visit(*stmt);
//}
//
///// Visit a DeclNode and create a symbol associated to the variable created
///// to keep track of its type
//void TopLevelSemanticAnalyzer::visit(DeclNode &node) {
//    if (!node.getScope()->isGlobalScope()) return;
//
//	ObjString *varName = node.getName();
//	ValueType varType = node.getType();
//
//	// Check if variable is already declared in the scope
//	if (m_symtable->lookupVariable(*node.getScope(), varName)) {
//		report(error(node.getId().get(),
//					 "'" + varName->toString() + "' has already been declared in this scope",
//					 "Error"));
//	}
//
//    auto varSymbol = std::make_unique<VarSymbol>(varName->toString(), varType);
//    node.setSymbol(varSymbol.get());
//
//    m_symtable->defineVariable(*node.getScope(), std::move(varSymbol));
//}
//
///// Visit a ConditionalNode and check symbols in both branches 'then' and 'else'
//void TopLevelSemanticAnalyzer::visit(ConditionalNode &node) {}
//
///// Visit a FunNode and define a function in the environment
//void TopLevelSemanticAnalyzer::visit(FunNode &node) {
//    if (node.getScope()->isLocalScope()) return;
//
//	ObjString *funName = node.getName();
//
//	// Check if function does not already exist
//	if (m_symtable->lookupFunction(*node.getScope(), funName)) {
//		report(error(node.getToken(),
//					 "Redefinition of function '" + funName->toString() + "()'",
//					 "Error"));
//	}
//
//	std::vector<std::unique_ptr<VarSymbol>> params;
//	for (auto& param : node.getParams()) {
//		auto varName = param->getVarName()->toString();
//		auto varType = param->getType();
//
//		params.push_back(std::make_unique<VarSymbol>(varName, varType));
//	}
//
//    auto funSymbol = std::make_unique<FunSymbol>(funName->toString(), params, node.getReturnType());
//    node.getBody()->getScope()->setFunctionSymbol(funSymbol.get());
//
//    node.setSymbol(funSymbol.get());
//
//    m_symtable->defineFunction(*node.getScope(), std::move(funSymbol));
//
//    for (auto &param : node.getParams()) {
//        auto funScope = *node.getBody()->getScope();
//        auto paramSymbol = std::make_unique<VarSymbol>(param->getVarName()->toString(), param->getType());
//        m_symtable->defineVariable(funScope, std::move(paramSymbol));
//    }
//}
//
///// Visit a ReturnNode and exit a function call by returning a value
//void TopLevelSemanticAnalyzer::visit(ReturnNode &node) {}
//
///// Visit a StmtExpressionNode and check semantics in the expression
//void TopLevelSemanticAnalyzer::visit(StmtExpressionNode &node) {
//	visit(*node.getExpr());
//}

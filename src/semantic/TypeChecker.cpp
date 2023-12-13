#include "semantic/TypeChecker.h"
#include "ast/ASTIncludes.h"
#include "objects/ObjString.h"
#include "symbols/SymbolTable.h"
#include "symbols/FunSymbol.h"
#include "symbols/VarSymbol.h"
#include "values/FunctionType.h"
#include "values/PrimitiveType.h"

TypeChecker::TypeChecker(AST& ast) :
    SemanticAnalyzer(ast),
    m_result(&PrimitiveType::VOID) {}

void TypeChecker::analyze() {
#ifdef DEBUG_TRACE_EXECUTION
    Logger::log("--- Type check pass ---");
#endif

    SemanticAnalyzer::analyze();

#ifdef DEBUG_TRACE_EXECUTION
    Logger::log("--- End of type check pass ---");
#endif
}

void TypeChecker::visit(AssignNode& node) {
    visit(*node.getExpr());
	LaxType* assignType = m_result;

	// Update the variable type in its symbol
	node.getSymbol()->setType(assignType);

    // Keep the variable type as a result to continue the expression type check
	m_result = assignType;
}

void TypeChecker::visit(BinOpNode& node) {
    visit(*node.getLeft());
    LaxType* leftType = m_result;
    visit(*node.getRight());
    LaxType* rightType = m_result;

    // TODO: check if types are compatible
    if (*leftType != *rightType)
        throw "";

    // TODO: compute common base type if both are different
    m_result = leftType;
}

void TypeChecker::visit(CallNode& node) {
    visit(*node.getCallee());
    LaxType* symbolType = node.getSymbol()->getType();

    if (!symbolType || !LaxType::isFunction(*symbolType)) {
        report(
            error(
                node.getCallee()->getToken(),
                "Could not resolve name '" +
                node.getSymbol()->getName()->toString() +
                "' as a function",
                "UndefinedSymbol"
            )
        );
    }

    auto functionType = LaxType::asFunction(*symbolType);

    const auto &params = functionType.getParamTypes();
    const auto &args = node.getArgs();
    const size_t paramsCount = params.size();
    const size_t argsCount = args.size();

    if (paramsCount < argsCount) {
        report(
            error(
                node.getToken(),
                "too many arguments to function '" + node.getSymbol()->getName()->toString() + "'",
                "error"
            )
        );
    }
    else if (paramsCount > argsCount) {
        report(
            error(
                node.getToken(),
                "too few arguments to function '" + node.getSymbol()->getName()->toString() + "'",
                "error"
            )
        );
    }

    for (int i = 0; i < argsCount; ++i) {
        LaxType* expectedType = params.at(i);
        auto& arg = args.at(i);
        visit(*arg);

        if (expectedType != m_result) {
            report(
                error(
                    arg->getToken(),
                    "Cannot match argument of type '" + m_result->toString()
                    + "' to expected type '" + expectedType->toString() + "'",
                    "IllegalType"
                )
            );
        }
    }

    m_result = &const_cast<LaxType&>(functionType.getReturnType());
}

void TypeChecker::visit(LiteralNode& node) {
	//m_result = node.getValue().type;
    switch (node.getValue().type) {
        case NUL:
            m_result = nullptr;
            break;
        case INTEGER:
            m_result = &PrimitiveType::INTEGER;
            break;
        case BOOLEAN:
            m_result = &PrimitiveType::BOOLEAN;
            break;
        case OBJECT: {
            if (Object::isObjType(node.getValue(), ObjType::OBJ_STRING)) {
                m_result = &PrimitiveType::STRING;
            }
        }
        default: break;
    }
}

void TypeChecker::visit(IdNode& node) {
    m_result = node.getSymbol()->getType();
}

void TypeChecker::visit(DeclNode& node) {
    if (!node.getRValue()) return;

    visit(*node.getRValue());

    LaxType* varType = node.getType();
    LaxType* valueType = m_result;

    if (varType && varType != valueType) {
        report(
            error(
                node.getRValue()->getToken(),
                "Cannot assign value of type '" + valueType->toString() +
                "' to variable of type '" + varType->toString() + "'",
                "IllegalType"
            )
        );
    }

    else if (!varType && valueType) {
        node.getSymbol()->setType(m_result);
    }

    // Reset the result for future uses
    m_result = &PrimitiveType::VOID;
}

void TypeChecker::visit(FunNode& node) {
	visit(*node.getBody());

	// TODO: check that returned value matches return type
}

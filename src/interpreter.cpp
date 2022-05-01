#include "interpreter.h"

/// Class constructor
Interpreter::Interpreter(Parser parser) : _parser(parser) {}

/// Interpret the program parsed by the parser
void Interpreter::interpret() {
    Stmt *tree = _parser.parse();
    execute(tree);
}

/// Evaluate an expression node and return the value to which it has been reduced
int Interpreter::evaluate(Expr *node) {
    return node->accept(this);
}

/// Visit a BinOpNode and compute the operation represented by the node
int Interpreter::visit(BinOpNode *node) {
    int left = evaluate(node->getLeft());
    int right = evaluate(node->getRight());
    Token op = node->getToken();

    switch (op.toString().at(0)) {
        case '+':
            return left + right;
        case '-':
            return left - right;
        case '*':
            return left * right;
        case '/':
            return left / right;
    }

    return 0;
}

/// Visit a ConstantNode and return the constant value represented
int Interpreter::visit(ConstantNode *node) {
    return node->getValue();
}

/// Execute a statement node
void Interpreter::execute(Stmt *node) {
    node->accept(this);
}

/// Visit a StmtExpression node and compute the expression in the statement
void Interpreter::visit(StmtExpression *node) {
    evaluate(node->getExpr());
}

/// Visit a StmtPrint node and print the result of the expression in the statement
void Interpreter::visit(StmtPrint *node) {
    int res = evaluate(node->getExpr());
    std::cout << "The result is : " << res << std::endl;
}

/// Visit an IfNode and execute the statement referenced if the condition
/// is evaluated to true
void Interpreter::visit(IfNode *node) {
    if (evaluate(node->getConditionExpression()))
        execute(node->getThenStatement());
}

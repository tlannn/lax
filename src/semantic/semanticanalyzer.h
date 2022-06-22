#ifndef LAX_SEMANTICANALYZER_H
#define LAX_SEMANTICANALYZER_H

#include "parser/parser.h"
#include "interpreter/exprvisitor.h"
#include "interpreter/stmtvisitor.h"

class SemanticAnalyzer : public ExprVisitor, StmtVisitor {
public:
    /**
     * Class constructor
     *
     * @param parser
     */
    explicit SemanticAnalyzer(Parser &parser);

    /// Interpret the program parsed by the parser
    void analyze();

    /// Evaluate an expression node and return the value to which it has been reduced
    int evaluate(ExprNode *node) override;

    /// Visit a BinOpNode and compute the operation represented by the node
    int visit(BinOpNode *node) override;

    /// Visit a ConstantNode and return the constant value represented
    int visit(ConstantNode *node) override;

    /// Visit a LogicalNode and return the boolean value represented by the boolean expression
    int visit(LogicalNode *node) override;

    /// Visit a RelationalNode and return a boolean value according to the truthiness of the equality or inequality
    int visit(RelationalNode *node) override;

    /// Execute a statement node
    void execute(StmtNode *node) override;

    /// Visit a StmtExpressionNode node and compute the expression in the statement
    void visit(StmtExpressionNode *node) override;

    /// Visit a StmtPrintNode node and print the result of the expression in the statement
    void visit(StmtPrintNode *node) override;

    /// Visit a ConditionalNode and execute the 'then' statement referenced if the condition
    /// is evaluated to true, otherwise execute the 'else' statement if there is one
    void visit(ConditionalNode *node) override;

    void visit(DeclNode *node) override;
    void visit(AssignNode *node) override;
    int visit(Id *node) override;
    void visit(BlockNode *node) override;

private:
    Parser _parser;
//    SymbolTable _table;
	Env _env;
    std::unordered_map<std::string, int> _memory;
	Type _resultType;
};

#endif // LAX_SEMANTICANALYZER_H

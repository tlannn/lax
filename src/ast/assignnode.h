#ifndef LAX_ASSIGNNODE_H
#define LAX_ASSIGNNODE_H

#include <string>

#include "ast/exprnode.h"
#include "ast/stmtnode.h"

class AssignNode : public StmtNode {
public:
    AssignNode(std::string id, ExprNode *expr);

    std::string getLValue();
    ExprNode* getRValue();

    void accept(StmtVisitor *visitor) override;

private:
    std::string _id;
    ExprNode *_expr;
};


#endif // LAX_ASSIGNNODE_H

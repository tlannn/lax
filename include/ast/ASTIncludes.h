#ifndef LAX_ASTINCLUDES_H
#define LAX_ASTINCLUDES_H

#include <memory>

/// Include base nodes.
#include "ast/nodes/ASTNode.h"
#include "ast/nodes/ExprNode.h"
#include "ast/nodes/StmtNode.h"

/// Include expression nodes.
#include "ast/nodes/AssignNode.h"
#include "ast/nodes/BinOpNode.h"
#include "ast/nodes/CallNode.h"
#include "ast/nodes/IdNode.h"
#include "ast/nodes/LiteralNode.h"
#include "ast/nodes/LogicalNode.h"
#include "ast/nodes/RelationalNode.h"
#include "ast/nodes/UnaryNode.h"

/// Include statement nodes.
#include "ast/nodes/BlockNode.h"
#include "ast/nodes/ConditionalNode.h"
#include "ast/nodes/DeclNode.h"
#include "ast/nodes/FunNode.h"
#include "ast/nodes/ReturnNode.h"
#include "ast/nodes/SeqNode.h"
#include "ast/nodes/StmtExpressionNode.h"

/// Include other AST-related headers.
#include "ast/AST.h"
#include "ast/ASTVisitor.h"

#endif //LAX_ASTINCLUDES_H

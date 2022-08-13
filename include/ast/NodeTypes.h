#ifndef LAX_NODETYPES_H
#define LAX_NODETYPES_H

#include <memory>

// Forward declarations
class ASTNode;
class AssignNode;
class BinOpNode;
class BlockNode;
class CallNode;
class ConditionalNode;
class DeclNode;
class ExprNode;
class FunNode;
class IdNode;
class LiteralNode;
class LogicalNode;
class RelationalNode;
class ReturnNode;
class SeqNode;
class StmtExpressionNode;
class StmtNode;
class UnaryNode;

// Type definition for unique pointers to AST nodes
typedef std::unique_ptr<ASTNode> UASTNode;
typedef std::unique_ptr<AssignNode> UAssignNode;
typedef std::unique_ptr<BinOpNode> UBinOpNode;
typedef std::unique_ptr<BlockNode> UBlockNode;
typedef std::unique_ptr<CallNode> UCallNode;
typedef std::unique_ptr<ConditionalNode> UConditionalNode;
typedef std::unique_ptr<DeclNode> UDeclNode;
typedef std::unique_ptr<ExprNode> UExprNode;
typedef std::unique_ptr<FunNode> UFunNode;
typedef std::unique_ptr<IdNode> UIdNode;
typedef std::unique_ptr<LiteralNode> ULiteralNode;
typedef std::unique_ptr<LogicalNode> ULogicalNode;
typedef std::unique_ptr<RelationalNode> URelationalNode;
typedef std::unique_ptr<ReturnNode> UReturnNode;
typedef std::unique_ptr<SeqNode> USeqNode;
typedef std::unique_ptr<StmtExpressionNode> UStmtExpressionNode;
typedef std::unique_ptr<StmtNode> UStmtNode;
typedef std::unique_ptr<UnaryNode> UUnaryNode;

#endif //LAX_NODETYPES_H

#include "stmt.h"

using namespace cxxgen;

CXXGEN_API StmtNode::StmtNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit, StmtKind stmtKind) : AstNode(AstNodeType::Stmt, selfAllocator, translationUnit), stmtKind(stmtKind) {
}

CXXGEN_API StmtNode::~StmtNode() {
}

CXXGEN_API ExprStmtNode::ExprStmtNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : StmtNode(selfAllocator, translationUnit, StmtKind::Expr) {
}

CXXGEN_API ExprStmtNode::~ExprStmtNode() {
}

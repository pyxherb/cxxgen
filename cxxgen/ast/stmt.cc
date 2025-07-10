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

CXXGEN_API VarDefEntry::VarDefEntry(peff::Alloc *allocator) : name(allocator), decorators(allocator) {
}

CXXGEN_API VarDefEntry::~VarDefEntry() {
}

CXXGEN_API VarDefNode::VarDefNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : AstNode(AstNodeType::Var, selfAllocator, translationUnit), varDefEntries(selfAllocator) {
}

CXXGEN_API VarDefNode::~VarDefNode() {
}

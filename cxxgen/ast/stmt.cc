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

CXXGEN_API LocalVarDefStmtNode::LocalVarDefStmtNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : StmtNode(selfAllocator, translationUnit, StmtKind::LocalVarDef) {
}

CXXGEN_API LocalVarDefStmtNode::~LocalVarDefStmtNode() {
}

CXXGEN_API IfStmtNode::IfStmtNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : StmtNode(selfAllocator, translationUnit, StmtKind::If) {
}

CXXGEN_API IfStmtNode::~IfStmtNode() {
}

CXXGEN_API ForStmtNode::ForStmtNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : StmtNode(selfAllocator, translationUnit, StmtKind::For) {
}

CXXGEN_API ForStmtNode::~ForStmtNode() {
}

CXXGEN_API WhileStmtNode::WhileStmtNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : StmtNode(selfAllocator, translationUnit, StmtKind::While) {
}

CXXGEN_API WhileStmtNode::~WhileStmtNode() {
}

CXXGEN_API DoWhileStmtNode::DoWhileStmtNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : StmtNode(selfAllocator, translationUnit, StmtKind::DoWhile) {
}

CXXGEN_API DoWhileStmtNode::~DoWhileStmtNode() {
}

CXXGEN_API BreakStmtNode::BreakStmtNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : StmtNode(selfAllocator, translationUnit, StmtKind::Break) {
}

CXXGEN_API BreakStmtNode::~BreakStmtNode() {
}

CXXGEN_API ContinueStmtNode::ContinueStmtNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : StmtNode(selfAllocator, translationUnit, StmtKind::Continue) {
}

CXXGEN_API ContinueStmtNode::~ContinueStmtNode() {
}

CXXGEN_API ReturnStmtNode::ReturnStmtNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : StmtNode(selfAllocator, translationUnit, StmtKind::Return) {
}

CXXGEN_API ReturnStmtNode::~ReturnStmtNode() {
}

CXXGEN_API BlockStmtNode::BlockStmtNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : StmtNode(selfAllocator, translationUnit, StmtKind::Block), body(selfAllocator) {
}

CXXGEN_API BlockStmtNode::~BlockStmtNode() {
}

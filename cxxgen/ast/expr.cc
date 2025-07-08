#include "expr.h"

using namespace cxxgen;

CXXGEN_API ExprNode::ExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit, ExprKind exprKind) : AstNode(AstNodeType::IfndefDirective, selfAllocator, translationUnit), exprKind(exprKind) {
}

CXXGEN_API ExprNode::~ExprNode() {
}

CXXGEN_API StringLiteralExprNode::StringLiteralExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : ExprNode(selfAllocator, translationUnit, ExprKind::StringLiteral), data(data) {}

CXXGEN_API StringLiteralExprNode::~StringLiteralExprNode() {}

CXXGEN_API NullptrLiteralExprNode::NullptrLiteralExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : ExprNode(selfAllocator, translationUnit, ExprKind::NullptrLiteral) {}

CXXGEN_API NullptrLiteralExprNode::~NullptrLiteralExprNode() {}

CXXGEN_API IdExprNode::IdExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : ExprNode(selfAllocator, translationUnit, ExprKind::NullptrLiteral) {}

CXXGEN_API IdExprNode::~IdExprNode() {}

CXXGEN_API InitializerListExprNode::InitializerListExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : ExprNode(selfAllocator, translationUnit, ExprKind::InitializerList), elements(selfAllocator) {}

CXXGEN_API InitializerListExprNode::~InitializerListExprNode() {}

CXXGEN_API UnaryExprNode::UnaryExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : ExprNode(selfAllocator, translationUnit, ExprKind::Unary) {}

CXXGEN_API UnaryExprNode::~UnaryExprNode() {}

CXXGEN_API BinaryExprNode::BinaryExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : ExprNode(selfAllocator, translationUnit, ExprKind::Binary) {}

CXXGEN_API BinaryExprNode::~BinaryExprNode() {}

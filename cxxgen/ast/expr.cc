#include "expr.h"

using namespace cxxgen;

CXXGEN_API ExprNode::ExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit, ExprKind exprKind) : AstNode(AstNodeType::Expr, selfAllocator, translationUnit), exprKind(exprKind) {
}

CXXGEN_API ExprNode::~ExprNode() {
}

CXXGEN_API StringLiteralExprNode::StringLiteralExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : ExprNode(selfAllocator, translationUnit, ExprKind::StringLiteral), data(selfAllocator) {}

CXXGEN_API StringLiteralExprNode::~StringLiteralExprNode() {}

CXXGEN_API NullptrLiteralExprNode::NullptrLiteralExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : ExprNode(selfAllocator, translationUnit, ExprKind::NullptrLiteral) {}

CXXGEN_API NullptrLiteralExprNode::~NullptrLiteralExprNode() {}

CXXGEN_API IdExprNode::IdExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : ExprNode(selfAllocator, translationUnit, ExprKind::Id), name(selfAllocator) {}

CXXGEN_API IdExprNode::~IdExprNode() {}

CXXGEN_API InitializerListExprNode::InitializerListExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : ExprNode(selfAllocator, translationUnit, ExprKind::InitializerList), elements(selfAllocator) {}

CXXGEN_API InitializerListExprNode::~InitializerListExprNode() {}

CXXGEN_API UnaryExprNode::UnaryExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : ExprNode(selfAllocator, translationUnit, ExprKind::Unary) {}

CXXGEN_API UnaryExprNode::~UnaryExprNode() {}

CXXGEN_API BinaryExprNode::BinaryExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : ExprNode(selfAllocator, translationUnit, ExprKind::Binary) {}

CXXGEN_API BinaryExprNode::~BinaryExprNode() {}

CXXGEN_API ScopeResolveExprNode::ScopeResolveExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : ExprNode(selfAllocator, translationUnit, ExprKind::ScopeResolve) {}

CXXGEN_API ScopeResolveExprNode::~ScopeResolveExprNode() {}

CXXGEN_API MemberAccessExprNode::MemberAccessExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : ExprNode(selfAllocator, translationUnit, ExprKind::MemberAccess) {}

CXXGEN_API MemberAccessExprNode::~MemberAccessExprNode() {}

CXXGEN_API PtrMemberAccessExprNode::PtrMemberAccessExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : ExprNode(selfAllocator, translationUnit, ExprKind::PtrMemberAccess) {}

CXXGEN_API PtrMemberAccessExprNode::~PtrMemberAccessExprNode() {}

CXXGEN_API CallExprNode::CallExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : ExprNode(selfAllocator, translationUnit, ExprKind::Call), args(selfAllocator) {}

CXXGEN_API CallExprNode::~CallExprNode() {}

CXXGEN_API CastExprNode::CastExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : ExprNode(selfAllocator, translationUnit, ExprKind::Cast) {}

CXXGEN_API CastExprNode::~CastExprNode() {}

CXXGEN_API NewExprNode::NewExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : ExprNode(selfAllocator, translationUnit, ExprKind::New), args(selfAllocator) {}

CXXGEN_API NewExprNode::~NewExprNode() {}

CXXGEN_API PlacementNewExprNode::PlacementNewExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : ExprNode(selfAllocator, translationUnit, ExprKind::PlacementNew), args(selfAllocator) {}

CXXGEN_API PlacementNewExprNode::~PlacementNewExprNode() {}

CXXGEN_API TernaryExprNode::TernaryExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : ExprNode(selfAllocator, translationUnit, ExprKind::Ternary) {}

CXXGEN_API TernaryExprNode::~TernaryExprNode() {}

CXXGEN_API TypeSizeofExprNode::TypeSizeofExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : ExprNode(selfAllocator, translationUnit, ExprKind::TypeSizeof) {}

CXXGEN_API TypeSizeofExprNode::~TypeSizeofExprNode() {}

CXXGEN_API ExprSizeofExprNode::ExprSizeofExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : ExprNode(selfAllocator, translationUnit, ExprKind::ExprSizeof) {}

CXXGEN_API ExprSizeofExprNode::~ExprSizeofExprNode() {}

CXXGEN_API AlignofExprNode::AlignofExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : ExprNode(selfAllocator, translationUnit, ExprKind::Alignof) {}

CXXGEN_API AlignofExprNode::~AlignofExprNode() {}

CXXGEN_API ThisExprNode::ThisExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : ExprNode(selfAllocator, translationUnit, ExprKind::This) {}

CXXGEN_API ThisExprNode::~ThisExprNode() {}

#include "misc.h"

using namespace cxxgen;

CXXGEN_API VarDefEntry::VarDefEntry(peff::Alloc *allocator) : name(allocator), declaractors(allocator) {
}

CXXGEN_API VarDefEntry::~VarDefEntry() {
}

CXXGEN_API DeclaractorNode::DeclaractorNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit, DeclaratorKind declaractorKind) : AstNode(AstNodeType::Declarator, selfAllocator, translationUnit), declaractorKind(declaractorKind) {
}

CXXGEN_API DeclaractorNode::~DeclaractorNode() {
}

CXXGEN_API PointerDeclaractorNode::PointerDeclaractorNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : DeclaractorNode(selfAllocator, translationUnit, DeclaratorKind::Pointer) {
}

CXXGEN_API PointerDeclaractorNode::~PointerDeclaractorNode() {
}

CXXGEN_API ArrayDeclaractorNode::ArrayDeclaractorNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : DeclaractorNode(selfAllocator, translationUnit, DeclaratorKind::Array) {
}

CXXGEN_API ArrayDeclaractorNode::~ArrayDeclaractorNode() {
}

CXXGEN_API RefDeclaractorNode::RefDeclaractorNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : DeclaractorNode(selfAllocator, translationUnit, DeclaratorKind::Ref) {
}

CXXGEN_API RefDeclaractorNode::~RefDeclaractorNode() {
}

CXXGEN_API RvalueDeclaractorNode::RvalueDeclaractorNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : DeclaractorNode(selfAllocator, translationUnit, DeclaratorKind::Rvalue) {
}

CXXGEN_API RvalueDeclaractorNode::~RvalueDeclaractorNode() {
}

CXXGEN_API VarDefNode::VarDefNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : AstNode(AstNodeType::Var, selfAllocator, translationUnit), varDefEntries(selfAllocator) {
}

CXXGEN_API VarDefNode::~VarDefNode() {
}

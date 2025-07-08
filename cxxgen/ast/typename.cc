#include "typename.h"

using namespace cxxgen;

CXXGEN_API TypeNameNode::TypeNameNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit, TypeNameKind typeNameKind) : AstNode(AstNodeType::IfndefDirective, selfAllocator, translationUnit), typeNameKind(typeNameKind) {
}

CXXGEN_API TypeNameNode::~TypeNameNode() {
}

CXXGEN_API VoidTypeNameNode::VoidTypeNameNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : TypeNameNode(selfAllocator, translationUnit, TypeNameKind::Void) {
}

CXXGEN_API VoidTypeNameNode::~VoidTypeNameNode() {
}

CXXGEN_API IntTypeNameNode::IntTypeNameNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : TypeNameNode(selfAllocator, translationUnit, TypeNameKind::Int) {
}

CXXGEN_API IntTypeNameNode::~IntTypeNameNode() {
}

CXXGEN_API BoolTypeNameNode::BoolTypeNameNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : TypeNameNode(selfAllocator, translationUnit, TypeNameKind::Bool) {
}

CXXGEN_API BoolTypeNameNode::~BoolTypeNameNode() {
}

CXXGEN_API CharTypeNameNode::CharTypeNameNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : TypeNameNode(selfAllocator, translationUnit, TypeNameKind::Char) {
}

CXXGEN_API CharTypeNameNode::~CharTypeNameNode() {
}

CXXGEN_API FloatTypeNameNode::FloatTypeNameNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : TypeNameNode(selfAllocator, translationUnit, TypeNameKind::Float) {
}

CXXGEN_API FloatTypeNameNode::~FloatTypeNameNode() {
}

CXXGEN_API DoubleTypeNameNode::DoubleTypeNameNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : TypeNameNode(selfAllocator, translationUnit, TypeNameKind::Double) {
}

CXXGEN_API DoubleTypeNameNode::~DoubleTypeNameNode() {
}

CXXGEN_API PointerTypeNameNode::PointerTypeNameNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : TypeNameNode(selfAllocator, translationUnit, TypeNameKind::Pointer) {
}

CXXGEN_API PointerTypeNameNode::~PointerTypeNameNode() {
}

CXXGEN_API FnPointerTypeNameNode::FnPointerTypeNameNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : TypeNameNode(selfAllocator, translationUnit, TypeNameKind::FnPointer), params(selfAllocator) {
}

CXXGEN_API FnPointerTypeNameNode::~FnPointerTypeNameNode() {
}

CXXGEN_API ArrayTypeNameNode::ArrayTypeNameNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : TypeNameNode(selfAllocator, translationUnit, TypeNameKind::Array) {
}

CXXGEN_API ArrayTypeNameNode::~ArrayTypeNameNode() {
}

CXXGEN_API RefTypeNameNode::RefTypeNameNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : TypeNameNode(selfAllocator, translationUnit, TypeNameKind::Ref) {
}

CXXGEN_API RefTypeNameNode::~RefTypeNameNode() {
}

CXXGEN_API RvalueTypeNameNode::RvalueTypeNameNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : TypeNameNode(selfAllocator, translationUnit, TypeNameKind::Rvalue) {
}

CXXGEN_API RvalueTypeNameNode::~RvalueTypeNameNode() {
}

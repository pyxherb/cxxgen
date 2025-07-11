#include "class.h"

using namespace cxxgen;

CXXGEN_API AbstractModuleNode::AbstractModuleNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit, AstNodeType astNodeType) : AstNode(astNodeType, selfAllocator, translationUnit), name(selfAllocator), body(selfAllocator) {
}

CXXGEN_API AbstractModuleNode::~AbstractModuleNode() {
}

CXXGEN_API RootNode::RootNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : AbstractModuleNode(selfAllocator, translationUnit, AstNodeType::Root) {
}

CXXGEN_API RootNode::~RootNode() {
}

CXXGEN_API ClassNode::ClassNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : AbstractModuleNode(selfAllocator, translationUnit, AstNodeType::Class) {
}

CXXGEN_API ClassNode::~ClassNode() {
}

CXXGEN_API StructNode::StructNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : AbstractModuleNode(selfAllocator, translationUnit, AstNodeType::Struct) {
}

CXXGEN_API StructNode::~StructNode() {
}

CXXGEN_API NamespaceNode::NamespaceNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : AbstractModuleNode(selfAllocator, translationUnit, AstNodeType::Namespace) {
}

CXXGEN_API NamespaceNode::~NamespaceNode() {
}

#include "class.h"

using namespace cxxgen;

CXXGEN_API AbstractModuleNode::AbstractModuleNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit, AstNodeType astNodeType) : AstNode(astNodeType, selfAllocator, translationUnit), name(selfAllocator), body(selfAllocator) {
}

CXXGEN_API AbstractModuleNode::~AbstractModuleNode() {
}

CXXGEN_API ClassNode::ClassNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit, AstNodeType astNodeType) : AbstractModuleNode(selfAllocator, translationUnit, AstNodeType::Class) {
}

CXXGEN_API ClassNode::~ClassNode() {
}

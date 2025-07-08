#include "fn.h"

using namespace cxxgen;

CXXGEN_API FnNode::FnNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : AstNode(AstNodeType::Fn, selfAllocator, translationUnit), params(selfAllocator) {
}

CXXGEN_API FnNode::~FnNode() {
}

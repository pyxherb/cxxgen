#include "directive.h"

using namespace cxxgen;

CXXGEN_API DirectiveNode::DirectiveNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : AstNode(AstNodeType::Directive, selfAllocator, translationUnit) {
}

CXXGEN_API DirectiveNode::~DirectiveNode() {
}

CXXGEN_API IfDirectiveNode::IfDirectiveNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : AstNode(AstNodeType::IfDirective, selfAllocator, translationUnit), body(selfAllocator) {
}

CXXGEN_API IfDirectiveNode::~IfDirectiveNode() {
}

CXXGEN_API IfdefDirectiveNode::IfdefDirectiveNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : AstNode(AstNodeType::IfdefDirective, selfAllocator, translationUnit), body(selfAllocator) {
}

CXXGEN_API IfdefDirectiveNode::~IfdefDirectiveNode() {
}

CXXGEN_API IfndefDirectiveNode::IfndefDirectiveNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : AstNode(AstNodeType::IfndefDirective, selfAllocator, translationUnit), body(selfAllocator) {
}

CXXGEN_API IfndefDirectiveNode::~IfndefDirectiveNode() {
}

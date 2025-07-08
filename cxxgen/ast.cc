#include "ast.h"

using namespace cxxgen;

CXXGEN_API void TranslationUnit::_doClearDeferredDestructibleAstNodes() {
	AstNode *i, *next;

	while ((i = destructibleAstNodeList)) {
		destructibleAstNodeList = nullptr;

		while (i) {
			next = i->_nextDestructible;
			i->_destructor(i);
			i = next;
		};
	}
}

CXXGEN_API void cxxgen::addAstNodeToDestructibleList(AstNode *astNode, AstNodeDestructor destructor) {
	astNode->_nextDestructible = astNode->translationUnit->destructibleAstNodeList;
	astNode->_destructor = destructor;
	astNode->translationUnit->destructibleAstNodeList = astNode;
}

CXXGEN_API AstNode::AstNode(AstNodeType astNodeType, peff::Alloc *selfAllocator, TranslationUnit *translationUnit) : translationUnit(translationUnit), astNodeType(astNodeType) {
	translationUnit->clearDeferredDestructibleAstNodes();
}

CXXGEN_API AstNode::~AstNode() {
}

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

CXXGEN_API AbstractModuleNode::AbstractModuleNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit, AstNodeType astNodeType) : AstNode(astNodeType, selfAllocator, translationUnit), name(selfAllocator), body(selfAllocator) {
}

CXXGEN_API AbstractModuleNode::~AbstractModuleNode() {
}

CXXGEN_API ClassNode::ClassNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit, AstNodeType astNodeType): AbstractModuleNode(selfAllocator, translationUnit, AstNodeType::Class) {
}

CXXGEN_API ClassNode::~ClassNode() {
}

#include "astnode.h"

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

#include "builder.h"

using namespace cxxgen;

CXXGEN_API AstBuilder::AstBuilder(peff::Alloc *allocator, TranslationUnit *translationUnit)
	: allocator(allocator), translationUnit(translationUnit) {
}

CXXGEN_API AstBuilder::~AstBuilder() {
}

CXXGEN_API AstNodePtr<RootNode> AstBuilder::buildRoot() {
	return cxxgen::makeAstNode<cxxgen::RootNode>(allocator.get(), allocator.get(), translationUnit);
}

CXXGEN_API AstNodePtr<NamespaceNode> AstBuilder::buildNamespace() {
	return cxxgen::makeAstNode<cxxgen::NamespaceNode>(allocator.get(), allocator.get(), translationUnit);
}

CXXGEN_API AstNodePtr<ClassNode> AstBuilder::buildClass() {
	return cxxgen::makeAstNode<cxxgen::ClassNode>(allocator.get(), allocator.get(), translationUnit);
}

CXXGEN_API AstNodePtr<StructNode> AstBuilder::buildStruct() {
	return cxxgen::makeAstNode<cxxgen::StructNode>(allocator.get(), allocator.get(), translationUnit);
}

#ifndef _CXXGEN_BUILDER_H_
#define _CXXGEN_BUILDER_H_

#include "ast.h"

namespace cxxgen {
	class AstBuilder final {
	public:
		peff::RcObjectPtr<peff::Alloc> allocator;
		TranslationUnit *translationUnit;

		CXXGEN_API AstBuilder(peff::Alloc *allocator, TranslationUnit *translationUnit);
		CXXGEN_API ~AstBuilder();

		CXXGEN_API AstNodePtr<RootNode> createRoot();

		CXXGEN_API AstNodePtr<NamespaceNode> createNamespace();

		CXXGEN_API AstNodePtr<ClassNode> createClass();

		CXXGEN_API AstNodePtr<StructNode> createStruct();

		CXXGEN_API AstNodePtr<IdExprNode> createIdExpr();

		CXXGEN_API AstNodePtr<IdExprNode> buildIdExpr(const std::string_view &name);

		CXXGEN_API AstNodePtr<IdExprNode> buildIdExpr(const std::string_view &name, AstNodePtr<AstNode> *templateArgs, size_t nArgs);

		CXXGEN_API AstNodePtr<ScopeResolveExprNode> createScopeResolveExpr();

		CXXGEN_API AstNodePtr<ExprNode> buildQualifiedIdExpr(AstNodePtr<IdExprNode> *ids, size_t nIds);
	};
}

#endif

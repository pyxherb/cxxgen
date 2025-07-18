#ifndef _CXXGEN_AST_DIRECTIVE_H_
#define _CXXGEN_AST_DIRECTIVE_H_

#include "astnode.h"
#include <peff/advutils/shared_ptr.h>
#include <peff/containers/dynarray.h>
#include <peff/containers/string.h>
#include <variant>
#include <optional>

namespace cxxgen {
	using DirectiveArgs =
		std::variant<
			std::monostate,
			peff::String,
			peff::DynArray<peff::String>>;

	class DirectiveNode : public AstNode {
	public:
		peff::String name;
		DirectiveArgs args;

		CXXGEN_API DirectiveNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~DirectiveNode();
	};

	class IncludeDirectiveNode : public AstNode {
	public:
		peff::String path;
		bool isSystem = true;

		CXXGEN_API IncludeDirectiveNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~IncludeDirectiveNode();
	};

	class IfDirectiveNode : public AstNode {
	public:
		DirectiveArgs args;
		peff::DynArray<AstNodePtr<AstNode>> body;
		std::optional<
			peff::DynArray<AstNodePtr<AstNode>>>
			elseBody;

		CXXGEN_API IfDirectiveNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~IfDirectiveNode();
	};

	class IfdefDirectiveNode : public AstNode {
	public:
		peff::String name;
		peff::DynArray<AstNodePtr<AstNode>> body;
		std::optional<
			peff::DynArray<AstNodePtr<AstNode>>>
			elseBody;

		CXXGEN_API IfdefDirectiveNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~IfdefDirectiveNode();
	};

	class IfndefDirectiveNode : public AstNode {
	public:
		peff::String name;
		peff::DynArray<AstNodePtr<AstNode>> body;
		std::optional<
			peff::DynArray<AstNodePtr<AstNode>>>
			elseBody;

		CXXGEN_API IfndefDirectiveNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~IfndefDirectiveNode();
	};
}

#endif

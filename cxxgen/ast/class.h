#ifndef _CXXGEN_AST_CLASS_H_
#define _CXXGEN_AST_CLASS_H_

#include "typename.h"
#include <peff/containers/string.h>
#include <peff/containers/dynarray.h>
#include <optional>

namespace cxxgen {
	class AbstractModuleNode : public AstNode {
	public:
		peff::String name;
		std::optional<peff::DynArray<AstNodePtr<AstNode>>> body;

		CXXGEN_API AbstractModuleNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit, AstNodeType astNodeType);
		CXXGEN_API virtual ~AbstractModuleNode();
	};

	enum class InheritanceAccess {
		Default = 0,
		Public,
		Private,
		Protected
	};

	struct InheritanceEntry {
		InheritanceAccess access = InheritanceAccess::Default;
		AstNodePtr<TypeNameNode> baseType;
	};

	class RootNode : public AbstractModuleNode {
	public:
		CXXGEN_API RootNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~RootNode();
	};

	class ClassNode : public AbstractModuleNode {
	public:
		peff::String name;
		bool isFinal = false;

		peff::DynArray<InheritanceEntry> baseTypes;

		CXXGEN_API ClassNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~ClassNode();

		[[nodiscard]] CXXGEN_API bool setName(const std::string_view &name);
	};

	class StructNode : public AbstractModuleNode {
	public:
		peff::String name;
		bool isFinal = false;

		peff::DynArray<InheritanceEntry> baseTypes;

		CXXGEN_API StructNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~StructNode();
	};

	class NamespaceNode : public AbstractModuleNode {
	public:
		peff::String name;

		CXXGEN_API NamespaceNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~NamespaceNode();
	};
}

#endif

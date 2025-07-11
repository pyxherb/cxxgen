#ifndef _CXXGEN_AST_CLASS_H_
#define _CXXGEN_AST_CLASS_H_

#include "typename.h"
#include <peff/containers/string.h>
#include <peff/containers/dynarray.h>

namespace cxxgen {
	class AbstractModuleNode : public AstNode {
	public:
		peff::String name;
		peff::DynArray<AstNodePtr<AstNode>> body;

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
		InheritanceAccess accessModifier;
	};

	class RootNode : public AbstractModuleNode {
	public:
		CXXGEN_API RootNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~RootNode();
	};

	class ClassNode : public AbstractModuleNode {
	public:
		bool isFinal = false;

		CXXGEN_API ClassNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~ClassNode();
	};

	class StructNode : public AbstractModuleNode {
	public:
		bool isFinal = false;

		CXXGEN_API StructNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~StructNode();
	};

	class NamespaceNode : public AbstractModuleNode {
	public:
		CXXGEN_API NamespaceNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~NamespaceNode();
	};
}

#endif

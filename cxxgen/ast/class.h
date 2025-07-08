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

	enum class AccessModifier {
		Default = 0,
		Public,
		Private,
		Protected
	};

	struct InheritanceEntry {
		AccessModifier accessModifier;
	};

	class ClassNode : public AbstractModuleNode {
	public:
		CXXGEN_API ClassNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit, AstNodeType astNodeType);
		CXXGEN_API virtual ~ClassNode();
	};
}

#endif

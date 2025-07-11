#ifndef _CXXGEN_AST_MISC_H_
#define _CXXGEN_AST_MISC_H_

#include "expr.h"

namespace cxxgen {
	enum class DeclaratorKind {
		Pointer = 0,
		Array,
		Ref,
		Rvalue,
	};

	class DeclaractorNode : public AstNode {
	public:
		DeclaratorKind declaractorKind;

		CXXGEN_API DeclaractorNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit, DeclaratorKind declaractorKind);
		CXXGEN_API virtual ~DeclaractorNode();
	};

	class PointerDeclaractorNode : public DeclaractorNode {
	public:
		bool isConst = false;
		bool isVolatile = false;

		CXXGEN_API PointerDeclaractorNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~PointerDeclaractorNode();
	};

	class ArrayDeclaractorNode : public DeclaractorNode {
	public:
		AstNodePtr<ExprNode> length;

		CXXGEN_API ArrayDeclaractorNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~ArrayDeclaractorNode();
	};

	class RefDeclaractorNode : public DeclaractorNode {
	public:
		CXXGEN_API RefDeclaractorNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~RefDeclaractorNode();
	};

	class RvalueDeclaractorNode : public DeclaractorNode {
	public:
		CXXGEN_API RvalueDeclaractorNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~RvalueDeclaractorNode();
	};

	struct VarDefEntry {
		peff::String name;
		peff::DynArray<AstNodePtr<DeclaractorNode>> declaractors;

		CXXGEN_API VarDefEntry(peff::Alloc *allocator);
		CXXGEN_API ~VarDefEntry();
	};

	class VarDefNode : public AstNode {
	public:
		peff::DynArray<VarDefEntry> varDefEntries;

		CXXGEN_API VarDefNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~VarDefNode();
	};
}

#endif

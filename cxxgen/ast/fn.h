#ifndef _CXXGEN_AST_FN_H_
#define _CXXGEN_AST_FN_H_

#include "typename.h"

namespace cxxgen {
	class FnNode : public AstNode {
	public:
		AstNodePtr<TypeNameNode> returnType;
		peff::DynArray<ParamSlot> params;
		bool isNoexcept = false;

		bool isConst = false;
		bool isFinal = false;
		bool isVirtual = false;
		bool isInline = false;

		CXXGEN_API FnNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~FnNode();
	};
}

#endif

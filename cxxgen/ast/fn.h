#ifndef _CXXGEN_AST_FN_H_
#define _CXXGEN_AST_FN_H_

#include "typename.h"

namespace cxxgen {
	class BlockStmtNode;

	class FnNode : public AstNode {
	public:
		peff::String name;

		AstNodePtr<TypeNameNode> returnType;
		peff::DynArray<ParamSlot> params;
		bool isNoexcept = false;

		bool isConst = false;
		bool isFinal = false;
		bool isVirtual = false;
		bool isInline = false;

		AstNodePtr<BlockStmtNode> body;

		CXXGEN_API FnNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~FnNode();
	};
}

#endif

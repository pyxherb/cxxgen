#ifndef _CXXGEN_AST_STMT_H_
#define _CXXGEN_AST_STMT_H_

#include "expr.h"

namespace cxxgen {
	enum class StmtKind : uint8_t {
		Expr = 0,
		LocalVarDef,
		If,
		For,
		While,
		Break,
		Continue,
		Return,
		Block,
		Label,
		Goto,
		Switch
	};

	class StmtNode : public AstNode {
	public:
		StmtKind stmtKind;

		CXXGEN_API StmtNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit, StmtKind stmtKind);
		CXXGEN_API virtual ~StmtNode();
	};

	class ExprStmtNode : public StmtNode {
	public:
		AstNodePtr<ExprStmtNode> expr;

		CXXGEN_API ExprStmtNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~ExprStmtNode();
	};

	enum class VarDefDecoratorKind {
		Pointer = 0,
		Array,
		Ref,
		Rvalue,
	};

	struct VarDefDecorator {
		VarDefDecoratorKind decoratorKind;
	};

	struct VarDefEntry {
		peff::String name;
		peff::DynArray<VarDefDecorator> decorators;

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

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

	class VarDefNode : public AstNode {
	public:
		CXXGEN_API VarDefNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~VarDefNode();
	};
}

#endif

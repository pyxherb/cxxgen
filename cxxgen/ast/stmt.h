#ifndef _CXXGEN_AST_STMT_H_
#define _CXXGEN_AST_STMT_H_

#include "expr.h"
#include "misc.h"

namespace cxxgen {
	enum class StmtKind : uint8_t {
		Expr = 0,
		LocalVarDef,
		If,
		For,
		While,
		DoWhile,
		Break,
		Continue,
		Return,
		Block,
		Label,
		Goto,
		Switch,
		CaseLabel
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

	class LocalVarDefStmtNode : public StmtNode {
	public:
		AstNodePtr<VarDefNode> varDef;

		CXXGEN_API LocalVarDefStmtNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~LocalVarDefStmtNode();
	};

	class IfStmtNode : public StmtNode {
	public:
		AstNodePtr<ExprStmtNode> condition;
		AstNodePtr<StmtNode> trueBranch, elseBranch;

		CXXGEN_API IfStmtNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~IfStmtNode();
	};

	class ForStmtNode : public StmtNode {
	public:
		AstNodePtr<StmtNode> initStmt;
		AstNodePtr<ExprStmtNode> condition;
		AstNodePtr<ExprStmtNode> step;
		AstNodePtr<StmtNode> body;

		CXXGEN_API ForStmtNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~ForStmtNode();
	};

	class WhileStmtNode : public StmtNode {
	public:
		AstNodePtr<ExprStmtNode> condition;
		AstNodePtr<StmtNode> body;

		CXXGEN_API WhileStmtNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~WhileStmtNode();
	};

	class DoWhileStmtNode : public StmtNode {
	public:
		AstNodePtr<ExprStmtNode> condition;
		AstNodePtr<StmtNode> body;

		CXXGEN_API DoWhileStmtNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~DoWhileStmtNode();
	};

	class BreakStmtNode : public StmtNode {
	public:
		CXXGEN_API BreakStmtNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~BreakStmtNode();
	};

	class ContinueStmtNode : public StmtNode {
	public:
		CXXGEN_API ContinueStmtNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~ContinueStmtNode();
	};

	class ReturnStmtNode : public StmtNode {
	public:
		AstNodePtr<ExprStmtNode> value;

		CXXGEN_API ReturnStmtNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~ReturnStmtNode();
	};

	class BlockStmtNode : public StmtNode {
	public:
		peff::DynArray<AstNodePtr<StmtNode>> body;

		CXXGEN_API BlockStmtNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~BlockStmtNode();
	};

	class LabelStmtNode : public StmtNode {
	public:
		peff::String name;

		CXXGEN_API LabelStmtNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~LabelStmtNode();
	};

	class GotoStmtNode : public StmtNode {
	public:
		peff::String name;

		CXXGEN_API GotoStmtNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~GotoStmtNode();
	};

	class SwitchStmtNode : public StmtNode {
	public:
		peff::DynArray<AstNodePtr<StmtNode>> body;

		CXXGEN_API SwitchStmtNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~SwitchStmtNode();
	};

	class CaseLabelStmtNode : public StmtNode {
	public:
		AstNodePtr<ExprNode> caseValue;

		CXXGEN_API CaseLabelStmtNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~CaseLabelStmtNode();
	};
}

#endif

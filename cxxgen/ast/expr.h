#ifndef _CXXGEN_AST_EXPR_H_
#define _CXXGEN_AST_EXPR_H_

#include "typename.h"
#include <peff/containers/dynarray.h>
#include <cstdint>

namespace cxxgen {
	enum class ExprKind : uint8_t {
		IntLiteral = 0,
		LongLiteral,
		UIntLiteral,
		ULongLiteral,
		CharLiteral,
		StringLiteral,
		FloatLiteral,
		DoubleLiteral,
		BoolLiteral,
		NullptrLiteral,
		Id,
		InitializerList,

		Unary,
		Binary,
		ScopeResolve,
		MemberAccess,
		PtrMemberAccess,
		Call,
		Cast,
		New,
		PlacementNew,
		Ternary,
		TypeSizeof,
		ExprSizeof,
		Alignof,
		This
	};

	class ExprNode : public AstNode {
	public:
		bool isConst = false;
		bool isVolatile = false;
		ExprKind exprKind;

		CXXGEN_API ExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit, ExprKind exprKind);
		CXXGEN_API virtual ~ExprNode();
	};

	template <typename T, ExprKind EK>
	class LiteralExprNode : public ExprNode {
	public:
		T data;

		inline LiteralExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit, T &&data) : ExprNode(selfAllocator, translationUnit, EK), data(data) {}
		virtual inline ~LiteralExprNode() {}
	};

	using IntLiteralExprNode = LiteralExprNode<int, ExprKind::IntLiteral>;
	using LongLiteralExprNode = LiteralExprNode<long, ExprKind::LongLiteral>;
	using UIntLiteralExprNode = LiteralExprNode<unsigned int, ExprKind::UIntLiteral>;
	using ULongLiteralExprNode = LiteralExprNode<unsigned long long, ExprKind::ULongLiteral>;
	using CharLiteralExprNode = LiteralExprNode<char, ExprKind::CharLiteral>;
	using FloatLiteralExprNode = LiteralExprNode<float, ExprKind::FloatLiteral>;
	using DoubleLiteralExprNode = LiteralExprNode<double, ExprKind::DoubleLiteral>;
	using BoolLiteralExprNode = LiteralExprNode<bool, ExprKind::BoolLiteral>;

	class StringLiteralExprNode final : public ExprNode {
	public:
		peff::String data;

		CXXGEN_API StringLiteralExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~StringLiteralExprNode();
	};

	class NullptrLiteralExprNode final : public ExprNode {
	public:
		CXXGEN_API NullptrLiteralExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~NullptrLiteralExprNode();
	};

	class IdExprNode final : public ExprNode {
	public:
		peff::String name;

		CXXGEN_API IdExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~IdExprNode();
	};

	class InitializerListExprNode final : public ExprNode {
	public:
		AstNodePtr<TypeNameNode> type;
		peff::DynArray<AstNodePtr<ExprNode>> elements;

		CXXGEN_API InitializerListExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~InitializerListExprNode();
	};

	enum class UnaryOp {
		Unspecified = 0,

		IncForward,
		IncBackward,
		DecForward,
		DecBackward,
		Plus,
		Negate,
		Not,
		LNot,
		Dereference,
		AddressOf,
	};

	class UnaryExprNode final : public ExprNode {
	public:
		UnaryOp unaryOp = UnaryOp::Unspecified;

		AstNodePtr<ExprNode> operand;

		CXXGEN_API UnaryExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~UnaryExprNode();
	};

	enum class BinaryOp {
		Unspecified = 0,

		Add,
		Sub,
		Mul,
		Div,
		Mod,
		And,
		Or,
		Xor,
		LAnd,
		LOr,
		Shl,
		Shr,
		Eq,
		Neq,
		Lt,
		Gt,
		LtEq,
		GtEq,
		Cmp,
		Subscript,

		Assign,
	};

	class BinaryExprNode final : public ExprNode {
	public:
		BinaryOp binaryOp = BinaryOp::Unspecified;

		AstNodePtr<ExprNode> lhs, rhs;

		CXXGEN_API BinaryExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~BinaryExprNode();
	};

	class ScopeResolveExprNode final : public ExprNode {
	public:
		AstNodePtr<ExprNode> lhs;
		AstNodePtr<IdExprNode> rhs;

		CXXGEN_API ScopeResolveExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~ScopeResolveExprNode();
	};

	class MemberAccessExprNode final : public ExprNode {
	public:
		AstNodePtr<ExprNode> lhs;
		AstNodePtr<IdExprNode> rhs;

		CXXGEN_API MemberAccessExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~MemberAccessExprNode();
	};

	class PtrMemberAccessExprNode final : public ExprNode {
	public:
		AstNodePtr<ExprNode> lhs;
		AstNodePtr<IdExprNode> rhs;

		CXXGEN_API PtrMemberAccessExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~PtrMemberAccessExprNode();
	};

	class CallExprNode final : public ExprNode {
	public:
		AstNodePtr<ExprNode> target;
		peff::DynArray<AstNodePtr<ExprNode>> args;

		CXXGEN_API CallExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~CallExprNode();
	};

	class CastExprNode final : public ExprNode {
	public:
		AstNodePtr<TypeNameNode> destType;
		AstNodePtr<ExprNode> operand;

		CXXGEN_API CastExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~CastExprNode();
	};

	class NewExprNode final : public ExprNode {
	public:
		AstNodePtr<TypeNameNode> type;
		peff::DynArray<AstNodePtr<ExprNode>> args;

		CXXGEN_API NewExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~NewExprNode();
	};

	class PlacementNewExprNode final : public ExprNode {
	public:
		AstNodePtr<ExprNode> location;
		AstNodePtr<TypeNameNode> type;
		peff::DynArray<AstNodePtr<ExprNode>> args;

		CXXGEN_API PlacementNewExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~PlacementNewExprNode();
	};

	class TernaryExprNode final : public ExprNode {
	public:
		AstNodePtr<ExprNode> condition, trueExpr, falseExpr;

		CXXGEN_API TernaryExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~TernaryExprNode();
	};

	class TypeSizeofExprNode final : public ExprNode {
	public:
		AstNodePtr<TypeNameNode> operand;

		CXXGEN_API TypeSizeofExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~TypeSizeofExprNode();
	};

	class ExprSizeofExprNode final : public ExprNode {
	public:
		AstNodePtr<ExprNode> operand;

		CXXGEN_API ExprSizeofExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~ExprSizeofExprNode();
	};

	class AlignofExprNode final : public ExprNode {
	public:
		AstNodePtr<TypeNameNode> operand;

		CXXGEN_API AlignofExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~AlignofExprNode();
	};

	class ThisExprNode final : public ExprNode {
	public:
		CXXGEN_API ThisExprNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~ThisExprNode();
	};
}

#endif

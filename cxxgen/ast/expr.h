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
		Call,
		Cast,
		New,
		Conditional,
		TypeSizeof,
		ExprSizeof,
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
		IdStorage name;

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
}

#endif

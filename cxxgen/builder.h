#ifndef _CXXGEN_BUILDER_H_
#define _CXXGEN_BUILDER_H_

#include "ast.h"

namespace cxxgen {
	class AstBuilder final {
	public:
		peff::RcObjectPtr<peff::Alloc> allocator;
		TranslationUnit *translationUnit;

		CXXGEN_API AstBuilder(peff::Alloc *allocator, TranslationUnit *translationUnit);
		CXXGEN_API ~AstBuilder();

		CXXGEN_API AstNodePtr<RootNode> createRoot();

		CXXGEN_API AstNodePtr<NamespaceNode> createNamespace();

		CXXGEN_API AstNodePtr<ClassNode> createClass();

		CXXGEN_API AstNodePtr<StructNode> createStruct();

		CXXGEN_API AstNodePtr<IdExprNode> createIdExpr();

		CXXGEN_API AstNodePtr<IntLiteralExprNode> buildIntLitrealExpr(int data);

		CXXGEN_API AstNodePtr<LongLiteralExprNode> buildLongLitrealExpr(long data);

		CXXGEN_API AstNodePtr<LongLongLiteralExprNode> buildLongLongLitrealExpr(long long data);

		CXXGEN_API AstNodePtr<UIntLiteralExprNode> buildUIntLitrealExpr(unsigned int data);

		CXXGEN_API AstNodePtr<ULongLiteralExprNode> buildULongLitrealExpr(unsigned long data);

		CXXGEN_API AstNodePtr<ULongLongLiteralExprNode> buildULongLongLitrealExpr(unsigned long long data);

		CXXGEN_API AstNodePtr<CharLiteralExprNode> buildCharLitrealExpr(char data);

		CXXGEN_API AstNodePtr<IdExprNode> buildIdExpr(const std::string_view &name);

		CXXGEN_API AstNodePtr<IdExprNode> buildIdExpr(const std::string_view &name, AstNodePtr<AstNode> *templateArgs, size_t nArgs);

		CXXGEN_API AstNodePtr<ScopeResolveExprNode> createScopeResolveExpr();

		CXXGEN_API AstNodePtr<ExprNode> buildQualifiedIdExpr(AstNodePtr<IdExprNode> *ids, size_t nIds);

		CXXGEN_API AstNodePtr<UnaryExprNode> createUnaryExpr();

		CXXGEN_API AstNodePtr<UnaryExprNode> buildUnaryExpr(UnaryOp unaryOp, AstNodePtr<ExprNode> operand);

		CXXGEN_API AstNodePtr<BinaryExprNode> createBinaryExpr();

		CXXGEN_API AstNodePtr<BinaryExprNode> buildBinaryExpr(BinaryOp binaryOp, AstNodePtr<ExprNode> lhs, AstNodePtr<ExprNode> rhs);

		CXXGEN_API AstNodePtr<ExprStmtNode> createExprStmt();

		CXXGEN_API AstNodePtr<ExprStmtNode> buildExprStmt(AstNodePtr<ExprNode> expr);

		CXXGEN_API AstNodePtr<IfStmtNode> createIfStmt();

		CXXGEN_API AstNodePtr<IfStmtNode> buildIfStmt(AstNodePtr<ExprNode> condition, AstNodePtr<StmtNode> trueBranch);

		CXXGEN_API AstNodePtr<IfStmtNode> buildIfStmt(AstNodePtr<ExprNode> condition, AstNodePtr<StmtNode> trueBranch, AstNodePtr<StmtNode> elseBranch);

		CXXGEN_API AstNodePtr<BlockStmtNode> createBlockStmt();
	};
}

#endif

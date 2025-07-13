#include "builder.h"

using namespace cxxgen;

CXXGEN_API AstBuilder::AstBuilder(peff::Alloc *allocator, TranslationUnit *translationUnit)
	: allocator(allocator), translationUnit(translationUnit) {
}

CXXGEN_API AstBuilder::~AstBuilder() {
}

CXXGEN_API AstNodePtr<RootNode> AstBuilder::createRoot() {
	return cxxgen::makeAstNode<cxxgen::RootNode>(allocator.get(), allocator.get(), translationUnit);
}

CXXGEN_API AstNodePtr<NamespaceNode> AstBuilder::createNamespace() {
	return cxxgen::makeAstNode<cxxgen::NamespaceNode>(allocator.get(), allocator.get(), translationUnit);
}

CXXGEN_API AstNodePtr<ClassNode> AstBuilder::createClass() {
	return cxxgen::makeAstNode<cxxgen::ClassNode>(allocator.get(), allocator.get(), translationUnit);
}

CXXGEN_API AstNodePtr<StructNode> AstBuilder::createStruct() {
	return cxxgen::makeAstNode<cxxgen::StructNode>(allocator.get(), allocator.get(), translationUnit);
}


CXXGEN_API AstNodePtr<IdExprNode> AstBuilder::createIdExpr() {
	return cxxgen::makeAstNode<cxxgen::IdExprNode>(allocator.get(), allocator.get(), translationUnit);
}

CXXGEN_API AstNodePtr<IdExprNode> AstBuilder::buildIdExpr(const std::string_view &name) {
	auto p = createIdExpr();

	if (!p) {
		return {};
	}

	if (!p->name.build(name)) {
		return {};
	}

	return p;
}

CXXGEN_API AstNodePtr<IdExprNode> AstBuilder::buildIdExpr(const std::string_view &name, AstNodePtr<AstNode> *templateArgs, size_t nArgs) {
	auto p = buildIdExpr(name);

	if (!p) {
		return {};
	}

	p->templateArgs = peff::DynArray<AstNodePtr<AstNode>>(p->selfAllocator.get());

	if (!p->templateArgs->resize(nArgs)) {
		return {};
	}

	for (size_t i = 0; i < nArgs; ++i) {
		p->templateArgs->at(i) = templateArgs[i];
	}

	return p;
}

CXXGEN_API AstNodePtr<ScopeResolveExprNode> AstBuilder::createScopeResolveExpr() {
	return cxxgen::makeAstNode<cxxgen::ScopeResolveExprNode>(allocator.get(), allocator.get(), translationUnit);
}

CXXGEN_API AstNodePtr<ExprNode> AstBuilder::buildQualifiedIdExpr(AstNodePtr<IdExprNode> *ids, size_t nIds) {
	auto p = createScopeResolveExpr();

	if (!p) {
		return {};
	}

	AstNodePtr<ScopeResolveExprNode> e;

	for (size_t i = 1; i < nIds; ++i) {
		if (e) {
			AstNodePtr<ScopeResolveExprNode> ne;

			if (!(ne = createScopeResolveExpr())) {
				return {};
			}
			ne->lhs = e.castTo<ExprNode>();
			e = ne;
		} else {
			if (!(e = createScopeResolveExpr())) {
				return {};
			}
			e->lhs = ids[0].castTo<ExprNode>();
		}

		e->rhs = ids[i];
	}

	if (!e) {
		return ids[0].castTo<ExprNode>();
	}

	return e.castTo<ExprNode>();
}

CXXGEN_API AstNodePtr<UnaryExprNode> AstBuilder::createUnaryExpr() {
	return cxxgen::makeAstNode<cxxgen::UnaryExprNode>(allocator.get(), allocator.get(), translationUnit);
}

CXXGEN_API AstNodePtr<UnaryExprNode> AstBuilder::buildUnaryExpr(UnaryOp binaryOp, AstNodePtr<ExprNode> operand) {
	auto p = createUnaryExpr();

	if (!p) {
		return {};
	}

	p->unaryOp = binaryOp;

	p->operand = operand;

	return p;
}


CXXGEN_API AstNodePtr<BinaryExprNode> AstBuilder::createBinaryExpr() {
	return cxxgen::makeAstNode<cxxgen::BinaryExprNode>(allocator.get(), allocator.get(), translationUnit);
}

CXXGEN_API AstNodePtr<BinaryExprNode> AstBuilder::buildBinaryExpr(BinaryOp binaryOp, AstNodePtr<ExprNode> lhs, AstNodePtr<ExprNode> rhs) {
	auto p = createBinaryExpr();

	if (!p) {
		return {};
	}

	p->binaryOp = binaryOp;

	p->lhs = lhs;
	p->rhs = rhs;

	return p;
}

CXXGEN_API AstNodePtr<IfStmtNode> AstBuilder::createIfStmt() {
	return cxxgen::makeAstNode<cxxgen::IfStmtNode>(allocator.get(), allocator.get(), translationUnit);
}

CXXGEN_API AstNodePtr<IfStmtNode> AstBuilder::buildIfStmt(AstNodePtr<ExprNode> condition, AstNodePtr<StmtNode> trueBranch) {
	auto p = createIfStmt();

	if (!p) {
		return {};
	}

	p->condition = condition;

	p->trueBranch = trueBranch;

	return p;
}

CXXGEN_API AstNodePtr<IfStmtNode> AstBuilder::buildIfStmt(AstNodePtr<ExprNode> condition, AstNodePtr<StmtNode> trueBranch, AstNodePtr<StmtNode> elseBranch) {
	auto p = createIfStmt();

	if (!p) {
		return {};
	}

	p->condition = condition;

	p->trueBranch = trueBranch;

	p->elseBranch = elseBranch;

	return p;
}

CXXGEN_API AstNodePtr<BlockStmtNode> AstBuilder::createBlockStmt() {
	return cxxgen::makeAstNode<cxxgen::BlockStmtNode>(allocator.get(), allocator.get(), translationUnit);
}

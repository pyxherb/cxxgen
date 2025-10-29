#include <cxxgen/builder.h>
#include <cxxgen/dump/dump.h>

class ANSIDumpWriter : public cxxgen::DumpWriter {
public:
	ANSIDumpWriter() {
	}

	virtual ~ANSIDumpWriter() {
	}

	virtual bool write(const char *src, size_t size) override {
		fwrite(src, size, 1, stdout);
		return true;
	}
};

int main() {
#ifndef NDEBUG
	#ifdef _MSC_VER
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif
#endif

	cxxgen::TranslationUnit tu;

	{
		cxxgen::AstBuilder astBuilder(peff::getDefaultAlloc(), &tu);
		cxxgen::AstNodePtr<cxxgen::RootNode> root;

		if (!(root = astBuilder.createRoot())) {
			throw std::bad_alloc();
		}

		{
			cxxgen::AstNodePtr<cxxgen::ClassNode> testClass;

			if (!(testClass = astBuilder.createClass())) {
				throw std::bad_alloc();
			}

			if (!(testClass->setName("Test")))
				throw std::bad_alloc();
		}

		cxxgen::AstNodePtr<cxxgen::ExprNode> testQualifiedId;
		{
			cxxgen::AstNodePtr<cxxgen::IdExprNode> testId[3];

			if (!(testId[0] = astBuilder.buildIdExpr("aaa"))) {
				throw std::bad_alloc();
			}

			if (!(testId[1] = astBuilder.buildIdExpr("bbb"))) {
				throw std::bad_alloc();
			}

			if (!(testId[2] = astBuilder.buildIdExpr("ccc"))) {
				throw std::bad_alloc();
			}

			if (!(testQualifiedId = astBuilder.buildQualifiedIdExpr(testId, std::size(testId)))) {
				throw std::bad_alloc();
			}
		}

		cxxgen::AstNodePtr<cxxgen::BinaryExprNode> binaryExpr;

		if (!(binaryExpr = astBuilder.buildBinaryExpr(cxxgen::BinaryOp::Add, testQualifiedId, testQualifiedId))) {
			throw std::bad_alloc();
		}

		cxxgen::AstNodePtr<cxxgen::IntLiteralExprNode> intExpr;

		if (!(intExpr = astBuilder.buildIntLiteralExpr(123))) {
			throw std::bad_alloc();
		}

		cxxgen::AstNodePtr<cxxgen::IfStmtNode> ifStmt;

		cxxgen::AstNodePtr<cxxgen::BlockStmtNode> blockStmt;
		cxxgen::AstNodePtr<cxxgen::ExprStmtNode> exprStmt;

		if (!(blockStmt = astBuilder.createBlockStmt())) {
			throw std::bad_alloc();
		}

		if (!(ifStmt = astBuilder.buildIfStmt(testQualifiedId, blockStmt.castTo<cxxgen::StmtNode>(), blockStmt.castTo<cxxgen::StmtNode>()))) {
			throw std::bad_alloc();
		}

		if (!(exprStmt = astBuilder.buildExprStmt(intExpr.castTo<cxxgen::ExprNode>()))) {
			throw std::bad_alloc();
		}

		if (!blockStmt->body.pushBack(exprStmt.castTo<cxxgen::StmtNode>())) {
			throw std::bad_alloc();
		}

		if (!(exprStmt = astBuilder.buildExprStmt(intExpr.castTo<cxxgen::ExprNode>()))) {
			throw std::bad_alloc();
		}

		if (!blockStmt->body.pushBack(exprStmt.castTo<cxxgen::StmtNode>())) {
			throw std::bad_alloc();
		}

		cxxgen::AstNodePtr<cxxgen::VoidTypeNameNode> voidType;

		if (!(voidType = astBuilder.buildVoidTypeName())) {
			throw std::bad_alloc();
		}

		cxxgen::AstNodePtr<cxxgen::NewExprNode> newExpr;

		cxxgen::AstNodePtr<cxxgen::ExprNode> args[] = {
			intExpr.castTo<cxxgen::ExprNode>(),
			binaryExpr.castTo<cxxgen::ExprNode>()
		};

		if (!(newExpr = astBuilder.buildNewExpr(voidType.castTo<cxxgen::TypeNameNode>(), std::size(args), args))) {
			throw std::bad_alloc();
		}

		if (!(exprStmt = astBuilder.buildExprStmt(newExpr.castTo<cxxgen::ExprNode>()))) {
			throw std::bad_alloc();
		}

		if (!blockStmt->body.pushBack(exprStmt.castTo<cxxgen::StmtNode>())) {
			throw std::bad_alloc();
		}

		cxxgen::AstNodePtr<cxxgen::FnNode> fn;

		if (!(fn = astBuilder.buildFn("test", voidType.castTo<cxxgen::TypeNameNode>()))) {
			throw std::bad_alloc();
		}

		fn->body = blockStmt;

		cxxgen::AstNodePtr<cxxgen::StructNode> s;

		if (!(s = astBuilder.buildStruct("Struct"))) {
			throw std::bad_alloc();
		}

		if (!s->body->pushBack(fn.castTo<cxxgen::AstNode>())) {
			throw std::bad_alloc();
		}

		cxxgen::InheritanceEntry e;

		e.access = cxxgen::InheritanceAccess::Public;
		e.baseType = voidType.castTo<cxxgen::TypeNameNode>();

		if (!s->baseTypes.pushBack(std::move(e))) {
			throw std::bad_alloc();
		}

		cxxgen::AstNodePtr<cxxgen::RootNode> r;

		if (!(r = astBuilder.buildRoot()))
			throw std::bad_alloc();

		if (!(r->body->pushBack(s.castTo<cxxgen::AstNode>())))
			throw std::bad_alloc();

		if (!(s = astBuilder.buildStruct("MyStruct")))
			throw std::bad_alloc();

		if (!(r->body->pushBack(s.castTo<cxxgen::AstNode>())))
			throw std::bad_alloc();

		ANSIDumpWriter writer;

		if (!cxxgen::dumpAstNode(peff::getDefaultAlloc(), &writer, r)) {
			throw std::bad_alloc();
		}
	}

	return 0;
}

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

		if (!(intExpr = astBuilder.buildIntLitrealExpr(123))) {
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

		ANSIDumpWriter writer;

		if (!cxxgen::dumpAstNode(peff::getDefaultAlloc(), &writer, ifStmt)) {
			throw std::bad_alloc();
		}
	}

	return 0;
}

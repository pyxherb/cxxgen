#include <cxxgen/builder.h>

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

			cxxgen::AstNodePtr<cxxgen::ExprNode> testQualifiedId;

			if (!(testQualifiedId = astBuilder.buildQualifiedId(testId, std::size(testId)))) {
				throw std::bad_alloc();
			}
		}
	}

	return 0;
}

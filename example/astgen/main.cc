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

		if (!(root = astBuilder.buildRoot())) {
			throw std::bad_alloc();
		}

		{
			cxxgen::AstNodePtr<cxxgen::ClassNode> testClass;

			if (!(testClass = astBuilder.buildClass())) {
				throw std::bad_alloc();
			}

			if (!(testClass->setName("Test")))
				throw std::bad_alloc();
		}
	}

	return 0;
}

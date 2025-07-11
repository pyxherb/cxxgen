#include <cxxgen/builder.h>

int main() {
	cxxgen::TranslationUnit tu;

	{
		cxxgen::AstBuilder astBuilder(peff::getDefaultAlloc(), &tu);
		cxxgen::AstNodePtr<cxxgen::RootNode> root;

		if (!(root = astBuilder.buildRoot())) {
			throw std::bad_alloc();
		}
	}

	return 0;
}

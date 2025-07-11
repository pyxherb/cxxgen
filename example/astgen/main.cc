#include <cxxgen/builder.h>

int main() {
	cxxgen::TranslationUnit tu;

	{
		cxxgen::AstNodePtr<cxxgen::RootNode> root;

		if (!(root = cxxgen::makeAstNode<cxxgen::RootNode>(peff::getDefaultAlloc(), peff::getDefaultAlloc(), &tu))) {
			throw std::bad_alloc();
		}
	}

	return 0;
}

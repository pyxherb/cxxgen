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
	};
}

#endif

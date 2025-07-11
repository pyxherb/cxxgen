#include "builder.h"

using namespace cxxgen;

CXXGEN_API AstBuilder::AstBuilder(peff::Alloc *allocator, TranslationUnit *translationUnit)
	: allocator(allocator), translationUnit(translationUnit) {
}

CXXGEN_API AstBuilder::~AstBuilder() {
}

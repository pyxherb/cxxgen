#ifndef _CXXGEN_AST_TYPENAME_H_
#define _CXXGEN_AST_TYPENAME_H_

#include "astnode.h"
#include <peff/containers/dynarray.h>
#include <cstdint>

namespace cxxgen {
	enum class TypeNameKind : uint8_t {
		Void = 0,
		Int,
		Bool,
		Char,
		Float,
		Double,
		Pointer,
		FnPointer,
		Array,
		Ref,
		Rvalue,
		Custom
	};

	class TypeNameNode : public AstNode {
	public:
		bool isConst = false;
		bool isVolatile = false;
		TypeNameKind typeNameKind;

		CXXGEN_API TypeNameNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit, TypeNameKind typeNameKind);
		CXXGEN_API virtual ~TypeNameNode();
	};

	class VoidTypeNameNode : public TypeNameNode {
	public:
		CXXGEN_API VoidTypeNameNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~VoidTypeNameNode();
	};

	enum class SignKind : uint8_t {
		Default = 0,
		Signed,
		Unsigned
	};

	enum class SizeModifierKind : uint8_t {
		Default = 0,
		Short,
		Long,
		LongLong,
	};

	class IntTypeNameNode : public TypeNameNode {
	public:
		SignKind signKind = SignKind::Default;
		SizeModifierKind sizeModifierKind = SizeModifierKind::Default;

		CXXGEN_API IntTypeNameNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~IntTypeNameNode();
	};

	class BoolTypeNameNode : public TypeNameNode {
	public:
		CXXGEN_API BoolTypeNameNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~BoolTypeNameNode();
	};

	class CharTypeNameNode : public TypeNameNode {
	public:
		SignKind signKind = SignKind::Default;

		CXXGEN_API CharTypeNameNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~CharTypeNameNode();
	};

	class FloatTypeNameNode : public TypeNameNode {
	public:
		SizeModifierKind sizeModifierKind = SizeModifierKind::Default;

		CXXGEN_API FloatTypeNameNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~FloatTypeNameNode();
	};

	class DoubleTypeNameNode : public TypeNameNode {
	public:
		SizeModifierKind sizeModifierKind = SizeModifierKind::Default;

		CXXGEN_API DoubleTypeNameNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~DoubleTypeNameNode();
	};

	class PointerTypeNameNode : public TypeNameNode {
	public:
		AstNodePtr<TypeNameNode> innerType;

		CXXGEN_API PointerTypeNameNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~PointerTypeNameNode();
	};

	struct ParamSlot {
		AstNodePtr<TypeNameNode> type;
		IdStorage name;
	};

	class FnPointerTypeNameNode : public TypeNameNode {
	public:
		AstNodePtr<TypeNameNode> returnType;
		peff::DynArray<ParamSlot> params;
		bool isNoexcept = false;

		CXXGEN_API FnPointerTypeNameNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~FnPointerTypeNameNode();
	};
}

#endif

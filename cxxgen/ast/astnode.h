#ifndef _CXXGEN_AST_ASTNODE_H_
#define _CXXGEN_AST_ASTNODE_H_

#include "../basedefs.h"
#include <peff/containers/string.h>
#include <peff/advutils/shared_ptr.h>
#include <variant>

namespace cxxgen {
	class AstNode;

	class TranslationUnit {
	private:
		CXXGEN_API void _doClearDeferredDestructibleAstNodes();

	public:
		AstNode *destructibleAstNodeList = nullptr;

		CXXGEN_FORCEINLINE void clearDeferredDestructibleAstNodes() {
			if (destructibleAstNodeList) {
				_doClearDeferredDestructibleAstNodes();
			}
		}
	};

	typedef void (*AstNodeDestructor)(AstNode *astNode);

	CXXGEN_API void addAstNodeToDestructibleList(AstNode *astNode, AstNodeDestructor destructor);

	template <typename T>
	struct AstNodeControlBlock : public peff::SharedPtr<T>::DefaultSharedPtrControlBlock {
		CXXGEN_FORCEINLINE AstNodeControlBlock(peff::Alloc *allocator, T *ptr) noexcept : peff::SharedPtr<T>::DefaultSharedPtrControlBlock(allocator, ptr) {}
		inline virtual ~AstNodeControlBlock() {}

		inline virtual void onStrongRefZero() noexcept override {
			addAstNodeToDestructibleList(this->ptr, [](AstNode *astNode) {
				peff::destroyAndRelease<T>(astNode->selfAllocator.get(), static_cast<T *>(astNode), alignof(T));
			});
		}

		inline virtual void onRefZero() noexcept override {
			peff::destroyAndRelease<AstNodeControlBlock<T>>(this->allocator.get(), this, alignof(AstNodeControlBlock<T>));
		}
	};

	enum class AstNodeType : uint8_t {
		Directive,
		IncludeDirective,
		IfDirective,
		IfdefDirective,
		IfndefDirective,
		Fn,
		Struct,
		Class,
		Root,
		Namespace,
		VarDef,
		TypeDef,
		TypeName,
		Stmt,
		Expr,
		AccessSpecifier,
		Declarator
	};

	class AstNode : public peff::SharedFromThis<AstNode> {
	private:
		AstNode *_destructibleAstNodeList = nullptr;
		AstNode *_nextDestructible = nullptr;
		AstNodeDestructor _destructor = nullptr;

		friend class TranslationUnit;
		friend void addAstNodeToDestructibleList(AstNode *astNode, AstNodeDestructor destructor);

	public:
		AstNodeType astNodeType;
		peff::RcObjectPtr<peff::Alloc> selfAllocator;
		TranslationUnit *translationUnit;

		CXXGEN_API AstNode(AstNodeType astNodeType, peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~AstNode();
	};

	template <typename T>
	using AstNodePtr = peff::SharedPtr<T>;

	template <typename T, typename... Args>
	PEFF_FORCEINLINE AstNodePtr<T> makeAstNode(peff::Alloc *allocator, Args &&...args) {
		return peff::makeSharedWithControlBlock<T, AstNodeControlBlock<T>>(allocator, std::forward<Args>(args)...);
	}
}

#endif

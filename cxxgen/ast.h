#ifndef _CXXGEN_AST_H_
#define _CXXGEN_AST_H_

#include "basedefs.h"
#include <peff/advutils/shared_ptr.h>
#include <peff/containers/dynarray.h>
#include <peff/containers/string.h>
#include <variant>
#include <optional>

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

	enum class AstNodeType {
		Directive,
		IncludeDirective,
		IfDirective,
		IfdefDirective,
		IfndefDirective,
		Fn,
		Struct,
		Class,
		Namespace,
		Var,
		TypeName,
		Stmt,
		Expr
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

	using DirectiveArgs =
		std::variant<
			std::monostate,
			peff::String,
			std::string_view,
			peff::DynArray<peff::String>,
			peff::DynArray<std::string_view>,
			peff::DynArray<std::variant<peff::String, std::string_view>>>;

	class DirectiveNode : public AstNode {
	public:
		DirectiveArgs args;

		CXXGEN_API DirectiveNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~DirectiveNode();
	};

	class IfDirectiveNode : public AstNode {
	public:
		DirectiveArgs args;
		peff::DynArray<AstNodePtr<AstNode>> body;
		std::optional<
			peff::DynArray<AstNodePtr<AstNode>>>
			elseBody;

		CXXGEN_API IfDirectiveNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~IfDirectiveNode();
	};

	class IfdefDirectiveNode : public AstNode {
	public:
		std::variant<std::monostate, peff::String, std::string_view> name;
		peff::DynArray<AstNodePtr<AstNode>> body;
		std::optional<
			peff::DynArray<AstNodePtr<AstNode>>>
			elseBody;

		CXXGEN_API IfdefDirectiveNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~IfdefDirectiveNode();
	};

	class IfndefDirectiveNode : public AstNode {
	public:
		std::variant<std::monostate, peff::String, std::string_view> name;
		peff::DynArray<AstNodePtr<AstNode>> body;
		std::optional<
			peff::DynArray<AstNodePtr<AstNode>>>
			elseBody;

		CXXGEN_API IfndefDirectiveNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit);
		CXXGEN_API virtual ~IfndefDirectiveNode();
	};

	class AbstractModuleNode : public AstNode {
	public:
		peff::String name;
		peff::DynArray<AstNodePtr<AstNode>> body;

		CXXGEN_API AbstractModuleNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit, AstNodeType astNodeType);
		CXXGEN_API virtual ~AbstractModuleNode();
	};

	enum class AccessModifier {
		Default = 0,
		Public,
		Private,
		Protected
	};

	struct InheritanceEntry {
		AccessModifier accessModifier;
	};

	class ClassNode : public AbstractModuleNode {
	public:
		CXXGEN_API ClassNode(peff::Alloc *selfAllocator, TranslationUnit *translationUnit, AstNodeType astNodeType);
		CXXGEN_API virtual ~ClassNode();
	};
}

#endif

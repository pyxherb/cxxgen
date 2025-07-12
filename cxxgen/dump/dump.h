#ifndef _CXXGEN_AST_DUMP_DUMP_H_
#define _CXXGEN_AST_DUMP_DUMP_H_

#include "base.h"
#include "../ast.h"

namespace cxxgen {
	enum class DumpFrameType {
		Initial = 0,

		IdTemplateArgs,

		InitializerListElement,

		UnaryOperand,

		BinaryLhs,
		BinaryRhs,

		ScopeResolveLhs,

		MemberAccessLhs,

		PtrMemberAccessLhs,

		CallTarget,
		CallArgs,

		CastTargetType,
		CastSource,

		NewTargetType,
		NewArgs,

		//PlacementNewLocation,
		//PlacementNewTargetType,
		//PlacementNewArgs,

		TernaryCondition,
		TernaryTrueBranch,
		TernaryFalseBranch,

		TypeSizeofOperand,
		ExprSizeofOperand,

		AlignofOperand,
	};

	struct IdTemplateArgsDumpFrameData {
		size_t index;
	};

	struct InitializerListElementDumpFrameData {
		size_t index;
	};

	struct CallArgsDumpFrameData {
		size_t index;
	};

	struct NewArgsDumpFrameData {
		size_t index;
	};

	struct PlacementNewArgsDumpFrameData {
		size_t index;
	};

	struct DumpFrame {
		std::variant<
			std::monostate,
			IdTemplateArgsDumpFrameData,
			InitializerListElementDumpFrameData,
			CallArgsDumpFrameData,
			NewArgsDumpFrameData,
			PlacementNewArgsDumpFrameData> data;
		AstNodePtr<AstNode> astNode;
		DumpFrameType frameType;
	};

	struct DumpContext {
		peff::List<DumpFrame> frames;
		size_t indentLevel = 0;
		DumpWriter *writer;

		CXXGEN_API DumpContext(peff::Alloc *allocator, DumpWriter *dumpWriter);
		CXXGEN_API ~DumpContext();
	};

	[[nodiscard]] CXXGEN_API bool _dumpAstNode(DumpContext *dumpContext);
	[[nodiscard]] CXXGEN_API bool dumpAstNode(peff::Alloc *allocator, DumpWriter *writer, AstNode *astNode);
}

#endif

#include "dump.h"

using namespace cxxgen;

#define CXXGEN_RETURN_IF_WRITE_FAILED(s) if (!(s)) return false

static bool _fillIndentation(DumpContext * dumpContext, size_t level) {
	for (size_t i = 0; i < level; ++i)
		CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("\t"));
	return true;
}

static bool _dumpDirectiveArgs(DumpContext* dumpContext, DirectiveArgs& args) {
	switch (args.index()) {
		case 0:
			// monostate
			break;
		case 1:
			// string
			CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(std::get<peff::String>(args)));
			break;
		case 2: {
			peff::DynArray<peff::String> &a = std::get<peff::DynArray<peff::String>>(args);
			// multiple tokens
			for (auto &i : a) {
				CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(i));
				CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" "));
			}
			break;
		}
	}
}

CXXGEN_API bool cxxgen::dumpAstNode(DumpContext* dumpContext, AstNode* astNode) {
	switch (astNode->astNodeType) {
		case AstNodeType::Directive: {
			DirectiveNode *an = (DirectiveNode *)astNode;

			CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("#"));
			CXXGEN_RETURN_IF_WRITE_FAILED(_fillIndentation(dumpContext, dumpContext->indentLevel));
			CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(an->name));

			CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" "));

			CXXGEN_RETURN_IF_WRITE_FAILED(_dumpDirectiveArgs(dumpContext, an->args));

			CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("\n"));

			break;
		}
		case AstNodeType::IncludeDirective: {
			IncludeDirectiveNode *an = (IncludeDirectiveNode *)astNode;

			CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("#"));
			CXXGEN_RETURN_IF_WRITE_FAILED(_fillIndentation(dumpContext, dumpContext->indentLevel));
			CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("include"));

			CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" "));

			if (an->isSystem) {
				CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("<"));
			} else {
				CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("\""));
			}

			// TODO: Quote it.
			CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(an->path));

			if (an->isSystem) {
				CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(">"));
			} else {
				CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("\""));
			}

			CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("\n"));

			break;
		}
		case AstNodeType::IfDirective:
			break;
		case AstNodeType::IfdefDirective:
			break;
		case AstNodeType::IfndefDirective:
			break;
		case AstNodeType::Fn:
			break;
		case AstNodeType::Struct:
			break;
		case AstNodeType::Class:
			break;
		case AstNodeType::Root:
			break;
		case AstNodeType::Namespace:
			break;
		case AstNodeType::VarDef:
			break;
		case AstNodeType::TypeDef:
			break;
		case AstNodeType::TypeName:
			break;
		case AstNodeType::Stmt:
			break;
		case AstNodeType::Expr: {
			ExprNode *an = (ExprNode *)astNode;

			switch (an->exprKind) {
				case ExprKind::IntLiteral:
					break;
				case ExprKind::LongLiteral:
					break;
				case ExprKind::UIntLiteral:
					break;
				case ExprKind::ULongLiteral:
					break;
				case ExprKind::CharLiteral:
					break;
				case ExprKind::StringLiteral:
					break;
				case ExprKind::FloatLiteral:
					break;
				case ExprKind::DoubleLiteral:
					break;
				case ExprKind::BoolLiteral:
					break;
				case ExprKind::NullptrLiteral:
					break;
				case ExprKind::Id:
					break;
				case ExprKind::InitializerList:
					break;

				case ExprKind::Unary:
					break;
				case ExprKind::Binary:
					break;
				case ExprKind::ScopeResolve:
					break;
				case ExprKind::MemberAccess:
					break;
				case ExprKind::PtrMemberAccess:
					break;
				case ExprKind::Call:
					break;
				case ExprKind::Cast:
					break;
				case ExprKind::New:
					break;
				case ExprKind::PlacementNew:
					break;
				case ExprKind::Ternary:
					break;
				case ExprKind::TypeSizeof:
					break;
				case ExprKind::ExprSizeof:
					break;
				case ExprKind::Alignof:
					break;
				case ExprKind::This:
					break;
			}
			break;
		}
		case AstNodeType::AccessSpecifier:
			break;
		case AstNodeType::Declarator:
			break;
	}
}

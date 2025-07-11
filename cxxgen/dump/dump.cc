#include "dump.h"

using namespace cxxgen;

#define CXXGEN_RETURN_IF_WRITE_FAILED(s) \
	if (!(s)) return false

static bool _fillIndentation(DumpContext *dumpContext, size_t level) {
	for (size_t i = 0; i < level; ++i)
		CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("\t"));
	return true;
}

static bool _dumpDirectiveArgs(DumpContext *dumpContext, DirectiveArgs &args) {
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

CXXGEN_API bool cxxgen::_dumpAstNode(DumpContext *dumpContext) {
loop:
	if (!dumpContext->frames.size())
		return true;

	DumpFrame &curFrame = dumpContext->frames.back();
	AstNode *astNode = curFrame.astNode.get();

	switch (curFrame.frameType) {
		case DumpFrameType::Initial: {
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
					ExprNode *expr = (ExprNode *)astNode;

					switch (expr->exprKind) {
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

						case ExprKind::Unary: {
							UnaryExprNode *unaryExpr = (UnaryExprNode *)expr;

							switch (unaryExpr->unaryOp) {
								case UnaryOp::IncForward:
									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("++"));

									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

									curFrame.frameType = DumpFrameType::UnaryOperand;

									goto loop;
								case UnaryOp::IncBackward:
									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

									curFrame.frameType = DumpFrameType::UnaryOperand;

									goto loop;
								case UnaryOp::DecForward:
									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("--"));

									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

									curFrame.frameType = DumpFrameType::UnaryOperand;

									goto loop;
								case UnaryOp::DecBackward:
									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

									curFrame.frameType = DumpFrameType::UnaryOperand;

									goto loop;
								case UnaryOp::Plus:
									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("+"));

									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

									curFrame.frameType = DumpFrameType::UnaryOperand;

									goto loop;
								case UnaryOp::Negate:
									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("-"));

									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

									curFrame.frameType = DumpFrameType::UnaryOperand;

									goto loop;
								case UnaryOp::Not:
									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("~"));

									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

									curFrame.frameType = DumpFrameType::UnaryOperand;

									goto loop;
								case UnaryOp::LNot:
									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("!"));

									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

									curFrame.frameType = DumpFrameType::UnaryOperand;

									goto loop;
								case UnaryOp::Dereference:
									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("*"));

									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

									curFrame.frameType = DumpFrameType::UnaryOperand;

									goto loop;
								case UnaryOp::AddressOf:
									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("&"));

									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

									curFrame.frameType = DumpFrameType::UnaryOperand;

									goto loop;
							}
							break;
						}
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
							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("this"));
							break;
					}
					break;
				}
				case AstNodeType::AccessSpecifier:
					break;
				case AstNodeType::Declarator:
					break;
			}
			break;
		}
		case DumpFrameType::UnaryOperand: {
			assert(astNode->astNodeType == AstNodeType::Expr);

			UnaryExprNode *unaryExpr = (UnaryExprNode *)astNode;

			switch (unaryExpr->unaryOp) {
				case UnaryOp::IncForward:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					dumpContext->frames.popBack();

					goto loop;
				case UnaryOp::IncBackward:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("++"));

					dumpContext->frames.popBack();

					goto loop;
				case UnaryOp::DecForward:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					dumpContext->frames.popBack();

					goto loop;
				case UnaryOp::DecBackward:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("--"));

					dumpContext->frames.popBack();

					goto loop;
				case UnaryOp::Plus:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					dumpContext->frames.popBack();

					goto loop;
				case UnaryOp::Negate:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					dumpContext->frames.popBack();

					goto loop;
				case UnaryOp::Not:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					dumpContext->frames.popBack();

					goto loop;
				case UnaryOp::LNot:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					dumpContext->frames.popBack();

					goto loop;
				case UnaryOp::Dereference:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					dumpContext->frames.popBack();

					goto loop;
				case UnaryOp::AddressOf:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					dumpContext->frames.popBack();

					goto loop;
			}
		}
	}
}

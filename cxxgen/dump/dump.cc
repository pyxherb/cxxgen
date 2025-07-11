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
				case AstNodeType::Fn: {
					FnNode *f = (FnNode *)astNode;

					if (f->isVirtual)
						CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("virtual "));

					if (f->isInline)
						CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("inline "));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpAstNode(dumpContext->frames.allocator(), dumpContext->writer, f->returnType.castTo<AstNode>()));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" "));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(f->name));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

					for (size_t i = 0; i < f->params.size(); ++i) {
						if (i) {
							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(", "));
						}

						CXXGEN_RETURN_IF_WRITE_FAILED(dumpAstNode(dumpContext->frames.allocator(), dumpContext->writer, f->params.at(i).type));

						CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" "));

						CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(f->params.at(i).name));
					}

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					if (f->isConst)
						CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" const"));

					if (f->isNoexcept)
						CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" noexcept"));
					break;
				}
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
						case ExprKind::IntLiteral: {
							char s[12];

							int len = sprintf(s, "%d", ((IntLiteralExprNode *)expr)->data);

							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(s, len));
							break;
						}
						case ExprKind::LongLiteral: {
							char s[22];

							int len = sprintf(s, "%ldL", ((LongLiteralExprNode *)expr)->data);

							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(s, len));
							break;
						}
						case ExprKind::UIntLiteral: {
							char s[13];

							int len = sprintf(s, "%uU", ((IntLiteralExprNode *)expr)->data);

							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(s, len));
							break;
						}
						case ExprKind::ULongLiteral: {
							char s[23];

							int len = sprintf(s, "%luLU", ((LongLiteralExprNode *)expr)->data);

							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(s, len));
							break;
						}
						case ExprKind::CharLiteral:
							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(&(((CharLiteralExprNode *)expr)->data), 1));

							break;
						case ExprKind::StringLiteral:
							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(((StringLiteralExprNode *)expr)->data));
							break;
						case ExprKind::FloatLiteral: {
							char s[32];

							int len = snprintf(s, sizeof(s), "%.8g", ((FloatLiteralExprNode *)expr)->data);

							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(s, len));
							break;
						}
						case ExprKind::DoubleLiteral: {
							char s[64];

							int len = snprintf(s, sizeof(s), "%.17g", ((FloatLiteralExprNode *)expr)->data);

							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(s, len));
							break;
						}
						case ExprKind::BoolLiteral:
							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(((BoolLiteralExprNode *)expr)->data ? "true" : "false"));
							break;
						case ExprKind::NullptrLiteral:
							break;
						case ExprKind::Id: {
							IdExprNode *idExpr = (IdExprNode *)expr;

							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(idExpr->name));

							if (idExpr->templateArgs) {
								auto &templateArgs = *idExpr->templateArgs;

								CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("<"));

								curFrame.data = IdTemplateArgsDumpFrameData{ 0 };

								curFrame.frameType = DumpFrameType::IdTemplateArgs;
							}
							break;
						}
						case ExprKind::InitializerList: {
							InitializerListExprNode *initializerListExpr = (InitializerListExprNode *)expr;

							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("{ "));

							curFrame.data = InitializerListElementDumpFrameData{ 0 };

							curFrame.frameType = DumpFrameType::InitializerListElement;
							break;
						}

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
		case DumpFrameType::IdTemplateArgs: {
			assert(astNode->astNodeType == AstNodeType::Expr);

			IdExprNode *idExpr = (IdExprNode *)astNode;

			IdTemplateArgsDumpFrameData &data = std::get<IdTemplateArgsDumpFrameData>(curFrame.data);

			if (data.index >= idExpr->templateArgs->size()) {
				CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(">"));
				dumpContext->frames.popBack();

				goto loop;
			}

			if (data.index) {
				CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(", "));
			}

			{
				DumpFrame dumpFrame;

				dumpFrame.astNode = idExpr->templateArgs->at(data.index);

				dumpFrame.frameType = DumpFrameType::Initial;

				if (!dumpContext->frames.pushBack(std::move(dumpFrame)))
					return false;
			}

			++data.index;

			goto loop;
		}
		case DumpFrameType::InitializerListElement: {
			assert(astNode->astNodeType == AstNodeType::Expr);

			InitializerListExprNode *initializerListExpr = (InitializerListExprNode *)astNode;

			InitializerListElementDumpFrameData &data = std::get<InitializerListElementDumpFrameData>(curFrame.data);

			if (data.index >= initializerListExpr->elements.size()) {
				CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" }"));
				dumpContext->frames.popBack();

				goto loop;
			}

			if (data.index) {
				CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(", "));
			}

			{
				DumpFrame dumpFrame;

				dumpFrame.astNode = initializerListExpr->elements.at(data.index).castTo<AstNode>();

				dumpFrame.frameType = DumpFrameType::Initial;

				if (!dumpContext->frames.pushBack(std::move(dumpFrame)))
					return false;
			}

			++data.index;

			goto loop;
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

CXXGEN_API bool cxxgen::dumpAstNode(peff::Alloc *allocator, DumpWriter *writer, AstNode *astNode) {
	DumpContext dumpContext(allocator, writer);

	{
		DumpFrame dumpFrame;

		dumpFrame.astNode = astNode->sharedFromThis();

		dumpFrame.frameType = DumpFrameType::Initial;

		if (!dumpContext.frames.pushBack(std::move(dumpFrame)))
			return false;
	}

	return _dumpAstNode(&dumpContext);
}

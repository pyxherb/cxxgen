#include "dump.h"

using namespace cxxgen;

#define CXXGEN_RETURN_IF_WRITE_FAILED(s) \
	if (!(s)) return false

struct cxxgen::DumpContext final {
	peff::RcObjectPtr<peff::Alloc> allocator;
	peff::List<DumpFrame> frames;
	size_t indentLevel = 0;
	DumpWriter *writer;

	CXXGEN_FORCEINLINE DumpContext(peff::Alloc *allocator, DumpWriter *dumpWriter) : allocator(allocator), writer(dumpWriter), frames(allocator) {
	}
	CXXGEN_FORCEINLINE ~DumpContext() {
	}
};

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

	auto pushInitialDumpFrame = [dumpContext](const AstNodePtr<AstNode> &astNode) -> bool {
		{
			DumpFrame dumpFrame;

			dumpFrame.astNode = astNode;

			dumpFrame.frameType = DumpFrameType::Initial;

			if (!dumpContext->frames.pushBack(std::move(dumpFrame)))
				return false;
		}
	};

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

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpAstNode(dumpContext->allocator.get(), dumpContext->writer, f->returnType.castTo<AstNode>()));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" "));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(f->name));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

					for (size_t i = 0; i < f->params.size(); ++i) {
						if (i) {
							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(", "));
						}

						CXXGEN_RETURN_IF_WRITE_FAILED(dumpAstNode(dumpContext->allocator.get(), dumpContext->writer, f->params.at(i).type));

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
				case AstNodeType::Stmt: {
					StmtNode *stmt = (StmtNode *)astNode;

					switch (stmt->stmtKind) {
						case StmtKind::Expr: {
							ExprStmtNode *s = (ExprStmtNode *)stmt;

							CXXGEN_RETURN_IF_WRITE_FAILED(dumpAstNode(dumpContext->allocator.get(), dumpContext->writer, s->expr));

							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(";"));

							goto loop;
						}
						case StmtKind::LocalVarDef: {
							LocalVarDefStmtNode *s = (LocalVarDefStmtNode *)stmt;

							CXXGEN_RETURN_IF_WRITE_FAILED(dumpAstNode(dumpContext->allocator.get(), dumpContext->writer, s->varDef));

							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(";"));

							goto loop;
						}
						case StmtKind::If: {
							IfStmtNode *s = (IfStmtNode *)stmt;

							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("if "));

							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

							CXXGEN_RETURN_IF_WRITE_FAILED(dumpAstNode(dumpContext->allocator.get(), dumpContext->writer, s->condition));

							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

							curFrame.frameType = DumpFrameType::IfTrueBranch;

							switch (s->trueBranch->stmtKind) {
								case StmtKind::Block:
								case StmtKind::If:
								case StmtKind::IfConstexpr:
									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" "));

									CXXGEN_RETURN_IF_WRITE_FAILED(pushInitialDumpFrame(s->trueBranch.castTo<AstNode>()));

									break;
								default:
									++dumpContext->indentLevel;

									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("\n"));

									CXXGEN_RETURN_IF_WRITE_FAILED(_fillIndentation(dumpContext, dumpContext->indentLevel));

									CXXGEN_RETURN_IF_WRITE_FAILED(pushInitialDumpFrame(s->trueBranch.castTo<AstNode>()));
							}

							goto loop;
						}
						case StmtKind::Block: {
							BlockStmtNode *s = (BlockStmtNode *)stmt;

							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("{\n"));

							++dumpContext->indentLevel;

							curFrame.frameType = DumpFrameType::BlockBody;

							curFrame.data = BlockBodyDumpFrameData{ 0 };

							goto loop;
						}
					}

					break;
				}
				case AstNodeType::Expr: {
					ExprNode *expr = (ExprNode *)astNode;

					switch (expr->exprKind) {
						case ExprKind::IntLiteral: {
							char s[12];

							int len = sprintf(s, "%d", ((IntLiteralExprNode *)expr)->data);

							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(s, len));

							dumpContext->frames.popBack();

							goto loop;
						}
						case ExprKind::LongLiteral: {
							char s[22];

							int len = sprintf(s, "%ldL", ((LongLiteralExprNode *)expr)->data);

							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(s, len));

							dumpContext->frames.popBack();

							goto loop;
						}
						case ExprKind::LongLongLiteral: {
							char s[23];

							int len = sprintf(s, "%ldLL", ((LongLiteralExprNode *)expr)->data);

							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(s, len));

							dumpContext->frames.popBack();

							goto loop;
						}
						case ExprKind::UIntLiteral: {
							char s[13];

							int len = sprintf(s, "%uU", ((IntLiteralExprNode *)expr)->data);

							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(s, len));

							dumpContext->frames.popBack();

							goto loop;
						}
						case ExprKind::ULongLiteral: {
							char s[23];

							int len = sprintf(s, "%luUL", ((LongLiteralExprNode *)expr)->data);

							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(s, len));

							dumpContext->frames.popBack();

							goto loop;
						}
						case ExprKind::ULongLongLiteral: {
							char s[24];

							int len = sprintf(s, "%luULL", ((LongLiteralExprNode *)expr)->data);

							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(s, len));

							dumpContext->frames.popBack();

							goto loop;
						}
						case ExprKind::CharLiteral:
							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(&(((CharLiteralExprNode *)expr)->data), 1));

							dumpContext->frames.popBack();

							goto loop;
						case ExprKind::StringLiteral:
							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(((StringLiteralExprNode *)expr)->data));

							dumpContext->frames.popBack();

							goto loop;
						case ExprKind::FloatLiteral: {
							char s[32];

							int len = snprintf(s, sizeof(s), "%.8g", ((FloatLiteralExprNode *)expr)->data);

							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(s, len));

							dumpContext->frames.popBack();

							goto loop;
						}
						case ExprKind::DoubleLiteral: {
							char s[64];

							int len = snprintf(s, sizeof(s), "%.17g", ((FloatLiteralExprNode *)expr)->data);

							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(s, len));

							dumpContext->frames.popBack();

							goto loop;
						}
						case ExprKind::BoolLiteral:
							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(((BoolLiteralExprNode *)expr)->data ? "true" : "false"));

							dumpContext->frames.popBack();

							goto loop;
						case ExprKind::NullptrLiteral:

							dumpContext->frames.popBack();

							goto loop;
						case ExprKind::Id: {
							IdExprNode *idExpr = (IdExprNode *)expr;

							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(idExpr->name));

							if (idExpr->templateArgs) {
								auto &templateArgs = *idExpr->templateArgs;

								CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("<"));

								curFrame.data = IdTemplateArgsDumpFrameData{ 0 };

								curFrame.frameType = DumpFrameType::IdTemplateArgs;
							} else {
								dumpContext->frames.popBack();
							}

							goto loop;
						}
						case ExprKind::InitializerList: {
							InitializerListExprNode *initializerListExpr = (InitializerListExprNode *)expr;

							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("{ "));

							curFrame.data = InitializerListElementDumpFrameData{ 0 };

							curFrame.frameType = DumpFrameType::InitializerListElement;

							goto loop;
						}

						case ExprKind::Unary: {
							UnaryExprNode *unaryExpr = (UnaryExprNode *)expr;

							switch (unaryExpr->unaryOp) {
								case UnaryOp::IncForward:
									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("++"));

									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

									curFrame.frameType = DumpFrameType::UnaryOperand;

									CXXGEN_RETURN_IF_WRITE_FAILED(pushInitialDumpFrame(unaryExpr->operand.castTo<AstNode>()));

									goto loop;
								case UnaryOp::IncBackward:
									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

									curFrame.frameType = DumpFrameType::UnaryOperand;

									CXXGEN_RETURN_IF_WRITE_FAILED(pushInitialDumpFrame(unaryExpr->operand.castTo<AstNode>()));

									goto loop;
								case UnaryOp::DecForward:
									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("--"));

									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

									curFrame.frameType = DumpFrameType::UnaryOperand;

									CXXGEN_RETURN_IF_WRITE_FAILED(pushInitialDumpFrame(unaryExpr->operand.castTo<AstNode>()));

									goto loop;
								case UnaryOp::DecBackward:
									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

									curFrame.frameType = DumpFrameType::UnaryOperand;

									CXXGEN_RETURN_IF_WRITE_FAILED(pushInitialDumpFrame(unaryExpr->operand.castTo<AstNode>()));

									goto loop;
								case UnaryOp::Plus:
									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("+"));

									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

									curFrame.frameType = DumpFrameType::UnaryOperand;

									CXXGEN_RETURN_IF_WRITE_FAILED(pushInitialDumpFrame(unaryExpr->operand.castTo<AstNode>()));

									goto loop;
								case UnaryOp::Negate:
									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("-"));

									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

									curFrame.frameType = DumpFrameType::UnaryOperand;

									CXXGEN_RETURN_IF_WRITE_FAILED(pushInitialDumpFrame(unaryExpr->operand.castTo<AstNode>()));

									goto loop;
								case UnaryOp::Not:
									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("~"));

									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

									curFrame.frameType = DumpFrameType::UnaryOperand;

									CXXGEN_RETURN_IF_WRITE_FAILED(pushInitialDumpFrame(unaryExpr->operand.castTo<AstNode>()));

									goto loop;
								case UnaryOp::LNot:
									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("!"));

									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

									curFrame.frameType = DumpFrameType::UnaryOperand;

									CXXGEN_RETURN_IF_WRITE_FAILED(pushInitialDumpFrame(unaryExpr->operand.castTo<AstNode>()));

									goto loop;
								case UnaryOp::Dereference:
									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("*"));

									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

									curFrame.frameType = DumpFrameType::UnaryOperand;

									CXXGEN_RETURN_IF_WRITE_FAILED(pushInitialDumpFrame(unaryExpr->operand.castTo<AstNode>()));

									goto loop;
								case UnaryOp::AddressOf:
									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("&"));

									CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

									curFrame.frameType = DumpFrameType::UnaryOperand;

									CXXGEN_RETURN_IF_WRITE_FAILED(pushInitialDumpFrame(unaryExpr->operand.castTo<AstNode>()));

									goto loop;
								default:
									std::terminate();
							}

							break;
						}
						case ExprKind::Binary: {
							BinaryExprNode *binaryExpr = (BinaryExprNode *)expr;

							curFrame.frameType = DumpFrameType::BinaryLhs;

							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

							CXXGEN_RETURN_IF_WRITE_FAILED(pushInitialDumpFrame(binaryExpr->lhs.castTo<AstNode>()));

							goto loop;
						}
						case ExprKind::ScopeResolve: {
							ScopeResolveExprNode *scopeResolveExpr = (ScopeResolveExprNode *)expr;

							curFrame.frameType = DumpFrameType::ScopeResolveLhs;

							CXXGEN_RETURN_IF_WRITE_FAILED(pushInitialDumpFrame(scopeResolveExpr->lhs.castTo<AstNode>()));

							goto loop;
						}
						case ExprKind::MemberAccess: {
							MemberAccessExprNode *memberAccessExpr = (MemberAccessExprNode *)expr;

							curFrame.frameType = DumpFrameType::MemberAccessLhs;

							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

							CXXGEN_RETURN_IF_WRITE_FAILED(pushInitialDumpFrame(memberAccessExpr->lhs.castTo<AstNode>()));

							goto loop;
						}
						case ExprKind::PtrMemberAccess: {
							MemberAccessExprNode *ptrMemberAccessExpr = (MemberAccessExprNode *)expr;

							curFrame.frameType = DumpFrameType::PtrMemberAccessLhs;

							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

							CXXGEN_RETURN_IF_WRITE_FAILED(pushInitialDumpFrame(ptrMemberAccessExpr->lhs.castTo<AstNode>()));

							goto loop;
						}
						case ExprKind::Call: {
							CallExprNode *e = (CallExprNode *)expr;

							curFrame.frameType = DumpFrameType::CallTarget;

							CXXGEN_RETURN_IF_WRITE_FAILED(pushInitialDumpFrame(e->target.castTo<AstNode>()));

							goto loop;
						}
						case ExprKind::Cast: {
							CastExprNode *e = (CastExprNode *)expr;

							curFrame.frameType = DumpFrameType::CastTargetType;

							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

							CXXGEN_RETURN_IF_WRITE_FAILED(pushInitialDumpFrame(e->destType.castTo<AstNode>()));

							goto loop;
						}
						case ExprKind::New: {
							NewExprNode *e = (NewExprNode *)expr;

							curFrame.frameType = DumpFrameType::NewTargetType;

							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("new "));

							CXXGEN_RETURN_IF_WRITE_FAILED(pushInitialDumpFrame(e->type.castTo<AstNode>()));

							goto loop;
						}
						case ExprKind::PlacementNew:
							break;
						case ExprKind::Ternary: {
							TernaryExprNode *e = (TernaryExprNode *)expr;

							curFrame.frameType = DumpFrameType::TernaryCondition;

							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

							CXXGEN_RETURN_IF_WRITE_FAILED(pushInitialDumpFrame(e->condition.castTo<AstNode>()));

							goto loop;
						}
						case ExprKind::TypeSizeof:
							break;
						case ExprKind::ExprSizeof:
							break;
						case ExprKind::Alignof:
							break;
						case ExprKind::This:
							CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("this"));

							dumpContext->frames.popBack();

							goto loop;
						default:
							std::terminate();
					}
					break;
				}
				case AstNodeType::AccessSpecifier:
					break;
				case AstNodeType::Declarator:
					break;
				default:
					std::terminate();
			}

			break;
		}
		case DumpFrameType::IfTrueBranch: {
			assert(astNode->astNodeType == AstNodeType::Stmt);

			IfStmtNode *s = (IfStmtNode *)astNode;

			switch (s->trueBranch->stmtKind) {
				case StmtKind::Block:
				case StmtKind::If:
				case StmtKind::IfConstexpr:
					break;
				default:
					--dumpContext->indentLevel;
			}

			if (s->elseBranch) {
				curFrame.frameType = DumpFrameType::IfFalseBranch;

				switch (s->elseBranch->stmtKind) {
					case StmtKind::Block:
					case StmtKind::If:
					case StmtKind::IfConstexpr:
						CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" else "));

						CXXGEN_RETURN_IF_WRITE_FAILED(pushInitialDumpFrame(s->elseBranch.castTo<AstNode>()));

						break;
					default:
						CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("\n"));

						CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("else"));

						CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("\n"));

						++dumpContext->indentLevel;

						CXXGEN_RETURN_IF_WRITE_FAILED(_fillIndentation(dumpContext, dumpContext->indentLevel));

						CXXGEN_RETURN_IF_WRITE_FAILED(pushInitialDumpFrame(s->elseBranch.castTo<AstNode>()));
				}

				goto loop;
			} else {
				dumpContext->frames.popBack();

				goto loop;
			}

			goto loop;
		}
		case DumpFrameType::IfFalseBranch: {
			assert(astNode->astNodeType == AstNodeType::Stmt);

			IfStmtNode *s = (IfStmtNode *)astNode;

			switch (s->elseBranch->stmtKind) {
				case StmtKind::Block:
				case StmtKind::If:
				case StmtKind::IfConstexpr:
					break;
				default:
					--dumpContext->indentLevel;
			}

			dumpContext->frames.popBack();

			goto loop;
		}
		case DumpFrameType::BlockBody: {
			assert(astNode->astNodeType == AstNodeType::Stmt);

			BlockStmtNode *s = (BlockStmtNode *)astNode;

			BlockBodyDumpFrameData &data = std::get<BlockBodyDumpFrameData>(curFrame.data);

			if (data.index >= s->body.size()) {
				--dumpContext->indentLevel;

				CXXGEN_RETURN_IF_WRITE_FAILED(_fillIndentation(dumpContext, dumpContext->indentLevel));

				CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("}"));
				dumpContext->frames.popBack();

				goto loop;
			}

			CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("\n"));

			CXXGEN_RETURN_IF_WRITE_FAILED(_fillIndentation(dumpContext, dumpContext->indentLevel));

			CXXGEN_RETURN_IF_WRITE_FAILED(pushInitialDumpFrame(s->body.at(data.index).castTo<AstNode>()));

			++data.index;

			goto loop;
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

			CXXGEN_RETURN_IF_WRITE_FAILED(pushInitialDumpFrame(idExpr->templateArgs->at(data.index)));

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

			CXXGEN_RETURN_IF_WRITE_FAILED(pushInitialDumpFrame(initializerListExpr->elements.at(data.index).castTo<AstNode>()));

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
				default:
					std::terminate();
			}

			break;
		}
		case DumpFrameType::BinaryLhs: {
			assert(astNode->astNodeType == AstNodeType::Expr);

			BinaryExprNode *binaryExpr = (BinaryExprNode *)astNode;

			CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

			switch (binaryExpr->binaryOp) {
				case BinaryOp::Add:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" + "));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

					break;
				case BinaryOp::Sub:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" - "));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

					break;
				case BinaryOp::Mul:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" * "));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

					break;
				case BinaryOp::Div:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" / "));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

					break;
				case BinaryOp::Mod:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" % "));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

					break;
				case BinaryOp::And:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" & "));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

					break;
				case BinaryOp::Or:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" | "));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

					break;
				case BinaryOp::Xor:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" ^ "));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

					break;
				case BinaryOp::LAnd:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" && "));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

					break;
				case BinaryOp::LOr:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" || "));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

					break;
				case BinaryOp::Shl:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" << "));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

					break;
				case BinaryOp::Shr:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" >> "));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

					break;
				case BinaryOp::Eq:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" == "));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

					break;
				case BinaryOp::Neq:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" != "));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

					break;
				case BinaryOp::Lt:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" < "));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

					break;
				case BinaryOp::Gt:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" > "));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

					break;
				case BinaryOp::LtEq:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" <= "));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

					break;
				case BinaryOp::GtEq:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" >= "));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

					break;
				case BinaryOp::Cmp:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" <=> "));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

					break;
				case BinaryOp::Subscript:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("["));

					break;
				case BinaryOp::Assign:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" = "));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

					break;
				case BinaryOp::AddAssign:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" += "));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

					break;
				case BinaryOp::SubAssign:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" -= "));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

					break;
				case BinaryOp::MulAssign:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" *= "));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

					break;
				case BinaryOp::DivAssign:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" /= "));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

					break;
				case BinaryOp::ModAssign:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" %= "));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

					break;
				case BinaryOp::AndAssign:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" &= "));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

					break;
				case BinaryOp::OrAssign:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" |= "));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

					break;
				case BinaryOp::XorAssign:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" ^= "));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

					break;
				case BinaryOp::ShlAssign:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" <<= "));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

					break;
				case BinaryOp::ShrAssign:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" >>= "));

					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

					break;
				default:
					std::terminate();
			}

			curFrame.frameType = DumpFrameType::BinaryRhs;

			CXXGEN_RETURN_IF_WRITE_FAILED(pushInitialDumpFrame(binaryExpr->rhs.castTo<AstNode>()));

			goto loop;
		}
		case DumpFrameType::BinaryRhs: {
			assert(astNode->astNodeType == AstNodeType::Expr);

			BinaryExprNode *binaryExpr = (BinaryExprNode *)astNode;

			switch (binaryExpr->binaryOp) {
				case BinaryOp::Add:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					break;
				case BinaryOp::Sub:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					break;
				case BinaryOp::Mul:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					break;
				case BinaryOp::Div:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					break;
				case BinaryOp::Mod:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					break;
				case BinaryOp::And:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					break;
				case BinaryOp::Or:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					break;
				case BinaryOp::Xor:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					break;
				case BinaryOp::LAnd:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					break;
				case BinaryOp::LOr:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					break;
				case BinaryOp::Shl:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					break;
				case BinaryOp::Shr:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					break;
				case BinaryOp::Eq:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					break;
				case BinaryOp::Neq:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					break;
				case BinaryOp::Lt:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					break;
				case BinaryOp::Gt:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					break;
				case BinaryOp::LtEq:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					break;
				case BinaryOp::GtEq:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					break;
				case BinaryOp::Cmp:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					break;
				case BinaryOp::Subscript:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("]"));

					break;
				case BinaryOp::Assign:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					break;
				case BinaryOp::AddAssign:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					break;
				case BinaryOp::SubAssign:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					break;
				case BinaryOp::MulAssign:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					break;
				case BinaryOp::DivAssign:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					break;
				case BinaryOp::ModAssign:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					break;
				case BinaryOp::AndAssign:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					break;
				case BinaryOp::OrAssign:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					break;
				case BinaryOp::XorAssign:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					break;
				case BinaryOp::ShlAssign:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					break;
				case BinaryOp::ShrAssign:
					CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

					break;
				default:
					std::terminate();
			}

			curFrame.frameType = DumpFrameType::BinaryRhs;

			dumpContext->frames.popBack();

			goto loop;
		}
		case DumpFrameType::ScopeResolveLhs: {
			assert(astNode->astNodeType == AstNodeType::Expr);

			ScopeResolveExprNode *scopeResolveExpr = (ScopeResolveExprNode *)astNode;

			CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("::"));

			dumpContext->frames.popBack();

			CXXGEN_RETURN_IF_WRITE_FAILED(pushInitialDumpFrame(scopeResolveExpr->rhs.castTo<AstNode>()));

			goto loop;
		}
		case DumpFrameType::MemberAccessLhs: {
			assert(astNode->astNodeType == AstNodeType::Expr);

			MemberAccessExprNode *memberAccessExpr = (MemberAccessExprNode *)astNode;

			CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

			CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("."));

			dumpContext->frames.popBack();

			CXXGEN_RETURN_IF_WRITE_FAILED(pushInitialDumpFrame(memberAccessExpr->rhs.castTo<AstNode>()));

			goto loop;
		}
		case DumpFrameType::PtrMemberAccessLhs: {
			assert(astNode->astNodeType == AstNodeType::Expr);

			PtrMemberAccessExprNode *ptrMemberAccessExpr = (PtrMemberAccessExprNode *)astNode;

			CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

			CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("->"));

			dumpContext->frames.popBack();

			CXXGEN_RETURN_IF_WRITE_FAILED(pushInitialDumpFrame(ptrMemberAccessExpr->rhs.castTo<AstNode>()));

			goto loop;
		}
		case DumpFrameType::CallTarget: {
			assert(astNode->astNodeType == AstNodeType::Expr);

			CallExprNode *e = (CallExprNode *)astNode;

			CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

			dumpContext->frames.popBack();

			{
				DumpFrame dumpFrame;

				dumpFrame.astNode = astNode->sharedFromThis();

				dumpFrame.frameType = DumpFrameType::CallArgs;

				dumpFrame.data = CallArgsDumpFrameData{ 0 };

				if (!dumpContext->frames.pushBack(std::move(dumpFrame)))
					return false;
			}

			goto loop;
		}
		case DumpFrameType::CallArgs: {
			assert(astNode->astNodeType == AstNodeType::Expr);

			CallExprNode *e = (CallExprNode *)astNode;

			CallArgsDumpFrameData &data = std::get<CallArgsDumpFrameData>(curFrame.data);

			if (data.index >= e->args.size()) {
				CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));
				dumpContext->frames.popBack();

				goto loop;
			}

			if (data.index) {
				CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(", "));
			}

			CXXGEN_RETURN_IF_WRITE_FAILED(pushInitialDumpFrame(e->args.at(data.index).castTo<AstNode>()));

			++data.index;

			goto loop;
		}
		case DumpFrameType::CastTargetType: {
			assert(astNode->astNodeType == AstNodeType::Expr);

			CastExprNode *e = (CastExprNode *)astNode;

			CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

			curFrame.frameType = DumpFrameType::CastSource;

			CXXGEN_RETURN_IF_WRITE_FAILED(pushInitialDumpFrame(e->operand.castTo<AstNode>()));

			goto loop;
		}
		case DumpFrameType::CastSource: {
			assert(astNode->astNodeType == AstNodeType::Expr);

			CastExprNode *e = (CastExprNode *)astNode;

			dumpContext->frames.popBack();

			goto loop;
		}
		case DumpFrameType::NewTargetType: {
			assert(astNode->astNodeType == AstNodeType::Expr);

			NewExprNode *e = (NewExprNode *)astNode;

			CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write("("));

			dumpContext->frames.popBack();

			{
				DumpFrame dumpFrame;

				dumpFrame.astNode = astNode->sharedFromThis();

				dumpFrame.frameType = DumpFrameType::CallArgs;

				dumpFrame.data = CallArgsDumpFrameData{ 0 };

				if (!dumpContext->frames.pushBack(std::move(dumpFrame)))
					return false;
			}

			goto loop;
		}
		case DumpFrameType::NewArgs: {
			assert(astNode->astNodeType == AstNodeType::Expr);

			NewExprNode *e = (NewExprNode *)astNode;

			NewArgsDumpFrameData &data = std::get<NewArgsDumpFrameData>(curFrame.data);

			if (data.index >= e->args.size()) {
				CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));
				dumpContext->frames.popBack();

				goto loop;
			}

			if (data.index) {
				CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(", "));
			}

			CXXGEN_RETURN_IF_WRITE_FAILED(pushInitialDumpFrame(e->args.at(data.index).castTo<AstNode>()));

			++data.index;

			goto loop;
		}
		case DumpFrameType::TernaryCondition: {
			assert(astNode->astNodeType == AstNodeType::Expr);

			TernaryExprNode *e = (TernaryExprNode *)astNode;

			CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" ? "));

			curFrame.frameType = DumpFrameType::TernaryTrueBranch;

			CXXGEN_RETURN_IF_WRITE_FAILED(pushInitialDumpFrame(e->trueExpr.castTo<AstNode>()));

			goto loop;
		}
		case DumpFrameType::TernaryTrueBranch: {
			assert(astNode->astNodeType == AstNodeType::Expr);

			TernaryExprNode *e = (TernaryExprNode *)astNode;

			CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(" : "));

			curFrame.frameType = DumpFrameType::TernaryFalseBranch;

			CXXGEN_RETURN_IF_WRITE_FAILED(pushInitialDumpFrame(e->falseExpr.castTo<AstNode>()));

			goto loop;
		}
		case DumpFrameType::TernaryFalseBranch: {
			assert(astNode->astNodeType == AstNodeType::Expr);

			TernaryExprNode *e = (TernaryExprNode *)astNode;

			CXXGEN_RETURN_IF_WRITE_FAILED(dumpContext->writer->write(")"));

			dumpContext->frames.popBack();

			goto loop;
		}
		default:
			std::terminate();
	}

	std::terminate();
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

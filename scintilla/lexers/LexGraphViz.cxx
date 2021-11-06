// This file is part of Notepad2.
// See License.txt for details about distribution and modification.
//! Lexer for GraphViz Dot, blockdiag.

#include <cassert>
#include <cstring>

#include <string>
#include <string_view>

#include "ILexer.h"
#include "Scintilla.h"
#include "SciLexer.h"

#include "WordList.h"
#include "LexAccessor.h"
#include "Accessor.h"
#include "StyleContext.h"
#include "CharacterSet.h"
#include "LexerModule.h"

using namespace Lexilla;

namespace {

constexpr bool IsGraphVizOperator(int ch) noexcept {
	return AnyOf(ch, '{', '}', '[', ']', '<', '>', '=', ';', ',', ':', '+', '-');
}

constexpr bool IsEscapeSequence(int ch) noexcept {
	// https://graphviz.gitlab.io/docs/attr-types/escString/
	return AnyOf(ch, '\\', 't', 'n', 'r', '"', '\'');
}

constexpr bool IsSpaceEquiv(int state) noexcept {
	return state <= SCE_GRAPHVIZ_HTML_COMMENT;
}

void ColouriseGraphVizDoc(Sci_PositionU startPos, Sci_Position lengthDoc, int initStyle, LexerWordList keywordLists, Accessor &styler) {
	const bool fold = styler.GetPropertyInt("fold", 1) & true;
	int levelCurrent = SC_FOLDLEVELBASE;

	int htmlTagLevel = 0;
	int htmlCommentStyle = SCE_GRAPHVIZ_DEFAULT;
	int visibleChars = 0;
	int chPrevNonWhite = 0;
	int chBeforeIdentifier = 0;

	StyleContext sc(startPos, lengthDoc, initStyle, styler);
	if (sc.currentLine > 0) {
		htmlTagLevel = styler.GetLineState(sc.currentLine - 1);
		htmlCommentStyle = htmlTagLevel & 15;
		htmlTagLevel >>= 4;
		levelCurrent = styler.LevelAt(sc.currentLine - 1) >> 16;
	}
	if (startPos != 0 && IsSpaceEquiv(initStyle)) {
		LookbackNonWhite(styler, startPos,SCE_GRAPHVIZ_HTML_COMMENT, chPrevNonWhite, initStyle);
	}

	int levelNext = levelCurrent;

	while (sc.More()) {
		switch (sc.state) {
		case SCE_GRAPHVIZ_OPERATOR:
			sc.SetState(SCE_GRAPHVIZ_DEFAULT);
			break;

		case SCE_GRAPHVIZ_NUMBER:
			if (!IsDecimalNumber(sc.chPrev, sc.ch, sc.chNext)) {
				sc.SetState(SCE_GRAPHVIZ_DEFAULT);
			}
			break;

		case SCE_GRAPHVIZ_IDENTIFIER:
			if (!(IsIdentifierChar(sc.ch) || (sc.ch == '-' && sc.chNext != '>'))) {
				if (chBeforeIdentifier == '[' || chBeforeIdentifier == ',') {
					sc.ChangeState(SCE_GRAPHVIZ_ATTRIBUTE);
				} else {
					const int chNext = sc.GetDocNextChar();
					if (chNext == '=' || (chBeforeIdentifier != '=' && (chNext == ']' || chNext == ','))) {
						sc.ChangeState(SCE_GRAPHVIZ_ATTRIBUTE);
					} else if (chBeforeIdentifier == '=') {
						sc.ChangeState(SCE_GRAPHVIZ_VALUE);
					} else {
						char s[16];
						sc.GetCurrent(s, sizeof(s));
						if (keywordLists[0]->InList(s)) {
							sc.ChangeState(SCE_GRAPHVIZ_WORD);
						}
					}
				}
				sc.SetState(SCE_GRAPHVIZ_DEFAULT);
			}
			break;

		case SCE_GRAPHVIZ_STRING:
			if (sc.ch == '\\') {
				if (IsEscapeSequence(sc.chNext)) {
					sc.SetState(SCE_GRAPHVIZ_ESCAPECHAR);
				}
				sc.Forward();
			} else if (sc.ch == '\"') {
				sc.ForwardSetState(SCE_GRAPHVIZ_DEFAULT);
			} else if (sc.atLineStart) {
				sc.SetState(SCE_GRAPHVIZ_DEFAULT);
			}
			break;

		case SCE_GRAPHVIZ_ESCAPECHAR:
			sc.SetState(SCE_GRAPHVIZ_STRING);
			continue;

		case SCE_GRAPHVIZ_COMMENTLINE:
			if (sc.atLineStart) {
				sc.SetState(SCE_GRAPHVIZ_DEFAULT);
			}
			break;

		case SCE_GRAPHVIZ_COMMENTBLOCK:
			if (sc.Match('*', '/')) {
				--levelNext;
				sc.Forward();
				sc.ForwardSetState(SCE_GRAPHVIZ_DEFAULT);
			}
			break;

		case SCE_GRAPHVIZ_HTML_TAG:
			if (sc.ch == '>') {
				--htmlTagLevel;
				sc.ForwardSetState(SCE_GRAPHVIZ_HTML_TEXT);
			} else if (IsASpace(sc.ch)) {
				sc.SetState(SCE_GRAPHVIZ_DEFAULT);
			}
			break;

		case SCE_GRAPHVIZ_HTML_COMMENT:
			if (sc.Match('-', '-', '>')) {
				sc.Advance(3);
				sc.SetState(htmlCommentStyle);
				htmlCommentStyle = SCE_GRAPHVIZ_DEFAULT;
			}
			break;
		}

		if (sc.state == SCE_GRAPHVIZ_HTML_TEXT || (sc.state == SCE_GRAPHVIZ_DEFAULT && htmlTagLevel != 0)) {
			// https://graphviz.org/doc/info/shapes.html#html
			if (sc.ch == '<') {
				if (sc.chNext == '!') {
					htmlCommentStyle = sc.state;
					sc.SetState(SCE_GRAPHVIZ_HTML_COMMENT);
					sc.Forward(3);
				} else {
					++htmlTagLevel;
					sc.SetState(SCE_GRAPHVIZ_HTML_TAG);
				}
			} else if (sc.ch == '>') {
				--htmlTagLevel;
				if (htmlTagLevel == 0) {
					sc.SetState(SCE_GRAPHVIZ_OPERATOR);
				} else {
					sc.SetState(SCE_GRAPHVIZ_HTML_TAG);
					sc.ForwardSetState(SCE_GRAPHVIZ_HTML_TEXT);
					continue;
				}
			} else if (sc.Match('/', '>')) {
				sc.SetState(SCE_GRAPHVIZ_HTML_TAG);
			} else if (sc.state == SCE_GRAPHVIZ_DEFAULT && sc.ch == '=') {
				sc.SetState(SCE_GRAPHVIZ_OPERATOR);
			}
		}
		else if (sc.state == SCE_GRAPHVIZ_DEFAULT && htmlTagLevel == 0) {
			if (sc.Match('/', '/') || (visibleChars == 0 && sc.ch == '#')) {
				sc.SetState(SCE_GRAPHVIZ_COMMENTLINE);
			} else if (sc.Match('/', '*')) {
				++levelNext;
				sc.SetState(SCE_GRAPHVIZ_COMMENTBLOCK);
				sc.Forward();
			} else if (IsGraphVizOperator(sc.ch)) {
				sc.SetState(SCE_GRAPHVIZ_OPERATOR);
				if (sc.ch == '{' || sc.ch == '[') {
					++levelNext;
				} else if (sc.ch == '}' || sc.ch == ']') {
					--levelNext;
				} else if (sc.ch == '<' && chPrevNonWhite == '=' && sc.GetDocNextChar(true) == '<') {
					// attr = < <tag> ... </tag> >
					htmlTagLevel = 1;
				}
			}
		}
		if (sc.state == SCE_GRAPHVIZ_DEFAULT) {
			if (sc.ch == '\"') {
				sc.SetState(SCE_GRAPHVIZ_STRING);
			} else if (chPrevNonWhite == '=' && IsNumberStart(sc.ch, sc.chNext)) {
				sc.SetState(SCE_GRAPHVIZ_NUMBER);
			} else if (IsIdentifierStart(sc.ch)) {
				chBeforeIdentifier = chPrevNonWhite;
				sc.SetState(SCE_GRAPHVIZ_IDENTIFIER);
			}
		}

		if (!isspacechar(sc.ch)) {
			visibleChars++;
			if (!IsSpaceEquiv(sc.state)) {
				chPrevNonWhite = sc.ch;
			}
		}
		if (sc.atLineEnd) {
			styler.SetLineState(sc.currentLine, (htmlTagLevel << 4) | htmlCommentStyle);
			visibleChars = 0;
			if (fold) {
				const int levelUse = levelCurrent;
				int lev = levelUse | levelNext << 16;
				if (levelUse < levelNext)
					lev |= SC_FOLDLEVELHEADERFLAG;
				if (lev != styler.LevelAt(sc.currentLine)) {
					styler.SetLevel(sc.currentLine, lev);
				}
				levelCurrent = levelNext;
			}
		}
		sc.Forward();
	}

	sc.Complete();
}

}

LexerModule lmGraphViz(SCLEX_GRAPHVIZ, ColouriseGraphVizDoc, "gv");

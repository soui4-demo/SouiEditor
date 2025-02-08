// Scintilla source code edit control
/** @file Catalogue.cxx
 ** Colourise for particular languages.
 **/
// Copyright 1998-2002 by Neil Hodgson <neilh@scintilla.org>
// The License.txt file describes the conditions under which this software may be distributed.

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <ctype.h>

#include <stdexcept>
#include <vector>

#include "ILexer.h"
#include "Scintilla.h"
#include "SciLexer.h"

#include "LexerModule.h"
#include "Catalogue.h"

#ifdef SCI_NAMESPACE
using namespace Scintilla;
#endif

static std::vector<LexerModule *> lexerCatalogue;
static int nextLanguage = SCLEX_AUTOMATIC+1;

const LexerModule *Catalogue::Find(int language) {
	Scintilla_LinkLexers();
	for (std::vector<LexerModule *>::iterator it=lexerCatalogue.begin();
		it != lexerCatalogue.end(); ++it) {
		if ((*it)->GetLanguage() == language) {
			return *it;
		}
	}
	return 0;
}

const LexerModule *Catalogue::Find(const char *languageName) {
	Scintilla_LinkLexers();
	if (languageName) {
		for (std::vector<LexerModule *>::iterator it=lexerCatalogue.begin();
			it != lexerCatalogue.end(); ++it) {
			if ((*it)->languageName && (0 == strcmp((*it)->languageName, languageName))) {
				return *it;
			}
		}
	}
	return 0;
}

void Catalogue::AddLexerModule(LexerModule *plm) {
	if (plm->GetLanguage() == SCLEX_AUTOMATIC) {
		plm->language = nextLanguage;
		nextLanguage++;
	}
	lexerCatalogue.push_back(plm);
}

// To add or remove a lexer, add or remove its file and run LexGen.py.

// Force a reference to all of the Scintilla lexers so that the linker will
// not remove the code of the lexers.
int Scintilla_LinkLexers() {

	static int initialised = 0;
	if (initialised)
		return 0;
	initialised = 1;

// Shorten the code that declares a lexer and ensures it is linked in by calling a method.
#define LINK_LEXER(lexer) extern LexerModule lexer; Catalogue::AddLexerModule(&lexer);

//++Autogenerated -- run scripts/LexGen.py to regenerate
//**\(\tLINK_LEXER(\*);\n\)
	LINK_LEXER(lmCPP);
	LINK_LEXER(lmCPPNoCase);
	LINK_LEXER(lmHTML);
	LINK_LEXER(lmPHPSCRIPT);
	LINK_LEXER(lmXML);

//--Autogenerated -- end of automatically generated section

	return 1;
}

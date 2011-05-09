// Nmlgc's shared Touhou Tool stuff
// --------------------------------
// LCLangFrame.cpp - Language Selection Frame
// --------------------------------
// "©" Nmlgc, 2011

#include <bgmlib/platform.h>
#include <bgmlib/infostruct.h>
#include <bgmlib/bgmlib.h>

#include <FXHash.h>
#include <FXStream.h>
#include <FXRectangle.h>
#include <FXEvent.h>
#include <FXHorizontalFrame.h>
#include <FXFont.h>
#include <FXGroupBox.h>

#include <FXHorizontalFrame.h>

#include <FXRadioButton.h>

#include "LCLangFrame.h"

// Message Map
FXDEFMAP(LCLangFrame) MMLangFrame[] =
{
	FXMAPFUNCS(SEL_COMMAND, LCLangFrame::LF_CHANGE_LANG, LCLangFrame::LF_CHANGE_LANG_END, LCLangFrame::onCmdChangeLang),
	FXMAPFUNCS(SEL_UPDATE, LCLangFrame::LF_CHANGE_LANG, LCLangFrame::LF_CHANGE_LANG_END, LCLangFrame::onUpdChangeLang),
};

FXIMPLEMENT(LCLangFrame, FXGroupBox, MMLangFrame, ARRAYNUMBER(MMLangFrame));

LCLangFrame::LCLangFrame(FXComposite *p, const FXString &text, ushort* _LangPtr, FXObject *tgt, FXSelector sel, FXuint opts, FXint x, FXint y, FXint w, FXint h, FXint pl, FXint pr, FXint pt, FXint pb, FXint hs, FXint vs)
	: FXGroupBox(p, text, opts, x, y, w, h, pl, pr, pt, pb, hs, vs)
{
	Frame = new FXHorizontalFrame(this, LAYOUT_FILL);

	for(ushort c = 0; c < LANG_COUNT; c++)
	{
		LangRB[c] = new FXRadioButton(Frame, BGMLib::LI[c].Display, this, LF_CHANGE_LANG + c);
	}

	target = tgt;
	message = sel;
	LangPtr = _LangPtr;
}

long LCLangFrame::onCmdChangeLang(FXObject* Sender, FXSelector Message, void* ptr)
{
	FXushort Send = (FXSELID(Message) - LF_CHANGE_LANG);
	if(LangPtr)	*LangPtr = Send;
	if(target)	return target->handle(Sender, FXSEL(SEL_COMMAND, message), (void*)Send);
	else      	return 1;
}

long LCLangFrame::onUpdChangeLang(FXObject* Sender, FXSelector Message, void* ptr)
{
	FXushort Send = (FXSELID(Message) - LF_CHANGE_LANG);
	if(LangPtr)	Sender->handle(this, Send == *LangPtr ? FXSEL(SEL_COMMAND, FXWindow::ID_CHECK) : FXSEL(SEL_COMMAND,ID_UNCHECK), NULL);
	return 1;
}

// Set language
bool LCLangFrame::setLang(FXushort NewLang)
{
	if(NewLang > LANG_COUNT)	return false;
	if(LangPtr)	*LangPtr = NewLang;
	LangRB[Lang]->setCheck(TRUE, true);
	return true;
}

// Get language
const short LCLangFrame::getLang()
{
	if(LangPtr)	return *LangPtr;
	else		return -1;
}
// Nmlgc's shared Touhou Tool stuff
// --------------------------------
// LCDirFrame.cpp - Directory Selection Frame
// --------------------------------
// "©" Nmlgc, 2011

#include <bgmlib/platform.h>

#include <FXHash.h>
#include <FXStream.h>
#include <FXRectangle.h>
#include <FXEvent.h>
#include <FXHorizontalFrame.h>
#include <FXFont.h>

#include <FXPath.h>
#include <FXSystem.h>

#include <FXTextField.h>
#include <FXButton.h>

#include <FXDirDialog.h>

#include <FXRegistry.h>
#include <FXThread.h>
#include <FXApp.h>

#include "LCDirFrame.h"

// Message Map
FXDEFMAP(LCDirFrame) MMDirFrame[] =
{
	FXMAPFUNC(SEL_COMMAND, LCDirFrame::DF_SELECT_DIR, LCDirFrame::onSelectDir),
};

FXIMPLEMENT(LCDirFrame, FXHorizontalFrame, MMDirFrame, ARRAYNUMBER(MMDirFrame));

LCDirFrame::LCDirFrame(FXComposite *p, FXString InitialDir, FXObject* tgt,FXSelector sel, FXuint opts, FXint x,FXint y,FXint w,FXint h,FXint pl,FXint pr,FXint pt,FXint pb,FXint hs,FXint vs)
	: FXHorizontalFrame(p, LAYOUT_FILL_X, x, y, w, h, pl, pr, pt, pb, hs, vs)
{
	FXuint WidgetOpts = opts & DIRFRAME_READONLY ? (FRAME_SUNKEN | TEXTFIELD_READONLY) : TEXTFIELD_NORMAL;

	Field = new FXTextField(this, 32, NULL, 0, WidgetOpts | LAYOUT_FILL | JUSTIFY_BOTTOM, 0, 0, 0, 0, DEFAULT_PAD, DEFAULT_PAD *4, DEFAULT_PAD, DEFAULT_PAD);
	Select = new FXButton(this, "...", NULL, this, DF_SELECT_DIR, BUTTON_NORMAL | LAYOUT_RIGHT | LAYOUT_FILL_X);
	Field->setText(InitialDir);

	if(opts & DIRFRAME_READONLY)
	{
		Field->setBackColor(getApp()->getBaseColor());
	}

	target=tgt;
	message=sel;
}

void LCDirFrame::setButtonText(const FXString& Str)
{
	Select->setText(Str);
	Select->setLayoutHints(LAYOUT_RIGHT);
}

long LCDirFrame::setDir(FXString& NewDir, FXbool notify)
{
	if(NewDir.empty())	return 1;

	NewDir = FXPath::simplify(NewDir);
	if(notify && target)
	{
		long Ret = target->handle(this, FXSEL(SEL_COMMAND, message), (void*)&NewDir);
		if(Ret)	Field->setText(NewDir, true);
		return Ret;
	}
	else
	{
		Field->setText(NewDir, true);
		return 1;
	}
}

FXString LCDirFrame::getDir()
{
	return FXPath::simplify(Field->getText() + PATHSEP);
}

void LCDirFrame::enable()
{
	Select->enable();
}

void LCDirFrame::disable()
{
	Select->disable();
}

long LCDirFrame::onSelectDir(FXObject* Sender, FXSelector Message, void* ptr)
{
	FXString Ret = Field->getText();

	if(Ret.empty())	Ret = FXSystem::getCurrentDirectory();
	else			Ret = FXPath::upLevel(Ret);
	Ret = FXDirDialog::getOpenDirectory(this, DlgCaption, Ret);
	
	return setDir(Ret, true);
}

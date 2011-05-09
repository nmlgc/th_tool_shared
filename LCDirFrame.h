// Nmlgc's shared Touhou Tool stuff
// --------------------------------
// LCDirFrame.h - Directory Selection Frame
// --------------------------------
// "©" Nmlgc, 2011

#ifndef LCDIRFRAME_H
#define LCDIRFRAME_H

// Directory Frame styles
enum {
  DIRFRAME_READONLY    = 0x00080000,    /// NOT editable
  };

// - If the selection button was clicked and a directory was selected,
//   the widget sends the specified message to it's target, and passes
//   an FXString* to the selected directory as third parameter.
class LCDirFrame : public FXHorizontalFrame
{
	FXDECLARE(LCDirFrame);

private:
	LCDirFrame()	{}

public:
	FXTextField* Field;
	FXButton* Select;

	FXString DlgCaption;

	LCDirFrame(FXComposite* p, FXString InitialDir = "", FXObject* tgt=NULL, FXSelector sel=0, FXuint opts=0, FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_SPACING,FXint pr=DEFAULT_SPACING,FXint pt=DEFAULT_SPACING,FXint pb=DEFAULT_SPACING,FXint hs=DEFAULT_SPACING,FXint vs=DEFAULT_SPACING);

	// Sets the directory to [NewDir].
	// If notify = true, the widget sends a SEL_COMMAND message with the specified selector to it's target
	long     setDir(FXString& NewDir, FXbool notify = true);
	FXString getDir();

	void setButtonText(const FXString& Str);

	void enable();
	void disable();

	enum
	{
		DF_SELECT_DIR = FXHorizontalFrame::ID_LAST,
		ID_LAST
	};

	long onSelectDir(FXObject* Sender, FXSelector Message, void* ptr);
};

#endif /* LCDIRFRAME_H */

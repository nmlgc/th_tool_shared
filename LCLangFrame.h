// Nmlgc's shared Touhou Tool stuff
// --------------------------------
// LCLangFrame.h - Language Selection Frame
// --------------------------------
// "©" Nmlgc, 2011

#ifndef LCLANGFRAME_H
#define LCLANGFRAME_H

class LCLangFrame : public FXGroupBox
{
	FXDECLARE(LCLangFrame);
private:
	LCLangFrame()	{}
public:
	long onCmdChangeLang(FXObject* Sender, FXSelector Message, void* ptr);
	long onUpdChangeLang(FXObject* Sender, FXSelector Message, void* ptr);
public:
	FXHorizontalFrame* Frame;
	ushort* LangPtr;

	FXRadioButton*	LangRB[LANG_COUNT];

	LCLangFrame(FXComposite* p,const FXString& text,ushort* Lang, FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=GROUPBOX_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_SPACING,FXint pr=DEFAULT_SPACING,FXint pt=DEFAULT_SPACING,FXint pb=DEFAULT_SPACING,FXint hs=DEFAULT_SPACING,FXint vs=DEFAULT_SPACING);

	/// Set language
	bool setLang(FXushort NewLang);

	/// Get language
	const short getLang();

	enum
	{
		LF_CHANGE_LANG = FXGroupBox::ID_LAST,
		LF_CHANGE_LANG_END = LF_CHANGE_LANG + LANG_COUNT,
		ID_LAST
	};
};

#endif /* LCLANGFRAME_H */

// Nmlgc's shared Touhou Tool stuff
// --------------------------------
// LCProgressBar.h - Custom FXProgressBar, automatically connecting to a FXDataTarget and with a custom label feature
// --------------------------------
// "©" Nmlgc, 2011

#ifndef LCPROGRESSBAR_H
#define LCPROGRESSBAR_H

/// New progress bar styles
enum {
  PROGRESSBAR_TEXT = 0x00010000,    /// Show custom text (same as PROGRESSBAR_PERCENTAGE,
                                    /// percentage is shown when string is empty)
  };

// Forward declarations
namespace FX
{
	class FXProgressBar;
	class FXDataTarget;
}

class LCProgressBar : public FX::FXProgressBar
{
	FXDECLARE(LCProgressBar);

protected:
	FXString text;	// custom text
	FXDataTarget dt;
protected:
	LCProgressBar()	{}

	void drawInterior(FXDCWindow& dc);
	FXString getDispText(FXint* n, FXint& percent);

public:
  long onPaint(FXObject*,FXSelector,void*);
public:
	/// Construct progress bar
	LCProgressBar(FXComposite* p,FXuint opts=PROGRESSBAR_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD);

	/// Set custom text
	void setCustomText(FXString str);

	/// Get custom text
	const FXString& getCustomText();

	/// Connect a variable
	void connect(volatile FXulong* var = NULL, FXulong max = 0);

	// All the other functions we don't need, but _HAVE TO_ copy verbatim, just because drawInterior(dc) is not virtual!
	// Thanks, Jeroen!

	void setTotal(FXuint value);
	void setProgress(FXuint value);

	long onCmdSetValue(FXObject*,FXSelector,void*);
	long onCmdSetIntValue(FXObject*,FXSelector,void*);
	long onCmdSetLongValue(FXObject*,FXSelector,void*);
	long onCmdSetIntRange(FXObject*,FXSelector,void*);
};

#endif /* LCPROGRESSBAR_H */

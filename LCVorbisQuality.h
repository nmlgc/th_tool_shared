// Nmlgc's shared Touhou Tool stuff
// --------------------------------
// LCVorbisQuality.h - Vorbis Quality Slider
// --------------------------------
// "©" Nmlgc, 2011

#ifndef LCVORBISQUALITY_H
#define LCVORBISQUALITY_H

// Forward declarations
namespace FX
{
	class FXRealSlider;
}

class LCVorbisQuality : public FXGroupBox
{
	FXDECLARE(LCVorbisQuality);

private:
	LCVorbisQuality()	{}

protected:
	FXRealSlider* Q;
	FXLabel*	EstBR;

public:
	LCVorbisQuality(FXComposite* p, FXdouble DefaultQuality = 5.0);

	void setQuality(FXdouble Quality);
	FXdouble getQuality();

	/// Enable the window
	virtual void enable();

	/// Disable the window
	virtual void disable();

	// Messages
	enum
	{
		VQ_UPDATE = FXGroupBox::ID_LAST,
		ID_LAST
	};

	long onVQUpdate(FXObject* Sender, FXSelector Message, void* ptr);
};

#endif /* LCVORBISQUALITY_H */

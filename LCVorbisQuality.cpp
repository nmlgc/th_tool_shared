// Nmlgc's shared Touhou Tool stuff
// --------------------------------
// LCVorbisQuality.cpp - Vorbis Quality Slider
// --------------------------------
// "©" Nmlgc, 2011

#include <bgmlib/platform.h>
#include <bgmlib/libvorbis.h>

#include <FXHash.h>
#include <FXStream.h>
#include <FXRectangle.h>
#include <FXEvent.h>
#include <FXHorizontalFrame.h>
#include <FXFont.h>
#include <FXGroupBox.h>
#include <FXRealSlider.h>
#include <FXLabel.h>

#include "LCVorbisQuality.h"

FXDEFMAP(LCVorbisQuality) MMVorbisQuality[] =
{
	// All kinds of messages we may possibly receive
	FXMAPFUNC(SEL_COMMAND, LCVorbisQuality::VQ_UPDATE, LCVorbisQuality::onVQUpdate),
	FXMAPFUNC(SEL_CHANGED, LCVorbisQuality::VQ_UPDATE, LCVorbisQuality::onVQUpdate),
};

FXIMPLEMENT(LCVorbisQuality, FXGroupBox, MMVorbisQuality, ARRAYNUMBER(MMVorbisQuality));

LCVorbisQuality::LCVorbisQuality(FX::FXComposite *p, FX::FXdouble DefaultQuality)
	: FXGroupBox(p, "Quality", GROUPBOX_NORMAL | FRAME_GROOVE | LAYOUT_FILL_X)
{
		FXHorizontalFrame*	QDesc;

		Q = new FXRealSlider(this, this, VQ_UPDATE, REALSLIDER_HORIZONTAL | REALSLIDER_ARROW_DOWN | REALSLIDER_TICKS_BOTTOM | LAYOUT_FILL_X);
	QDesc = new FXHorizontalFrame(this, LAYOUT_FILL_X);
		
		new FXLabel(QDesc, "Smallest file", NULL, LABEL_NORMAL | LAYOUT_LEFT);
		new FXLabel(QDesc, "Best quality", NULL, LABEL_NORMAL | LAYOUT_RIGHT);

		EstBR = new FXLabel(QDesc, "", NULL, LABEL_NORMAL | LAYOUT_CENTER_X | LAYOUT_FIX_WIDTH | FRAME_SUNKEN, 0, 0, 100);

	// Set values
	Q->setRange(-1.0, 10.0);
	Q->setIncrement(0.1);
	Q->setGranularity(0.1);
	Q->setTickDelta(11.0);
	setQuality(DefaultQuality);
}

void LCVorbisQuality::setQuality(FXdouble Quality)
{
	Q->setValue(Quality, true);
}

FXdouble LCVorbisQuality::getQuality()
{
	return Q->getValue();
}

void LCVorbisQuality::disable()
{
	FXGroupBox::disable();
	Q->disable();
}

void LCVorbisQuality::enable()
{
	FXGroupBox::enable();
	Q->enable();
}

long LCVorbisQuality::onVQUpdate(FXObject* Sender, FXSelector Message, void* ptr)
{
	FXString Str;
	FXfloat New = Q->getValue();
	Str.format("~%.0f kbps, q%.1f", vorbis_quality_to_bitrate(New) / 1000.0f, New);

	EstBR->setText(Str);

	return 1;
}
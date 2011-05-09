// Nmlgc's shared Touhou Tool stuff
// --------------------------------
// LCProgressBar.cpp - Custom FXProgressBar, automatically connecting to a FXDataTarget and with a custom label feature
// --------------------------------
// "©" Nmlgc, 2011

#include <stdio.h>
#include <fxdefs.h>
#include <FXHash.h>
#include <FXThread.h>
#include <FXStream.h>
#include <FXString.h>
#include <FXSize.h>
#include <FXPoint.h>
#include <FXRectangle.h>
#include <FXRegistry.h>
#include <FXFont.h>
#include <FXEvent.h>
#include <FXWindow.h>
#include <FXBitmap.h>
#include <FXDCWindow.h>
#include <FXColors.h>
#include <FXApp.h>

using namespace FX;

#include <FXDataTarget.h>
#include <FXProgressBar.h>
#include "LCProgressBar.h"


// Map
FXDEFMAP(LCProgressBar) LCProgressBarMap[]={
  FXMAPFUNC(SEL_PAINT,0,LCProgressBar::onPaint),
  FXMAPFUNC(SEL_COMMAND,FXProgressBar::ID_SETVALUE,LCProgressBar::onCmdSetValue),
  FXMAPFUNC(SEL_COMMAND,FXProgressBar::ID_SETINTVALUE,LCProgressBar::onCmdSetIntValue),
  FXMAPFUNC(SEL_COMMAND,FXProgressBar::ID_SETLONGVALUE,LCProgressBar::onCmdSetLongValue),
  FXMAPFUNC(SEL_COMMAND,FXProgressBar::ID_SETINTRANGE,LCProgressBar::onCmdSetIntRange),
  };


// Object implementation
FXIMPLEMENT(LCProgressBar,FXProgressBar,LCProgressBarMap,ARRAYNUMBER(LCProgressBarMap))

// Construct progress bar
LCProgressBar::LCProgressBar(FXComposite* p,FXuint opts,FXint x,FXint y,FXint w,FXint h,FXint pl,FXint pr,FXint pt,FXint pb)
: FXProgressBar(p, &dt, FXDataTarget::ID_VALUE, opts, x, y, w, h, pl, pr, pt, pb)
{
}

FXString LCProgressBar::getDispText(FXint* n, FXint& percent)
{
	if(!text.empty())
	{
		if(n)	*n = text.length();
		return text;
	}
	else
	{
		FXString Ret;
		if(progress > 0)	Ret.format("%d%%",percent);
		if(n)	*n = Ret.length();
		return Ret;
	}
}

// Draw only the interior, i.e. the part that changes
void LCProgressBar::drawInterior(FXDCWindow& dc){
  register FXdouble fraction=(total>0)?((FXdouble)progress/(FXdouble)total):1.0;
  register FXint percent,barlength,barwidth,barfilled,ang,tx,ty,tw,th,dx,dy,ds,n;
  // Nmlgc
  // -----
  FXString disptext;
  // -----

  // Calculate percentage complete
  percent=(FXuint)(100.0*fraction);

  // Nmlgc
  // -----
  if(options&PROGRESSBAR_TEXT)
  {
	disptext = getDispText(&n, percent);
  }
  // -----

  // Round dial
  if(options&PROGRESSBAR_DIAL){

    // If total is 0, it's 100%
    barfilled=(FXuint)(23040.0*fraction);

    // Dial size and location
    tw=width-(border<<1)-padleft-padright;
    th=height-(border<<1)-padtop-padbottom;
    ds=FXMIN(tw,th)-1;
    dx=border+padleft+(tw-ds)/2;
    dy=border+padtop+(th-ds)/2;

    // Draw unfilled piece
    if(barfilled!=23040){
      dc.setForeground(barBGColor);
      dc.fillArc(dx,dy,ds,ds,5760,23040-barfilled);
      }

    // Draw filled piece
    if(barfilled!=0){

      // Original code
      //dc.setForeground(barColor);
      //dc.fillArc(dx,dy,ds,ds,5760,-barfilled);

      // New gradient method
      for(int i=ds; i>0; i-=8){
        dc.setForeground(makeBlendColor(barBGColor,barColor,(100*i+ds/2)/ds));
        dc.fillArc(dx+(ds-i)/2,dy+(ds-i)/2,i,i,5760,-barfilled);
        }
/*
      ang=0;
      n=640;
      while(ang<barfilled){
        if(ang+n>barfilled) n=barfilled-ang;
        dc.setForeground(makeBlendColor(barBGColor,barColor,(460800+80*(ang+n))/23040));
        dc.fillArc(dx,dy,ds,ds,5760-ang,-n);
        ang+=n;
        }
*/
      }

    // Draw outside circle
    dc.setForeground(borderColor);
    dc.drawArc(dx+1,dy,ds,ds,90*64,45*64);
    dc.drawArc(dx,dy+1,ds,ds,135*64,45*64);
    dc.setForeground(baseColor);
    dc.drawArc(dx-1,dy,ds,ds,270*64,45*64);
    dc.drawArc(dx,dy-1,ds,ds,315*64,45*64);

    dc.setForeground(shadowColor);
    dc.drawArc(dx,dy,ds,ds,45*64,180*64);
    dc.setForeground(hiliteColor);
    dc.drawArc(dx,dy,ds,ds,225*64,180*64);

    // Draw text
    if(options&PROGRESSBAR_PERCENTAGE){
		// Nmlgc
		// -----
		if(!text.empty())	tw=font->getTextWidth(text);
		else
		// -----
      tw=font->getTextWidth("100%",4);
      if(tw>(10*ds)/16) return;                  // Text too wide
      th=font->getFontHeight();
      if(th>ds/2) return;                        // Text too tall
	  
      tw=font->getTextWidth(disptext);
      th=font->getFontHeight();
      tx=dx+ds/2-tw/2;
      ty=dy+ds/2+font->getFontAscent()+5;
      dc.setFont(font);
      dc.setForeground(textNumColor);
      dc.drawText(tx,ty,disptext);
      }
    }

  // Vertical bar
  else if(options&PROGRESSBAR_VERTICAL){

    // Calculate length and filled part of bar
    barlength=height-(border<<1)-padtop-padbottom;
    barwidth=width-(border<<1)-padleft-padbottom;
    barfilled=(FXuint)(barlength*fraction);

    // Draw completed bar
    if(0<barfilled){

      // Light/dark bubble
      dc.fillHorizontalGradient(border+padleft,height-border-padbottom-barfilled,barwidth/2,barfilled,makeHiliteColor(barColor,40),barColor);
      dc.fillHorizontalGradient(border+padleft+barwidth/2,height-border-padbottom-barfilled,barwidth-barwidth/2,barfilled,barColor,makeShadowColor(barColor,20));

      // Bubble
      //dc.fillHorizontalGradient(border+padleft,height-border-padbottom-barfilled,barwidth/2,barfilled,makeHiliteColor(barColor,60),barColor);
      //dc.fillHorizontalGradient(border+padleft+barwidth/2,height-border-padbottom-barfilled,barwidth-barwidth/2,barfilled,barColor,makeHiliteColor(barColor,60));

      // Original code
      //dc.setForeground(barColor);
      //dc.fillRectangle(border+padleft,height-border-padbottom-barfilled,barwidth,barfilled);

      // Increasing gradient
      //dc.fillVerticalGradient(border+padleft,height-border-padbottom-barfilled,barwidth,barfilled,makeBlendColor(barBGColor,barColor,20+(80*percent)/100),makeBlendColor(barBGColor,barColor,20));
      }

    // Draw uncompleted bar
    if(barfilled<barlength){
      dc.setForeground(barBGColor);
      dc.fillRectangle(border+padleft,border+padtop,barwidth,barlength-barfilled);
      }

    // Draw text
    if(options&PROGRESSBAR_PERCENTAGE){
		tw=font->getTextWidth(disptext);
      th=font->getFontHeight();
      ty=border+padtop+(barlength-th)/2+font->getFontAscent();
      tx=border+padleft+(barwidth-tw)/2;
      dc.setFont(font);
      if(height-border-barfilled>ty){           // In upper side
        dc.setForeground(textNumColor);
        dc.setClipRectangle(border+padleft,border+padtop,barwidth,barlength);
        dc.drawText(tx,ty,disptext);
        }
      else if(ty-th>height-border-barfilled){   // In lower side
        dc.setForeground(textAltColor);
        dc.setClipRectangle(border+padleft,border+padtop,barwidth,barlength);
        dc.drawText(tx,ty,disptext);
        }
      else{                                     // In between!
        dc.setForeground(textAltColor);
        dc.setClipRectangle(border+padleft,height-border-padbottom-barfilled,barwidth,barfilled);
        dc.drawText(tx,ty,disptext);
        dc.setForeground(textNumColor);
        dc.setClipRectangle(border+padleft,border+padtop,barwidth,barlength-barfilled);
        dc.drawText(tx,ty,disptext);
        dc.clearClipRectangle();
        }
      }
    }

  // Horizontal bar
  else{

    // Calculate length and filled part of bar
    barlength=width-(border<<1)-padleft-padright;
    barwidth=height-(border<<1)-padtop-padbottom;
    barfilled=(FXuint)(barlength*fraction);

    // Draw completed bar
    if(0<barfilled){

      // Light/dark bubble
      dc.fillVerticalGradient(border+padleft,border+padtop,barfilled,barwidth/2,makeHiliteColor(barColor,40),barColor);
      dc.fillVerticalGradient(border+padleft,border+padtop+barwidth/2,barfilled,barwidth-barwidth/2,barColor,makeShadowColor(barColor,20));

      // Bubble
      //dc.fillVerticalGradient(border+padleft,border+padtop,barfilled,barwidth/2,makeHiliteColor(barColor,60),barColor);
      //dc.fillVerticalGradient(border+padleft,border+padtop+barwidth/2,barfilled,barwidth-barwidth/2,barColor,makeHiliteColor(barColor,60));

      // Original code
      //dc.setForeground(barColor);
      //dc.fillRectangle(border+padleft,border+padtop,barfilled,barwidth);

      // Increasing gradient
      //dc.fillHorizontalGradient(border+padleft,border+padtop,barfilled,barwidth,makeBlendColor(barBGColor,barColor,20),makeBlendColor(barBGColor,barColor,20+(80*percent)/100));
      }

    // Draw uncompleted bar
    if(barfilled<barlength){
      dc.setForeground(barBGColor);
      dc.fillRectangle(border+padleft+barfilled,border+padtop,barlength-barfilled,barwidth);
      }

    // Draw text
    if(options&PROGRESSBAR_PERCENTAGE){
      tw=font->getTextWidth(disptext);
      th=font->getFontHeight();
      ty=border+padtop+(barwidth-th)/2+font->getFontAscent();
      tx=border+padleft+(barlength-tw)/2;
      dc.setFont(font);
      if(border+padleft+barfilled<=tx){           // In right side
        dc.setForeground(textNumColor);
        dc.setClipRectangle(border+padleft,border+padtop,barlength,barwidth);
        dc.drawText(tx,ty,disptext);
        }
      else if(tx+tw<=border+padleft+barfilled){   // In left side
        dc.setForeground(textAltColor);
        dc.setClipRectangle(border+padleft,border+padtop,barlength,barwidth);
        dc.drawText(tx,ty,disptext);
        }
      else{                               // In between!
        dc.setForeground(textAltColor);
        dc.setClipRectangle(border+padleft,border+padtop,barfilled,barwidth);
        dc.drawText(tx,ty,disptext);
        dc.setForeground(textNumColor);
        dc.setClipRectangle(border+padleft+barfilled,border+padtop,barlength-barfilled,barwidth);
        dc.drawText(tx,ty,disptext);
        dc.clearClipRectangle();
        }
      }
    }
  }
  

// Set custom text
void LCProgressBar::setCustomText(FX::FXString str)
{
	text = str;
	update();
}

// Set custom text
const FXString& LCProgressBar::getCustomText()
{
	return text;
}

// Connect a variable
void LCProgressBar::connect(volatile FX::FXulong *var, FX::FXulong max)
{
	if(!var)
	{
		dt.connect();
		setProgress(0);
		setTotal(1);
	}
	else
	{
		dt.connect((FXulong&)*var);
		setTotal(max);
	}
}

// Draw the progress bar
long LCProgressBar::onPaint(FXObject*,FXSelector,void *ptr)
{
  FXDCWindow dc(this,(FXEvent*)ptr);

  // Erase to base color
  dc.setForeground(baseColor);
  dc.fillRectangle(0,0,width,height);

  // Draw borders
  drawFrame(dc,padleft,padtop,width-padleft-padright,height-padtop-padbottom);

  // Draw interior
  drawInterior(dc);
  return 1;
  }

// All the other functions we don't need, but _HAVE TO_ copy verbatim, just because drawInterior(dc) is not virtual!
// Thanks, Jeroen!

void LCProgressBar::setProgress(FXuint value){
  if(value>total) value=total;
  if(value!=progress){
    progress=value;
    if(xid){
      FXDCWindow dc(this);
      drawInterior(dc);
      }
    getApp()->flush();
    }
  }

// Set total amount to completion
void LCProgressBar::setTotal(FXuint value){
  if(value!=total){
    total=value;
    if(xid){
      FXDCWindow dc(this);
      drawInterior(dc);
      }
    getApp()->flush();
    }
  }

// Update progress value from a message
long LCProgressBar::onCmdSetValue(FXObject*,FXSelector,void* ptr){
  setProgress((FXuint)(FXival)ptr);
  return 1;
  }

// Set value
long LCProgressBar::onCmdSetIntValue(FXObject*,FXSelector,void* ptr){
  setProgress(*((FXint*)ptr));
  return 1;
  }

// Update value from a message
long LCProgressBar::onCmdSetLongValue(FXObject*,FXSelector,void* ptr){
  setProgress((FXint)*((FXlong*)ptr));
  return 1;
  }

// Update range from a message
long LCProgressBar::onCmdSetIntRange(FXObject*,FXSelector,void* ptr){
  setTotal(((FXint*)ptr)[1]-((FXint*)ptr)[0]);
  return 1;
  }
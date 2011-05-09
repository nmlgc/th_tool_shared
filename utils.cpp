// Nmlgc's shared Touhou Tool stuff
// --------------------------------
// utils.cpp - The most random of the random stuff
// --------------------------------
// "©" Nmlgc, 2011

#include <bgmlib/platform.h>
#include <bgmlib/list.h>
#include <bgmlib/infostruct.h>
#include <bgmlib/bgmlib.h>
#include <stdio.h>
#include <fxdefs.h>
#include <FXString.h>
#include <FXPath.h>
#include <FXSystem.h>

#include <FXRectangle.h>
#include <FXEvent.h>
#include <FXHash.h>
#include <FXStream.h>
#include <FXFont.h>
#include <FXText.h>
#include <FXRegistry.h>
#include <FXThread.h>
#include <FXApp.h>

using namespace FX;

// This will fix the issue that our current directory stays at %HOMEPATH%
// if somebody specifies a command line parameter via Explorer
FXString CorrectAppPath(char* CmdLine)
{
	FXString FN, Dir = CmdLine;

	FN = FX::FXPath::name(Dir);
	Dir.length(Dir.length() - FN.length());

	if(!Dir.empty())
	{
		FXSystem::setCurrentDirectory(Dir);
		return Dir;
	}
	else	return FXSystem::getCurrentDirectory() + PATHSEP;
}

FXString WebPageDesc(const FXString& WebPage)
{
	return "Get the latest version of this tool, as well as the source code, at <" + WebPage + ">.\n"
	"This program was not made by anyone from shrinemaiden.org.\n\n";
}

void TranslateGameNames(FXText* Stat, ushort Lang)
{
	ListEntry<GameInfo>* CurGame = BGMLib::Game.First();
	FXint beg, end, start, l = 1;
	FXString Search, Replace;
	GameInfo* GI;

	// Update status box game names
	while(CurGame)
	{
		GI = &CurGame->Data;
		Replace = GI->DelimName(Lang);

		for(ushort c = 0; c < LANG_COUNT; c++)
		{
			if(c == Lang)	continue;
			Search = GI->DelimName(c);

			start = 0;
			while(Stat->findText(Search, &beg, &end, start, SEARCH_FORWARD | SEARCH_EXACT))
			{
				Stat->replaceText(beg, end - beg, Replace);
				start = beg + Replace.length();
			}
		}

		CurGame = CurGame->Next();
	}
}

void PrintStat(FXApp* App, FXText* Stat, const FXString& Str)
{
	FXint NewRow;

	Stat->appendText(Str, true);
	NewRow = Stat->rowStart(Stat->getLength());
	Stat->makePositionVisible(NewRow);
	Stat->setCursorRow(NewRow, true);
	Stat->update();
	Stat->recalc();

	App->repaint();
}
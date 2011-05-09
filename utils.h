// Nmlgc's shared Touhou Tool stuff
// --------------------------------
// utils.h - The most random of the random stuff
// --------------------------------
// "©" Nmlgc, 2011

#ifndef UTILS_H
#define UTILS_H

FXString CorrectAppPath(char* CmdLine);
FXString WebPageDesc(const FXString& WebPage);

void TranslateGameNames(FXText* Stat, ushort Lang);

void PrintStat(FXApp* App, FXText* Stat, const FXString& Str);

#endif /* UTILS_H */
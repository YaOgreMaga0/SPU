#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "../OneginFunc/FileFunc.h"
#include "../OneginFunc/StringFunc.h"
#include "../OneginFunc/IndexFunc.h"

#include "LanguageCode.h"

int Translator(char* filenamein, char* filenameout);
int FillByteOutput(struct Line* index, const char* filename, int len);
int CleanBuf(struct Line* index, int len);

#endif //TRANSLATOR_H

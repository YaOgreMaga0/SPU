#ifndef INDEXFUNC_H
#define INDEXFUNC_H
#include "StringFunc.h"


int CountOfSymbols(const char* name);
int FillIndex(char* buf, struct Line* index, long long int count);
int FillOutput(struct Line* index, const char* filename, int  len);
int FillBuf(const int SymbolsCount, FILE* text, char* buf);


#endif //INDEXFUNC_H

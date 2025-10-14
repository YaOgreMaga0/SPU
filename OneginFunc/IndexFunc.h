#ifndef INDEXFUNC_H
#define INDEXFUNC_H
#include "StringFunc.h"


unsigned long long int CountOfSymbols(const char* name);
int FillIndex(char* buf, struct Line* index, long long int count);
int FillOutput(struct Line* index, const char* filename, int  len);
unsigned int FillBuf(const unsigned long long int cnt, FILE* text, char* buf);


#endif //INDEXFUNC_H

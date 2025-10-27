#ifndef FILEFUNC_H
#define FILEFUNC_H

#include "StringFunc.h"
#include "IndexFunc.h"

typedef struct Index
{
    char* buf;
    Line* index;
    int CntLines;
}Index;

Index MakeIndex(const char* filename);
void MemoryFree(Index *Inf);



#endif //FILEFUNC_H

#ifndef FILEFUNC_H
#define FILEFUNC_H

#include "StringFunc.h"
#include "IndexFunc.h"

typedef struct BufAndIndexInf
{
    char* buf;
    struct Line* index;
    int CntLines;
}BufAndIndexInf;

BufAndIndexInf FileReadAndMakeBuf(const char* filename);
void MemoryFree(BufAndIndexInf *Inf);



#endif //FILEFUNC_H

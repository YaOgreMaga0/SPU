#ifndef SPU_H
#define SPU_H

#include <string.h>
#include <math.h>
#include "CommandFunc.h"

const float spu_version = 1.3f;

int SPUInit(SPUMem* SPUMemory, const char* FilenameIn);
int SPUDeInit(SPUMem* SPUMemory);
int CheckSignature(FILE* Code);
int SPU(SPUMem* SPUMemory);

#endif //SPU_H

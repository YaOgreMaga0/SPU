#ifndef BYTECODE_H
#define BYTECODE_H

#include <stdio.h>
#include "CommandFunc.h"

int ByteCode(char* filename);
int GetByte(FILE* fp);
int CheckSignature(FILE* code, int* PC);
int FillStack(FILE* code, int PC, stack* stk);

#endif //BYTECODE_H

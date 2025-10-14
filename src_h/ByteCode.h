#ifndef BYTECODE_H
#define BYTECODE_H

#include <stdio.h>
#include "CommandFunc.h"

int ByteCode(char* filename);
int GetByte(FILE* fp);
int FillStack(char* filename);

#endif //BYTECODE_H

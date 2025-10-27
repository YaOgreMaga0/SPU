#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include "../src_h/CommandFunc.h"

int* GetCode(const char* FilenameIn, int* code_commands_count);
int FillText(int* Code, const char* FilenameOut, int PC);

#endif //DISASSEMBLER_H

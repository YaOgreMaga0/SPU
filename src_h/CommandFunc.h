#ifndef COMMANDFUNC_H
#define COMMANDFUNC_H

#include <string.h>
#include <stdio.h>
#include "SPU_Types.h"

void push(SPUMem* SPUMemory);
void out(SPUMem* SPUMemory);
void add(SPUMem* SPUMemory);
void sub(SPUMem* SPUMemory);
void mul(SPUMem* SPUMemory);
void div(SPUMem* SPUMemory);
void pushr(SPUMem* SPUMemory);
void popr(SPUMem* SPUMemory);
void jmp(SPUMem* SPUMemory);
void jb(SPUMem* SPUMemory);
void jbe(SPUMem* SPUMemory);
void ja(SPUMem* SPUMemory);
void jae(SPUMem* SPUMemory);
void je(SPUMem* SPUMemory);
void jne(SPUMem* SPUMemory);
void call(SPUMem* SPUMemory);
void ret(SPUMem* SPUMemory);
void draw(SPUMem* SPUMemory);
void pushmem(SPUMem* SPUMemory);
void popmem(SPUMem* SPUMemory);

const command Commands[count_of_commands] =
{
    {"HLT", HLT, 0, NULL},
    {"PUSH", PUSH, 1, &push},
    {"OUT", OUT, 0, &out},
    {"ADD", ADD, 0, &add},
    {"SUB", SUB, 0, &sub},
    {"MUL", MUL, 0, &mul},
    {"DIV", DIV, 0, &div},
    {"PUSHR", PUSHR, 1, &pushr},
    {"POPR", POPR, 0, &popr},
    {"JMP", JMP, 1, &jmp},
    {"JB", JB, 1, &jb},
    {"JBE", JBE, 1, &jbe},
    {"JA", JA, 1, &ja},
    {"JAE", JAE, 1, &jae},
    {"JE", JE, 1, &je},
    {"JNE", JNE, 1, &jne},
    {"CALL", CALL, 1, &call},
    {"RET", RET, 0, &ret},
    {"DRAW", DRAW, 0, &draw},
    {"PUSHMEM", PUSHMEM, 1, &pushmem},
    {"POPMEM", POPMEM, 1, &popmem}
};

const char RegNames[reg_count][3]
{
    "AX",
    "BX",
    "CX",
    "DX"
};


#endif //COMMANDFUNC_H

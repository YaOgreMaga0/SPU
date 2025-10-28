#ifndef SPU_TYPES
#define SPU_TYPES

#include "../StackFunc/Stack.h"

const int horizontal = 40;
const int vertical = 40;
const int RAM_size = horizontal * vertical;
const int reg_count = 4;

const int signature_size = 2;

const short int count_of_commands = 21;

typedef enum
{
    HLT = 0,
    PUSH = 1,
    OUT = 2,
    ADD = 3,
    SUB = 4,
    MUL = 5,
    DIV = 6,
    PUSHR = 7,
    POPR = 8,
    JMP = 9,
    JB = 10,
    JBE = 11,
    JA = 12,
    JAE = 13,
    JE = 14,
    JNE = 15,
    CALL = 16,
    RET = 17,
    DRAW = 18,
    PUSHMEM = 19,
    POPMEM = 20,
} CommandCodes;

typedef struct
{
    int command_pointer;
    int code_commands_count;
    stack Calculations;
    int* commands;
    int registers[reg_count];
    int* Jumps;
    stack Returns;
    char* RAM;
} SPUMem;


typedef void (*FuncPointer)(SPUMem*);

typedef struct
{
    const char* Name;
    CommandCodes code;
    const int Arguments_count;
    FuncPointer func;
} command;

#endif //SPU_TYPES

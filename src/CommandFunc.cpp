#include "../src_h/CommandFunc.h"

void push(SPUMem* SPUMemory)
{
    int arg = SPUMemory->commands[SPUMemory->command_pointer];
    StackPush(&SPUMemory->Calculations, arg);
}

void out(SPUMem* SPUMemory)
{
    int value = StackPop(&SPUMemory->Calculations);
    printf("%d\n", value);
}

void add(SPUMem* SPUMemory)
{
    int value1 = StackPop(&SPUMemory->Calculations);
    int value2 = StackPop(&SPUMemory->Calculations);
    StackPush(&SPUMemory->Calculations, value1 + value2);
}

void sub(SPUMem* SPUMemory)
{
    int value1 = StackPop(&SPUMemory->Calculations);
    int value2 = StackPop(&SPUMemory->Calculations);
    StackPush(&SPUMemory->Calculations, value1 - value2);
}

void mul(SPUMem* SPUMemory)
{
    int value1 = StackPop(&SPUMemory->Calculations);
    int value2 = StackPop(&SPUMemory->Calculations);
    StackPush(&SPUMemory->Calculations, value1 * value2);
}

void div(SPUMem* SPUMemory)
{
    int value1 = StackPop(&SPUMemory->Calculations);
    int value2 = StackPop(&SPUMemory->Calculations);
    StackPush(&SPUMemory->Calculations, value1 / value2);
}

void pushr(SPUMem* SPUMemory)
{
    int reg = SPUMemory->commands[SPUMemory->command_pointer];
    SPUMemory->registers[reg] = StackPop(&SPUMemory->Calculations);
}

void popr(SPUMem* SPUMemory)
{
    int reg = SPUMemory->commands[SPUMemory->command_pointer];
    StackPush(&SPUMemory->Calculations, SPUMemory->registers[reg]);
}

void jmp(SPUMem* SPUMemory)
{
    int label_pointer = SPUMemory->commands[SPUMemory->command_pointer];
    SPUMemory->command_pointer = label_pointer;
}

void jb(SPUMem* SPUMemory)
{
    int label_pointer = SPUMemory->commands[SPUMemory->command_pointer];
    int value1 = StackPop(&SPUMemory->Calculations);
    int value2 = StackPop(&SPUMemory->Calculations);
    if(value1 > value2)
        SPUMemory->command_pointer = label_pointer;
}

void jbe(SPUMem* SPUMemory)
{
    int label_pointer = SPUMemory->commands[SPUMemory->command_pointer];
    int value1 = StackPop(&SPUMemory->Calculations);
    int value2 = StackPop(&SPUMemory->Calculations);
    if(value1 >= value2)
        SPUMemory->command_pointer = label_pointer;
}

void ja(SPUMem* SPUMemory)
{
    int label_pointer = SPUMemory->commands[SPUMemory->command_pointer];
    int value1 = StackPop(&SPUMemory->Calculations);
    int value2 = StackPop(&SPUMemory->Calculations);
    if(value1 < value2)
        SPUMemory->command_pointer = label_pointer;
}

void jae(SPUMem* SPUMemory)
{
    int label_pointer = SPUMemory->commands[SPUMemory->command_pointer];
    int value1 = StackPop(&SPUMemory->Calculations);
    int value2 = StackPop(&SPUMemory->Calculations);
    if(value1 <= value2)
        SPUMemory->command_pointer = label_pointer;
}

void je(SPUMem* SPUMemory)
{
    int label_pointer = SPUMemory->commands[SPUMemory->command_pointer];
    int value1 = StackPop(&SPUMemory->Calculations);
    int value2 = StackPop(&SPUMemory->Calculations);
    if(value1 == value2)
        SPUMemory->command_pointer = label_pointer;
}

void jne(SPUMem* SPUMemory)
{
    int label_pointer = SPUMemory->commands[SPUMemory->command_pointer];
    int value1 = StackPop(&SPUMemory->Calculations);
    int value2 = StackPop(&SPUMemory->Calculations);
    if(value1 != value2)
        SPUMemory->command_pointer = label_pointer;
}

void call(SPUMem* SPUMemory)
{
    int label_pointer = SPUMemory->commands[SPUMemory->command_pointer];
    StackPush(&SPUMemory->Returns, SPUMemory->command_pointer);
    SPUMemory->command_pointer = label_pointer;
}

void ret(SPUMem* SPUMemory)
{
    int ret = StackPop(&SPUMemory->Returns);
    SPUMemory->command_pointer = ret;
}

void draw(SPUMem* SPUMemory)
{
    for(int i = 0; i < vertical; i++)
    {
        for(int j = 0; j < horizontal; j++)
            printf("%c", SPUMemory->RAM[i * horizontal + j]);
        printf("\n");
    }
}

void pushmem(SPUMem* SPUMemory)
{
    int reg = SPUMemory->commands[SPUMemory->command_pointer];
    int value = SPUMemory->registers[reg];
    SPUMemory->registers[reg] = 0;
    SPUMemory->RAM[reg] = value;
}

void popmem(SPUMem* SPUMemory)
{
    int reg = SPUMemory->commands[SPUMemory->command_pointer];
    int value = SPUMemory->registers[reg];
    SPUMemory->registers[reg] = 0;
    StackPush(&SPUMemory->Calculations, value);
}

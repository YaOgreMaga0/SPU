#include "../src_h/SPU.h"

int main(const int argc, const char* argv[])
{
    if(argc < 1)
    {
        fprintf(stderr, "not enough arguments");
        return 1;
    }
    const char* FilenameIn = argv[1];
    SPUMem SPUMemory = {};
    SPUInit(&SPUMemory, FilenameIn);

    SPU(&SPUMemory);

    SPUDeInit(&SPUMemory);
    return 0;
}

int SPUInit(SPUMem* SPUMemory, const char* FilenameIn)
{
    FILE* Code = fopen(FilenameIn, "rb");
    if(Code == NULL)
    {
        fprintf(stderr, "incorrect input file\n");
        return -1;
    }

    SPUMemory->command_pointer = signature_size;
    SPUMemory->code_commands_count = CheckSignature(Code);
    StackCtor(&(SPUMemory->Calculations), stack_size);
    SPUMemory->commands = (int*)calloc((size_t)SPUMemory->code_commands_count, sizeof(int));
    StackCtor(&(SPUMemory->Returns), stack_size);
    fread(SPUMemory->commands, sizeof(int), (size_t)SPUMemory->code_commands_count, Code);
    fclose(Code);
    return 0;
}

int CheckSignature(FILE* Code)
{
    float assembler_version = 0;
    int PC = 0;
    fread(&assembler_version, sizeof(float), 1, Code);
    fread(&PC, sizeof(int), 1, Code);
    if(abs(assembler_version - spu_version) >= 0.1)
    {
        fprintf(stderr, "different versions of SPU and assembler\n");
        return -1;
    }
    return PC;
}

int SPUDeInit(SPUMem* SPUMemory)
{
    StackDtor(&(SPUMemory->Calculations));
    free(SPUMemory->commands);
    StackDtor(&(SPUMemory->Returns));
    return 0;
}


int SPU(SPUMem* SPUMemory)
{
    short comm = 0;
    for(;SPUMemory->command_pointer < SPUMemory->code_commands_count; SPUMemory->command_pointer++)
    {
        comm = *(short*)(SPUMemory->commands + sizeof(short) * (size_t)SPUMemory->command_pointer);
        fprintf(stderr, "%hd\n", comm);
        SPUMemory->command_pointer++;
        if(comm == HLT)
            return HLT;
        else
            Commands[comm].func(SPUMemory);
    }
    return 1;
}


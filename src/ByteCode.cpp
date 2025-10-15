#include "../src_h/ByteCode.h"

int ByteCode(char* filename)
{
    FILE* code = fopen(filename, "rb");
    if(code == NULL)
    {
        fprintf(stderr, "file open error");
        return 1;
    }

    stack numbers = {};
    StackCtor(&numbers, 10);
    int PC = 0;

    if(CheckSignature(code, &PC) == 1)
    {
        fprintf(stderr, "different versions of code and proccessor");
        return 1;
    }

    stack stk = {};
    StackCtor(&stk, PC);

    FillStack(code, PC, &stk);
    int pos = 0;
    while(true)
    {
        int arg = 0;
        int command = stk.data[pos];
        pos++;
        if(command == HLT)
            return 0;
        if(command == PUSH)
        {
            arg = stk.data[pos];
            pos++;
        }
        CommSwitch(command, &numbers, code, BIN, arg);
    }

    return 0;
}


int GetByte(FILE* fp)
{
    int byte = 0;
    fread(&byte, sizeof(int), 1, fp);
    return byte;
}

int FillStack(FILE* code, int PC, stack* stk)
{
    for(int i = 0; i < PC; i++)
    {
        int command = GetByte(code);
        StackPush(stk, command);
        if(command == PUSH)
        {
            int arg = 0;
            fread(&arg, sizeof(int), 1, code);
            StackPush(stk, arg);
        }
    }
    fclose(code);
    return 0;
}

int CheckSignature(FILE* code, int* PC)
{
    float SPUversion = 1.10;
    float CODEversion = 0;
    fread(&CODEversion, sizeof(float), 1, code);
    if(abs(CODEversion - SPUversion) > 0.001)
        return 1;
    fread(PC, sizeof(int), 1, code);
    return 0;
}

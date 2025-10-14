#include "../src_h/ByteCode.h"

int ByteCode(char* filename)
{
    int StackCapacity = FillStack(filename);
    return 0;
}


int GetByte(FILE* fp)
{
    int command = 0;
    fread(&command, sizeof(int), 1, fp);
    return command;
}

int FillStack(char* filename)
{
    stack stk = {};
    StackCtor(&stk, 10);
    FILE* fp = fopen(filename, "rb");
    for(int i = 0; i < 11; i++)
    {
        int command = GetByte(fp);
        fprintf(stderr, "%d \n", command);
        if(command == HLT)
        {
            fclose(fp);
            StackDtor(&stk);
            return 0;
        }
        CommSwitch(command, &stk, fp);
    }
    fclose(fp);
    StackDtor(&stk);
    return 1;
}

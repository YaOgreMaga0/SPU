#include "../src_h/disassembler.h"

int main(const int argc, const char* argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, "not enough arguments\n");
        return 1;
    }
    const char* FilenameIn = argv[1];
    const char* FilenameOut = argv[2];

    int code_commands_count = 0;
    int* Code = GetCode(FilenameIn, &code_commands_count);
    FillText(Code, FilenameOut, code_commands_count);
    return 0;
}

int* GetCode(const char* FilenameIn, int* code_commands_count)
{
    FILE* ByteCode = fopen(FilenameIn, "rb");
    if(ByteCode == NULL)
    {
        fprintf(stderr, "incorrect input file\n");
        return NULL;
    }
    float version = 0;
    fread(&version, sizeof(float), 1, ByteCode);
    fread(code_commands_count, sizeof(int), 1, ByteCode);
    int* Code = (int*)calloc((size_t)*code_commands_count, sizeof(int));
    fread(Code, sizeof(int), (size_t)*code_commands_count, ByteCode);
    fclose(ByteCode);
    return Code;
}

int FillText(int* Code, const char* FilenameOut, int PC)
{
    FILE* Text = fopen(FilenameOut, "wb");
    if(Text == NULL)
    {
        fprintf(stderr, "incorrect output file\n");
        return -1;
    }
    for(int i = 0; i < PC; i++)
    {
        fprintf(Text, "%s ", Commands[Code[i]].Name);
        if(Code[i] == PUSH)
        {
            i++;
            fprintf(Text, "%d\n", Code[i]);
        }
        else
        {
            fprintf(Text, "\n");
        }
    }
    fclose(Text);
    return 0;
}

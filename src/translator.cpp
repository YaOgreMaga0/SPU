#include "../src_h/translator.h"

int Translator(char* filenamein, char* filenameout)
{
    BufAndIndexInf Inf = FileReadAndMakeBuf(filenamein);

    if(Inf.buf == NULL || Inf.CntLines == -1 || Inf.index == NULL)
    {
        fprintf(stderr, "incorrect input file\n");
        MemoryFree(&Inf);
        return 1;
    }

    CleanBuf(Inf.index, Inf.CntLines);

    if(FillByteOutput(Inf.index, filenameout, Inf.CntLines) == 1)
    {
        printf("incorrect output file\n");
        MemoryFree(&Inf);
        return 1;
    }

    MemoryFree(&Inf);
    return 0;
}

int FillByteOutput(struct Line* index, const char* filename, int  len)
{
    assert(index != NULL);
    assert(filename != NULL);
    assert(len > 0);

    FILE* outfile = fopen(filename, "w");
    if(outfile == NULL)
    {
        fprintf(stderr, "Error file open\n");
        return 1;
    }

    for(int i = 0; i < len; i++)
    {
        const char* string = index[i].string;
        int command = TurnNameIntoCode(string);
        fwrite(&command, sizeof(int), 1, outfile);
        if(command == PUSH)
        {
            int arg = atoi(string + 4);
            fprintf(stderr, "%d ", arg);
            fwrite(&arg, sizeof(int), 1, outfile);
        }
    }
    fclose(outfile);
    return 0;
}

int CleanBuf(struct Line* index, int len)
{
    for(int i = 0; i < len; i++)
    {
        int len = index[i].len;
        for(int j = 0; j < len; j++)
        {
            if(index[i].string[j] == ' ' && strncmp(index->string, "PUSH", 4) != 0)
            {
                index[i].string[j] = '\0';
                break;
            }
            else if(index[i].string[j] == ';' && strncmp(index->string, "PUSH", 4) == 0)
            {
                index[i].string[j] = '\0';
                break;
            }
        }
    }
    return 0;
}

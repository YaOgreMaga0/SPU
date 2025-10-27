#include "StringFunc.h"
#include "IndexFunc.h"

int CountOfSymbols(const char* name)
{
    assert(name != NULL);

    struct stat fileinf = {};
    stat(name, &fileinf);
    int SymbolsCount = (int)fileinf.st_size;
    if(SymbolsCount == 0)
        return -1;

    return SymbolsCount;
}

int FillIndex(char* buf, Line* index, long long int count)
{
    if(buf == NULL || index == NULL || count == 0)
        return -1;

    int LineLen = 1, n = 0;
    for(int i = 0; i < count; i++)
    {
        if(*buf == '\0')
        {
            index[n].string = buf - (LineLen - 1);
            index[n].len = LineLen;
            n++;
            LineLen = 0;
        }
        LineLen++;
        buf += sizeof(char);
    }
    return 0;
}


int FillOutput(struct Line* index, const char* filename, int  len)
{
    assert(index != NULL);
    assert(filename != NULL);
    assert(len > 0);

    FILE* OutFile = fopen(filename, "wb");
    if(OutFile == NULL)
    {
        printf("Error file open\n");
        return 1;
    }

    for(int i = 0; i < len; i++)
    {
        const char* string = index[i].string;
        fputs(string, OutFile);
        fputs("\n", OutFile);
    }
    fclose(OutFile);
    return 0;
}


int FillBuf(const int SymbolsCount, FILE* text, char* buf)
{
    assert(text != NULL);
    assert(buf != NULL);
    if (SymbolsCount == -1)
        return -1;

    int CountOfLines = 0;
    fread(buf, (size_t)SymbolsCount, sizeof(char), text);
    for(long long int i = 0; i < SymbolsCount; i++)
    {
        if(buf[i] == '\n')
        {
            buf[i] = '\0';
            CountOfLines++;
        }
    }

    return CountOfLines;
}

#include "FileFunc.h"

Index MakeIndex(const char* filename)
{
    int SymbolsCount = CountOfSymbols(filename);
    if(SymbolsCount == -1)
        fprintf(stderr, "file is empty\n");

    char* buf = (char*)calloc((size_t)SymbolsCount, sizeof(char));
    if(buf == NULL)
        fprintf(stderr, "memory allocation error1\n");
    FILE* text = fopen(filename, "rb");
    if(text == NULL)
        fprintf(stderr, "Error file input open\n");

    int CntLines = FillBuf(SymbolsCount, text, buf);
    fclose(text);
    Line* index = (Line*)calloc((size_t)CntLines, sizeof(struct Line));
    if(index == NULL)
        fprintf(stderr, "memory allocation error2\n");

    FillIndex(buf, index, SymbolsCount);
    return {buf, index, CntLines};
}


void MemoryFree(Index *Inf)
{
    free(Inf->index);
    free(Inf->buf);
}

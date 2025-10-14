#include "FileFunc.h"

struct BufAndIndexInf FileReadAndMakeBuf(const char* filename)
{
    unsigned long long int symbolscnt = CountOfSymbols(filename); //get count of symbols from file
    if(symbolscnt == -1)
        printf("file is empty\n");

    char* buf = (char*)calloc(symbolscnt, sizeof(char)); //make buffer
    if(buf == NULL)
        printf("memory allocation error\n");

    FILE* text = fopen(filename, "r"); //open file
    if(text == NULL)
        printf("Error file input open\n");

    unsigned int linecount = FillBuf(symbolscnt, text, buf); //Fill buffer and return count of lines
    fclose(text); //close file

    Line* index = (Line*)calloc(linecount, sizeof(struct Line)); //make index struct array
    if(index == NULL)
        printf("memory allocation error\n");

    FillIndex(buf, index, symbolscnt - linecount);   //fill index array. subtract linecount because "\r" is deleted from buffer, but contained in symbolscnt

    return {buf, index, (int)linecount};
}


void MemoryFree(BufAndIndexInf *Inf)
{
    free(Inf->index);
    free(Inf->buf);
}

#ifndef STRINGFUNC_H
#define STRINGFUNC_H
#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <ctype.h>



typedef struct Line
{
    unsigned int len;
    char* string;
}Line;


int BackCompare(const void* a, const void* b);
int FrontCompare(const void* a, const void* b);
void MySort(struct Line* index, int len);
int StrCmpIgnorPunctuation(const Line* line1, const Line* line2, int mode);
void BubleQsort(void* begin, size_t count, size_t size, int(*CompFunc)(const void* a, const void* b));


#endif //STRINGFUNC_H

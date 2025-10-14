#include "StringFunc.h"

int BackCompare(const void* a, const void* b)
{
    assert(a != NULL);
    assert(b != NULL);

    const Line* str1 = (const Line*)(a);
    const Line* str2 = (const Line*)(b);

    return StrCmpIgnorPunctuation(str1, str2, -1);
}


int FrontCompare(const void* a, const void* b)
{
    assert(a != NULL);
    assert(b != NULL);

    const Line* str1 = (const Line*)a;
    const Line* str2 = (const Line*)b;

    return StrCmpIgnorPunctuation(str1, str2, 1);
}


void MySort(struct Line* index, int len)
{
    assert(index != NULL);
    assert(len > 0);
    for(int i = 1; i < len; i++)
    {
        for(int j = 0; j < len-i; j++)
        {
            const Line* line1 = index + j;
            const Line* line2 = index + j + 1;
            if(FrontCompare(line1, line2) != -1)
            {
                Line swap = index[j];
                index[j] = index[j + 1];
                index[j + 1] = swap;
            }
        }
    }
}

int StrCmpIgnorPunctuation(const Line* line1, const Line* line2, int mode)
{
    assert(line1 != NULL);
    assert(line2 != NULL);
    assert(abs(mode) == 1);

    int len1 = line1->len;
    int len2 = line2->len;
    char *char1 = line1->string;
    char *char2 = line2->string;
    if(mode == -1)
    {
        char1 += (len1 - 1);
        char2 += (len2 - 1);
    }
    while(len1 > 0 && len2 > 0)
    {
        while(!isalpha(*char1) && len1 > 0)
        {
            len1--;
            char1 += mode;
            if((int)(*char1) == 13 || (int)(*char1) == 10)
                return 0;
        }
        while(!isalpha(*char2) && len2 > 0)
        {
            len2--;
            char2 += mode;
            if((int)(*char2) == 13 || (int)(*char2) == 10)
                return 0;
        }
        if(tolower(*char1) > tolower(*char2))
            return 1;
        if(tolower(*char1) < tolower(*char2))
            return -1;
        char1 += mode;
        char2 += mode;
        len1--;
        len2--;
    }
    return 0;
}


void BubleQsort(void* begin, size_t count, size_t size, int(*CompFunc)(const void* a, const void* b))
{
    assert(begin != NULL);

    for(size_t i = 1; i < count; i++)
    {
        for(size_t j = 0; j < count - i; j++)
        {
            int res = CompFunc((void*)((size_t)begin + j * size), (void*)((size_t)begin + (j + 1) * size));
            if(res != -1 && res != 1 && res != 0)
            {
                printf("Incorrect comprator\n");
                i = count;
                j = 1;
            }
            if(res != -1)
            {
                for(size_t i = 0; i < size; i++)
                {
                    char swap = *((char*)((size_t)begin + j * size + i));
                    *((char*)((size_t)begin + j * size + i)) = *((char*)((size_t)begin + j * size + i + size));
                    *((char*)((size_t)begin + j * size + i + size)) = swap;
                }
            }
        }
    }
}

#include "../src_h/StackVerify.h"

int StackDump(stack* stk, int er, const char* filename, const int linen, const char* funcname)
{
    ErrorPos(filename, linen, funcname);
    ErrorPrint(stk, er);
    StackPrint(stk);
}

int StackVer(stack* stk, const char* filename, const int linen, const char* funcname)
{
    int er = NO_ERRORS;
    if(stk == NULL)
    {
        er = STACK_POINTER_IS_NULL;
        StackDump(stk, er, filename, linen, funcname);
        return er;
    }
    if(stk->size <= 0)
        er += NEGATIVE_SIZE;
    if(stk->capacity < 0)
        er += NEGATIVE_CAPACITY;
    if(stk->data == NULL)
        er += DATA_POINTER_IS_NULL;
    if((stk->capacity) > (stk->size))
    {
        er += STACK_IS_FULL;
        StackDump(stk, er, filename, linen, funcname);
        return er;
    }
    #ifdef WITHCANARY
    CanaryCheck(stk, &er);
    #endif //WITHCANARY
    if(er != 0)
        StackDump(stk, er, filename, linen, funcname);
    return er;
}

int ErrorPrint(stack* stk, int er)
{
    if(er != 0)
    {
        fprintf(stderr, "\n!ERROR!\n");
        if(er == STACK_POINTER_IS_NULL)
        {
            fprintf(stderr,"stack pointer is NULL\n");
            return STACK_POINTER_IS_NULL;
        }
        if(er & NEGATIVE_SIZE)
            fprintf(stderr, "size is not a positive integer(1)\n");
        if(er & NEGATIVE_CAPACITY)
            fprintf(stderr, "capacity is not a positive integer(2)\n");
        if(er & STACK_IS_FULL)
            fprintf(stderr, "capacity is greater than size(3)\n");
        if(er & DATA_POINTER_IS_NULL)
            fprintf(stderr, "data pointer is NULL(4)\n");
        if(er & BEGIN_CANARY_DIED)
            fprintf(stderr, "begin canary died(5)\n");
        if(er & END_CANARY_DIED)
            fprintf(stderr, "end canary died(6)\n");
        if(er & HASH_ERROR)
            fprintf(stderr, "hash error(7)\n");
    }
    return er;
}

int StackPrint(stack* stk)
{
    fprintf(stderr, "stack <%s>[%x]\n",type_name, stk);
    fprintf(stderr, "{\n    size = %d\n", stk->size);
    fprintf(stderr, "    capacity = %d\n", stk->capacity);
    fprintf(stderr, "data[%x]\n{\n", stk->data);
    for(int i = 1; i <= stk->capacity; i++)
    {
        fprintf(stderr, "[%d] = %d", i, stk->data[i + canary_size]);
        fprintf(stderr, "\n");
    }
    fprintf(stderr, "}\n}\n\n");
    return 0;
}

int ErrorPos(const char* filename, const int linen, const char* funcname)
{
    fprintf(stderr, "In file %s\n", filename);
    fprintf(stderr, "Line: %d\n", linen);
    fprintf(stderr, "Function:%s\n", funcname);
    return 0;
}

#ifdef WITHCANARY
int CanaryCheck(stack* stk, int* er)
{
    if(*stk->data != canary_value)
        *er += BEGIN_CANARY_DIED;
    if(*(stk->data + stk->size + 1) != canary_value)
        *er += END_CANARY_DIED;
}
#endif //WITHCANARY

int StackRealloc(stack* stk)
{
    stack_type* new_data = (stack_type*)realloc(stk->data,stk->size * 2 * sizeof(stack_type));
    if(new_data == NULL)
    {
        fprintf(stderr, "new mem allocation error");
        return STACK_IS_FULL;
    }
    stk->size *= 2;
    stk->data = new_data;
    #ifdef WITHCANARY
    MakeCanary(stk);
    #endif //WITHCANARY

    return 0;
}

#ifdef WITHHASH
long long int GetHash(stack* stk)
{
    long long int hash = 6952;
    for(int i = 0; i < stk->capacity; i++)
        hash = ((hash << 5) + hash) + stk->data[i];
    return hash;
}

int CheckHash(stack* stk)
{
    if(GetHash(stk) != stk->hash)
        return HASH_ERROR;
    return 0;
}
#endif //WITHHASH

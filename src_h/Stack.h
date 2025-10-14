#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

const char type_name[7] = "int";
typedef int stack_type;

#ifdef WITHCANARY
const int canary_value = 52;
const int canary_size = 4;
#else
const int canary_size = 0;
#endif //WITHCANARY

typedef struct
{
    stack_type* data;
    int size;
    int capacity;
    #ifdef WITHHASH
    long long int hash;
    #endif //WITHHASH
}stack;

typedef enum
{
    NO_ERRORS = 0,
    STACK_POINTER_IS_NULL = -1,
    NEGATIVE_SIZE = 1,
    NEGATIVE_CAPACITY = 2,
    STACK_IS_FULL = 4,
    DATA_POINTER_IS_NULL = 8,
    BEGIN_CANARY_DIED = 16,
    END_CANARY_DIED = 32,
    HASH_ERROR = 64,
}ErrCode;

#define StackVerify(stk) StackVer(stk, __FILE__, __LINE__, __FUNCTION__);

int StackDump(stack* stk, int er, const char* filename, const int linen, const char* funcname);
int StackVer(stack* stk, const char* filename, const int linen, const char* funcname);
int ErrorPrint(stack* stk, int er);
int StackPrint(stack* stk);
int ErrorPos(const char* filename, const int linen, const char* funcname);
int StackRealloc(stack* stk);
#ifdef WITHCANARY
int CanaryCheck(stack* stk, int* er);
#endif //WITHCANARY

#ifdef WITHHASH
long long int GetHash(stack* stk);
int CheckHash(stack* stk);
#endif //WITHHASH


int StackCtor(stack* stk, int size);
int StackDtor(stack* stk);
int StackPush(stack* stk, stack_type c);
stack_type StackPop(stack* stk);

#ifdef WITHCANARY
int MakeCanary(stack* stk);
#endif //WITHCANARY


#endif //STACK_H

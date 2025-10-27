#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char type_name[] = "int";
typedef int stack_type;
const int stack_size = 10;
const int poison_value = 123456789;
const long long int hash_value = 6952;

#ifdef WITHCANARY
const int canary_value = 52;
const size_t canary_size = 1;
#else
const size_t canary_size = 0;
#endif //WITHCANARY

typedef struct
{
    stack_type* data;
    int size;
    int capacity;
    #ifdef WITHHASH
    long long int hash;
    #endif //WITHHASH
} stack;

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
    POISON_ERROR = 128
} ErrCode;

#include "StackFunc.h"
#include "StackVerify.h"

#endif //STACK_H

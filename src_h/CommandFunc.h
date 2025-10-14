#ifndef CALCFUNC_H
#define CALCFUNC_H

#include <string.h>
#include <stdio.h>
#include "StackFunc.h"

typedef enum
{
    PUSH = 1,
    OUT = 2,
    ADD = 3,
    SUB = 4,
    MUL = 5,
    DIV = 6,
    HLT = 7
}command;

void CommSwitch(int comm, stack* stk, FILE* fp);
void push(stack*stk, FILE* fp);
void out(stack* stk);
void add(stack* stk);
void sub(stack* stk);
void mul(stack* stk);
void div(stack* stk);


#endif //CALCFUNC_H

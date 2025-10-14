#include "../src_h/CommandFunc.h"

void push(stack* stk, FILE* fp)
{
    stack_type arg = 0;
    fscanf(fp, "%d", &arg);
    StackPush(stk, arg);
}

void out(stack* stk)
{
    stack_type value = StackPop(stk);
    printf("%d ", value);
}

void add(stack* stk)
{
    stack_type value1 = StackPop(stk);
    stack_type value2 = StackPop(stk);
    StackPush(stk, value1 + value2);
}

void sub(stack* stk)
{
    stack_type value1 = StackPop(stk);
    stack_type value2 = StackPop(stk);
    StackPush(stk, value1 - value2);
}

void mul(stack* stk)
{
    stack_type value1 = StackPop(stk);
    stack_type value2 = StackPop(stk);
    StackPush(stk, value1 * value2);
}

void div(stack* stk)
{
    stack_type value1 = StackPop(stk);
    stack_type value2 = StackPop(stk);
    StackPush(stk, value1 / value2);
}

void CommSwitch(int comm, stack* stk, FILE* fp)
{
    if(comm == PUSH)
        push(stk, fp);
    if(comm == OUT)
        out(stk);
    if(comm == ADD)
        add(stk);
    if(comm == SUB)
        sub(stk);
    if(comm == MUL)
        mul(stk);
    if(comm == DIV)
        div(stk);
}


/*
switch(comm)


*/

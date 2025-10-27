#ifndef STACKFUNC_H
#define STACKFUNC_H

#include "Stack.h"

int StackCtor(stack* stk, int size);
int StackDtor(stack* stk);
int StackPush(stack* stk, stack_type c);
stack_type StackPop(stack* stk);
int StackRealloc(stack* stk);
int TurnToPoison(stack* stk);

#ifdef WITHCANARY
int MakeCanary(stack* stk);
#endif //WITHCANARY

#ifdef WITHHASH
long long int GetHash(stack* stk);
#endif //WITHHASH

#endif //STACKFUNC_H

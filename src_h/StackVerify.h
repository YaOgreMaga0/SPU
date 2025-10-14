#ifndef STACK_VERIFY_H
#define STACK_VERIFY_H

#include "Stack.h"

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

#endif //STACK_VERIFY_H

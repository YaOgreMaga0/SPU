#ifndef STACK_VERIFY_H
#define STACK_VERIFY_H

#include "Stack.h"

#define StackVerify(stk) StackVerifier(stk, __FILE__, __LINE__, __FUNCTION__);

int StackDump(stack* stk, int er, const char* filename, const int linen, const char* funcname);
int StackVerifier(stack* stk, const char* filename, const int linen, const char* funcname);
int ErrorPrint(int er);
int StackPrint(stack* stk);
int ErrorPos(const char* filename, const int linen, const char* funcname);
#ifdef WITHCANARY
int CanaryCheck(stack* stk, int* er);
#endif //WITHCANARY

#ifdef WITHHASH
int CheckHash(stack* stk);
#endif //WITHHASH

#endif //STACK_VERIFY_H

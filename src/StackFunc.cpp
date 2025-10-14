#include "../src_h/StackFunc.h"

int StackCtor(stack* stk, int size)
{
    if(stk == NULL)
    {
        ErrorPrint(stk, STACK_POINTER_IS_NULL);
        return STACK_POINTER_IS_NULL;
    }
    if(size <= 0)
    {
        fprintf(stderr, "Negative size");
        return NEGATIVE_SIZE;
    }
    stk->size = size;
    stk->capacity = 0;
    stk->data = (int*)calloc(size + 2 * canary_size, sizeof(stack_type)); //размер канарейки при любом типе стека кратен размеру элемента стека, поэтому не занимаюсь лишними проверками деления
    #ifdef WITHASH
    stk->hash = GetHash(stk);
    #endif //WITHHASH
    #ifdef WITHCANARY
    MakeCanary(stk);
    #endif //WITHCANARY
    return 0;
}

int StackDtor(stack* stk)
{
    if(stk == NULL)
        return STACK_POINTER_IS_NULL;
    stk->capacity = -1;
    stk->size = -1;
    free(stk->data);
    stk->data = NULL;
    #ifdef WITHHASH
    stk->hash = 0;
    #endif //WITHHASH
    return 0;
}

int StackPush(stack* stk, stack_type a)
{
    StackVerify(stk)
    if(stk->capacity < stk->size)
    {
        *(stk->data + stk->capacity + canary_size) = a;
        stk->capacity++;
        return 0;
    }
    else
    {
        if(StackRealloc(stk) == STACK_IS_FULL)
        {
            return STACK_IS_FULL;
        }
        else
        {
            *(stk->data + stk->capacity + canary_size) = a;
            stk->capacity++;
        }
    }
    StackVerify(stk)
}

stack_type StackPop(stack* stk)
{
    StackVerify(stk)
    stack_type c = *(stk->data + stk->capacity + canary_size - 1);
    *(stk->data + stk->capacity + canary_size - 1) = 0;
    stk->capacity--;
    StackVerify(stk)
    return c;
}

#ifdef WITHCANARY
int MakeCanary(stack* stk)
{
    *(stk->data) = canary_value;
    *(stk->data + stk->size + 1) = canary_value;
}
#endif //WITHCANARY

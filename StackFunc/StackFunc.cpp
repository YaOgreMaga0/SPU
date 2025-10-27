#include "Stack.h"

int StackCtor(stack* stk, int size)
{
    if(stk == NULL)
    {
        fprintf(stderr, "Stack Pointer is NULL");
        return STACK_POINTER_IS_NULL;
    }
    if(size <= 0)
    {
        fprintf(stderr, "Negative size");
        return NEGATIVE_SIZE;
    }
    stk->size = size;
    stk->capacity = 0;
    stk->data = (int*)calloc((size_t)size + 2 * canary_size, sizeof(stack_type)) + canary_size;
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
    TurnToPoison(stk);
    free(stk->data);
    stk->data = NULL;
    #ifdef WITHHASH
    stk->hash = 0;
    #endif //WITHHASH
    return 0;
}

int StackPush(stack* stk, stack_type ToPush)
{
    StackVerify(stk)
    if(stk->capacity < stk->size)
    {
        *(stk->data + stk->capacity + canary_size) = ToPush;
        stk->capacity++;
        return 0;
    }
    else
    {
        if(StackRealloc(stk) == STACK_IS_FULL)
            return STACK_IS_FULL;
        else
        {
            *(stk->data + stk->capacity + canary_size) = ToPush;
            stk->capacity++;
        }
    }
    StackVerify(stk)
    return 0;
}

stack_type StackPop(stack* stk)
{
    StackVerify(stk)
    stack_type value = *(stk->data + stk->capacity - 1);
    if(value == poison_value)
    {
        fprintf(stderr, "Popped poison value");
        return POISON_ERROR;
    }
    *(stk->data + stk->capacity - 1 ) = poison_value;
    stk->capacity--;
    StackVerify(stk)
    return value;
}

#ifdef WITHCANARY
int MakeCanary(stack* stk)
{
    *(stk->data) = canary_value;
    *(stk->data + stk->size + 1) = canary_value;
}
#endif //WITHCANARY

int StackRealloc(stack* stk)
{
    stack_type* new_data = (stack_type*)realloc(stk->data, (size_t)stk->size * 2 * sizeof(stack_type));
    if(new_data == NULL)
    {
        fprintf(stderr, "new memory allocation error");
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
    long long int hash = hash_value;
    for(int i = 0; i < stk->capacity; i++)
        hash = ((hash << 5) + hash) + stk->data[i];
    return hash;
}
#endif //WITHHASH

int TurnToPoison(stack* stk)
{
    for(int i = 0; i < stk->size; i++)
    {
        stk->data[i] = poison_value;
    }
    return 0;
}

#include <stddef.h>
#include "assert.h"
#include "mem.h"
#include "stack.h"

#define T stack_t

struct T {
    int count;
    struct elem {
        void *x;
        struct elem *link;
    } *head;
};

stack_t stack_new(void)
{
    T stk;

    NEW(stk);
    stk->count = 0;
    stk->head = NULL;
    return stk;
}

int stack_empty(T stk)
{
    assert(stk);
    return stk->count == 0;
}

void stack_push (T stk, void *x)
{
    struct elem *t;

    assert(stk);
    NEW(t);
    t->x = x;
    t->link = stk->head;
    stk->head = t;
    stk->count++;
}

void *stack_pop  (T stk)
{
    void *x;
    struct elem *t;

    assert(stk);
    assert(stk->count > 0);
    t = stk->head;
    stk->head = t->link;
    stk->count--;
    x = t->x;
    FREE(t);
    return x;
}

void stack_free (T *stk)
{
    struct elem *t, *u;

    assert(stk && *stk);
    for (t = (*stk->head); t; t = u) {
        u = t->link;
        FREE(t);
    }
    FREE(*stk);
}

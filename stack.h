#ifndef STACK_H_
#define STACK_H_

#define T stack_t

typedef struct T *T; // define stack_t a pointer.

extern T     stack_new  (void);
extern int   stack_empty(T stk);
extern void  stack_push (T stk, void *x);
extern void *stack_pop  (T stk);
extern void  stack_free (T *stk);

#endif


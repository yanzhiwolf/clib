#ifndef RING_H_
#define RING_H_

#define T ring_t
typedef struct T *T;

extern T    ring_new(void);
extern T    ring_ring(void *x, ...);
extern void ring_free(T *ring);
extern int  ring_length(T ring);
extern void *ring_get(T ring, int i);
extern void *ring_put(T ring, int i, void *x);
extern void *ring_add(T ring, int pos, void *x);
extern void *ring_addlo(T ring, void *x);
extern void *ring_addhi(T ring, void *x);
extern void *ring_remove(T ring, int i);
extern void *ring_remlo(T ring);
extern void *ring_remhi(T ring);
extern void *ring_rotate(T ring, int n);

#undef T
#endif

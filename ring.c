#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "assert.h"
#include "ring.h"
#include "mem.h"

#define T ring_t

struct T {
    struct node {
        struct node *llink, *rlink;
        void *value;
    } *head;
    int length;
};

/*macros*/
#define RING_NODE(ring, i, q)               \
{                                           \
    int n;                                  \
    q = ring->head;                         \
    if (i <= ring->length / 2)              \
        for (n = i; n-- > 0; )              \
            q = q->rlink;                   \
    else                                    \
        for (n = ring->length - i; n-- > 0) \
            q = q->llink;                   \
}

/*insert p to the left of q*/
#define INSERT_LEFT(p, q)                   \
{                                           \
        p->llink = q->llink;                \
        q->llink->rlink = p;                \
        p->rlink = q;                       \
        q->llink = p;                       \
}

#define DELETE_NODE(ring, q)                \
{
    q->llink->rlink = q->rlink;
    q->rlink->llink = q->llink;
    FREE(q);
    if (--ring->length == 0)
        ring->head = NULL;
}

/*functions*/
T ring_new(void)
{
    T ring;

    NEW0(ring);
    ring->head = NULL;
    return ring;
}

T ring_ring(void *x, ...)
{
    va_list ap;
    T ring = ring_new();

    va_start(ap, x);
    for ( ; x; x = va_arg(ap, void *))
        ring_addhi(ring, x);
    va_end(ap);
    return ring;
}

void ring_free(T *ring)
{
    struct node *p, *q;

    assert(ring && *ring);
    if ((p = (*ring)->head) != NULL) {
        int n = (*ring)->length;
        for ( ; n-- > 0; p = q) {
            q = p->rlink;
            FREE(p);
        }
    }
    FREE(*ring);
}

int  ring_length(T ring)
{
    assert(ring);
    return ring->length;
}

void *ring_get(T ring, int i)
{
    struct node *p;

    assert(ring);
    assert(i >= 0 && i < ring->length);
    RING_NODE(ring, i, p);
    return p->value;
}

void *ring_put(T ring, int i, void *x)
{
    struct node *q;
    void *prev;

    assert(ring);
    assert(i >= 0 && i < ring->length);
    RING_NODE(ring, i, q);
    prev = q->value;
    q->value = x;
    return prev;
}

void *ring_add(T ring, int pos, void *x)
{
    assert(ring);
    assert(pos >= -ring->length && pos <= ring->length+1);
    if (pos == 1 || pos == -ring->length) {
        return ring_addlo(ring, x);
    } else if (pos == 0 || pos == ring->length+1) {
        return ring_addhi(ring, x);
    } else {
        struct node *p, *q;
        int i = pos < 0 ? pos + ring->length : pos - 1;
        RING_NODE(ring, i, q);
        NEW(p);
        INSERT_LEFT(p, q);
        ring->length++;
        return p->value = x;
    }
    return NULL;
}

void *ring_addlo(T ring, void *x)
{
    assert(ring);
    ring_addhi(ring, x);
    ring->head = ring->head->llink;
    return x;
}

void *ring_addhi(T ring, void *x)
{
    struct node *p, *q;

    assert(ring);
    NEW(p);
    if ((q = ring->head) != NULL) {
        INSERT_LEFT(p, q);
    } else {
        ring->head = p->llink = p->rlink = p;
    }
    ring->length++;
    return p->value = x;
}

void *ring_remove(T ring, int i)
{
    struct node *q;

    assert(ring);
    assert(ring->length > 0);
    assert(i >= 0 && i < ring->length);
    RING_NODE(ring, i, q);
    if (i == 0)
        ring->head = ring->head->rlink;
    x = q->value;
    DELETE_NODE(ring, q);
    return x;
}

void *ring_remlo(T ring)
{
    assert(ring);
    assert(ring->length > 0);
    ring->head = ring->head->rlink;
    return ring_remhi(ring);
}

void *ring_remhi(T ring)
{
    struct node *q;
    void *x;

    assert(ring);
    assert(ring->length > 0);
    q = ring->head->llink;
    x = q->value;
    DELETE_NODE(ring, q);
    return x;
}

void *ring_rotate(T ring, int n)
{
    struct node *q;
    int i;

    assert(ring);
    assert(n >= -ring->length && n <= ring->length);
    if (n >= 0)
        i = n % ring->length;
    else
        i = n + ring->length;
    RING_NODE(ring, i, q);
    ring->head = q;
}


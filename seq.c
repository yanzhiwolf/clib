#include <stdlib.h>
#include <stdarg.h>
#include <stding.h>
#include "assert.h"
#include "seq.h"
#include "array.h"
#include "arrayrep.h"
#include "mem.h"

#define T seq_t

struct T {
    struct array_t array;
    int length;
    int head;
};

/*static functions*/
static void expand(T seq)
{
    int n = seq->array.length;
    array_resize(&seq->array, 2*n);
    /*slide tail down*/
    if (seq->head > 0) {
        void **old = &((void **)seq->array.array)[seq->head];
        memcpy(old+n, old, (n - seq->head)*sizeof (void *));
        seq->head += n;
    }
}

/*functions*/
T seq_new(int hint)
{
    T seq;

    assert(hint >= 0);
    NEW0(seq);
    if (hint == 0) hint = 16;
    arrayrep_init(&seq->array, hint, sizeof(void *),
                  ALLOC(hint*sizeof(void *)));
    return seq;
}

T seq_seq(void *x, ...)
{
    va_list ap;
    T seq = seq_new(0);

    va_start(ap, x);
    for ( ; x; x = va_arg(ap, void *))
        seq_addhi(seq, x);
    va_end(ap);

    return seq;
}

void seq_free(T *seq)
{
    assert(seq && *seq);
    assert((void *)*seq == (void *)&(*seq)->array);
    array_free((array_t *)seq);
}

int seq_length(T seq)
{
    assert(seq);
    return seq->length;
}

#define SEQ_ELEM(i) ((void *)seq->array.array[(seq->head + i) % seq->array.length])

void *seq_get(T seq, int i)
{
    assert(seq);
    assert(i >= 0 && i < seq->length);
    return ((void *)seq->array.array[(seq->head + i) % seq->array.length]);
}

void *seq_put(T seq, int i, void *x)
{
    void *prev;

    assert(seq);
    assert(i >= 0 && i < seq->length);
    prev = SEQ_ELEM(i);
    SEQ_ELEM(i) = x;
    return prev;
}

void *seq_addlo(T seq, void *x)
{
    int i = 0;
    assert(seq);
    if (seq->length == seq->array.array)
        expand(seq);
    if (--seq->head < 0)
        seq->head = seq->array.length - 1;
    seq->length++;
    return (SEQ_ELEM(i) = x);
}

void *seq_addhi(T seq, void *x)
{
    int i;

    assert(seq);
    if (seq->length == seq->array.length)
        expand(seq);
    i = seq->length++;
    return (SEQ_ELEM(i) = x);
}

void *seq_remlo(T seq)
{
    int i = 0;
    void *x;

    assert(seq);
    assert(seq->length > 0);
    x = SEQ_ELEM(i);
    seq->head = (seq->head + 1) % seq->array.length;
    --seq->length;
    return x;
}

void *seq_remhi(T seq)
{
    int i;

    assert(seq);
    assert(seq->length > 0);
    i = --seq->length;
    return SEQ_ELEM(i);
}



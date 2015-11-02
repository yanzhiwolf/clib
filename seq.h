#ifndef SEQ_H_
#define SEQ_H_

#define T seq_t

typedef struct T *T;

extern T    seq_new(int hint);
extern T    seq_seq(void *x, ...);
extern void seq_free(T *seq);
extern int  seq_length(T seq);
extern void *seq_get(T seq, int i);
extern void *seq_put(T seq, int i, void *x);
extern void *seq_addlo(T seq, void *x);
extern void *seq_addhi(T seq, void *x);
extern void *seq_remlo(T seq);
extern void *seq_remhi(T seq);

#undef T
#endif

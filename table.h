#ifndef TABLE_H_
#define TABLE_H_

#define T table_t
typedef struct T *T;

extern T    table_new(int hint, 
                      int cmp(const void *x, const void *y), 
                      unsigned hash(const void *key));
extern void table_free(T *table);

#undef T
#endif

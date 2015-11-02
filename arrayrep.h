#ifndef ARRAYREP_H_
#define ARRAYREP_H_

#define T array_t
struct T {
    int length;
    int size;
    char *array;
};

extern void arrayrep_init(T array, int length, 
                          int size, void *ary);

#endif


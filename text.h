#ifndef TEXT_H_
#define TEXT_H_

#include <stdarg.h>

#define T text_t
typedef struct text_t {
    int len;
    const char *str;
};

extern T     text_put(const char *str);
extern char *text_get(char *str, int size, T s);
extern T     text_box(const char *str, int len);
#undef T
#endif

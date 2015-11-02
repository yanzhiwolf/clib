#ifndef FMT_H_
#define FMT_H_
#include <stdarg.h>
#include <stdio.h>
#include "except.h"

#define T fmt_t
typedef void (*T) (int code,
                   va_list *app, 
                   int put(int c, void *cl), 
                   void *cl, 
                   unsigned char flags[256], 
                   int width, 
                   int precision);

extern char *fmt_flags;
extern const except_t fmt_overflow;

extern void fmt_fmt (int put(int c, void *cl), void *cl, const char *fmt, ...);
extern void fmt_vfmt(int put(int c, void *cl), void *cl, const char *fmt, va_list ap);
extern void fmt_print(const char *fmt, ...);                                // printf
extern void fmt_fprint(FILE *stream, const char *fmt, ...);                 // fprintf
extern int  fmt_sfmt (char *buf, int size, const char *fmt, ...);           // sprintf
extern int  fmt_vsfmt(char *buf, int size, const char *fmt, va_list ap);    // vsprintf
extern char *fmt_string(const char *fmt, ...);
extern char *fmt_vstring(const char *fmt, va_list ap);

extern T fmt_register(int code, T newcvt);

extern void fmt_putd(const char *str, 
                     int len, 
                     int put(int c, void *cl), 
                     void *cl, 
                     unsigned char flags[256], 
                     int width, 
                     int precision);

extern void fmt_puts(const char *str, 
                     int len, 
                     int put(int c, void *cl), 
                     void *cl, 
                     unsigned char flags[256], 
                     int width, 
                     int precision);

#undef T
#endif

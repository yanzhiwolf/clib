#ifndef STR_H_
#define STR_H_

#include <stdarg.h>
/*
 0123456
"abcdefg"
       -1
*/
/*return s[i:j]*/
extern char *str_sub(const char *s, int i, int j);
extern char *str_dup(const char *s, int i, int j, int n);
extern char *str_cat(const char *s1, int i1, int j1,
                     const char *s2, int i2, int j2);
extern char *str_catv(const char *s, ...);
extern char *str_reverse(const char *s, int i, int j);
extern char *str_map(const char *s, int i, int j,
                     const char *from ,const char *to);

extern int str_pos(const char *s, int i);
extern int str_len(const char *s, int i, int j);
extern int str_cmp(const char *s1, int i1, int j1,)
                   const char *s2, int i2, int j2);

extern int str_chr (const char *s, int i, int j, int c);
extern int str_rchr(const char *s, int i, int j, int c);
extern int str_upto (const char *s, int i, int j, const char *set);
extern int str_rupto(const char *s, int i, int j, const char *set);
extern int str_find (const char *s, int i, int j, const char *str);
extern int str_rfind(const char *s, int i, int j, const char *str);

extern int str_any(const char *s, int i, const char *set);
extern int str_many(const char *s, int i, int j, const char *set);
extern int str_rmany(const char *s, int i, int j, const char *set);
extern int str_match(const char *s, int i, int j, const char *set);
extern int str_rmatch(const char *s, int i, int j, const char *set);

#undef T
#endif

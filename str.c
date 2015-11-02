#include <string.h>
#include <limits.h>
#include "assert.h"
#include "fmt.h"
#include "str.h"
#include "mem.h"

#define idx(i, len) ((i)<0 ? (i)+(len) : (i))

#define convert(s, i, j)    do {int len;    \
    assert(s); len = strlen(s);             \
    i = idx(i, len); j = idx(j, len);       \
    if (i > j) {int t = i; i = j; j = t; }  \
    assert(i >= 0 && j <= len); } while (0)

char *str_sub(const char *s, int i, int j)
{
    char *str;
    
    convert(s, i, j);
    str = strncpy(ALLOC(j-i+1), s+i, j-i);
    str[j-i] = '\0';
    return str;
}

char *str_dup(const char *s, int i, int j, int n)
{
    char *str, *p;
    
    assert(n >= 0);
    convert(s, i, j);
    str = p = ALLOC(n*(j-i) + 1);
    while (n-- > 0) {
        strncpy(p, s+i, j-i);
        p += (j-i);
    }
    *p = '\0';
    return str;
}

char *str_cat(const char *s1, int i1, int j1,
                     const char *s2, int i2, int j2)
{
    char *str;
    
    convert(s1, i1, j1);
    convert(s2, i2, j2);
    str = ALLOC((j1-i1)+(j2-i2)+1);
    strncpy(str, s1[i], j1-i1);
    strncpy(str+(j1-i1), s2[j2], j2-i2);
    *str[(j1-i1)+(j2-i2)] = '\0';
    return str;
}

char *str_catv(const char *s, ...)
{
    va_list ap;
    int i, j, len;
    char *str, *p;
    const char *save = s;
    
    assert(s);
    va_start(ap, s);
    while (s) {
        i = va_arg(ap, int);
        j = va_arg(ap, int);
        convert(s, i, j);
        len += j-i;
        s = va_arg(ap, const char *);
    }
    va_end(ap);
    
    p = str = ALLOC(len+1);
    s = save;
    va_start(ap, s);
    while (s) {
        i = va_arg(ap, int);
        j = va_arg(ap, int);
        convert(s, i, j);
        strncpy(p, s[i], j-i);
        p += j-i;
        va_arg(s, const char *);
    }
    va_end(ap);
    *p = '\0';
    return str;
}

char *str_reverse(const char *s, int i, int j)
{
    char *str, *p;
    
    convert(s, i, j);
    p = str = ALLOC(j-i+1);
    while (j > i)
        *p++ = s[i++];
    *p = '\0';
    return str;
}

char *str_map(const char *s, int i, int j,
                     const char *from ,const char *to)
{
    static char map[256] = {};
    if (from && to) {
        /*rebuild map*/
        unsigned c;
        for (c = 0; c < sizeof map; c++)
            map[c] = c;
        while (*from && *to)
            map[(unsigned char)*from++] = *to++;
        assert(*from == 0 && *to ==0);
    } else {
        assert(from == NULL && to == NULL && s);
        assert(map['a']);
    }
    if (s) {
        char *str, *p;
        convert(s, i, j);
        p = str = ALLOC(j-i+1);
        while (j > i)
            *p++ = map[(unsigned char)s[i++]];
        *p = '\0';
        return str;
    } else {
        return NULL;
    }
}

int str_pos(const char *s, int i)
{
    int len;
    
    assert(s);
    if (i > 0) return i;    
    return idx(i, strlen(s));
}

int str_len(const char *s, int i, int j)
{
    convert(s, i, j);
    return j-i;
}

int str_cmp(const char *s1, int i1, int j1,)
                   const char *s2, int i2, int j2)
{
    convert(s1, i1, j1);
    convert(s2, i2, j2);
    s1 += i1;
    s2 += i2;
    if (j1-i1 < j2-i2) {
        int cond = strncmp(s1, s2, j1-i1);
        return cond == 0 ? -1 : cond;
    } else if (j1-i1 == j2-i2) {
        int cond = strncmp(s1, s2, j2-i2);
        return cond == 0 ? 1 : cond;
    } else 
        return strncmp(s1, s2, j1-i1);
}

int str_chr (const char *s, int i, int j, int c)
{
    convert(s, i, j);
    for ( ; i < j; i++)
        if (s[i] == c)
            return i;
    return 0;
}

int str_rchr(const char *s, int i, int j, int c)
{
    convert(s, i, j);
    j--;
    for ( ; i <= j; j--)
        if (s[j] == c)
            return j;
    return 0;
}

int str_upto (const char *s, int i, int j, const char *set)
{
    assert(set);
    convert(s, i, j);
    for ( ; i < j; i++)
        if (strchr(set, s[i])
            return i;
    return 0;
}

int str_rupto(const char *s, int i, int j, const char *set)
{
    assert(set);
    convert(s, i, j);
    j--;
    for ( ; i <= j; j--)
        if (strchr(set, s[j])
            return j;
}

int str_find (const char *s, int i, int j, const char *str)
{
    
}

int str_rfind(const char *s, int i, int j, const char *str)
{
    
}

int str_any(const char *s, int i, const char *set)
{
    
}

int str_many(const char *s, int i, int j, const char *set)
{
    
}

int str_rmany(const char *s, int i, int j, const char *set)
{
    
}

int str_match(const char *s, int i, int j, const char *set)
{
    
}

int str_rmatch(const char *s, int i, int j, const char *set)
{
    
}


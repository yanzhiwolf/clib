#include "fmt.h"

int main()
{
    int i = 10;
    float f = 14.564f;
    const char *s = "hello, world";
    //fmt_print("hello world!\n");
    //fmt_print("%5d, %3.9f\n", i, f);
    //printf("%0f\n", f);
    //fmt_print("%0f\n", f);

    /*
:%s:	    :hello, world:	    :hello, world:
:%10s:	    :hello, world:	    :hello, world:
:%.10s:	    :hello, wor:	    :hello, wor:
:%-10s:	    :hello, world:	    :hello, world:
:%.15s:	    :hello, world:	    :hello, world:
:%-15s:	    :hello, world   :	:hello, world:
:%15.10s:	:     hello, wor:	:     hello, wor:
:%-15.10s:	:hello, wor     :	:hello, wor:
    */

    printf(":%%s:\t", s);          printf(":%s:\t", s);          fmt_print(":%s:\n", s);
    printf(":%%10s:\t", s);        printf(":%10s:\t", s);        fmt_print(":%10s:\n", s); 
    printf(":%%.10s:\t", s);       printf(":%.10s:\t", s);       fmt_print(":%.10s:\n", s); 
    printf(":%%-10s:\t", s);       printf(":%-10s:\t", s);       fmt_print(":%-10s:\n", s); 
    printf(":%%.15s:\t", s);       printf(":%.15s:\t", s);       fmt_print(":%.15s:\n", s); 
    printf(":%%-15s:\t", s);       printf(":%-15s:\t", s);       fmt_print(":%-15s:\n", s); 
    printf(":%%15.10s:\t", s);     printf(":%15.10s:\t", s);     fmt_print(":%15.10s:\n", s); 
    printf(":%%-15.10s:\t", s);    printf(":%-15.10s:\t", s);    fmt_print(":%-15.10s:\n", s); 

    printf("%x, %o, %p\n", i, i, &i);
    fmt_print("%x, %o, %p\n", i, i, &i);
    return 0;
}

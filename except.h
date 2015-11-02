#ifndef EXCEPT_H_
#define EXCEPT_H_

#include <setjmp.h>

#define T except_t
typedef struct T {
    const char *reason;
} T;


typedef struct except_frame except_frame;
struct except_frame {
    except_frame *prev;
    jmp_buf       env;
    const char   *file;
    int           line;
    const T      *exception;
};

enum {
    except_entered = 0,
    except_raised,
    except_handled,
    except_finalized,
};

// point to the top of except_stack
extern except_frame *except_stack;


void except_raise(const T *e, const char *file, int line);



#define RAISE(e) except_raise(&(e), __FILE__, __LINE__)
#define RERAISE(e) except_raise(except_frame.exception, \
    except_frame.file, except_frame, line)

#define RETURN switch (except_stack = except_stack->prev, 0) default: return



#define TRY do {    \
    volatile int except_flag;               \
    except_frame frame;                     \
    frame.prev = except_stack;              \
    except_stack = &frame;                  \
    except_flag = setjmp(frame.env);        \
    if (except_flag == except_entered) {    \

#define EXCEPT(e)   \
    if (except_flag == except_entered)      \
        except_stack = except_stack->prev;  \
    } else if (frame_.exception == &(e))    \
        except_flag = except_handled;

#define ELSE        \
    if (except_flag == except_entered)      \
        except_stack = except_stack->prev;  \
    } else {                                \
        except_flag = except_handled;

#define FINALLY     \
    if (except_flag == except_entered)      \
        except_stack = except_stack->prev;  \
    } {                                     \
        if (except_flag == except_handled)  \
            except_flag = except_finalized;

#define END_TRY     \
    if (except_flag == except_entered)      \
        except_stack = except_stack->prev;  \
    } if (except_flag == except_raised)     \
        RERAISE;                            \
    } while (0)


#undef T
#endif

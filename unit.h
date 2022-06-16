#ifndef YUBEL_LIBRARY_H
#define YUBEL_LIBRARY_H

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>
#include "colors.h"

#define IS_OK "The actual value match true"
#define IS_KO "The actual value match false"
#define IS_EQUALS "The numbers are equals"
#define IS_NOT_EQUALS "The numbers are not equals"
#define IS_IDENTICAL "The strings are identical"
#define IS_NOT_IDENTICAL "The strings are different"
#define THEORY_IS_TRUE "The theory is true"
#define THEORY_IS_FALSE "The theory is false"
#define IS_DEF "The value has been defined successfully"
#define IS_NOT_DEF "The value has not been defined"
#define IS_EMPTY "The value is empty"
#define IS_NOT_EMPTY "The value is not empty"
#define IS_FULL "The value is at the maximum value"
#define IS_NOT_FULL "The value is not at the maximum value"
#define IS_NOT "The value is not equal to the expected value"
#define IS_NO_NOT "The value is equal to the expected value"
#define IS_IS "The value is equal to the expected value"
#define IS_NOT_IS "The value is not equal to the expected value"
#define PARADOX_IS_TRUE "The paradox is true"
#define PARADOX_IS_FALSE "The paradox is false"
#define IS_SUPERIOR "The value is superior to the expected value"
#define IS_NOT_SUPERIOR "The value is not superior to the expected value"
#define IS_INFERIOR "The value is inferior to the expected value"
#define IS_NOT_INFERIOR "The value is not inferior to the expected value"
#define IS_SUCCESSFUL "The exit status code is 0"
#define IS_NOT_SUCCESSFUL "The exit status code isn't 0"
#define IS_FAILED "The exit status code is 1"
#define IS_NOT_FAILED "The exit status code isn't 0"
#define CONTAINS "The actual value contains expected value"
#define NOT_CONTAINS "The actual value not contains the expected value"

extern bool before_all_called;
extern double assertions;
extern double failures;
extern int status;
extern char *pass;
extern void before_all(void);
extern void before(void);
extern void after(void);
extern void after_all(void);

#define repeat(input, count)          \
    for (int i = 0; i < count; i++)   \
    {                                 \
        fprintf(stdout, "%s", input); \
    }
#define immunity()                                                                                                                                                                                                                                                                               \
    fprintf(stdout, "\n\n%s[%s", FOREGROUND_WHITE, FOREGROUND_RESET);                                                                                                                                                                                                                            \
    if (failures)                                                                                                                                                                                                                                                                                \
    {                                                                                                                                                                                                                                                                                            \
        repeat("\033[1;32m#\033[030m", (assertions / (assertions / failures) * 100) / 2) repeat("\033[1;31m#\033[030m", (failures / (failures + assertions) * 100) / 2) fprintf(stdout, "\033[1;37m] [ \033[1;32m%0.f \033[1;31m %0.f\033[1,37m\033[1;37m ]\033[30m\n\n", assertions, failures); \
    }                                                                                                                                                                                                                                                                                            \
    else                                                                                                                                                                                                                                                                                         \
    {                                                                                                                                                                                                                                                                                            \
        repeat("\033[1;32m#", (assertions / (assertions + failures) * 100) / 2) fprintf(stdout, "\033[1;37m] [ \033[1;32m%0.f \033[1;31m%0.f \033[1;37m]\033[30m\n\n", assertions, failures);                                                                                                    \
    }                                                                                                                                                                                                                                                                                            \
    after_all();
#define check(test, s, f)                            \
    if (before_all_called == false)                  \
    {                                                \
        before_all();                                \
        before();                                    \
        before_all_called = true;                    \
    }                                                \
    else                                             \
    {                                                \
        before();                                    \
    }                                                \
    if (test)                                        \
    {                                                \
        assertions++;                                \
        echo(s, BACKGROUND_BLACK, FOREGROUND_GREEN); \
        status = EXIT_SUCCESS;                       \
    }                                                \
    else                                             \
    {                                                \
        failures++;                                  \
        status = EXIT_FAILURE;                       \
        echo(s, BACKGROUND_BLACK, FOREGROUND_RED);   \
    }                                                \
    after();                                         \
    if (status)                                      \
    {                                                \
        immunity();                                  \
        exit(status);                                \
    }

#define ok(actual) check((actual), IS_OK, IS_KO);
#define ko(actual) check(!(actual), IS_KO, IS_OK);
#define superior(actual, expected) check((actual) > expected, IS_SUPERIOR, IS_NOT_SUPERIOR);
#define inferior(actual, expected) check((actual) < expected, IS_INFERIOR, IS_NOT_INFERIOR);
#define successful(actual) check((actual) == EXIT_SUCCESS, IS_SUCCESSFUL, IS_NOT_SUCCESSFUL);
#define fail(actual) check((actual) == EXIT_FAILURE, IS_NOT_SUCCESSFUL, IS_SUCCESSFUL);
#define equals(actual, expected) check((actual) == (expected), IS_EQUALS, IS_NOT_EQUALS);
#define unequals(actual, expected) check((actual) != (expected), IS_EQUALS, IS_NOT_EQUALS);
#define identical(actual, expected) check(strcmp((actual), (expected)) == 0, IS_IDENTICAL, IS_NOT_IDENTICAL);
#define different(actual, expected) check(strcmp((actual), (expected)) != 0, IS_NOT_IDENTICAL, IS_IDENTICAL);
#define def(actual) check((actual) != NULL, IS_DEF, IS_NOT_DEF);
#define undef(actual) check((actual) == NULL, IS_NOT_DEF, IS_DEF);
#define empty(actual) check(strcmp((actual), "") == 0, IS_EMPTY, IS_NOT_EMPTY);
#define contains(expected,actual) check(strstr(actual,expected) !=NULL,CONTAINS,NOT_CONTAINS);

#define full(actual, max)                                     \
    if ((max))                                                \
    {                                                         \
        check(((actual) / (max)) == 1, IS_FULL, IS_NOT_FULL); \
    }
#define scenario(description, f)                          \
    echo(description, BACKGROUND_BLACK, FOREGROUND_CYAN); \
    f();
#define theory(description, expected, f)                  \
    echo(description, BACKGROUND_BLACK, FOREGROUND_CYAN); \
    check((expected) == (f()), THEORY_IS_TRUE, THEORY_IS_FALSE);
#define not(actual, expected) check(actual != expected, IS_NOT, IS_NO_NOT);
#define is(actual, expected) check(actual == expected, IS_IS, IS_NOT_IS);
#define paradox(description, actual, expected) \
    msg(description);                          \
    check((actual) != (expected), PARADOX_IS_TRUE, PARADOX_IS_FALSE);

#endif

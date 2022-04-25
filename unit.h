#ifndef YUBEL_LIBRARY_H
#define YUBEL_LIBRARY_H

#include "yugi.h"

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
#define IS_FULL "The value is at tye maximum value"
#define IS_NOT_FULL "The value is not at the maximum value"
#define IS_NOT "The value is not equal to the expected value"
#define IS_NO_NOT "The value is equal to the expected value"
#define IS_IS "The value is equal to the expected value"
#define IS_NOT_IS "The value is not equal to the expected value"

#define ok(actual) check((actual), IS_OK, IS_KO);
#define ko(actual) check(!(actual), IS_KO, IS_OK);
#define equals(actual, expected) check((actual) == (expected), IS_EQUALS, IS_NOT_EQUALS);
#define unequals(actual, expected) check((actual) != (expected), IS_EQUALS, IS_NOT_EQUALS);
#define identical(actual, expected) check(strcmp((actual), (expected)) == 0, IS_IDENTICAL, IS_NOT_IDENTICAL);
#define different(actual, expected) check(strcmp((actual), (expected)) != 0, IS_NOT_IDENTICAL, IS_IDENTICAL);
#define def(actual) check((actual) != NULL, IS_DEF, IS_NOT_DEF);
#define empty(actual) check(strcmp((actual), "") == 0, IS_EMPTY, IS_NOT_EMPTY);
#define full(actual, max)                                     \
    if ((max))                                                \
    {                                                         \
        check(((actual) / (max)) == 1, IS_FULL, IS_NOT_FULL); \
    };
#define scenario(description, f) \
    title(description);           \
    f();
#define theory(description, expected, f) title(description); check((expected) == (f()), THEORY_IS_TRUE, THEORY_IS_FALSE);
#define not(actual, expected) check(actual != expected, IS_NOT, IS_NO_NOT);
#define is(actual, expected) check(actual == expected, IS_IS, IS_NOT_IS);

#endif

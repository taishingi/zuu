#include "unit.h"

bool before_all_called = false;
unit u;

unit *scenario(const char *description, unit *(*f)(unit *u))
{
    echo(description, BACKGROUND_BLACK, FOREGROUND_CYAN);

    return u.check(f(&u), SCENARIO_IS_TRUE, SCENARIO_IS_FALSE);
}

unit *check(bool test, const char *s, const char *f)
{

    if (before_all_called == false)
    {
        before_all();
        before();
        before_all_called = true;
    }
    else
    {
        before();
    }
    if (test)
    {
        u.assertions++;
        echo(s, BACKGROUND_BLACK, FOREGROUND_GREEN);
        u.status = EXIT_SUCCESS;
    }
    else
    {
        u.failures++;
        u.status = EXIT_FAILURE;
        if (policy)
        {
            after();
            die(f);
        }
        else
        {
            echo(f, BACKGROUND_BLACK, FOREGROUND_RED);
            after();
        }
        if (u.status)
        {
            exit(u.immunity());
        }
    }
    return &u;
}

unit *ok(bool actual)
{
    return u.check(actual, IS_OK, IS_KO);
}
unit *ko(bool actual)
{
    return u.check(!actual, IS_KO, IS_OK);
}

unit *superior(int expected, int min)
{
    return u.check(expected > min, IS_SUPERIOR, IS_NOT_SUPERIOR);
}

unit *inferior(int expected, int max)
{
    return u.check(expected < max, IS_INFERIOR, IS_NOT_INFERIOR);
}

unit *equals(int expected, int actual)
{
    return u.check(expected == actual, IS_EQUALS, IS_NOT_EQUALS);
}
unit *unequals(int expected, int actual)
{
    return u.check(expected != actual, IS_EQUALS, IS_NOT_EQUALS);
}
unit *identical(const char *expected, const char *actual)
{
    return u.check(strcmp(expected, actual) == 0, IS_IDENTICAL, IS_NOT_IDENTICAL);
}

unit *different(const char *expected, const char *actual)
{
    return u.check(strcmp(expected, actual) != 0, IS_IDENTICAL, IS_NOT_IDENTICAL);
}

unit *def(void *p)
{
    return u.check(p != NULL, IS_DEF, IS_NOT_DEF);
}

unit *undef(void *p)
{
    return u.check(p == NULL, IS_DEF, IS_NOT_DEF);
}

unit *full(const char *actual)
{
    return u.check(strlen(actual) > 0, IS_NOT_EMPTY, IS_EMPTY);
}

unit *beetween(int actual, int min, int max)
{
    return u.check(actual < max && actual > min, IS_BEETWEEN, IS_NOT_BEETWEEN);
}
unit *empty(const char *actual)
{
    return u.check(strcmp(actual, "") == 0, IS_EMPTY, IS_NOT_EMPTY);
}

unit *contains(const char *needle, const char *actual)
{
    return u.check(strstr(actual, needle) != NULL, CONTAINS, NOT_CONTAINS);
}
unit *success(int (*code)(void))
{
    return u.check(code() == EXIT_SUCCESS, IS_NOT_FAILED, IS_FAILED);
}

unit *fail(int (*code)(void))
{
    return u.check(code() == EXIT_FAILURE, IS_FAILED, IS_NOT_FAILED);
}
unit *theory(const char *description, bool expected, bool (*f)(unit *u))
{
    puts(description);
    return u.check(expected == f(&u), THEORY_IS_TRUE, THEORY_IS_FALSE);
}

unit *Unit(const char *description)
{
    u.assertions = 0;
    u.failures = 0;
    u.status = EXIT_FAILURE;

    u.ok = &ok;
    u.ko = &ko;
    u.check = &check;
    u.contains = &contains;
    u.def = &def;
    u.empty = &empty;
    u.equals = &equals;
    u.fail = &fail;
    u.full = &full;
    u.identical = &identical;
    u.different = &different;
    u.inferior = &inferior;
    u.unequals = &unequals;
    u.scenario = &scenario;
    u.theory = &theory;
    u.beetween = &beetween;
    u.success = &success;
    u.undef = &undef;
    u.immunity = &immunity;
    puts(description);
    return &u;
}

int immunity(void)
{
    after_all();
    fprintf(stdout, "\n\nAssertions : \033[1;32m%0.f\033[1;37m\n\nFailures   : \033[1;31m%0.f\n\n\033[1;37mTotal      : \033[1;33m%0.f\033[30m\n\n", u.assertions, u.failures, u.assertions + u.failures);
    return u.status ? EXIT_FAILURE : EXIT_SUCCESS;
}
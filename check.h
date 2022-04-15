#ifndef YUBEL_CHECK_H
#define YUBEL_CHECK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

extern double success;
extern double failures;
extern int status;
extern char bar_success[FILENAME_MAX];
extern char bar_failure[FILENAME_MAX];
#define repeat(input, count)          \
    for (int i = 0; i < count; i++)   \
    {                                 \
        fprintf(stdout, "%s", input); \
    }
#define immunity()                                                                                                                                                                                                                                                                   \
    if (failures)                                                                                                                                                                                                                                                                    \
    {                                                                                                                                                                                                                                                                                \
        fprintf(stdout, "\n\033[1;37m[\033[30m");                                                                                                                                                                                                                                    \
        repeat("\033[1;32m#\033[030m", (success / (success / failures) * 100) / 3) repeat("\033[1;31m#\033[030m", (failures / (failures + success) * 100) / 3) fprintf(stdout, "\033[1;37m] [ \033[1;32m%0.f \033[1;31m %0.f\033[1,37m\033[1;37m ]\033[30m\n\n", success, failures); \
    }                                                                                                                                                                                                                                                                                \
    else                                                                                                                                                                                                                                                                             \
    {                                                                                                                                                                                                                                                                                \
        fprintf(stdout, "\n\n\033[1;37m[\033[30m");                                                                                                                                                                                                                                  \
        repeat("\033[1;32m#", (success / (success + failures) * 100) / 3) fprintf(stdout, "\033[1;37m] [ \033[1;32m%0.f \033[1;31m%0.f \033[1;37m]\033[30m\n\n", success, failures);                                                                                                 \
    }
#define check(test, s, f)                                                                      \
    if (test)                                                                                  \
    {                                                                                          \
        success++;                                                                             \
        fprintf(stdout, "\n\033[1;37m[  \033[1;32mOK\033[0;30m  \033[1;37m] %s\033[30m\n", s); \
        status = EXIT_SUCCESS;                                                                 \
        strcat(bar_success, "\033[1;32m#\033[030");                                            \
    }                                                                                          \
    else                                                                                       \
    {                                                                                          \
        failures++;                                                                            \
        fprintf(stderr, "\n\033[1;37m[  \033[1;31mKO\033[1;37m  ] %s\033[30m\n", f);           \
        strcat(bar_failure, "\033[1;31m#\033[30m");                                            \
        status = EXIT_FAILURE;                                                                 \
    }                                                                                          \
    usleep(100000);                                                                            \
    if (status)                                                                                \
    {                                                                                          \
        immunity();                                                                            \
        exit(status);                                                                          \
    };

#endif
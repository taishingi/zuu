#ifndef YUBEL_CHECK_H
#define YUBEL_CHECK_H

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "colors.h"
#include "unit.h"

extern bool before_all_called;
extern double assertions;
extern double failures;
extern int status;
extern char bar_success[FILENAME_MAX];
extern char bar_failure[FILENAME_MAX];
extern void before_all(void);
extern void before(void);
extern void after(void);
extern void after_all(void);
extern FILE *foh;

#define repeat(input, count)          \
    for (int i = 0; i < count; i++)   \
    {                                 \
        fprintf(stdout, "%s", input); \
    }
#define immunity()                                                                                                                                                                                                                                                                               \
    if (failures)                                                                                                                                                                                                                                                                                \
    {                                                                                                                                                                                                                                                                                            \
        fprintf(stdout, "\n\033[1;37m[\033[30m");                                                                                                                                                                                                                                                \
        repeat("\033[1;32m#\033[030m", (assertions / (assertions / failures) * 100) / 3) repeat("\033[1;31m#\033[030m", (failures / (failures + assertions) * 100) / 3) fprintf(stdout, "\033[1;37m] [ \033[1;32m%0.f \033[1;31m %0.f\033[1,37m\033[1;37m ]\033[30m\n\n", assertions, failures); \
    }                                                                                                                                                                                                                                                                                            \
    else                                                                                                                                                                                                                                                                                         \
    {                                                                                                                                                                                                                                                                                            \
        fprintf(stdout, "\n\n\033[1;37m[\033[30m");                                                                                                                                                                                                                                              \
        repeat("\033[1;32m#", (assertions / (assertions + failures) * 100) / 3) fprintf(stdout, "\033[1;37m] [ \033[1;32m%0.f \033[1;31m%0.f \033[1;37m]\033[30m\n\n", assertions, failures);                                                                                                    \
    }                                                                                                                                                                                                                                                                                            \
    after_all();
#define check(test, s, f)           \
    if (before_all_called == false) \
    {                               \
        before_all();               \
        before();                   \
        before_all_called = true;   \
    }                               \
    else                            \
    {                               \
        before();                   \
    }                               \
    if (test)                       \
    {                               \
        assertions++;               \
        success(s);                 \
        status = EXIT_SUCCESS;      \
    }                               \
    else                            \
    {                               \
        failures++;                 \
        danger(f);                  \
    }                               \
    after();                        \
    if (status)                     \
    {                               \
        immunity();                 \
        exit(status);               \
    };

int run(int argc, const char **argv);
bool found(const char *a, const char *b);
bool has(const char *x, const char *needle);
bool oh_execute_last_command(void);
FILE *get(const char *filename, const char *mode);
bool has_oh_files(int argc, const char **argv);
char *oh_file_path(const char *filename);
bool oh(const char *filename);
int oh_close();
bool is_oh(const char *filename);
bool oh_exec(char *cmd);
#endif

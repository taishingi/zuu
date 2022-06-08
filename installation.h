#ifndef INSTALLATION
#define INSTALLATION

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>

typedef struct installation installation;
struct installation
{
    installation *(*get)(const char *repo);
    installation *(*cd)(const char *directory);
    installation *(*make)(const char *command);
    installation *(*rm)(const char *data);
    installation *(*exist)(const char *filename);
    installation *(*download)(const char *filename);
    int (*run)(void);
};

int run(void);
installation *download(const char *filename);
installation *get(const char *repo);
installation *exist(const char *filename);
installation *cd(const char *directory);
installation *install(const char *description);
installation *make(const char *command);
installation *rm(const char *data);

#endif

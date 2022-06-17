#ifndef COLORS
#define COLORS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FORMAT_RESET "\033[0m"
#define FORMAT_BRIGHT "\033[1m"
#define FORMAT_DIM "\033[2m"
#define FORMAT_ITALIC "\033[3m"
#define FORMAT_UNDERSCORE "\033[4m"
#define FORMAT_BLINK "\033[1;40m\033[5m"
#define FORMAT_BLINK2 "\033[6m"
#define FORMAT_REVERSE "\033[7m"
#define FORMAT_HIDDEN "\033[8m"

#define FOREGROUND_RESET "\033[1;30m"
#define FOREGROUND_RED "\033[1;31m"
#define FOREGROUND_GREEN "\033[1;32m"
#define FOREGROUND_YELLOW "\033[1;33m"
#define FOREGROUND_BLUE "\033[1;34m"
#define FOREGROUND_MAGENTA "\033[1;35m"
#define FOREGROUND_CYAN "\033[1;36m"
#define FOREGROUND_WHITE "\033[1;37m"
#define FOREGROUND_CRIMSON "\033[1;38m"

#define BACKGROUND_BLACK "\033[1;40m"
#define BACKGROUND_RED "\033[1;41m"
#define BACKGROUND_GREEN "\033[1;42m"
#define BACKGROUND_YELLOW "\033[1;43m"
#define BACKGROUND_BLUE "\033[1;44m"
#define BACKGROUND_MAGENTA "\033[1;45m"
#define BACKGROUND_CYAN "\033[1;46m"
#define BACKGROUND_WHITE "\033[1;47m"
#define BACKGROUND_CRIMSON "\033[1;48m"
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define echo(message, background, foreground) fprintf(stdout, "%s%s%s%s\n", background, foreground, message, FORMAT_RESET);
#define msg(message) echo(message, BACKGROUND_BLACK, FOREGROUND_CYAN);
#define die(message)                                              \
    echo(message,FORMAT_BLINK, FOREGROUND_RED); \
    exit(1);

#endif

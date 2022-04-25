#ifndef COLORS
#define COLORS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FORMAT_RESET "\033[0m"
#define FORMAT_BRIGHT "\033[1m"
#define FORMAT_DIM "\033[2m"
#define FORMAT_ITALIC "\033[3m"
#define FORMAT_UNDERSCORE "\033[4m"
#define FORMAT_BLINK "\033[5m"
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

#define msg(message, background, foreground,icon) fprintf(stdout, "%s%s%s\n\n %s %s\n%s\n", FORMAT_BRIGHT, background, foreground, icon, message, FORMAT_RESET);
#define success(message) msg(message, BACKGROUND_GREEN, FOREGROUND_WHITE,"🗸");
#define title(message) msg(message, BACKGROUND_BLUE, FOREGROUND_WHITE,"≟");
#define danger(message) msg(message, BACKGROUND_RED, FOREGROUND_WHITE,"🟔");
#define alert(message) \
    danger(message);   \
    exit(1);
#define die(message) alert(message);
#define warning(message) msg(message, BACKGROUND_YELLOW, FOREGROUND_WHITE,"✴");
#define info(message) msg(message, BACKGROUND_CYAN, FOREGROUND_WHITE,"✵");
#define primary(message) msg(message, BACKGROUND_BLUE, FOREGROUND_WHITE,"🟍");
#define secondary(message) msg(message, BACKGROUND_WHITE, FOREGROUND_RESET,"⭒");
#define link(link) primary(link);
#endif

#include "check.h"

double success = 0;
double failures = 0;
int status = EXIT_FAILURE;
char bar_success[FILENAME_MAX];
char bar_failure[FILENAME_MAX];
bool before_all_called = false;

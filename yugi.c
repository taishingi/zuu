#include "yugi.h"

double assertions = 0;
double failures = 0;
int status = EXIT_FAILURE;
char bar_success[FILENAME_MAX];
char bar_failure[FILENAME_MAX];
bool before_all_called = false;

bool found(const char *a, const char *b)
{
    return strcmp(a, b) == 0;
}

bool has(const char *x, const char *needle)
{
    return strstr(x, needle) != NULL;
}
int run(int argc, const char **argv)
{

    for (int i = 0; i < argc; i++)
    {
        if (has(argv[i], ".c"))
        {
            char cmd[FILENAME_MAX];
            snprintf(cmd, FILENAME_MAX, "gcc %s -o debug -l yugi -l unit && ./debug", argv[i]);
            FILE *f = popen(cmd, "w");

            if (!f)
            {
                pclose(f);
                alert("Failed to start the compilation");
            }

            if (access("debug", F_OK) == 0)
            {
                remove("debug");
            }
            pclose(f);
            status = EXIT_SUCCESS;
        }
    }
    return status;
}
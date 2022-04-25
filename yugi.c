#include "yugi.h"

double assertions = 0;
double failures = 0;
int status = EXIT_FAILURE;
char bar_success[FILENAME_MAX];
char bar_failure[FILENAME_MAX];
bool before_all_called = false;
FILE *foh = NULL;

bool found(const char *a, const char *b)
{
    return strcmp(a, b) == 0;
}

bool has(const char *x, const char *needle)
{
    return strstr(x, needle) != NULL;
}

bool has_oh_files(int argc, const char **argv)
{
    for (int i = 0; i < argc; i++)
    {
        if (has(argv[i], "_oh.c"))
        {
            return true;
        }
    }
    return false;
}
FILE *get(const char *filename, const char *mode)
{
    foh = fopen(filename, mode);
    if (!foh)
    {
        fclose(foh);
        die("Failed to open the file");
    }
    return foh;
}
bool oh_execute_last_command(void)
{
    char filename[FILENAME_MAX];
    char *line;
    size_t len;
    snprintf(filename, FILENAME_MAX, "%s/.oh_history", getenv("HOME"));
    foh = get(filename,"r");
    fseek(foh, 0L, SEEK_END);
    int x = getline(&line, &len, foh);

    if (len > 0 && oh_close() && x)
    {
        return oh_exec(line);
    }
    die("We are not found history");
}
int oh_close()
{
    if (access("./debug", F_OK) == 0)
    {
        remove("./debug");
    }
    fclose(foh);
    return status;
}
char *oh_file_path(const char *filename)
{
    char *path =NULL;
    char *res = realpath(filename, path);
    if (res)
    {
        return path;
    }
    die("Failed to find the filename path");
}

bool oh_exec(char *cmd)
{
    bool s = false;
    FILE *c = popen(cmd, "w");
    if (!c)
    {
        status = EXIT_FAILURE;
        if (pclose(c) == -1)
        {
            die("Failed to close the command");
        }
    }
    else
    {
        s = true;
        status = EXIT_SUCCESS;
        if (pclose(c) == -1)
        {
            status = EXIT_FAILURE;
            die("Failed to close the command");
        }
    }
    return s;
}
bool oh(const char *filename)
{
    char cmd[PATH_MAX];
    snprintf(cmd, PATH_MAX, "gcc %s -o debug -l yugi -l unit && ./debug", oh_file_path(filename));
    return oh_exec(cmd);
}
bool is_oh(const char *filename)
{
    return strstr(filename, "_oh.c");
}
int run(int argc, const char **argv)
{
    if (has_oh_files(argc, argv))
    {

        for (int i = 1; i < argc; i++)
        {
            if (is_oh(argv[i]))
            {
                if (oh(argv[i]))
                {
                    status = EXIT_SUCCESS;
                }
                else
                {
                    status = EXIT_FAILURE;
                }
            }
        }
    }
    else if (oh_execute_last_command())
    {
        status = EXIT_SUCCESS;
    }
    return oh_close();
}
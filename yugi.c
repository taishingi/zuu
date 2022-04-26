#include "yugi.h"

double assertions = 0;
double failures = 0;
int status = EXIT_FAILURE;
char bar_success[FILENAME_MAX];
char bar_failure[FILENAME_MAX];
bool before_all_called = false;
FILE *foh = NULL;
char x[FILENAME_MAX];
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
    for (int i = 1; i < argc; i++)
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
char *oh_history_file(void)
{
    snprintf(x, FILENAME_MAX, "%s/.oh_history", getenv("HOME"));
    return x;
}
bool oh_execute_last_command(void)
{
    return oh_exec("yugi");
}
int oh_close()
{
    if (access("./debug", F_OK) == 0)
    {
        remove("./debug");
    }
    if (foh != NULL)
    {
        fclose(foh);
    }
    return status;
}
const char *oh_file_path(const char *filename)
{
    char *res = realpath(filename, x);
    return res != NULL ? x : "";
}

bool oh_exec(const char *cmd)
{
    bool s = false;
    FILE *c = popen(cmd, "w");

    if (!has(cmd, "yugi"))
    {
        FILE *save = get(oh_history_file(), "a+");
        if (cmd != NULL)
        {
            fprintf(save, "%s\n", cmd);
        }
        fclose(save);
    }

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
    char path[1024];

    char cmd[PATH_MAX];
    if (getcwd(path, 1024) == NULL)
    {
        die("Failed t found the current directory pathname");
    }
    snprintf(cmd, PATH_MAX, "gcc %s -o %s/specs/debug -l yugi -l unit", oh_file_path(filename), path);
    oh_exec(cmd);
    snprintf(cmd, PATH_MAX, "%s/specs/debug", path);
    return oh_exec(cmd);
}
bool is_oh(const char *filename)
{
    return strstr(filename, "_oh.c") != NULL;
}
int run(int argc, const char **argv)
{
    if (argc == 1)
    {
        if (oh_execute_last_command())
        {
            status = EXIT_SUCCESS;
        }
        return status;
    }

    if (argc == 2)
    {
        if (access(argv[1], F_OK) == 0)
        {
            goto run;
        }
        else
        {
            goto mode;
        }
    }
    if (argc > 2)
    {
        if(found(argv[1], "-w") && found(argv[2], "-t"))
        {
            snprintf(x, FILENAME_MAX, "yugi --watch -t %s", argv[3]);
            if (oh_exec(x))
            {
                status = EXIT_SUCCESS;
            }
        }
        goto end;
    }
run:
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
    return status;
mode:
    if (found(argv[1], "-w"))
    {
        if (oh_exec("yugi --watch"))
        {
            status = EXIT_SUCCESS;
        }
        else
        {
            die("failed to run the watch mode");
        }
        goto end;
    }
end:
    return status;
}
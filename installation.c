#include "installation.h"

installation i;
installation *download(const char *filename)
{
    char cmd[FILENAME_MAX];
    snprintf(cmd,FILENAME_MAX,"curl -fsSL %s",filename);
    return cd("/tmp")->make(cmd);
}
installation *install(const char *description)
{
    puts(description);
    i.get = &get;
    i.cd = &cd;
    i.make = &make;
    i.rm = &rm;
    i.run = &run;
    i.exist = &exist;
    i.download = &download;
    return &i;
}
installation *exist(const char *filename)
{
    cd("/tmp");             
    if (access(filename, F_OK))
    {
        puts("The filename has been found\n");
    }
    else
    {
        die("The filename has not been founded in the system\n");
    }
    return rm(filename);
}
installation *get(const char *repo)
{
    char cmd[FILENAME_MAX];
    snprintf(cmd, FILENAME_MAX, "git clone %s oh", repo);
    return cd("/tmp")->rm("oh")->make(cmd)->cd("oh");
}

installation *rm(const char *data)
{
    char cmd[FILENAME_MAX];
    snprintf(cmd, FILENAME_MAX, "rm -rf %s", data);
    system(cmd);
    return &i;
}
installation *make(const char *command)
{
    FILE *f = popen(command, "w");
    if (!f)
    {
        pclose(f);
        exit(EXIT_FAILURE);
    }
    pclose(f);
    return &i;
}

installation *cd(const char *directory)
{
    if (chdir(directory) == 0)
    {
        puts("The current directory has been changed successfully\n");
    }
    else
    {
        die("The current directory has not been changed\n");
    }
    return &i;
}

int run(void)
{
    return 0;
}
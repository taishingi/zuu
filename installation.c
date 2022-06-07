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
    sleep(1);
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
        sleep(1);
    }
    else
    {
        puts("The filename has not been founded in the system\n");
        sleep(1);
        exit(EXIT_FAILURE);
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
    sleep(1);
    return &i;
}

installation *cd(const char *directory)
{
    if (chdir(directory) == 0)
    {
        puts("The current directory has been changed successfully\n");
        sleep(1);
    }
    else
    {
        fprintf(stderr, "The current directory has not been changed\n");
        sleep(1);
        exit(EXIT_FAILURE);
    }
    return &i;
}

int run(void)
{
    return 0;
}
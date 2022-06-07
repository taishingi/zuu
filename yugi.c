#include "yugi.h"
char *lines;
char line[FILENAME_MAX];
long length(const char *file)
{
    FILE *f;
    long length;
    f = fopen(file, "rb");
    if (!f)
    {
        fprintf(stderr, "Failed o open the file\n");
        exit(EXIT_FAILURE);
    }
    fseek(f, 0, SEEK_END); /* on se place à 0 octets de la fin du fichier (SEEK_END) */
    length = ftell(f);     /* fournit la taille du fichier, car on est à la fin du fichier */
    fclose(f);
    return length;
}

char *parse(FILE *file,long length)
{
    lines = malloc(sizeof(lines) * sizeof(length) * length);
    while (fgets(line, FILENAME_MAX, file) != NULL)
    {
        strcat(lines, line);
    }
    fclose(file);
    free(lines);
    return lines;
}
int main(int argc, const char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Missing the filename parameter\n");
        exit(EXIT_FAILURE);
    }
    if (strstr(argv[1], ".c") != NULL)
    {
        fprintf(stdout, "Formating the %s source file...\n", argv[1]);
    }
    else if (strstr(argv[1], ".h") != NULL)
    {
        fprintf(stdout, "Formating the %s header file...\n", argv[1]);
    }
    else
    {
        fprintf(stderr, "The filename don't exist\n");
    }
    if (access(argv[0], F_OK) == 0)
    {
        fprintf(stdout, parse(fopen(argv[1], "r+"),length(argv[1])));
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
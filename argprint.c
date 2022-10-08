#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int i;
    char** arg;

    printf("argc: %d\n", argc);
    for (i = 0; i < argc; i++)
    {
        printf("Argument %d: %s\n", i, argv[i]);
    }

    printf("\nThe same via pointers....\n");
    i = 0;
    for (arg = argv; *arg; arg++)
    {
        printf("Argument %d: %s\n", i++, *arg);
    }
    exit(EXIT_SUCCESS);
}
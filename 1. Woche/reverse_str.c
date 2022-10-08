#include <stdio.h>
#include <stdlib.h>

#define MAXITEMS 10000

int main(int argc, char* argv[]) {
    FILE* in = stdin;

    if (argc > 2) {
        fprintf(stderr, "Usage:_%s_[<file>]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (argc == 2) {
        in = fopen(argv[1], "r");
        if (!in)
        {
            perror(argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    
    int i = 0;
    // char words[MAXITEMS][255];
    char** words = malloc(MAXITEMS * sizeof(char*));

    do {
        words[i] = malloc(255 * sizeof(char));
    } while (fgets(words[i], 255, in) && i++ < MAXITEMS);

    while (i >= 0) {
        fprintf(stdout, "%s", words[i--]);
        free(words[i + 1]);
    }

    if (in != stdin) {
        fclose(in);
    }

    exit(EXIT_SUCCESS);
}
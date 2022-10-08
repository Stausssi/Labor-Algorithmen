#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	FILE* in = stdin;

	if (argc > 2) {
		fprintf(stderr, "Usage:_%s_[<file>]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

    if (argc == 2)
    {
        in = fopen(argv[1], "r");
        if (!in)
        {
            perror(argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    /* Here: Read from in with (e.g.) fgets(), ... */
    if (in != stdin)
    {
        fclose(in);
    }
    exit(EXIT_SUCCESS);
}
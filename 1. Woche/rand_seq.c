#include <stdio.h>
#include <stdlib.h>

#define MAXNUM 1000

int main(int argc, char* argv[]) {
	if (argc > 2) {
		fprintf(stderr, "Usage:_%s_[<file>]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

    int max = 50;
	if (argc == 2) {
	    max = atoi(argv[1]);
	}

	for (int i = 0; i < max; i++) {
		int randInt = rand() % MAXNUM;
		fprintf(stdout, "%d\n", randInt);
	}

	exit(EXIT_SUCCESS);
}
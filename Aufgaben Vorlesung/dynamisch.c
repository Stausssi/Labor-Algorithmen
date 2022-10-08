//
// Created by Simon on 28.05.2020.
//
#include <stdio.h>

#define dyn_n 18

int bruteForce(int n) {
    int steps = 0;

    while (n > 1) {
        n -= 1;
        steps++;

        if (n % 2 == 0) {
            n /= 2;
            steps++;
        }

        if (n % 3 == 0) {
            n /= 3;
            steps++;
        }
    }

    return steps;
}

int greedy(int n) {
    int steps = 0;

    while (n > 1) {
        while (n % 3 == 0) {
            n /= 3;
            steps++;
        }

        if (n == 1) break;

        if (n % 2 == 0)
            n /= 2;
        else
            n--;

        steps++;
    }

    return steps;
}

int main(void) {
    fprintf(stdout, "Anzahl der Schritte mit Brute-Force: %d\n", bruteForce(dyn_n));
    fprintf(stdout, "Anzahl der Schritte mit greedy: %d", greedy(dyn_n));
}
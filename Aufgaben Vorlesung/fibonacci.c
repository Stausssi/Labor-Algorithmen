#include <stdio.h>

#define fib_n 164

long long fibonacci_rec(int n) {
    if (n == 1 || n == 2)
        return 1;
    else
        return fibonacci_rec(n - 1) + fibonacci_rec(n - 2);
}

long long fibonacci_rec_improved(int n) {
    static long long fib[fib_n + 1] = {0};

    if (n == 1 || n == 2)
        return 1;
    else if (fib[n] == 0)
        fib[n] = fibonacci_rec_improved(n - 1) + fibonacci_rec_improved(n - 2);

    return fib[n];
}

long long fibonacci_iter(int n) {
    long long a = 0;
    long long b = 1;
    long long temp;
    for (int i = 1; i <= n; ++i) {
        temp = a;
        a = b;
        b += temp;
    }

    return a;
}

int main(int argc, char *argv[]) {
//    fprintf(stdout, "Fibonacci von %d: %lli (Rekursiv)", fib_n, fibonacci_rec(fib_n));
//    fprintf(stdout, "\n");
    fprintf(stdout, "Fibonacci von %d: %lli (Rekursiv, Improved)", fib_n, fibonacci_rec_improved(fib_n));
    fprintf(stdout, "\n");
    fprintf(stdout, "Fibonacci von %d: %lli (Iterativ)", fib_n, fibonacci_iter(fib_n));
}
#include<stdio.h>

void print_fibonacci_to(int n) {

    if (n <= 0) {

        printf("{}");
        return;

    } else if (n == 1) {

        printf("{1}");
        return;
    }

    printf("{1, ");

    unsigned long long fib = 1; // int overflows faster ...
    unsigned long long last_fib = 0;

    for (int i = 0; i < n - 1; i++) {

        unsigned long long j = last_fib;
        last_fib = fib;
        fib = j + fib;

        if (i != n - 2)
            printf("%llu, ", fib);
        else
            printf("%llu", fib);
    }

    printf("}");
}

int main() {

    int n = 32;
    print_fibonacci_to(n);

    return 0;
}
#include<stdio.h>

#define u64 unsigned long long

void print_is_prime(u64 num) {

    if (num % 2 == 0) {
        printf(": false\n");
        return;
    }

    u64 range = num;
    int inc = 1;

    for (u64 i = 3; i < range; i+=2) {

        if (num % i == 0) {
            printf(": false\n");
            return;
        }

        range = num / i;
    }

    printf(": true\n");
}

int main() {

    u64 input[] = {31, 86, 94, 97, 796, 797, 301, 3};

    for (int i = 0; i < sizeof(input) / sizeof(u64); i++) {
        printf("%llu", input[i]);
        print_is_prime(input[i]);
    }

    return 0;
}
#include<stdio.h>

void print_binary(int num) {

    printf("%d: ", num);

    int bin[64] = {0};
    int i = 0;

    for (;num;) {
        bin[i++] = num & 1;
        num >>= 1;
    }

    for (--i; i >= 0; i--) {
        printf("%d", bin[i]);
    }

    printf("\n");
}

int main() {

    int input[] = {
        20,
        81,
        9172
    };

    for (int i = 0; i < sizeof(input) / sizeof(int); i++) {
        print_binary(input[i]);
    }

    return 0;
}
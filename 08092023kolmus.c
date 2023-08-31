#include<stdio.h>

int main() {

    int input = 19;
    long long unsigned factorial = 1;

    for (; input > 0; input--) {

        factorial *= input;
        
        if (input != 1) {
            printf("%d x ", input);
        } else {
            printf("%d = %llu", input, factorial);
        }
        
    }

    return 0;
}
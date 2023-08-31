#include<stdio.h>
#include<stdlib.h>

int least_common_divisor(int a, int b) {

    int div = 2;

    while (div <= a && div <= b) {
        
        if (a % div == 0 && b % div == 0)
            return div;
        
        div++;
    }

    return 1;
}

int main() {

    int num1 = 96;
    int num2 = 189;

    int div = least_common_divisor(abs(num1), abs(num2));

    if (div != 1)
        printf("%d", div);
    else 
        printf("%d and %d don't have any divisors in common!", num1, num2);

    return 0;
}
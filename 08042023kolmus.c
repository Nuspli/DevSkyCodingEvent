#include<stdio.h>

int is_prime(int num) {

    for (int i = 2; i < num; i++) {
        if (num % i == 0)
            return 0;
    }

    return 1;
}

int get_prime_factors(int num, int *factors) {

    if (is_prime(num)) {
        factors[0] = num;
        return 1;
    }

    int p = 0;

    while (!is_prime(num)) {

        for (int i = 2; i < num; i++) {

            if (is_prime(i) && (num % i == 0)) {
                factors[p++] = i;
                num /= i;
                break;
            }
        }
    }

    factors[p++] = num;

    return p;
}

void print_array(int arr[], int arr_size) {

    printf("{");

    for (int i = 0; i < arr_size; i++) {
        if (i != arr_size - 1)
            printf("%d, ", arr[i]);
        else
            printf("%d", arr[i]);
    }

    printf("}");
}

int main() {

    int input = 6748;

    int primeFactors[100];
    int amount = get_prime_factors(input, &primeFactors[0]);

    print_array(primeFactors, amount);

    return 0;
}
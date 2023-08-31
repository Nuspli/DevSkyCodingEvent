#include<stdio.h>

void swap(char *c1, char *c2) {

    char t = *c1;
    *c1 = *c2;
    *c2 = t;
}

void print_permutations(char *arr, int left, int right) {

    if (left == right) {
        printf("%s\n", arr);

    } else {

        for (int i = left; i <= right; i++) {

            swap(arr + left, arr + i);

            print_permutations(arr, left + 1, right);
        }
    }
    
}

int main() {

    char input1[3] = "AB";
    char input2[4] = "CDE";
    char input3[5] = "FGHJ";

    print_permutations(input1, 0, sizeof(input1) / sizeof(char) - 2);
    printf("\n");
    print_permutations(input2, 0, sizeof(input2) / sizeof(char) - 2);
    printf("\n");
    print_permutations(input3, 0, sizeof(input3) / sizeof(char) - 2);
    printf("\n");

    return 0;
}
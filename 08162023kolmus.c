#include<stdio.h>

void swap(int *x, int *y) {

    int t = *x;
    *x = *y;
    *y = t;
}

void bubble_sort(int *arr, int arrLen) {

    int sorted = 0;

    for (int n = 0; !sorted; n++) {

        sorted = 1;

        for (int i = 0; i < arrLen - n - 1; i++) {
            if (arr[i] > arr[i+1]) {
                sorted = 0;
                swap(arr+i, arr+i+1);
            }
        }
    }

}

void print_array(int *arr, int arrLen) {

    printf("{");

    for (int i = 0; i < arrLen; i++) {

        printf("%d", arr[i]);

        if (i != arrLen - 1) {
            printf(", "); 
        }
    }

    printf("}");
}

int main() {

    int input[] = {
        987, 234, 712, 86, 453, 129, 578, 938, 192, 601, 387, 920, 76, 834, 250, 439, 671, 163, 567, 314, 728, 509, 103, 891, 675, 482, 945, 541, 200, 887, 912, 367, 680, 756, 122, 895, 318, 987, 231, 777, 489, 645, 123, 987, 294, 535, 897, 681, 786, 192
    };

    bubble_sort(input, sizeof(input) / sizeof(int));

    print_array(input, sizeof(input) / sizeof(int));

    return 0;
}
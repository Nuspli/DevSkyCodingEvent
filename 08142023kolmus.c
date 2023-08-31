#include<stdio.h>
#define UP 1

int count(int direction, int from, int increment) {

    int i = from;

    if (direction == UP) {
        for (; i <= 100; i += increment) {
            printf("%d ", i);
        }
        i -= increment;
        
    } else {
        for (; i >= 0; i -= increment) {
            printf("%d ", i);
        }
        i += increment;
    }

    printf("\n");
    return i;
}

int main() {

    int start = 0;

    for (int i = 10; i > 0; i--) {
        start = count(i % 2 == 0, start, i);
    }

    return 0;
}
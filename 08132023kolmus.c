#include<stdio.h>
#include<stdlib.h>

int main() {

    long red, blue, green;
    char input[32];
    char *p, *p1, *p2;

    printf("enter red value: ");
    fgets(&input[0], 32, stdin);

    red = strtol(&input[0], &p, 10);
    fflush(stdin);

    printf("enter blue value: ");
    fgets(&input[0], 32, stdin);

    blue = strtol(&input[0], &p1, 10);
    fflush(stdin);

    printf("enter green value: ");
    fgets(&input[0], 32, stdin);
    printf("\n");

    green = strtol(&input[0], &p2, 10);
    fflush(stdin);

    if (red >= blue && red >= green) {
        red--;

    } else if (blue >= red && blue >= green) {
        blue--;

    } else {
        green--;
    }

    int sum = red + blue + green;
    printf("red: %.2f%% ", (float)(100) * (float)(red) / (float)(sum));
    printf("blue: %.2f%% ", (float)(100) * (float)(blue) / (float)(sum));
    printf("green: %.2f%%\n", (float)(100) * (float)(green) / (float)(sum));

    return 0;
}
#include<stdio.h>
#include<stdlib.h>

#define row_1_has_three_of(arr, x) (arr[0][0] == x && arr[0][1] == x && arr[0][2] == x)
#define row_2_has_three_of(arr, x) (arr[1][0] == x && arr[1][1] == x && arr[1][2] == x)
#define row_3_has_three_of(arr, x) (arr[2][0] == x && arr[2][1] == x && arr[2][2] == x)

#define column_1_has_three_of(arr, x) (arr[0][0] == x && arr[1][0] == x && arr[2][0] == x)
#define column_2_has_three_of(arr, x) (arr[0][1] == x && arr[1][1] == x && arr[2][1] == x)
#define column_3_has_three_of(arr, x) (arr[0][2] == x && arr[1][2] == x && arr[2][2] == x)

#define diagonal_1_has_three_of(arr, x) (arr[0][0] == x && arr[1][1] == x && arr[2][2] == x)
#define diagonal_2_has_three_of(arr, x) (arr[0][2] == x && arr[1][1] == x && arr[2][0] == x)

#define has_3_connected(arr, x) ( \
    row_1_has_three_of(arr, x) || row_2_has_three_of(arr, x) || row_3_has_three_of(arr, x) || \
    column_1_has_three_of(arr, x) || column_2_has_three_of(arr, x) || column_3_has_three_of(arr, x) || \
    diagonal_1_has_three_of(arr, x) || diagonal_2_has_three_of(arr, x)\
)

int get_game_status(int arr[3][3]) {

    int one = 0;
    int two = 0;

    one += has_3_connected(arr, 1);

    two += 2 * has_3_connected(arr, 2);

    if (one + two == 3) {
        printf("invalid input! there can only be one winner!\n");
        exit(1);
    }

    return one + two;
}


int main() {

    int input[][3][3] = {
        {
        {1,0,2},
        {1,2,0},
        {1,0,0}
        }, {
        {1,1,2},
        {2,1,0},
        {2,0,1}
        }, {
        {2,1,2},
        {1,1,2},
        {1,2,1}
        }, {
        {2,1,1},
        {2,2,2},
        {1,1,0}
        }
    };

    int inputSize = sizeof(input) / sizeof(input[0]);

    for (int i = 0; i < inputSize; i++) {
        printf("%d\n", get_game_status(input[i]));
    }

    return 0;
}
#include<stdio.h>
#include<wchar.h>
#include<locale.h>

#define MAXNAME 32

void swap(wchar_t **x, wchar_t **y) {
    wchar_t *t = *x;
    *x = *y;
    *y = t;
}

int is_later(wchar_t *c1, wchar_t *c2) {
    return wcscmp(c1, c2) > 0;
}

void bubble_sort(wchar_t *arr[], int arrLen) {
    int sorted = 0;

    for (int n = 0; !sorted; n++) {
        sorted = 1;

        for (int i = 0; i < arrLen - n - 1; i++) {
            if (is_later(arr[i], arr[i+1])) {
                sorted = 0;
                swap(&arr[i], &arr[i+1]);
            }
        }
    }
}

void print_string_array(wchar_t *arr[], int arrLen) {
    printf("{");

    for (int i = 0; i < arrLen; i++) {
        wprintf(L"\"%ls\"", arr[i]);

        if (i != arrLen - 1) {
            printf(", ");
        }
    }

    printf("}");
}

int main() {

    setlocale(LC_ALL, "");

    wchar_t *input[] = {
        L"Alex Meier",
        L"Christian Schneider",
        L"Juri Wagner",
        L"Jona Müller",
        L"Sophie Weber",
        L"Lasse Müller",
        L"Sophie Schneider",
        L"Merle Köhler",
        L"Billy Becker",
        L"Luis Meister",
        L"Juri Fischer",
        L"Luisa Becker",
        L"Leonard Meier",
        L"Johanna Schmidt",
        L"Johannes Schmidt",
        L"Luis Fischer"
    };

    int inputSize = sizeof(input) / sizeof(input[0]);

    bubble_sort(input, inputSize);

    print_string_array(input, inputSize);

    return 0;
}

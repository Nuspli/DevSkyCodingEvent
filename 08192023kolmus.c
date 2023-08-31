#include <stdio.h>
#include <string.h>

int is_anagram(char *s1, char *s2) {

    int n = strlen(s1);

    if (n == strlen(s2)) {
        
        for (int i = 0; i < n; i++) {
            if (strchr(s1, s2[i]) == NULL) {
                return 0;
            }
        }

        return 1;
    }

    return 0;
}

void get_anagrams(char *arr[], int arrLen, int *printed) {

    int f = 0;
    printf("{");

    for (int i = 0; i < arrLen; i++) {

        int found = f;

        if (!printed[i]) {

            for (int j = i+1; j < arrLen; j++) {

                if (is_anagram(arr[i], arr[j])) {
                    found += 1;

                    if (!printed[i]) {
                        if (f != 0) {
                            printf(", ");
                        }
                        printf("{\"%s\"", arr[i]);
                        printed[i] = 1;
                    }

                    printf(", \"%s\"", arr[j]);
                    printed[j] = 1;
                }
            }

            if (found >= f + 1) {
                printf("}");
            }
        }

        f = found;
    }

    printf("}\n");
}

int main() {

    char *input[] = {"silent", "listen", "debit", "bed", "credit", "act", "trace", "race", "care", "evil", "vile", "arc", "grab", "barg", "man", "nam", "debit", "act", "evil", "man", "grab", "silent", "trace"};
    int inputSize = sizeof(input) / sizeof(input[0]);
    int printed[inputSize];

    for (int i = 0; i < inputSize; i++) {
        printed[i] = 0;
    }

    get_anagrams(input, inputSize, printed);

    return 0;
}
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct info_t {
    int iFirst;
    int nFirst;
    int iSecond;
    int nSecond;
    int iThird;
    int nThird;
} info_t;

void read_file(FILE *file, char *input, int *maxIn) {

    char c;
    int i = 0;

    while ((c = fgetwc(file)) != EOF) {

        input[i++] = c;

        if (i > *maxIn - 1) {
            *maxIn *= 2;
            input = realloc(input, *maxIn * sizeof(char));
            if (input == NULL) {
                printf("failed to reallocate %d bytes for input!\n", *maxIn * sizeof(char));
                exit(1);
            }
        }
    }

    input[i] = 0;
}

void pre_parse(char *input, char *copy) {

    int i = 0;
    int j = 0;
    while (input[i] != 0) {
        if (!(input[i] == '\n' || input[i] == '[' || input[i] == ']' || input[i] == '\'' || input[i] == '\"' || input[i] == ' ')) {
            copy[j++] = input[i];
        }
        i++;
    }
    copy[j] = 0;
}

int num_of_char_in_str(char *str, char c) {
    
    int i = 0;
    int count = 0;
    while (str[i] != 0) {
        if (str[i] == c) {
            count++;
        }
        i++;
    }
    return count;
}

void get_entry_info(char *str) {

    info_t info = {0, 0, 0, 0, 0, 0};

    int n = num_of_char_in_str(str, ',') + 1;

    int count[n];
    char elements[n][100];
    int elementCount = 0;

    for (int i = 0; i < n; i++) {
        count[i] = 0;
    }

    int i = 0;
    int s = 0;

    char e[100];

    while (str[i] != 0) {

        if (str[i] == ',' || str[i+1] == 0) {

            e[s] = 0;

            int t = 0;
            for (int i = 0; i < elementCount; i++) {
                if (strcmp(elements[i], e) == 0) {
                    t = i;
                }
            }
            if (t == 0) {
                strcpy(elements[elementCount], e);
                t = elementCount;
                elementCount++;
            }

            count[t]++;

            s = 0;
            i++;
            continue;
        }

        e[s] = str[i];

        s++;
        i++;
    }

    for (int i = 0; i < elementCount; i++) {
        if (count[i] > info.nFirst) {

            info.nThird = info.nSecond;
            info.iThird = info.iSecond;
            info.nSecond = info.nFirst;
            info.iSecond = info.iFirst;
            info.nFirst = count[i];
            info.iFirst = i;

        } else if (count[i] > info.nSecond) {

            info.nThird = info.nSecond;
            info.iThird = info.iSecond;
            info.nSecond = count[i];
            info.iSecond = i;

        } else if (count[i] > info.nThird) {

            info.nThird = count[i];
            info.iThird = i;
        }
    }

    printf("%s %d\n", elements[info.iFirst], info.nFirst);
    printf("%s %d\n", elements[info.iSecond], info.nSecond);
    printf("%s %d\n", elements[info.iThird], info.nThird);

}

int main() {

    char *input;
    int maxInput = 1000;
    input = malloc(maxInput * sizeof(char));
    if (input == NULL) {
        printf("failed to allocate %d bytes for input!\n", maxInput * sizeof(char));
        exit(1);
    }

    char fileName[] = "input08262023.txt";
    FILE *file = fopen(fileName, "r");

    if (file == NULL) {
        printf("failed to open file: %s!\n", fileName);
        exit(1);
    }

    read_file(file, input, &maxInput);
    fclose(file);

    char *preparsed;
    preparsed = malloc(maxInput * sizeof(char));
    if (preparsed == NULL) {
        printf("failed to allocate %d bytes for preparsed!\n", maxInput * sizeof(char));
        exit(1);
    }

    pre_parse(input, preparsed);

    free(input);

    get_entry_info(preparsed);

    free(preparsed);

    return 0;
}
#include<stdio.h>

char lower_case(char c) {
    return c + (c < 91) * 32;
}

int get_word_amount(char *arr, int inputLen) {

    int wordAmount = 1;

    for (int i = 0; i < inputLen; i++) {
        if (arr[i] == ',') wordAmount++;
    }

    return wordAmount;
}

int fill_word_lengths(int *wordl, char *input, int inputLen) {

    int counter = 0;
    int max = 0;

    for (int i = 0, j = 0; i < inputLen; i++) {
        if (input[i] == ',' || input[i] == '\0') {
            wordl[j++] = counter;
            max = counter > max ? counter : max;
            counter = 0;
            continue;
        }
        counter++;
    }

    return max;
}

void print_is_palindrome(char word[], int wordLength) {

    for (int i = 0, j = wordLength - 1; i < wordLength; i++, j--) {
        if (lower_case(word[i]) != lower_case(word[j])) {
            printf("false\n");
            return;
        }
    }

    printf("true\n");
}

int main() {

    char input[] = "Lagerregal,Otto,Test,Anna,Baum,Essen";
    int inputLen = sizeof(input) / sizeof(char);

    if (input[0] == '\0') {
        printf("no input was provided!");
        return 1;
    }

    int wordAmount = get_word_amount(&input[0], inputLen);

    int wordLengths[wordAmount];
    int maxLen = fill_word_lengths(&wordLengths[0], &input[0], inputLen);

    int c = 0;

    for (int i = 0; i < wordAmount; i++) {

        char word[wordLengths[i] + 1];

        for (int j = 0; j < wordLengths[i]; j++) {
            
            word[j] = input[c++];
        }

        word[wordLengths[i]] = '\0';
        c++;

        printf("%s", word);

        for (int x = 0; x < (maxLen - wordLengths[i] + 1); x++) {
            printf(" ");
        }

        print_is_palindrome(word, wordLengths[i]);
    }

    return 0;
}
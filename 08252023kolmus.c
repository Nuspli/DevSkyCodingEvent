#include<stdio.h>
#include<wchar.h>
#include<locale.h>
#include<stdlib.h>

#define LOWERSTART 97
#define LOWEREND 122
#define UPPERSTART 65
#define UPPEREND 90

typedef struct textInfo_t {
    int words;
    int sentences;
    int vowels;
    wchar_t mostUsedLetter;
    int letterCount[256];
    wchar_t *longestSentence;
    int longestSentenceLength;
    wchar_t *longestWord;
    int longestWordLength;
} textInfo_t;

wchar_t lower_case(wchar_t c) {
    if (c >= LOWERSTART && c <= LOWEREND) return c;
    else if (c >= UPPERSTART && c <= UPPEREND) return c + 32;
    else if (c == L'Ä') return L'ä';
    else if (c == L'Ö') return L'ö';
    else if (c == L'Ü') return L'ü';
    else return c; 
}

void get_longest_word(wchar_t *input, textInfo_t *info) {

    int i = 0;
    int w = 0;
    int start = 0;

    while (input[i] != 0) {

        if (!(input[i] >= LOWERSTART && input[i] <= LOWEREND) && !(input[i] >= UPPERSTART && input[i] <= UPPEREND) && 
            !(input[i] == L'Ä') && !(input[i] == L'Ö') && !(input[i] == L'Ü') && 
            !(input[i] == L'ä') && !(input[i] == L'ö') && !(input[i] == L'ü') && 
            !(input[i] == L'ß')) {
            i++;
            if (w > info->longestWordLength) {
                info->longestWordLength = w;
                info->longestWord = realloc(info->longestWord, (w+1) * sizeof(wchar_t));
                if (info->longestWord == NULL) {
                    printf("failed to reallocate %d bytes for longestWord!\n", (w+1) * sizeof(wchar_t));
                    exit(1);
                }
                for (int x = 0; x < w; x++) {
                    info->longestWord[x] = input[start + x];
                }
                info->longestWord[w] = 0;
            }
            w = 0;
            start = i;
            continue;
        }
        w++;
        i++;
    }
}

void read_file(FILE *file, wchar_t *input, int *maxIn, textInfo_t *info) {

    info->words = 0;
    info->sentences = 0;
    info->vowels = 0;
    info->mostUsedLetter = 0;
    for (int i = 0; i < 256; i++) {
        info->letterCount[i] = 0;
    }
    info->longestSentence = malloc(0);
    info->longestSentenceLength = 0;
    info->longestWord = malloc(0);
    info->longestWordLength = 0;

    int i = 0;
    wchar_t c;
    wchar_t lc = 0;
    int s = 0;

    while ((c = fgetwc(file)) != WEOF) {

        input[i++] = c;
        s++;

        if (i > *maxIn - 1) {
            *maxIn *= 2;
            input = realloc(input, *maxIn * sizeof(wchar_t));
            if (input == NULL) {
                printf("failed to reallocate %d bytes for input!\n", *maxIn * sizeof(wchar_t));
                exit(1);
            }
        }

        if ((c == '.' || c == '!' || c == '?') && !(lc == '.' || lc == '!' || lc == '?')) {
            info->sentences++;

            if (s > info->longestSentenceLength) {
                info->longestSentenceLength = s;
                info->longestSentence = realloc(info->longestSentence, (s+1) * sizeof(wchar_t));
                if (info->longestSentence == NULL) {
                    printf("failed to reallocate %d bytes for longestSentence!\n", (s+1) * sizeof(wchar_t));
                    exit(1);
                }
                for (int x = 0; x < s; x++) {
                    info->longestSentence[x] = input[i - s + x];
                }
                info->longestSentence[s] = 0;
            }
            s = -1;

        } else if ((c == ' ' || c == '\n') && !(lc == ' ' || lc == '\n')) {
            info->words++;
        } else {
            wchar_t lowc = lower_case(c);
            info->letterCount[lowc]++;
            if (info->letterCount[lowc] > info->letterCount[info->mostUsedLetter]) info->mostUsedLetter = lowc;
            if (lowc == 'a' || lowc == 'e' || lowc == 'i' || lowc == 'o' || lowc == 'u') info->vowels++;
        }

        lc = c;
    }

    if (!(lc == ' ' || lc == '\n')) {
        info->words++;
    }

    input[i] = 0;

    get_longest_word(input, info);
    // printf("\n\n=================================================================================\n"); // DEBUG
}

int main() {

    setlocale(LC_ALL, "");

    wchar_t *input;
    int maxInput = 1000;
    input = malloc(maxInput * sizeof(wchar_t));
    if (input == NULL) {
        printf("failed to allocate %d bytes for input!\n", maxInput * sizeof(wchar_t));
        exit(1);
    }

    char fileName[] = "input08252023.txt";
    FILE *file = fopen(fileName, "r, ccs=UTF-8");

    if (file == NULL) {
        printf("failed to open file: %s!\n", fileName);
        exit(1);
    }

    textInfo_t info;

    read_file(file, input, &maxInput, &info);

    // wprintf(L"[DEBUG] input:\n%s\n", input);

    printf("words: %d\n", info.words);
    printf("sentences: %d\n", info.sentences);
    printf("vowels: %d\n", info.vowels);
    wprintf(L"most used letter: %c\n", info.mostUsedLetter);
    wprintf(L"longest sentence:\n%s\n\n", info.longestSentence);
    // printf("[DEBUG] longest sentence length:%d\n", info.longestSentenceLength);
    wprintf(L"longest word: %s\n", info.longestWord);
    // printf("[DEBUG] longest word length: %d\n", info.longestWordLength);

    free(input);
    free(info.longestSentence);
    free(info.longestWord);

    return 0;
}
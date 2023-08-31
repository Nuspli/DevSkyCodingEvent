#include<stdio.h>
#include<stdlib.h>
#include<wchar.h>
#include<locale.h>

wchar_t *numPrefix[] = {
    L"null",
    L"ein",
    L"zwei",
    L"drei",
    L"vier",
    L"fünf",
    L"sechs",
    L"sieben",
    L"acht",
    L"neun"
};

wchar_t *numPrefixLessThan100[] = {
    L"null",
    L"ein",
    L"zwei",
    L"drei",
    L"vier",
    L"fünf",
    L"sech",
    L"sieben",
    L"acht",
    L"neun",
    L"zehn",
    L"elf",
    L"zwölf",
    L"dreizehn",
    L"vierzehn",
    L"fünfzehn",
    L"sechzehn",
    L"siebzehn",
    L"achtzehn",
    L"neunzehn"
};

wchar_t *numPrefix10[] = {
    L"null...",
    L"zehn...",
    L"zwanzig",
    L"dreißig",
    L"vierzig",
    L"fünfzig",
    L"sechzig",
    L"siebzig",
    L"achtzig",
    L"neunzig"
};

wchar_t *itowrds(int n) {

    wchar_t *out = malloc(100);

    if (out == NULL) {
        printf("failed to allocate 100 bytes for the string representation of: %d !\n", n);
        exit(1);
    }

    out[0] = 0;

    if (n == 0) {
        wcscat(out, numPrefix[n]);
    }

    if (n >= 1000) {
        wcscat(out, numPrefix[n/1000]);
        wcscat(out, L"tausend");
        n %= 1000;
    }

    if (n >= 100) {
        wcscat(out, numPrefix[n/100]);
        wcscat(out, L"hundert");
        n %= 100;
    }

    if (n > 19) {

        if (n % 10 != 0) {
            wcscat(out, numPrefixLessThan100[n%10]);
            wcscat(out, L"und");
        }

        wcscat(out, numPrefix10[n/10]);

    } else if (n != 0) {
        wcscat(out, numPrefixLessThan100[n]);
        if (n == 1 || n == 6) {
            wcscat(out, L"s");
        }
    }

    return out;
}

int main() {

    setlocale(LC_ALL, "");

    int input[] = {55, 167, 6384};
    int inputSize = sizeof(input) / sizeof(input[0]);

    for (int i = 0; i < inputSize; i++) {
        wchar_t *words = itowrds(input[i]);
        wprintf(L"%s\n", words);
        free(words);
    }

    return 0;
}
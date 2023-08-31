#include<stdio.h>

// 'A' - 'Z' == 65 - 90
// 'a' - 'z' == 97 - 122

char encrypt(char c, int offset) {
    
    if (c > 64 && c < 91) {
        // uppercase letter
        int wrap_offset = (c - 65 + offset) % 26;
        return (char)('A' + wrap_offset);

    } else if (c > 96 && c < 123) {
        // lowercase letter
        int wrap_offset = (c - 97 + offset) % 26;
        return (char)('a' + wrap_offset);

    } else {
        // whitespace or special characters like '\0' remain
        return c;
    }
}

void caesar_cipher(char *text, int text_lenght, char *encr, int offset) {

    for (int i = 0; i < text_lenght; i++) {
        encr[i] = encrypt(text[i], offset);
    }
}

int main() {

    char input[] = "Ich bin ein verschluesselter Text";
    int offset = 9;
    offset %= 26;

    int input_length = sizeof(input) / sizeof(char);
    char output[input_length];

    caesar_cipher(&input[0], input_length, &output[0], offset);

    printf("%s", output);

    return 0;
}
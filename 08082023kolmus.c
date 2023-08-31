#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include<limits.h>

char *get_command() {

    fflush(stdin);

    int maxInputLen = 500;
    char *c = (char *) malloc(maxInputLen);

    if (c == NULL) {
        fprintf(stderr, "failed to allocate %d bytes for your input!\n", maxInputLen);
        exit(EXIT_FAILURE);
    }

    if (fgets(&c[0], maxInputLen, stdin) == NULL) {
        fprintf(stderr, "failed to get input from commandline!\n");
        exit(EXIT_FAILURE);
    }

    while (memchr(&c[0], '\n', maxInputLen) == NULL) {

        printf("your input was too long to process ...\nplease try again\n\n^^> ");
        maxInputLen *= 2;

        if ((c = realloc(&c[0], maxInputLen)) == NULL) {

            fprintf(stderr, "failed to reallocate %d bytes for your input!\n", maxInputLen);
            fprintf(stderr, "please consider using something smaller or try again\n\n");
            exit(EXIT_FAILURE);
        }

        fflush(stdin);

        if (fgets(&c[0], maxInputLen, stdin) == NULL) {
            fprintf(stderr, "failed to get input from commandline!\n");
            exit(EXIT_FAILURE);
        }
    }

    return &c[0];
}

void check_err(long long n) {
    if (n == 0) {
        if (errno == EINVAL) {
            printf("conversion error occurred: %d\n", errno);
            exit(EXIT_FAILURE);
        }
    }

    if (n == LLONG_MIN || n == LLONG_MAX) {
        if (errno == ERANGE) {
            printf("the value provided was out of range\n");
            exit(EXIT_FAILURE);
        }
    }
}

int main() {

    while (1) {
        printf("^^> ");
        char *command = get_command();
        
        if (strstr(command, "rechne ") == command) {

            command += sizeof("rechne");

            char *p;
            long long x = strtoll(strtok(command, "*"), &p, 10);
            check_err(x);

            long long y = strtoll(p+1, &p, 10);
            check_err(y);

            printf("\n%lld\n\n", x*y);
            free(p);
            
        } else if (strstr(command, "wiederhole: ") == command) {

            printf("\n%s\n", command + sizeof("wiederhole:"));

        } else {
            printf("invalid command!\n");
            printf("usage: rechne x*y\n");
            printf("       wiederhole: xyz\n");
            printf("quit : ctrl+c\n\n");
        }
        free(command);
    }

    return 0;
}
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXTODOENTRYLEN 200
#define MAXTODOLISTLEN 100

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


int init_todo(char *todo[], FILE *todoFile) {

    printf("allocating memory for todo list\n");

    for (int i = 0; i < MAXTODOLISTLEN; i++) {
        todo[i] = malloc(MAXTODOENTRYLEN); 
        if (todo[i] == NULL) {
            fprintf(stderr, "failed to allocate memory for todo!\n");
            exit(EXIT_FAILURE);
        }
    }

    printf("accessing previous sessions...\n");
    int numTodos = 0;
    fread(&numTodos, sizeof(int), 1, todoFile);
    if (numTodos == 0) {
        printf("no data found!\n");
    } else {
        printf("reading data...\n");
    }

    for (int i = 0; i < numTodos && i < MAXTODOLISTLEN; i++) {

        char c;
        int n = 0;

        while (1) {
            fread(&c, sizeof(char), 1, todoFile);
            todo[i][n] = c;
            n++;
            if (c == '\0') {
                break;
            }
        }

        printf("[DEBUG] : %s", todo[i]);
    }

    return numTodos;
}

void write_todo(char *todo[], int todoSize, FILE *todoFile) {

    fseek(todoFile, 0, SEEK_SET);

    fwrite(&todoSize, sizeof(int), 1, todoFile);
    
    for (int i = 0; i < todoSize; i++) {
        char c;
        int n = 0;
        while (1) {
            c = todo[i][n];
            fwrite(&c, sizeof(char), 1, todoFile);
            if (c == '\0') {
                break;
            }
            n++;
        }
    }
}

void add_todo(char *todo[], int *todoSize, char *text) {

    if (strlen(text) > MAXTODOENTRYLEN - 6) {
        printf("todo too long, try something below 180 characters!\n");
        return;
    }
    strcpy(todo[*todoSize], text);
    printf("[DEBUG] : added: %s\n", text);
    *todoSize = *todoSize + 1;
}

void delete_todo(char *todo[], char *copy[], int *todoSize, char *text) {

    int found = 0;
    char tick[MAXTODOENTRYLEN];
    strcpy(tick, text);
    tick[strlen(text) - 1] = ' ';
    tick[strlen(text)] = '<';
    tick[strlen(text)+1] = 'X';
    tick[strlen(text)+2] = '>';
    tick[strlen(text)+3] = '\n';
    tick[strlen(text)+4] = '\0';
    
    int copied = 0;
    int originalSize = *todoSize;

    for (int i = 0; i < originalSize; i++) {
        if (strcmp(todo[i], text) == 0 || strcmp(todo[i], tick) == 0) {

            found = 1;
            *todoSize = *todoSize - 1;
            printf("[DEBUG] : removed: %s\n", text);
            continue;
        }
        copy[copied] = malloc(MAXTODOENTRYLEN);
        if (copy[copied] == NULL) {
            fprintf(stderr, "failed to allocate memory for copy!\n");
            exit(EXIT_FAILURE);
        }
        strcpy(copy[copied], todo[i]);
        copied++;
    }

    if (!found) {
        printf("todo entry not found!\nenter \"ShowTodo\" for a list of all todo entries!\n");
        return;
    }

    for (int i = 0; i < *todoSize; i++) {
        strcpy(todo[i], copy[i]);
    }
}

void show_todo(char *todo[], int todoSize) {

    printf("\n");
    for (int i = 0; i < todoSize; i++) {
        printf("%s", todo[i]);
    }
    printf("\n");
}

void tick_todo(char *todo[], int todoSize, char* text) {

    int found = 0;

    for (int i = 0; i < todoSize; i++) {
        if (strcmp(todo[i], text) == 0) {
            todo[i][strlen(text) - 1] = ' ';
            todo[i][strlen(text)] = '<';
            todo[i][strlen(text)+1] = 'X';
            todo[i][strlen(text)+2] = '>';
            todo[i][strlen(text)+3] = '\n';
            todo[i][strlen(text)+4] = '\0';
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("todo entry not found!\nenter \"ShowTodo\" for a list of all todo entries!\n");
        return;
    }

    printf("[DEBUG] : ticked: %s\n", text);
}

int main() {
    FILE *todoFile;

    todoFile = fopen("todo.dat", "r+");

    if (todoFile == NULL) {
        printf("[DEBUG] : creating file: todo.dat\n");
        todoFile = fopen("todo.dat", "w+");
    }

    char *todo[MAXTODOENTRYLEN];

    int numTodos = init_todo(todo, todoFile);

    printf("=-=-=-=-=-=-=-=-=-=-TODO LIST-=-=-=-=-=-=-=-=-=-=\n\n");
    
    while (1) {

        printf("^^> ");
        char *command = get_command();
        
        if (strstr(command, "AddTodo ") == command) {

            command += sizeof("AddTodo");
            add_todo(todo, &numTodos, command);
            command -= sizeof("AddTodo");
            write_todo(todo, numTodos, todoFile);
            
        } else if (strstr(command, "DeleteTodo ") == command) {

            command += sizeof("DeleteTodo");
            char *copy[MAXTODOENTRYLEN];
            delete_todo(todo, copy, &numTodos, command);
            for (int i = 0; i < numTodos; i++) {
                free(copy[i]);
            }
            command -= sizeof("DeleteTodo");
            write_todo(todo, numTodos, todoFile);

        } else if (strstr(command, "ShowTodo") == command) {

            show_todo(todo, numTodos);

        } else if (strstr(command, "TickTodo ") == command) {

            command += sizeof("TickTodo");
            tick_todo(todo, numTodos, command);
            command -= sizeof("TickTodo");
            write_todo(todo, numTodos, todoFile);

        } else if (strstr(command, "q") == command) {

            write_todo(todo, numTodos, todoFile);

            fclose(todoFile);
            printf("closed file\n");
            for (int i = 0; i < MAXTODOLISTLEN; i++) {
                free(todo[i]);
            }
            printf("freed memory\n");
            exit(0);

        } else {
            printf("invalid command!\n");
            printf("usage: AddTodo <todo string>\n");
            printf("       DeleteTodo <todo string>\n");
            printf("       ShowTodo\n");
            printf("       TickTodo <todo string>\n");
            
            printf("quit : q\n\n");
        }

        free(command);
    }

    return 0;
}
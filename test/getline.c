#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 128

/**
 * custom_getline - program performs a getline function
 * Return: Always 0
 */

char *custom_getline() {
    static char buffer[BUFFER_SIZE];
    static int position = 0;
    static int length = 0;
    char *line = NULL;
    int c;
    int size = 0;

    while (1) {
        if (position >= length) {
            position = 0;
            length = read(STDIN_FILENO, buffer, BUFFER_SIZE);
            if (length <= 0) {
                if (line != NULL && size > 0) {
                    line[size] = '\0';
                    return (line);
                }
                return (NULL);
            }
        }

        c = buffer[position++];
        if (c == '\n' || c == EOF) {
            if (line == NULL) {
                line = (char *)malloc(size + 1);
            } else {
                char *temp = (char *)realloc(line, size + 1);
                if (temp == NULL) {
                    free(line);
                    return (NULL); 
		}
                line = temp;
            }
            line[size] = '\0';
            return (line);
        } else {
            if (line == NULL) {
                line = (char *)malloc(size + 1);
            } else {
                char *temp = (char *)realloc(line, size + 1);
                if (temp == NULL) {
                    free(line);
                    return (NULL);
                }
                line = temp;
            }
            line[size++] = c;
        }
    }
}

/**
 * main: main function
 * Returnn: Always 0
 */

int main() {
    char *line;

    while ((line = custom_getline()) != NULL) {
        printf("Input: %s\n", line);
        free(line);
    }

    return (0);
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 128

char *custom_getline() {
    char *line = NULL;
    int size = 0;
    int capacity = BUFFER_SIZE;
     char *temp = (char *)malloc(capacity);
     int i;

    while (1) {
        char c;
        int bytes_read = read(STDIN_FILENO, &c, 1);

        if (bytes_read <= 0) {
            if (line != NULL && size > 0) {
                line[size] = '\0';
                return line;
            }
            return NULL;
        }

        if (c == '\n' || c == EOF) {
            if (line == NULL) {
                line = (char *)malloc(size + 1);
                if (line == NULL) {
                    perror("Memory allocation error");
                    return NULL;
                }
            } else if (size >= capacity - 1) {
                capacity *= 2;
                
                if (temp == NULL) {
                    perror("Memory allocation error");
                    free(line);
                    return NULL;
                }
                for (i = 0; i < size; ++i) {
                    temp[i] = line[i];
                }
                free(line);
                line = temp;
            }
            line[size++] = '\0';
            return line;
        } else {
            if (line == NULL) {
                line = (char *)malloc(capacity);
                if (line == NULL) {
                    perror("Memory allocation error");
                    return NULL;
                }
            } else if (size >= capacity - 1) {
                capacity *= 2;
               
                if (temp == NULL) {
                    perror("Memory allocation error");
                    free(line);
                    return NULL;
                }
                for (i = 0; i < size; ++i) {
                    temp[i] = line[i];
                }
                free(line);
                line = temp;
            }
            line[size++] = c;
        }
    }
}


int main() {
    char *line;

    while ((line = custom_getline()) != NULL) {
        int i = 0;
        while (line[i] != '\0') {
            write(STDOUT_FILENO, &line[i], 1);
            ++i;
        }
        write(STDOUT_FILENO, "\n", 1);
        free(line);
    }

    return 0;
}

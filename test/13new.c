#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

extern char **environ;

#define MAX_ALIASES 50
#define MAX_ALIAS_LEN 100

char *aliases[MAX_ALIASES][2];

void print_all_aliases() {
    int i = 0;
    while (i < MAX_ALIASES && aliases[i][0] != NULL) {
        write(STDOUT_FILENO, aliases[i][0], strlen(aliases[i][0]));
        write(STDOUT_FILENO, "='", 2);
        write(STDOUT_FILENO, aliases[i][1], strlen(aliases[i][1]));
        write(STDOUT_FILENO, "'\n", 2);
        i++;
    }
}

void print_specific_alias(const char *name) {
    int i = 0;
    while (i < MAX_ALIASES && aliases[i][0] != NULL) {
        if (strcmp(aliases[i][0], name) == 0) {
            write(STDOUT_FILENO, aliases[i][0], strlen(aliases[i][0]));
            write(STDOUT_FILENO, "='", 2);
            write(STDOUT_FILENO, aliases[i][1], strlen(aliases[i][1]));
            write(STDOUT_FILENO, "'\n", 2);
            return;
        }
        i++;
    }
    write(STDERR_FILENO, "Alias '", 7);
    write(STDERR_FILENO, name, strlen(name));
    write(STDERR_FILENO, "' not found\n", 12);
}

void set_alias(const char *name, const char *value) {
    int i = 0;
    while (i < MAX_ALIASES) {
        if (aliases[i][0] == NULL) {
            aliases[i][0] = strdup(name);
            aliases[i][1] = strdup(value);
            return;
        } else if (strcmp(aliases[i][0], name) == 0) {
            free(aliases[i][1]);
            aliases[i][1] = strdup(value);
            return;
        }
        i++;
    }
    write(STDERR_FILENO, "No more space for aliases\n", 26);
}

void handle_alias_command(int argc, char *argv[]) {
    int i;
    for (i = 1; i < argc; i++) {
        char *token = strtok(argv[i], "=");
        if (token != NULL) {
            char *name = token;
            char *value = strtok(NULL, "=");

            if (value != NULL) {
                set_alias(name, value);
            } else {
                print_specific_alias(name);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "alias") == 0) {
        handle_alias_command(argc - 1, argv + 1);
    } else {
        char **env = environ;
        while (*env != NULL) {
            write(STDOUT_FILENO, *env, strlen(*env));
            write(STDOUT_FILENO, "\n", 1);
            env++;
        }
    }
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

#define MAX_ALIASES 50
#define MAX_ALIAS_LEN 100

char *aliases[MAX_ALIASES][2];

void print_all_aliases() {
	int i;

    for (i = 0; i < MAX_ALIASES && aliases[i][0] != NULL; i++) {
        printf("%s='%s'\n", aliases[i][0], aliases[i][1]);
    }
}

void print_specific_alias(const char *name) {
	int i;

    for (i = 0; i < MAX_ALIASES && aliases[i][0] != NULL; i++) {
        if (strcmp(aliases[i][0], name) == 0) {
            printf("%s='%s'\n", aliases[i][0], aliases[i][1]);
            return;
        }
    }
    fprintf(stderr, "Alias '%s' not found\n", name);
}

void set_alias(const char *name, const char *value) {
	int i;

    for (i = 0; i < MAX_ALIASES; i++) {
        if (aliases[i][0] == NULL) {
            aliases[i][0] = strdup(name);
            aliases[i][1] = strdup(value);
            return;
        } else if (strcmp(aliases[i][0], name) == 0) {
            free(aliases[i][1]);
            aliases[i][1] = strdup(value);
            return;
        }
    }
    fprintf(stderr, "No more space for aliases\n");
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
            printf("%s\n", *env);
            env++;
        }
    }

    return 0;
}

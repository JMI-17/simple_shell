#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

extern char **environ;

int custom_setenv(const char *name, const char *value, int overwrite)
{
	char *env_entry;
    size_t len = strlen(name) + strlen(value) + 2;
    env_entry = (char *)malloc(len);

    if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL) {
        fprintf(stderr, "Invalid variable name\n");
        return (-1);
    }

    if (!overwrite && getenv(name) != NULL) {
        fprintf(stderr, "Variable already exists\n");
        return (0);
    }

   
    if (env_entry == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return (-1);
    }

    snprintf(env_entry, len, "%s=%s", name, value);

    if (putenv(env_entry) != 0) {
        fprintf(stderr, "Failed to set environment variable: %s\n", strerror(errno));
        free(env_entry);
        return (-1);
    }

    return (0);
}

int custom_unsetenv(const char *name) {
    if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL) {
        fprintf(stderr, "Invalid variable name\n");
        return (-1);
    }

    if (unsetenv(name) != 0) {
        fprintf(stderr, "Failed to unset environment variable: %s\n", strerror(errno));
        return (-1);
    }

    return (0);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage:\n");
        fprintf(stderr, "  setenv VARIABLE VALUE\n");
        fprintf(stderr, "  unsetenv VARIABLE\n");
        return (1);
    }

    if (strcmp(argv[1], "setenv") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
            return (1);
        }
        return (custom_setenv(argv[2], argv[3], 1));
    } else if (strcmp(argv[1], "unsetenv") == 0) {
        if (argc != 3) {
            fprintf(stderr, "Usage: unsetenv VARIABLE\n");
            return (1);
        }
        return (custom_unsetenv(argv[2]));
    } else {
        fprintf(stderr, "Unknown command: %s\n", argv[1]);
        return (1);
    }

    return (0);
}


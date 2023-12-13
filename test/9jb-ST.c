#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int custom_setenv(const char *name, const char *value, int overwrite) {
    char *env_entry;
    size_t len = strlen(name) + strlen(value) + 2;
    env_entry = (char *)malloc(len);

    if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL) {
        char error_msg[] = "Invalid variable name\n";
        write(STDERR_FILENO, error_msg, sizeof(error_msg) - 1);
        return -1;
    }

    if (!overwrite && getenv(name) != NULL) {
        char error_msg[] = "Variable already exists\n";
        write(STDERR_FILENO, error_msg, sizeof(error_msg) - 1);
        return 0;
    }

    if (env_entry == NULL) {
        char error_msg[] = "Memory allocation error\n";
        write(STDERR_FILENO, error_msg, sizeof(error_msg) - 1);
        return -1;
    }

    strcpy(env_entry, name);
    strcat(env_entry, "=");
    strcat(env_entry, value);

    if (putenv(env_entry) != 0) {
        char error_msg[] = "Failed to set environment variable: ";
        write(STDERR_FILENO, error_msg, sizeof(error_msg) - 1);
        write(STDERR_FILENO, strerror(errno), strlen(strerror(errno)));
        write(STDERR_FILENO, "\n", 1);
        free(env_entry);
        return -1;
    }

    return 0;
}


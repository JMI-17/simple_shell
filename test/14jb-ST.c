#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

char *get_replaced_variable(const char *var) {
    if (strcmp(var, "$?") == 0) {
        return ("SomeReturnValue"); 
    } else if (strcmp(var, "$$") == 0) {
        pid_t pid = getpid();
        char *pid_str = malloc(sizeof(char) * 20);
        if (pid_str != NULL) {
            sprintf(pid_str, "%d", pid);
            return (pid_str);
        }
    }
    return (NULL);
}

void print_environment_with_replacement() {
    char **env = environ;

    while (*env != NULL) {
        char *current_env = *env;

        char *var = strtok(current_env, "="); 
        char *val = strtok(NULL, "=");       
        if (var != NULL && val != NULL) {
            char *replaced_val = get_replaced_variable(val);
            if (replaced_val != NULL) {
                printf("%s=%s\n", var, replaced_val);
                free(replaced_val); 
            } else {
                printf("%s=%s\n", var, val);
            }
        }

        env++;
    }
}

int main() {
    print_environment_with_replacement();

    return (0);
}


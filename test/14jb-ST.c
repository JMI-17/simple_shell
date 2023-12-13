#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

extern char **environ;

char *get_replaced_variable(const char *var) {

	int i;
	int j;

    if (strcmp(var, "$?") == 0) {
        char *returnValue = (char *)malloc(sizeof(char) * 15);
        if (returnValue != NULL) {
            memcpy(returnValue, "SomeReturnValue", sizeof("SomeReturnValue"));
            return returnValue;
        }
    } else if (strcmp(var, "$$") == 0) {
        pid_t pid = getpid();
        char *pid_str = (char *)malloc(sizeof(char) * 20);
        if (pid_str != NULL) {
            int pidLen = 0;
            while (pid > 0) {
                pid_str[pidLen++] = (pid % 10) + '0';
                pid /= 10;
            }
            if (pidLen > 0) {
                pid_str[pidLen] = '\0';
                i = 0, j = pidLen - 1;
                while (i < j) {
                    char temp = pid_str[i];
                    pid_str[i] = pid_str[j];
                    pid_str[j] = temp;
                    i++;
                    j--;
                }
                return pid_str;
            } else {
                free(pid_str);
            }
        }
    }
    return NULL;
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
                write(STDOUT_FILENO, var, strlen(var));
                write(STDOUT_FILENO, "=", 1);
                write(STDOUT_FILENO, replaced_val, strlen(replaced_val));
                write(STDOUT_FILENO, "\n", 1);
                free(replaced_val);
            } else {
                write(STDOUT_FILENO, var, strlen(var));
                write(STDOUT_FILENO, "=", 1);
                write(STDOUT_FILENO, val, strlen(val));
                write(STDOUT_FILENO, "\n", 1);
            }
        }
        env++;
    }
}

int main() {
    print_environment_with_replacement();
    return 0;
}


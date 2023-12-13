#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"


int main(int argc, char *argv[]) {

        char setenv_error[] = "Function for setenv is not implemented.\n";
        char unsetenv_error[] = "Function for unsetenv is not implemented.\n";



    if (argc < 3) {
        char usage[] = "Usage:\n"
                       "  setenv VARIABLE VALUE\n"
                       "  unsetenv VARIABLE\n";
        write(STDERR_FILENO, usage, strlen(usage));
        return 1;
    }

    if (strcmp(argv[1], "setenv") == 0) {
        if (argc != 4) {
            char usage_setenv[] = "Usage: setenv VARIABLE VALUE\n";
             write(STDERR_FILENO, usage_setenv, strlen(usage_setenv));
            return 1;
        }


        write(STDERR_FILENO, setenv_error, strlen(setenv_error));
        return 1;
    } else if (strcmp(argv[1], "unsetenv") == 0) {
        if (argc != 3) {
            char usage_unsetenv[] = "Usage: unsetenv VARIABLE\n";
            write(STDERR_FILENO, usage_unsetenv, strlen(usage_unsetenv));
            return 1;
        }


        write(STDERR_FILENO, unsetenv_error, strlen(unsetenv_error));
        return 1;
    } else {
        char unknown_command[] = "Unknown command: ";
        write(STDERR_FILENO, unknown_command, strlen(unknown_command));
        write(STDERR_FILENO, argv[1], strlen(argv[1]));
        write(STDERR_FILENO, "\n", 1);
        return 1;
    }

    return 0;
}

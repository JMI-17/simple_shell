#include "main.h"



int main(int argc, char *argv[]) {
         const char *directory = (argc == 2) ? argv[1] : NULL;


    if (argc > 2) {
        char error_msg[] = "Usage: cd [DIRECTORY]\n";
        write(STDERR_FILENO, error_msg, sizeof(error_msg) - 1);
        return 1;
    }

    if (custom_cd(directory) != 0) {
        char error_msg[] = "Failed to change directory\n";
        write(STDERR_FILENO, error_msg, sizeof(error_msg) - 1);
        return 1;
    }

    return 0;
}



#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int custom_cd(const char *directory) {
    char current_dir[1024]; 
    
    if (directory == NULL || strcmp(directory, "") == 0 || strcmp(directory, "~") == 0) {
        directory = getenv("HOME");
        if (directory == NULL) {
            char error_msg[] = "HOME environment variable not set\n";
            write(STDERR_FILENO, error_msg, sizeof(error_msg) - 1);
            return -1;
        }
    } else if (strcmp(directory, "-") == 0) {
        directory = getenv("OLDPWD");
        if (directory == NULL) {
            char error_msg[] = "OLDPWD environment variable not set\n";
            write(STDERR_FILENO, error_msg, sizeof(error_msg) - 1);
            return -1;
        }
    }

    if (getcwd(current_dir, sizeof(current_dir)) == NULL) {
        char error_msg[] = "PWD environment variable not set\n";
        write(STDERR_FILENO, error_msg, sizeof(error_msg) - 1);
        return -1;
    }

    if (chdir(directory) != 0) {
        char error_msg[] = "Failed to change directory: ";
        write(STDERR_FILENO, error_msg, sizeof(error_msg) - 1);
        write(STDERR_FILENO, strerror(errno), strlen(strerror(errno)));
        write(STDERR_FILENO, "\n", 1);
        return -1;
    }

    if (setenv("OLDPWD", current_dir, 1) != 0) {
        char error_msg[] = "Failed to set OLDPWD environment variable\n";
        write(STDERR_FILENO, error_msg, sizeof(error_msg) - 1);
        return -1;
    }

    if (setenv("PWD", directory, 1) != 0) {
        char error_msg[] = "Failed to set PWD environment variable\n";
        write(STDERR_FILENO, error_msg, sizeof(error_msg) - 1);
        return -1;
    }

    return 0;
}

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


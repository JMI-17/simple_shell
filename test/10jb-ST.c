#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int custom_cd(const char *directory) {
    char current_dir[1024];
    const char *home_dir = getenv("HOME");
    const char *old_pwd = getenv("OLDPWD");

    if (!directory || !strcmp(directory, "") || !strcmp(directory, "~")) {
        directory = home_dir;
        if (!directory) {
            write(STDERR_FILENO, "HOME environment variable not set\n", 32);
            return -1;
        }
    } else if (!strcmp(directory, "-")) {
        directory = old_pwd;
        if (!directory) {
            write(STDERR_FILENO, "OLDPWD environment variable not set\n", 33);
            return -1;
        }
    }

    if (!getcwd(current_dir, sizeof(current_dir))) {
        write(STDERR_FILENO, "PWD environment variable not set\n", 32);
        return -1;
    }

    if (chdir(directory) != 0) {
        write(STDERR_FILENO, "Failed to change directory: ", 28);
        write(STDERR_FILENO, strerror(errno), strlen(strerror(errno)));
        write(STDERR_FILENO, "\n", 1);
        return -1;
    }

    if (setenv("OLDPWD", current_dir, 1) != 0) {
        write(STDERR_FILENO, "Failed to set OLDPWD environment variable\n", 42);
        return -1;
    }

    if (setenv("PWD", directory, 1) != 0) {
        write(STDERR_FILENO, "Failed to set PWD environment variable\n", 38);
        return -1;
    }

    return 0;
}


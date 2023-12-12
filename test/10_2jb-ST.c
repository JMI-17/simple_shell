#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

extern char **environ;

int custom_cd(const char *directory) {
    char *current_dir = NULL;
    directory = getenv("HOME");
    directory = getenv("OLDPWD");
    current_dir = getenv("PWD");

    if (directory == NULL || strcmp(directory, "") == 0 || strcmp(directory, "~") == 0) 
    {
        if (directory == NULL) {
            fprintf(stderr, "HOME environment variable not set\n");
            return (-1);
        }
    } else if (strcmp(directory, "-") == 0) {
        
        if (directory == NULL) {
            fprintf(stderr, "OLDPWD environment variable not set\n");
            return (-1);
        }
    }

    
    if (current_dir == NULL) {
        fprintf(stderr, "PWD environment variable not set\n");
        return (-1);
    }

    if (chdir(directory) != 0) {
        fprintf(stderr, "Failed to change directory: %s\n", strerror(errno));
        return (-1);
    }

    if (setenv("OLDPWD", current_dir, 1) != 0) {
        fprintf(stderr, "Failed to set OLDPWD environment variable\n");
        return (-1);
    }

    if (setenv("PWD", directory, 1) != 0) {
        fprintf(stderr, "Failed to set PWD environment variable\n");
        return (-1);
    }

    return (0);
}

int main(int argc, char *argv[]) {
    const char *directory = (argc == 2) ? argv[1] : NULL;
	if (argc > 2) {
        fprintf(stderr, "Usage: cd [DIRECTORY]\n");
        return (1);
    }

    
    
    if (custom_cd(directory) != 0) {
        fprintf(stderr, "Failed to change directory\n");
        return (1);
    }

    return (0);
}


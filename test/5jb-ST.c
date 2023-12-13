#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>


extern char **environ;

int main() {
    int i = 0;
    char *env_var;


    while ((env_var = environ[i++]) != NULL) {
        write(STDOUT_FILENO, env_var, strlen(env_var));
        write(STDOUT_FILENO, "\n", 1);
    }

    return 0;
}



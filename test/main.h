#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

<<<<<<< HEAD
#define MAX_COMMAND_LENGTH 100
=======
extern char **environ;
int custom_setenv(const char *name, const char *value, int overwrite);
>>>>>>> 71e39c435b44359267ac16c292106542444f2b6f

/* Function prototypes */
void displayPrompt(void);
void printError(const char *msg);
void displayPrompt2(void);
#endif /* MAIN_H */

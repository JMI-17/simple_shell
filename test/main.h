#ifndef MAIN_H
#define MAIN_H

<<<<<<< HEAD
extern char **environ;
int custom_setenv(const char *name, const char *value, int overwrite);
int custom_cd(const char *directory);
=======
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
>>>>>>> fd1a050f366a0ed4231d60ddd19863abfa7ee158

#define MAX_COMMAND_LENGTH 100

/**
 * displayPrompt - Displays the shell prompt.
 */
void displayPrompt(void);

/**
 * printError - Prints an error message.
 * @msg: The error message to print.
 */
void printError(const char *msg);

/**
 * executeCommand - Executes the given command using fork and execve.
 * @command: The command to execute.
 */
void executeCommand(const char *command);

#endif /* MAIN_H */

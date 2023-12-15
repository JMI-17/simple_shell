#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

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

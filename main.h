#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 100

/* Function prototypes */
void displayPrompt(void);
void printError(const char *msg);
void displayPrompt2(void);
#endif /* MAIN_H */

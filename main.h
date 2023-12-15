#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>

#define BUFFER_SIZE 1024

/**
 * display_prompt - Display the shell prompt.
 */
void display_prompt(void);

/**
 * write_exit_status - Write exit status message to standard output.
 * @exit_status: The exit status of the child process.
 */
void write_exit_status(int exit_status);

/**
 * write_signal_message - Write signal termination message to standard output.
 * @signal_number: The signal number that terminated the child process.
 */
void write_signal_message(int signal_number);

#endif /* MAIN_H */

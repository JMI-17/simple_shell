#include "main.h"
/**
 * display_prompt - Display the shell prompt.
 */
void display_prompt(void)
{
        char prompt[] = "$ ";
        write(STDOUT_FILENO, prompt, sizeof(prompt) - 1);
}

/**
 * write_exit_status - Write exit status message to standard output.
 * @exit_status: The exit status of the child process.
 */
void write_exit_status(int exit_status)
{
        char exit_status_message[64];
        int n = snprintf(exit_status_message, sizeof(exit_status_message),
                "Child process exited with status %d\n", exit_status);
        write(STDOUT_FILENO, exit_status_message, n);
}
/**
 * write_signal_message - Write signal termination message to standard output.
 * @signal_number: The signal number that terminated the child process.
 */
void write_signal_message(int signal_number)
{
        char signal_message[64];
        int n = snprintf(signal_message, sizeof(signal_message),
                "Child process terminated by signal %d\n", signal_number);
        write(STDOUT_FILENO, signal_message, n);
}

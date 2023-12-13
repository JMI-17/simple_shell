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
void displayPrompt(void)
{
    char prompt[] = "$\t";
    write(STDOUT_FILENO, prompt, sizeof(prompt) - 1); /* Ensure the prompt is displayed immediately */
}

/**
 * main - Entry point of the shell program.
 * Return: Always 0 on success.
 */
int main(void)
{
    char *const envp[] = {NULL};
    char command[MAX_COMMAND_LENGTH];
    pid_t pid;
    char *args[2];
    args[1] = NULL; /* Ensure the second element is NULL initially */

    while (1)
    {
        displayPrompt();

        /* Read a command from the user */
        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
        {
            /* Handle end of file (Ctrl+D) */
            write(STDOUT_FILENO, "\n", 1);
            break;
        }

        /* Remove the newline character at the end */
        command[strcspn(command, "\n")] = '\0';

        /* Fork a new process */
        pid = fork();

        if (pid == -1)
        {
            char error_message[] = "Error: Fork failed\n";
            write(STDERR_FILENO, error_message, sizeof(error_message) - 1);
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            /* Child process */
            /* Execute the command */
            args[0] = command;
            if (execve(command, args, envp) == -1)
            {
                char error_message[] = "Error: execve failed\n";
                write(STDERR_FILENO, error_message, sizeof(error_message) - 1);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            /* Parent process */
            /* Wait for the child process to complete */
            int status;
            if (waitpid(pid, &status, 0) == -1)
            {
                char error_message[] = "Error: waitpid failed\n";
                write(STDERR_FILENO, error_message, sizeof(error_message) - 1);
                exit(EXIT_FAILURE);
            }

            /* Check if the child process terminated successfully */
            if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
            {
                char error_message[MAX_COMMAND_LENGTH + sizeof("Error: Command '' not found\n")];
                sprintf(error_message, "Error: Command '%s' not found\n", command);
                write(STDERR_FILENO, error_message, strlen(error_message));
            }
        }
    }

    return 0;
}

#include "main.h"

int main(void)
{
    char *const envp[] = {NULL};
    char command[MAX_COMMAND_LENGTH];
    pid_t pid;
    char *args[MAX_ARGUMENTS + 1]; /* +1 for the NULL at the end */
    args[MAX_ARGUMENTS] = NULL; /* Ensure the last element is NULL */

    while (1)
    {
        displayPrompt();

        /* Read a command from the user */
        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
        {
            /* Handle end of file (Ctrl+D) */
            printf("\n");
            break;
        }

        /* Remove the newline character at the end */
        command[strcspn(command, "\n")] = '\0';

        /* Fork a new process */
        pid = fork();

        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            /* Child process */
            /* Execute the command */
            args[0] = command;
            args[1] = command; /* Additional argument for execve */
            if (execve("/bin/sh", args, envp) == -1)
            {
                perror("execve");
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
                perror("waitpid");
                exit(EXIT_FAILURE);
            }

            /* Check if the child process terminated successfully */
            if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
            {
                fprintf(stderr, "Error: Command '%s' not found\n", command);
            }
        }
    }

    return (0);
}

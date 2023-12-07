#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

/**
 * displayPrompt - Displays the shell prompt.
 */
void displayPrompt(void)
{
    printf("$\t");
    fflush(stdout); /* Ensure the prompt is displayed immediately */
}

/**
 * checkCommandInPath - Checks if the command is in the PATH.
 * Return: 1 if found, 0 if not found.
 */
int checkCommandInPath(const char *command)
{
    char *path = getenv("PATH");
    char *token = strtok(path, ":");

    while (token != NULL)
    {
        char fullPath[MAX_COMMAND_LENGTH];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", token, command);

        if (access(fullPath, X_OK) == 0)
        {
            return 1; /* Command found in the PATH */
        }

        token = strtok(NULL, ":");
    }

    return 0; /* Command not found in the PATH */
}

/**
 * main - Entry point of the shell program.
 * Return: Always 0 on success.
 */
int main(void)
{
    char command[MAX_COMMAND_LENGTH];
    pid_t pid;
    char *args[MAX_ARGUMENTS + 1];  /* +1 for the NULL at the end */
    int i;
    char *token;

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

        /* Tokenize the command into arguments */
        i = 0;
        token = strtok(command, " ");
        while (token != NULL && i < MAX_ARGUMENTS)
        {
            args[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        args[i] = NULL;  /* Set the last element to NULL to terminate the args array */

        /* Check if the command is the built-in exit */
        if (strcmp(args[0], "exit") == 0)
        {
            printf("Exiting the shell.\n");
            exit(EXIT_SUCCESS);
        }

        /* Check if the command is in the PATH */
        if (!checkCommandInPath(args[0]))
        {
            fprintf(stderr, "Error: Command '%s' not found\n", args[0]);
            continue; /* Skip fork and prompt again */
        }

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
            /* Execute the command with arguments */
            if (execvp(args[0], args) == -1)
            {
                perror("execvp");
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
        }
    }

    return 0;
}
